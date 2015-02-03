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

#include <assert.h>
#include <qthread.h>

#include "UserScriptJob.hpp"
#include "runmanager/lib/../../utilities/core/Logger.hpp"
#include "runmanager/lib/JobType.hpp"
#include "runmanager/lib/RubyJob.hpp"
#include "runmanager/lib/ToolInfo.hpp"

namespace openstudio {
namespace runmanager {
class Files;
struct JobState;
}  // namespace runmanager
}  // namespace openstudio

namespace openstudio {
namespace runmanager {
namespace detail {

  UserScriptJob::UserScriptJob(const UUID &t_uuid,
      const Tools &t_tools,
      const JobParams &t_params,
      const Files &t_files,
      const JobState &t_restoreData)
    : RubyJob(t_uuid, JobType::UserScript, t_tools, t_params, t_files, t_restoreData)
  {
    LOG(Trace, "UserScriptJob Created");
  }

  UserScriptJob::~UserScriptJob()
  { 
    assert(QThread::currentThread() != this);
    shutdownJob();
  }


} // detail
} // runmanager
} // openstudio



