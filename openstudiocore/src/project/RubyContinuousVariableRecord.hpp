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

#ifndef PROJECT_RUBYCONTINUOUSVARIABLERECORD_HPP
#define PROJECT_RUBYCONTINUOUSVARIABLERECORD_HPP

#include <boost/optional/optional.hpp>
#include <memory>
#include <vector>

#include "ContinuousVariableRecord.hpp"
#include "ProjectAPI.hpp"
#include "project/../utilities/core/LogMessage.hpp"
#include "project/../utilities/core/Logger.hpp"
#include "project/../utilities/time/../core/Enum.hpp"
#include "project/OSArgumentRecord.hpp"
#include "project/ProjectDatabase.hpp"
#include "project/RubyMeasureRecord.hpp"
#include "project/VariableRecord.hpp"

class QSqlQuery;
namespace openstudio {
namespace project {
class FunctionRecord;
class ProblemRecord;
}  // namespace project
}  // namespace openstudio

namespace openstudio {

namespace analysis {
class RubyContinuousVariable;
class Variable;
}

namespace project {

class OSArgumentRecord;
class RubyMeasureRecord;

namespace detail {

  class RubyContinuousVariableRecord_Impl;

} // detail

/** RubyContinuousVariableRecord is a ContinuousVariableRecord. */
class PROJECT_API RubyContinuousVariableRecord : public ContinuousVariableRecord {
 public:

  typedef detail::RubyContinuousVariableRecord_Impl ImplType;
  typedef VariableRecordColumns ColumnsType;
  typedef VariableRecord ObjectRecordType;

  /** @name Constructors and Destructors */
  //@{

  RubyContinuousVariableRecord(const analysis::RubyContinuousVariable& rubyContinuousVariable,
                               ProblemRecord& problemRecord,
                               int variableVectorIndex);

  RubyContinuousVariableRecord(const analysis::RubyContinuousVariable& rubyContinuousVariable,
                               FunctionRecord& functionRecord,
                               int variableVectorIndex,
                               boost::optional<double> functionCoefficient);

  RubyContinuousVariableRecord(const QSqlQuery& query, ProjectDatabase& database);

  /** Construct from impl. */
  RubyContinuousVariableRecord(std::shared_ptr<detail::RubyContinuousVariableRecord_Impl> impl,
                               ProjectDatabase database);

  virtual ~RubyContinuousVariableRecord() {}

  //@}

  static boost::optional<RubyContinuousVariableRecord> factoryFromQuery(const QSqlQuery& query,
                                                                        ProjectDatabase& database);

  static std::vector<RubyContinuousVariableRecord> getRubyContinuousVariableRecords(
      ProjectDatabase& database);

  static boost::optional<RubyContinuousVariableRecord> getRubyContinuousVariableRecord(
      int id,
      ProjectDatabase& database);

  /** @name Getters */
  //@{

  OSArgumentRecord osArgumentRecord() const;

  RubyMeasureRecord rubyMeasureRecord() const;

  analysis::RubyContinuousVariable rubyContinuousVariable() const;

  //@}
 protected:
  /// @cond
  explicit RubyContinuousVariableRecord(std::shared_ptr<detail::RubyContinuousVariableRecord_Impl> impl);

  friend class detail::RubyContinuousVariableRecord_Impl;
  friend class Record;
  friend class ProjectDatabase;
  /// @endcond
 private:
  REGISTER_LOGGER("openstudio.project.RubyContinuousVariableRecord");

  virtual void constructRelatedRecords(const analysis::Variable& variable);
};

/** \relates RubyContinuousVariableRecord*/
typedef boost::optional<RubyContinuousVariableRecord> OptionalRubyContinuousVariableRecord;

/** \relates RubyContinuousVariableRecord*/
typedef std::vector<RubyContinuousVariableRecord> RubyContinuousVariableRecordVector;

} // project
} // openstudio

#endif // PROJECT_RUBYCONTINUOUSVARIABLERECORD_HPP

