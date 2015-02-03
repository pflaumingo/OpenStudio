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

#ifndef RUNMANAGER_LIB_ADDTOOL_HPP
#define RUNMANAGER_LIB_ADDTOOL_HPP

#include <boost/optional.hpp>
#include <boost/optional/optional.hpp>
#include <qdialog.h>
#include <qnamespace.h>
#include <qobjectdefs.h>
#include <runmanager/lib/ui_AddTool.h>
#include <QTimer>
#include <string>
#include <utility>

#include "Job.hpp"
#include "RunManager.hpp"

class QWidget;


namespace openstudio {
namespace runmanager {

  //! QDialog based user interface for setting RunManager configuration options. 
  //! \sa http://doc.qt.nokia.com/qdialog.html
class ToolLocationInfo;
class ToolVersion;

  class AddTool : public QDialog
  {
    Q_OBJECT

  public:
    //! Create a AddTool dialog for setting ConfigOptions
    AddTool(QWidget *parent = nullptr, Qt::WindowFlags flags = nullptr);
    virtual ~AddTool();

    //! Returns the tool created during execution of the dialog
    boost::optional<std::pair<ToolVersion, ToolLocationInfo> > getTool();


  private:
    //! Used for QDesigner classes.
    Ui::AddToolDialog ui;

  private slots:
    void localBrowse();
  };


} // runmanager namespace
} // openstudio namespace


#endif // RUNMANAGER_LIB_ADDTOOL_HPP
