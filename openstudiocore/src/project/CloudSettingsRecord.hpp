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

#ifndef PROJECT_CLOUDSETTINGSRECORD_HPP
#define PROJECT_CLOUDSETTINGSRECORD_HPP

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

#include "ObjectRecord.hpp"
#include "ProjectAPI.hpp"
#include "project/../utilities/cloud/CloudProvider.hpp"
#include "project/../utilities/core/EnumBase.hpp"
#include "project/../utilities/core/LogMessage.hpp"
#include "project/../utilities/core/Logger.hpp"
#include "project/../utilities/core/Path.hpp"
#include "project/../utilities/time/../core/Enum.hpp"
#include "project/ProjectDatabase.hpp"
#include "project/Record.hpp"

class QSqlQuery;

namespace openstudio {

class CloudSettings;

namespace project {

namespace detail {

  class CloudSettingsRecord_Impl;

} // detail

/** \class CloudSettingsRecordType
 *  \brief ObjectRecord types that derive from CloudSettingsRecord.
 *  \details See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual
 *  macro call is:
 *  \code
OPENSTUDIO_ENUM(CloudSettingsRecordType,
    ((VagrantSettingsRecord))
    ((AWSSettingsRecord))
);
 *  \endcode */
OPENSTUDIO_ENUM(CloudSettingsRecordType,
    ((VagrantSettingsRecord))
    ((AWSSettingsRecord))
);

/** \class CloudSettingsRecordColumns
 *  \brief Column definitions for the CloudSettingsRecords table.
 *
 *  \relates CloudSettingsRecord */
OPENSTUDIO_ENUM(CloudSettingsRecordColumns,
  ((id)(INTEGER PRIMARY KEY)(0))
  ((handle)(TEXT)(1))
  ((name)(TEXT)(2))
  ((displayName)(TEXT)(3))
  ((description)(TEXT)(4))
  ((timestampCreate)(TEXT)(5))
  ((timestampLast)(TEXT)(6))
  ((uuidLast)(TEXT)(7))
  ((cloudSettingsRecordType)(INTEGER)(8))
  ((userAgreementSigned)(BOOLEAN)(9))
  ((serverPath)(TEXT)(10))
  ((serverUrlRecordId)(INTEGER)(11))
  ((workerPath)(TEXT)(12))
  ((workerUrlRecordId)(INTEGER)(13))
  ((haltOnStop)(BOOLEAN)(14))
  ((username)(TEXT)(15))
  ((numWorkers)(INTEGER)(16))
  ((terminationDelayEnabled)(BOOLEAN)(17))
  ((terminationDelay)(INTEGER)(18))
  ((region)(TEXT)(19))
  ((serverInstanceType)(TEXT)(20))
  ((workerInstanceType)(TEXT)(21))
);

/** CloudSettingsRecord is a ObjectRecord. */
class PROJECT_API CloudSettingsRecord : public ObjectRecord {
 public:

  typedef detail::CloudSettingsRecord_Impl ImplType;
  typedef CloudSettingsRecordColumns ColumnsType;
  typedef CloudSettingsRecord ObjectRecordType;

  /** @name Constructors and Destructors */
  //@{

  virtual ~CloudSettingsRecord() {}

  //@}

  static std::string databaseTableName();

  static UpdateByIdQueryData updateByIdQueryData();

  static void updatePathData(ProjectDatabase database,
                             const openstudio::path& originalBase,
                             const openstudio::path& newBase);

  /** Get CloudSettingsRecord from query. Returned object will be of the correct
   *  derived type. */
  static boost::optional<CloudSettingsRecord> factoryFromQuery(const QSqlQuery& query, ProjectDatabase& database);

  static CloudSettingsRecord factoryFromCloudSettings(const CloudSettings& cloudSettings, ProjectDatabase& database);

  static std::vector<CloudSettingsRecord> getCloudSettingsRecords(ProjectDatabase& database);

  static boost::optional<CloudSettingsRecord> getCloudSettingsRecord(int id, ProjectDatabase& database);

  /** @name Getters */
  //@{

  CloudSettings cloudSettings() const;

  //@}
 protected:
  /// @cond
  explicit CloudSettingsRecord(std::shared_ptr<detail::CloudSettingsRecord_Impl> impl);

  friend class detail::CloudSettingsRecord_Impl;
  friend class Record;
  friend class ProjectDatabase;

  /** Construct from impl. */
  CloudSettingsRecord(std::shared_ptr<detail::CloudSettingsRecord_Impl> impl,
                      ProjectDatabase database);

  /// @endcond
 private:
  REGISTER_LOGGER("openstudio.project.CloudSettingsRecord");
};

/** \relates CloudSettingsRecord*/
typedef boost::optional<CloudSettingsRecord> OptionalCloudSettingsRecord;

/** \relates CloudSettingsRecord*/
typedef std::vector<CloudSettingsRecord> CloudSettingsRecordVector;

} // project
} // openstudio

#endif // PROJECT_CLOUDSETTINGSRECORD_HPP

