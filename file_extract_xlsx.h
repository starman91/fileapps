//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		    		file_extract_xlsx.h
//
//  Class to open an Excel .xlsx file. Explodes thwe zipped file into a temp directory
//  returns data form desired worksheet as Dom Document
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


#ifndef FILE_EXTRACT_XLSX_H
#define FILE_EXTRACT_XLSX_H

#include "fileApps_base.h"
#include <XML_API>
#include <QtCore/QMutex>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Class that can open and extract data from a MS Excel .xlsx file. Inherits the FileApps_Base class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FileExtractXLSX : public FileApps_Base
{
	public:
		FileExtractXLSX();
		~FileExtractXLSX();

		bool accessXLSXFile (const QString, const QString, QDomDocument&);

	private:
		bool unzipFile (const QString&);
		bool getWorksheet (const QString&);

	private:
        QString excelFilename;
        QDomDocument m_workingDoc;

};

#endif  // FILE_EXTRACT_XLSX_H

