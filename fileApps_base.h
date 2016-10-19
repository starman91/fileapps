///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		    		fileapps_base.h
//
//	Class to provide general access to a stored file. Includes basic capabilites to
// open as read only, write only or both. Also provides error response from file
// system. Extends capability of the Qt library for file handling.
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

#ifndef FILEAPPS_BASE_H
#define FILEAPPS_BASE_H

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QFile>
#include <QtGui/QFileDialog>
#include <QtCore/QTextStream>

/// List of possible access types for opening a file
enum access_types {RD, WT, AP};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class to provide access to a file. Can initiate file, access exisitng file and provide access to error responses from file system
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FileApps_Base
{
	public:
		FileApps_Base();
		~FileApps_Base();

       	bool initFile (const QString);
		bool accessFile(const access_types , const QString);
		static QString errorString(const int);

 		QFile targetFile;

	private:
};

#endif
