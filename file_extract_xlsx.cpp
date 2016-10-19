///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		    		file_extract_xlsx.cpp
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


#include <iostream>
#include "errno.h"

#include "file_extract_xlsx.h"



FileExtractXLSX::FileExtractXLSX()
{
	return;
}

FileExtractXLSX::~FileExtractXLSX()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base method for controlling access to a MS Excel .xlsx file (version 2007+) 
/// Returns xml data Dom Document passed in by reference
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FileExtractXLSX::accessXLSXFile (const QString filename, const QString worksheetName, QDomDocument& excelDoc)
{
    std::cout << "HERE";
    QDomDocument tempDoc;

    if (!unzipFile(filename) )
	{
		return false;
	}

	if (!getWorksheet (worksheetName) )
	{
		return false;
	}

	excelDoc = m_workingDoc;
	return true;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Method for opening up the .xlsx type file. Copies file into the /tmp directory
/// and performns a system call unzip on the file to open up the directories
/// encapsulating the data
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FileExtractXLSX::unzipFile (const QString& filename)
{
	int success = -1;
	QString copyProceedure = "sudo cp -p " ;
	QString destination = "/tmp";

	success = system((copyProceedure + filename + " " + destination).toLatin1().constData());
	if (success != 0)
	{	//Bad copy
		std::cerr << "ERROR: Transferring file " << filename.toLatin1().constData() << " to " << destination.toLatin1().constData() << ".  errno = " << errno << "\n";
        return false;
	}

	QString chmodProceedure = "sudo chmod 660 " ;
	QString newFile = destination + "/" + filename.section("/",-1);
	success = system((chmodProceedure +  newFile).toLatin1().constData());
	if (success != 0)
	{	//Bad copy
		std::cerr << "ERROR: Transferring file " << filename.toLatin1().constData() << " to " << destination.toLatin1().constData() << ".  errno = " << errno << "\n";
        return false;
	}

    //If xl subdir exists get rid of it before unzip
    QDir dir("/tmp/xl");
	if (dir.exists() )
	{
		QString rmdirProceedure = "sudo rm -Rf /tmp/xl" ;
		success = system( (rmdirProceedure).toLatin1().constData() );
		if (success != 0)
		{	//Bad unzip
			std::cerr << "ERROR: removing existing /tmp/xl directory. errno = " << errno << "\n";
			return false;
		}
	}

	QString unzipProceedure = "sudo unzip ";
	QString unzipDir = "/tmp/xl ";
	success = system( (unzipProceedure + newFile + " -d " + unzipDir).toLatin1().constData() );
	if (success != 0)
	{	//Bad unzip
		std::cerr << "ERROR: Unzipping file " << filename.toLatin1().constData() << " to " << destination.toLatin1().constData() << ".  errno = " << errno << "\n";
        return false;
	}
	return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FileExtractXLSX::getWorksheet (const QString& worksheetName)
{
	QFile file("/tmp/xl/xl/worksheets/" + worksheetName + ".xml");

	if (!file.open(QIODevice::ReadOnly))
	{
        std::cerr << "Unable to open Excel worksheet " << file.fileName().toLatin1().constData() << "\n";
		return false;
	}
	if (!m_workingDoc.setContent(&file))
	{
        std::cerr << "Unable to set Excel worksheet " << file.fileName().toLatin1().constData() << " contents into xml Dom Document\n";
		file.close();
		return false;
	}
	file.close();

	// Now remove unzipped dir
	QString rmdirProceedure = "sudo rm -Rf /tmp/xl" ;
	int success = system( (rmdirProceedure).toLatin1().constData() );
	if (success != 0)
	{	//Bad unzip
		std::cerr << "ERROR: removing existing /tmp/xl directory after extracting xml worksheet. errno = " << errno << "\n";
	}

	return true;
}











