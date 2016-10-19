///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		    		fileapps_base.cpp
//
//	Class to provide general access to a stored file. Includes basic capabilites to
// open as read only, write only or both. Also provides error response from file
// system. Extends capability of the Qt library for file handling.
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


#include "fileApps_base.h"
#include <iostream>


FileApps_Base::FileApps_Base()
{
	return;	
}

FileApps_Base::~FileApps_Base()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Performs initial file creation
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FileApps_Base::initFile (const QString filename)
{
    QFile tmpFile;
    
    tmpFile.setFileName(filename);
    if (!tmpFile.exists())
    {
        if (accessFile(WT, filename))
        {
            targetFile.close();
            return true;
        }   
        else
	      return false;
	}
	else
	{
	   std::cout << "--> " << filename.toLatin1().constData() <<  " already exists. Not creating a new one\n";
	   return true;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Opens the file for either reading, writing or appending.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FileApps_Base::accessFile(const access_types process, const QString filename)
{
	targetFile.setFileName(filename);
	
	// Open file for particular transaction type
    switch (process)
	{
 		case RD:
    		if (targetFile.exists())
   			{
 				if (!targetFile.open(QIODevice::ReadOnly))
				{	
					std::cerr << "ERROR: opening file, " << filename.toLatin1().constData() << " to read\n";
					std::cerr << "Error detail: " << errorString(targetFile.error() ).toLatin1().constData() << "\n";
					return false;	
				}
 			}
  			else
  			{
    			std::cerr << "ERROR: The file, " << targetFile.fileName().toLatin1().constData() << " does not exist\n";
    			return false;
  			}
			break;

		case WT:		//Will create file if it does not exist
			if (!targetFile.open(QIODevice::WriteOnly))
			{	
				std::cerr << "Error creating file, " << filename.toLatin1().constData() << " to write\n";
				std::cerr << "Error detail: " << errorString(targetFile.error() ).toLatin1().constData() << "\n";
				return false;	
			}
			break;

		case AP:
    		if (targetFile.exists())
   			{
 				if (!targetFile.open(QIODevice::Append))
				{	
					std::cerr << "Error opening file, " << filename.toLatin1().constData() << " to append\n";
					std::cerr << "Error detail: " << errorString(targetFile.error() ).toLatin1().constData() << "\n";
					return false;	
				}
 			}
  			else
  			{
    			std::cerr << "ERROR: The file, " << targetFile.fileName().toLatin1().constData() << " does not exist\n";
    			return false;
  			}
			break;
		
		default:
			return false;
			break;
	}
	return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Opens the file for either reading, writing or appending.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QString FileApps_Base::errorString(const int errorValue)
{
	QString message;
	switch (errorValue)
	{
		case (QFile::NoError):
			message = "No error occurred.";
			break;

		case (QFile::ReadError):
			message = "An error occurred when reading from the file";
			break;

		case (QFile::WriteError):
			message = "An error occurred when writing to the file.";
			break;

		case (QFile::FatalError):
			message = "A fatal error occurred.";
			break;

		case (QFile::ResourceError):
			message = "Resources could not be allocated or were busy";
			break;

		case (QFile::OpenError):
			message = "The file could not be opened.";
			break;

		case (QFile::AbortError):
			message = "The operation was aborted.";
			break;

		case (QFile::TimeOutError):
			message = "A timeout occurred.";
			break;

		case (QFile::UnspecifiedError):
			message = "An unspecified error occurred.";
			break;

		case (QFile::RemoveError):
			message = "The file could not be removed.";
			break;

		case (QFile::RenameError):
			message = "The file could not be renamed.";
			break;

		case (QFile::PositionError):
			message = "The position in the file could not be changed.";
			break;

		case (QFile::ResizeError):
			message = "The file could not be resized.";
			break;

		case (QFile::PermissionsError):
			message = "The file could not be accessed.";
			break;

		case (QFile::CopyError):
			message = "The file could not be copied.";
			break;
	
		default:
			message = "Unknown file error";
			break;
	}
	return message;
}
