////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		    		file_log .cpp
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


#include "file_log.h"
#include <iostream>
#include <QtCore/QDateTime>
#include <QtCore/QMutexLocker>

QString File_Log::logFileName;

File_Log::File_Log()
{
    dateTimeFormat = "yyyy MM dd  hh:mm:ss.zzz";
    return;
}

File_Log::~File_Log()
{
    return;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool File_Log::Init (const QString log_filename)
{
    QMutexLocker locker(&mutex);  //locks function asset access unitl exited (only one writes to file at a time)

    if (initFile(log_filename))
    {
        std::cout << "--> " << log_filename.toLatin1().constData() << " initated\n";
        setLogFileName(log_filename);
     }
    else
    {
        std::cerr << "ERROR: creating log file\n";
        targetFile.close();
        return true;
    }
    targetFile.close();
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool File_Log::append (const QString logText, const bool withDateTime)
{
    QMutexLocker locker(&mutex); //locks function asset access unitl exited (only one writes to file at a time)
    QString outString = logText;

    //Open file for appending and set target file equal to the log file
    if (!accessFile(AP, getLogFileName()))
    {
        std::cerr << "ERROR: Trying to append to log file: " << getLogFileName().toLatin1().constData() << "\n";
        targetFile.close();
         return false;
    }

    if (withDateTime)
    {
		//Get current time
		QDateTime time = QDateTime::currentDateTime();
        outString.prepend( time.toString(dateTimeFormat) + "   ");
    }
    outString.append ("\n");

   	#ifdef DEBUG
//   		std::cout << "filename 1 = " << targetFile.fileName().toLatin1().constData() << "\n";
   	#endif
   	QTextStream outStream(&targetFile);
	outStream << outString;
    targetFile.close();
    return true;
}


