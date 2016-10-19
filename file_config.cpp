////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		    		file_config .cpp
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

#include "file_config.h"
#include <iostream>

File_Config::File_Config()
{
    return;
}

File_Config::~File_Config()
{
    return;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Opens the config file passed into function. Sets target file within class
/// to be used for harvesting variable values.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool File_Config::accessConfigFile (const QString config_filename)
{
    //Call access function to open fiel for reading
    if (!accessFile(RD, config_filename))
    {
        std::cerr << "ERROR: Unable to access configuration file, " << config_filename.toLatin1().constData() << "\n";
        return false;
    }
   
   // Store file data as stream
	QTextStream fileData(&targetFile);
	// Read data from file into string
	m_configFileData = fileData.readAll();
    
    return true;
}
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Checks for parameter existing. Returns true if it is in file.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool File_Config::parameterExists (const QString variableName)
{
    //Validate that there is data to be had
	if (!m_configFileData.isEmpty() ) 
	{
		// break into lines using "\n" as deliminator
		QStringList fileLines = m_configFileData.split( "\n");	

	 	// First find the line containing desired string.
		QStringList tempLineList = fileLines.filter (variableName);	
		//Be sure file had a variable of that name
		if (tempLineList.isEmpty())
		{
		   return false;
		}
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Retrieves varaibles from config file as passed in and returns those values
/// by reference as a string. Has no knowledge of type  that the variable is,
/// That must be decoded by calling function.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool File_Config::getConfigValue (const QString variableName, QString& retVal)
{
	QString deliminatorSingle = " ";
	int position = -1;
   
    //Validate that there is data to be had
	if ((m_configFileData.isNull())|(m_configFileData.isEmpty()))
	{
		std::cerr<<"ERROR: No valid data in configuration file.\n";
		return false;
	}

	// break into lines using "\n" as deliminator
	QStringList fileLines = m_configFileData.split( "\n");

 	// First find the line containing desired string.
	QStringList tempLineList = fileLines.filter (variableName);	
	//Be sure file had a variable of that name
	if (tempLineList.isEmpty())
	{
	   std::cerr << "ERROR: No value with variable name, " << variableName.toLatin1().constData() << " in configuration file.\n";
	   return false;
	}
	
	// Create a single string from the line.
	QString tempLine = tempLineList.join("");
	
	// Be sure it is not an empty string
	if (tempLine.isEmpty())
	{
	   std::cerr << "ERROR: No value with variable in file, " " in configuration file.\n";
	   return false;
	}
	
	// grab the last word in the string, using the deliminator as the separation.
	QString simplifiedString = tempLine.simplified();
	
	//Check for quotes enslosing special chars including spaces
	if (simplifiedString.contains("\"") )
	{
		QStringList linePieces = simplifiedString.split(deliminatorSingle);
		//Assemble pieces to get whole section
		//Add last piece first
		for (int i=linePieces.size()-1; 1<=i; i--)
		{
			if (i==linePieces.size()-1)
			{	
				retVal.prepend(linePieces[i]);
			}
			else
			{
				retVal.prepend(linePieces[i] + " ");
				if (linePieces[i].contains("\"") )
				{
					//found last one...now exit
					break;
				}
			}
		}
		//Remove " markers
		retVal.remove("\"");
	}
	else
	{	
		retVal = simplifiedString.section(deliminatorSingle, position);
	}
	#ifdef DEBUG
//		std::cout << "Value found = " << retVal.toAscii().constData() << "\n";		
	#endif
    return true;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///	Finds and returns a list of values from a series of same named records
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool File_Config::getConfigValueList (const QString variableName, QStringList& retList)
{
	QString deliminatorSingle = " ";
	int position = -1;
  
    //Validate that there is data to be had
	if ((m_configFileData.isNull())|(m_configFileData.isEmpty()))
	{
		std::cerr<<"ERROR: No valid data in configuration file.\n";
		return false;
	}

	// break into lines using "\n" as deliminator
	QStringList fileLines = m_configFileData.split( "\n");

 	// First find the line containing desired string.
	QStringList tempLineList = fileLines.filter (variableName);	
	//Be sure file had a variable of that name
	if (tempLineList.isEmpty())
	{
	   std::cerr << "ERROR: No value with variable name, " << variableName.toLatin1().constData() << " in configuration file.\n";
	   return false;
	}

	retList.clear();
	for (int i=0; i< tempLineList.size(); i++)
	{
		QString tempLine = tempLineList[i];
		QString value = tempLine.simplified().section(deliminatorSingle, position);
		retList << value;	
	}
	return true;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///	Finds and returns a list of lines. Usually used to gather lines with many fields
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool File_Config::getConfigFileLines (const QString variableName, QStringList& retList)
{
	QString deliminatorSingle = " ";
  //Validate that there is data to be had
	if ((m_configFileData.isNull())|(m_configFileData.isEmpty()))
	{
		std::cerr<<"ERROR: No valid data in configuration file.\n";
		return false;
	}

	// break into lines using "\n" as deliminator
	QStringList fileLines = m_configFileData.split( "\n");

 	// First find the line containing desired string.
	retList = fileLines.filter (variableName);	
	//Be sure file had a variable of that name
	if (retList.isEmpty())
	{
	   std::cerr << "ERROR: No value with variable name, " << variableName.toLatin1().constData() << " in configuration file.\n";
	   return false;
	}
	return true;
}

