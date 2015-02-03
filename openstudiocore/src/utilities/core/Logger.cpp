/**********************************************************************
*  Copyright (c) 2008-2015, Alliance for Sustainable Energy.
*  All rights reserved.
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

#include <boost/log/attributes/function.hpp>
#include <boost/log/core/core.hpp>
#include <boost/log/core/record.hpp>
#include <boost/log/detail/attachable_sstream_buf.hpp>
#include <boost/log/keywords/channel.hpp>
#include <boost/log/keywords/severity.hpp>
#include <boost/log/sinks/sink.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/utility/formatting_ostream.hpp>
#include <boost/parameter/aux_/tagged_argument.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/smart_ptr/intrusive_ref_counter.hpp>
#include <boost/utility/empty_deleter.hpp>
#include <boost/utility/explicit_operator_bool.hpp>
#include <qlogging.h>
#include <qreadwritelock.h>
#include <qthread.h>
#include <iostream>
#include <sstream>
#include <utility>

#include "Logger.hpp"
#include "utilities/core/LogSink.hpp"
#include "utilities/core/Singleton.hpp"

namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

namespace openstudio{

  // handle Qt messages
  void logQtMessage(QtMsgType type, const char *msg)
  {
    switch (type) {
      case QtDebugMsg:
        logFree(Debug, "Qt", msg);
        break;
      case QtWarningMsg:
        logFree(Warn, "Qt", msg);
        break;
      case QtCriticalMsg:
        logFree(Error, "Qt", msg);
        break;
      case QtFatalMsg:
        logFree(Fatal, "Qt", msg);
        break;
    }
  }

  // handle Qt messages after logger is destroyed
  void consoleLogQtMessage(QtMsgType type, const char *msg)
  {
    std::cout << "[Qt] <" << type << "> " << msg << std::endl;
  }

  /// convenience function for SWIG, prefer macros in C++
  void logFree(LogLevel level, const std::string& channel, const std::string& message)
  {
    BOOST_LOG_SEV(openstudio::Logger::instance().loggerFromChannel(channel), level) << message;
  }

  LoggerSingleton::LoggerSingleton()
    : m_mutex(new QReadWriteLock())
  {
    // Make QThread attribute available to logging
    boost::log::core::get()->add_global_attribute("QThread", boost::log::attributes::make_function(&QThread::currentThread));

    // We have to provide an empty deleter to avoid destroying the global stream
    boost::shared_ptr<std::ostream> stdOut(&std::cout, boost::empty_deleter());
    m_standardOutLogger.setStream(stdOut);
    m_standardOutLogger.setLogLevel(Warn);
    this->addSink(m_standardOutLogger.sink());

    // We have to provide an empty deleter to avoid destroying the global stream
    boost::shared_ptr<std::ostream> stdErr(&std::cerr, boost::empty_deleter());
    m_standardErrLogger.setStream(stdErr);
    m_standardErrLogger.setLogLevel(Warn);
    //this->addSink(m_standardErrLogger.sink());

    // register Qt message handler
    //qInstallMsgHandler(logQtMessage);
  }

  LoggerSingleton::~LoggerSingleton()
  {
    // unregister Qt message handler
    //qInstallMsgHandler(consoleLogQtMessage);

    delete m_mutex;
  }

  LogSink LoggerSingleton::standardOutLogger() const
  {
    QReadLocker l(m_mutex);

    return m_standardOutLogger;
  }

  LogSink LoggerSingleton::standardErrLogger() const
  {
    QReadLocker l(m_mutex);

    return m_standardErrLogger;
  }

  LoggerType& LoggerSingleton::loggerFromChannel(const LogChannel& logChannel)
  {
    QReadLocker l(m_mutex);

    auto it = m_loggerMap.find(logChannel);
    if (it == m_loggerMap.end()){
      //LoggerType newLogger(keywords::channel = logChannel, keywords::severity = Debug);
      LoggerType newLogger(keywords::channel = logChannel);

      std::pair<LogChannel, LoggerType> newPair(logChannel,newLogger);

      // Drop the read lock and grab a write lock - we need to add the new file to the map
      // this will reduce contention when multiple threads trying to log at once.
      l.unlock();
      QWriteLocker l2(m_mutex);

      std::pair<LoggerMapType::iterator, bool> inserted = m_loggerMap.insert(newPair);

      return inserted.first->second;

    }

    return it->second;
  }

  bool LoggerSingleton::findSink(boost::shared_ptr<LogSinkBackend> sink)
  {
    QWriteLocker l(m_mutex);

    auto it = m_sinks.find(sink);

    return (it != m_sinks.end());
  }

  void LoggerSingleton::addSink(boost::shared_ptr<LogSinkBackend> sink)
  {
    QWriteLocker l(m_mutex);

    auto it = m_sinks.find(sink);
    if (it == m_sinks.end()){

      // Drop the read lock and grab a write lock - we need to add the new file to the map
      // this will reduce contention when multiple threads trying to log at once.
      l.unlock();
      QWriteLocker l2(m_mutex);

      m_sinks.insert(sink);

      // Register the sink in the logging core
      boost::log::core::get()->add_sink(sink);
    }
  }

  void LoggerSingleton::removeSink(boost::shared_ptr<LogSinkBackend> sink)
  {
    QWriteLocker l(m_mutex);

    auto it = m_sinks.find(sink);
    if (it != m_sinks.end()){

      // Drop the read lock and grab a write lock - we need to add the new file to the map
      // this will reduce contention when multiple threads trying to log at once.
      l.unlock();
      QWriteLocker l2(m_mutex);

      m_sinks.erase(it);

      // Register the sink in the logging core
      boost::log::core::get()->remove_sink(sink);
    }
  }

} // openstudio
