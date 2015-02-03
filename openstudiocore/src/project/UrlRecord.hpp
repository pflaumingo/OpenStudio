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

#ifndef PROJECT_URLRECORD_HPP
#define PROJECT_URLRECORD_HPP

#include <boost/optional/optional.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/comparison/not_equal.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/detail/auto_rec.hpp>
#include <boost/preprocessor/logical/bool.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/repetition/detail/for.hpp>
#include <boost/preprocessor/repetition/for.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "../utilities/core/Url.hpp"
#include "ObjectRecord.hpp"
#include "ProjectAPI.hpp"
#include "project/../utilities/core/LogMessage.hpp"
#include "project/../utilities/core/Logger.hpp"
#include "project/../utilities/core/Path.hpp"
#include "project/../utilities/time/../core/Enum.hpp"
#include "project/ProjectDatabase.hpp"
#include "project/Record.hpp"

class QSqlQuery;

namespace openstudio {
namespace project {

namespace detail {

  class UrlRecord_Impl;

} // detail

/** \class UrlRecordColumns
 *  \brief Column definitions for the UrlRecords table.
 *  
 *  \relates UrlRecord */
OPENSTUDIO_ENUM(UrlRecordColumns,
  ((id)(INTEGER PRIMARY KEY)(0))
  ((handle)(TEXT)(1))
  ((name)(TEXT)(2))
  ((displayName)(TEXT)(3))
  ((description)(TEXT)(4))
  ((timestampCreate)(TEXT)(5))
  ((timestampLast)(TEXT)(6))
  ((uuidLast)(TEXT)(7))
  ((parentDatabaseTableName)(TEXT)(8))
  ((parentRecordId)(INTEGER)(9))
  ((url)(TEXT)(10))
);

/** UrlRecord is a ObjectRecord. */
class PROJECT_API UrlRecord : public ObjectRecord {
 public:

  typedef detail::UrlRecord_Impl ImplType;
  typedef UrlRecordColumns ColumnsType;
  typedef UrlRecord ObjectRecordType;

  /** @name Constructors and Destructors */
  //@{

  UrlRecord(const openstudio::Url& url, ObjectRecord& parentRecord);

  UrlRecord(const QSqlQuery& query, ProjectDatabase& database);

  virtual ~UrlRecord() {}

  //@}

  static std::string databaseTableName();

  static UpdateByIdQueryData updateByIdQueryData();

  static void updatePathData(ProjectDatabase database,
                             const openstudio::path& originalBase,
                             const openstudio::path& newBase);

  /** Get UrlRecord from query. Returned object will be of the correct derived type. */
  static boost::optional<UrlRecord> factoryFromQuery(const QSqlQuery& query, ProjectDatabase& database);

  static std::vector<UrlRecord> getUrlRecords(ProjectDatabase& database);

  static boost::optional<UrlRecord> getUrlRecord(int id, ProjectDatabase& database);

  /** @name Getters */
  //@{

  openstudio::Url url() const;

  //@}
 protected:
  /// @cond
  explicit UrlRecord(std::shared_ptr<detail::UrlRecord_Impl> impl);

  friend class detail::UrlRecord_Impl;
  friend class Record;
  friend class ProjectDatabase;

  /** Construct from impl. */
  UrlRecord(std::shared_ptr<detail::UrlRecord_Impl> impl,
            ProjectDatabase database);

  /// @endcond
 private:
  REGISTER_LOGGER("openstudio.project.UrlRecord");
};

/** \relates UrlRecord*/
typedef boost::optional<UrlRecord> OptionalUrlRecord;

/** \relates UrlRecord*/
typedef std::vector<UrlRecord> UrlRecordVector;

} // project
} // openstudio

#endif // PROJECT_URLRECORD_HPP

