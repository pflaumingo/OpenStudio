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

#ifndef PROJECT_INPUTVARIABLERECORD_HPP
#define PROJECT_INPUTVARIABLERECORD_HPP

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

#include "ProjectAPI.hpp"
#include "VariableRecord.hpp"
#include "project/../utilities/core/EnumBase.hpp"
#include "project/../utilities/core/LogMessage.hpp"
#include "project/../utilities/core/Logger.hpp"
#include "project/../utilities/time/../core/Enum.hpp"
#include "project/ProjectDatabase.hpp"

class QSqlQuery;
namespace openstudio {
namespace project {
class AttributeRecord;
class FunctionRecord;
class ProblemRecord;
}  // namespace project
}  // namespace openstudio

namespace openstudio {
namespace analysis {
  class InputVariable;
class UncertaintyDescription;
}

namespace project {

namespace detail {

  class InputVariableRecord_Impl;

} // detail

/** \class InputVariableRecordType
 *  \brief ObjectRecord types that derive from InputVariableRecord.
 *  \details See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual
 *  macro call is:
 *  \code
OPENSTUDIO_ENUM(InputVariableRecordType,
                ((DiscreteVariableRecord)(DiscreteVariableRecord)(0))
                ((ContinuousVariableRecord)(ContinuousVariableRecord)(1))
                );
 *  \endcode */
OPENSTUDIO_ENUM(InputVariableRecordType,
                ((DiscreteVariableRecord)(DiscreteVariableRecord)(0))
                ((ContinuousVariableRecord)(ContinuousVariableRecord)(1))
                );

/** InputVariableRecord is a VariableRecord. */
class PROJECT_API InputVariableRecord : public VariableRecord {
 public:
  typedef detail::InputVariableRecord_Impl ImplType;
  typedef VariableRecordColumns ColumnsType;
  typedef VariableRecord ObjectRecordType;

  /** @name Constructors and Destructors */
  //@{

  virtual ~InputVariableRecord() {}

  //@}

  /** Get InputVariableRecord from query. Returned object will be of the correct
   *  derived type. */
  static boost::optional<InputVariableRecord> factoryFromQuery(const QSqlQuery& query,
                                                               ProjectDatabase& database);

  /** Create an InputVariableRecord from inputVariable that belongs to the problem serialized to
   *  ProblemRecord. The index is the vector index of inputVariable's WorkflowStep in problem. */
  static InputVariableRecord factoryFromInputVariable(const analysis::InputVariable& inputVariable,
                                                      ProblemRecord& problemRecord,
                                                      int workflowIndex);

  /** Create an InputVariableRecord from inputVariable that belongs to the function serialized to
   *  functionRecord. The index is the vector index of inputVariable in function. */
  static InputVariableRecord factoryFromInputVariable(const analysis::InputVariable& inputVariable,
                                                      FunctionRecord& functionRecord,
                                                      int variableVectorIndex,
                                                      boost::optional<double> functionCoefficient);

  static std::vector<InputVariableRecord> getInputVariableRecords(ProjectDatabase& database);

  static boost::optional<InputVariableRecord> getInputVariableRecord(int id, ProjectDatabase& database);

  /** @name Getters */
  //@{

  /** Returns this InputVariableRecord's parent ProblemRecord. */
  boost::optional<ProblemRecord> problemRecord() const;

  /** Returns this InputVariableRecord's AttributeRecords, which are used to store
   *  uncertainty description information. */
  std::vector<AttributeRecord> attributeRecords() const;

  boost::optional<analysis::UncertaintyDescription> uncertaintyDescription() const;

  analysis::InputVariable inputVariable() const;

  //@}
 protected:
  /// @cond
  explicit InputVariableRecord(std::shared_ptr<detail::InputVariableRecord_Impl> impl);

  friend class detail::InputVariableRecord_Impl;
  friend class Record;
  friend class ProjectDatabase;

  /** Construct from impl. */
  InputVariableRecord(std::shared_ptr<detail::InputVariableRecord_Impl> impl,
                      ProjectDatabase database,
                      const boost::optional<analysis::InputVariable>& inputVariable);

  virtual void constructRelatedRecords(const analysis::InputVariable& inputVariable);

  /// @endcond
 private:
  REGISTER_LOGGER("openstudio.project.InputVariableRecord");
};

/** \relates InputVariableRecord*/
typedef boost::optional<InputVariableRecord> OptionalInputVariableRecord;

/** \relates InputVariableRecord*/
typedef std::vector<InputVariableRecord> InputVariableRecordVector;

} // project
} // openstudio

#endif // PROJECT_INPUTVARIABLERECORD_HPP

