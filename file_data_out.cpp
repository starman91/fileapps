////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		    		file_data_out .cpp
//
//  Class to write ascii data to a file. Includes ability to process and include headers
// and write records row by row to create a tidy data format
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

#include "file_data_out.h"
#include <iostream>
#include <QtCore/QDateTime>

QString File_Data_Out::outputFileName;

File_Data_Out::File_Data_Out()
{
    dateTimeFormat = "yyyy MM dd  hh:mm:ss.zzz";
    outputFileName = "";
    return;
}

File_Data_Out::~File_Data_Out()
{
    return;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool File_Data_Out::Init (const QString out_filename)
{
    if (initFile(out_filename))
    {
		QDateTime time = QDateTime::currentDateTime();
    
        std::cout << "Output file initated\n";
        outputFileName = out_filename;
//        record( time.toString(dateTimeFormat) + "   Output File Created\n");
    }
    else
    {
        std::cerr << "ERROR: creating output file\n";
        targetFile.close();
        return false;
    }
    targetFile.close();
    return true;
}
 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool File_Data_Out::header (const QString headerInfo)
{
    record(headerInfo);
    return true;
}


 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool File_Data_Out::record (const QString outputData)
{
    QString outString = outputData;
    	
   	//Open file for appending and set target file equal to the log file
    if (!accessFile(AP, outputFileName))
    {
        std::cerr << "ERROR: Trying to append record to output file: " << outputFileName.toLatin1().constData() << "\n";
        targetFile.close();
       return false;
    }
     
   	QTextStream outStream(&targetFile);
	outStream << outString;
    targetFile.close();
    return true;
}


