//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		    		file_log.h
//  
// Class to create and append operational data as a log file to monitpor software
// operations.
//              -------------------
// author 		: Robert R. White
// date			: Wed Jan 23 2008
// copyright	: (C) 2008 by  NREL
// email			: robert.white@nrel.gov
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 	  Copyright	(C):  2008 by Robert R. White and  NREL
//    This file is part of the Fileapps library.
//
//    Fileapps library is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    Fileapps library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//    along with Fileapps library.  If not, see <http://www.gnu.org/licenses/>.
//
//	 We also ask that you maintain this copyright block and that any publications
//   surrounding, attributed to, or linked to this file or entire software system are also 
//   credited to the author and institution of this copyright
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef FILE_LOG_H
#define FILE_LOG_H

#include "fileApps_base.h"
#include <QtCore/QMutex>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Class for creation and appending of log files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class File_Log : public FileApps_Base
{
	public:
		File_Log();
		~File_Log();

        bool Init (const QString);
        bool append (const QString, const bool withDateTime = true);

        inline void setLogFileName(const QString text)  {   logFileName = text; };
        inline QString getLogFileName(void) const  {return logFileName;    };

	private:
        static QString logFileName;
        QString dateTimeFormat;
        QMutex mutex;
};

#endif

