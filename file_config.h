//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		    		file_config.h
//
//	Class to read in basic text files and to extract key pairs from file based on certain
// format criteria. Used to access text based config files.
//
//              -------------------
// author 		: Robert R. White
// date			: Wed Jan 23 2008
// copyright	: (C) 2008 by  NREL
// email			: rwhite@lanl.gov
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 	  Copyright	(C):  2008 by Robert R. White and  NREL
//    This file is part of Fileapps library.
//
//   Fileapps is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    Fileapps is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//    along with Fileapps.  If not, see <http://www.gnu.org/licenses/>.
//
//	 We also ask that you maintain this copyright block and that any publications
//   surrounding, attributed to, or linked to this file or entire software system are also 
//   credited to the author and institution of this copyright
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef FILE_CONFIG_H
#define FILE_CONFIG_H

#include "fileApps_base.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Class to open a text based configuration file. Provides mehods to target specific keypair values and create values or lists. Class
/// inherits the FileApps_Base
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class File_Config : public FileApps_Base
{
	public:                             
		File_Config();
		~File_Config();
		
        bool accessConfigFile (const QString);
        bool getConfigValue (const QString, QString&);
		bool getConfigValueList (const QString, QStringList&);
		inline QString getAllConfigFile (void) const {	return m_configFileData;	};
		bool getConfigFileLines	(const QString, QStringList&);
		bool parameterExists (const QString);
         
	private:
        QString m_configFileData;
};

#endif

