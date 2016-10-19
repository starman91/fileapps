//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		    		file_data_out.h
//
//  Class to write ascii data to a file. Includes ability to process and include headers
// and write records row by row to create a tidy data format
//
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


#ifndef FILE_DATA_OUT_H
#define FILE_DATA_OUT_H

#include "fileApps_base.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class to provide access to a file. Can initiate file, access exisitng file and provide access to error responses from file system.
/// Class inherits the FileApps_Base class to provide basic read, write and append functionality.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class File_Data_Out : public FileApps_Base
{
	public:                             
		File_Data_Out();
		~File_Data_Out();
		
        bool Init (const QString);
        bool header (const QString);
        bool record (const QString);
		
		inline void setOutputFilename(const QString text)		{ outputFileName = text; };
		inline QString getOutputFilename(void)								{ return outputFileName;	};
         
	private:
        static QString outputFileName;
        QString dateTimeFormat;
};

#endif

