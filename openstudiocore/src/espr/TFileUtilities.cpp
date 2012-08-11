/***************************************************************************
 *   Copyright (C) 2005 by Phylroy Lopez                                   *
 *   plopez@bert                                                           *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <iostream>
#include <fstream>
#include "regexp.h"
#include "TFileUtilities.h"


std::vector<boost::filesystem::path>
find_files( const boost::filesystem::path & dir_path,     // in this directory,
            const std::string & file_name) // search for this regular expression,

{
    //Assign the regular expression .
    boost::regex expression(file_name);

    //Create the vector of paths that will be returned.
    std::vector< boost::filesystem::path> found_files;

    //cmatch is the equivilant of perl $1. It contains the ordered matches. Only required in this case because the function
    //  reg_match requires it.
    boost::cmatch what;

    //Check to see if input folder exists. Otherwise return the empty vector.
    if ( !exists( dir_path ) ) return found_files;

    // default construction yields past-the-end
    boost::filesystem::directory_iterator end_itr;

    //Loop through all files and folders.
    for ( boost::filesystem::directory_iterator itr( dir_path );
            itr != end_itr;
            ++itr )
    {
        //if this is folder.
        if ( is_directory( *itr ) )
        {
            //Create a vector for the files in the subfolder.
            std::vector <boost::filesystem::path> subfiles;
            //Do a recursive call.
            subfiles  = find_files( *itr, file_name);
            // push the vector returned to the our parent vector.
            std::vector<boost::filesystem::path>::iterator counter;
            for ( counter=subfiles.begin();
                    counter != subfiles.end();
                    counter++)
            {
                found_files.push_back(*counter);
            }
        }
        //If a file and the file matches the regular expression.
        else if ( boost::regex_match(itr->leaf().c_str(), what, expression)  ) // see below
        {
            // Add to found files list.
            found_files.push_back(*itr);
        }
    }
    //return all found files.
    return found_files;;
}

void  remove_folder(const boost::filesystem::path & dir_path)
{
    //To-do there should be a throw catch here if unable to remove the directory.

    if (exists( dir_path ))
    {


        unsigned long ulNumberofFilesRemoved = 1;
        while( ulNumberofFilesRemoved > 0)
        {

            ulNumberofFilesRemoved = boost::filesystem::remove_all( dir_path );

        }


    }
}

std::string read_file_into_string(std::string sFile)
{
    std::ifstream in(sFile.c_str());
    std::string s, line;
    while(getline(in, line))
        s += line + "\n";
    return s;
}

std::vector<std::string> read_file_into_vector(const openstudio::path& sFile)
{
    std::vector<std::string> file;
    std::string line;
    file.clear();
	boost::filesystem::ifstream infile( sFile );
    while (getline(infile, line, '\n'))
    {
		 
        file.push_back (line);
    }
    return file;
}


std::vector<std::string> read_file_into_vector_strip_comments(const openstudio::path& sFile)
{
    std::vector<std::string> file;
    std::string line;
    file.clear();
	boost::filesystem::ifstream infile(sFile);
    while (getline(infile, line, '\n'))
    {
		//Remove empty lines and comments lines. 
		if (!IsRegexpMatch("^\\s*\\#.*$",line) && !IsRegexpMatch("^\\s*$",line) )
		{
        file.push_back (line);
		}
    }
    return file;
}

double GetTokenValueToDouble(std::vector<std::string> TokenList, std::string sToken)
{
    // Set up regular expression to search for.
    boost::regex expression("(^"+sToken+")(.*?)$");
    //Initialize return value
    double dReturnValue = 0.0;
    //Set up match variable
    boost::cmatch what;

    //Create iterator to walk the token list.
    std::vector<std::string>::iterator counter;
    for ( counter=TokenList.begin();
            counter != TokenList.end();
            counter++)
    {
        //If the search token is found, return the value.
        if (boost::regex_match(counter->c_str(), what, expression))
        {
            dReturnValue = std::strtod(what[2].first, NULL);
	     std::cout <<sToken <<"--"<< dReturnValue <<std::endl;


        }

    }
    return dReturnValue;
}


std::string GetTokenValueToString(std::vector<std::string> TokenList, std::string sToken)
{
    std::string sReturnValue = "";
    boost::regex expression("(^"+sToken+")(\\s*)(.*?)$");
    boost::cmatch what;
    std::vector<std::string>::iterator counter;
    for ( counter=TokenList.begin();
            counter != TokenList.end();
            counter++)
    {

        if (boost::regex_match(counter->c_str(), what, expression)){
            sReturnValue = what[3].first;
            std::cout <<sToken <<"--"<< sReturnValue <<std::endl;

        }
    }


    return sReturnValue;
}


std::vector<std::string> CSVTokenizer(std::string sCSVLine)

{
    std::vector<std::string> sReturnVector;
    boost::tokenizer<boost::escaped_list_separator<char> > tok(sCSVLine);
    for(boost::tokenizer<boost::escaped_list_separator<char> >::iterator beg=tok.begin();
            beg!=tok.end();
            ++beg)
    {
        std::string sTemp = *beg;
        //std::cout << sTemp << std::endl;
        sReturnVector.push_back(sTemp);
    }
    return sReturnVector;
}

std::vector<std::string> Tokenizer(std::string sString, std::string sSeparator)

{
    std::vector<std::string> sReturnVector;
    boost::char_separator<char> sep(sSeparator.c_str());
    boost::tokenizer<boost::char_separator<char> > tok(sString,sep);
    for(boost::tokenizer<boost::char_separator<char> >::iterator  beg=tok.begin();
            beg!=tok.end();
            ++beg)
    {
        std::string sTemp = *beg;
        //std::cout << sTemp << std::endl;
        sReturnVector.push_back(sTemp);
    }
    return sReturnVector;
}

void Trim(std::string& s)
{
    s.erase(0,s.find_first_not_of(" \n\r\t"));
    s.erase(s.find_last_not_of(" \n\r\t")+1);

}


std::vector< std::vector<std::string> > CSVToVectorOfColumns(const openstudio::path& sCSVFile)
{

    // Read in the values from the .csv file
    std::vector< std::string > vsCSVFile = read_file_into_vector(sCSVFile);
    //Create iterator for the rows in the csv file.
    std::vector<std::string>::iterator iterCSV = vsCSVFile.begin();

    //create results vector for this case.
    std::vector< std::vector <std::string> > vvsResults;

    while( iterCSV != vsCSVFile.end() )
    {


        //Get all fields into a string vector.
        std::vector<std::string> vsCSVFields =   CSVTokenizer(*iterCSV);
        // Is this the first line?
        if (iterCSV == vsCSVFile.begin())
        {
            // Create an iterator for the fields.
            std::vector< std::string>::iterator iterCSVField = vsCSVFields.begin();
            //Loop around fields in first row.
            for (  std::vector< std::string>::iterator iterCSVField = vsCSVFields.begin(); iterCSVField != vsCSVFields.end(); iterCSVField++ )
            {
                std::vector<std::string> sTemp;
                sTemp.push_back(*iterCSVField);
                vvsResults.push_back(sTemp);
                //				std::cout << *iterCSVField << vsCSVFields.size() <<std::endl;

            }
        }
        else
        {
            //create iterator for Results vector
            std::vector< std::vector< std::string > >::iterator iterResults = vvsResults.begin();
            int iFieldNumber = 0;
            while( iterResults != vvsResults.end()-1 )
            {
                iterResults->push_back( vsCSVFields[iFieldNumber] );
		//                std::cout << vsCSVFields[iFieldNumber] <<std::endl;
                iFieldNumber++;
                iterResults++;
            }
        }
	//        std::cout << "next line" << vvsResults.size() <<std::endl;
        iterCSV++;
    }
    return vvsResults;
}


std::vector< std::vector<std::string> > CSVToVectorOfRows(const openstudio::path& sCSVFile)
{

    std::vector< std::vector<std::string> > vvsReturn;
    //Read file into a vector of strings.
    std::vector<std::string> vsParameterTable = read_file_into_vector(sCSVFile);


    //Iterate through rows
    std::vector<std::string>::iterator iterRow;
    for (iterRow = vsParameterTable.begin(); iterRow != vsParameterTable.end(); iterRow++)
    {
        //tokenize the row into a vector.
        std::vector<std::string> vsCSVFields =   CSVTokenizer(*iterRow);

        //otherwise place the rows into a vector.

        vvsReturn.push_back(vsCSVFields);
    }
    return vvsReturn;
}








std::string GetLeaf(std::string sFilePath)
{
    boost::filesystem::path Path(sFilePath);
    return Path.leaf();
}



std::string GetParentFolder(std::string sFilePath, int iNumberUp)
{
    boost::filesystem::path Path(sFilePath);
    int iCounter = iNumberUp;
    while(iCounter > 0 )
    {
        Path = Path.branch_path();
        iCounter--;
    }
    return Path.string();
}

std::vector<double> ToDouble( std::vector<std::string> vsDoubleList  )
{
    std::vector<double> vdReturn;
    std::vector<std::string>::iterator counter;
    BOOST_FOREACH(std::string stringvalue , vsDoubleList)
    {
        vdReturn.push_back( boost::lexical_cast<double>(stringvalue) );
    }
    return vdReturn;
}


bool FileExists(const openstudio::path& sPath)
{
	 return boost::filesystem::exists( sPath);
	 std::cerr << sPath.string().c_str() << " does no exist!!!!" << std::endl;
};
	
	
std::vector<double> SplitToDouble(std::string line, std::string splitter)
{
		boost::algorithm::trim( line );
        std::vector<std::string> temp;
		boost::split(temp,line,boost::is_any_of(splitter));
        return ToDouble( temp  );

}