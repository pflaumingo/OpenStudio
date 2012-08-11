/***************************************************************************
 *   Copyright (C) 2005 by Phylroy Lopez                                   *
 *   plopez@bert                                                           *
 *           
 *                                                                 *
 ***************************************************************************/
#ifndef REGEXPH
#define REGEXPH

//OpenSutdio definition for paths. 
#include <utilities/core/Path.hpp>


#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp> 
#include <boost/tokenizer.hpp>
#include <boost/filesystem/fstream.hpp>
#include <iostream>
#include <stdlib.h> 
#include <string>
#include <vector> 
/**
 * This function will find all the files in a current folder that matches a 
 * regular expression string. 
 * @param dir_path folder to search
 * @param file_name regular expression to search for. 
 * @return std::vector<boost::filesystem::path> a vector containing all the 
 * matched paths. 
 */
std::vector<boost::filesystem::path>
find_files( const openstudio::path& dir_path,     // in this directory,
            const std::string & file_name);// search for this name.





/**
 * This function will remove the directory of path specifed.  This is a wrapper 
 * to the boost library function. 
 * @param dir_path The path to the directory to be removed. 
 */
void remove_folder(const openstudio::path& dir_path);


/**
 * This function will read a file into a string. 
 * @param sFile 
 * @return The contents of the file to a string. 
 */


std::string read_file_into_string(const openstudio::path& sFile);


/**
 * This function will read through a vector of strings and find the value 
 * matching the token name provided and return it as a double. 
 * @param TokenList The vector of strings containing the token list.  
 * @param sToken The token name to search for. 
 * @return the token pair value as a double. 
 */
double GetTokenValueToDouble(std::vector<std::string> TokenList,
                             std::string sToken);
/**
 * This will take a file a place each line as a string in a vector. 
 * @param sFile The file to be read in. 
 * @return The file as a vector of strings
 */
std::vector<std::string> read_file_into_vector( const openstudio::path& sFile);
std::vector<std::string> read_file_into_vector_strip_comments(const openstudio::path& sFile);

/**
 * This function will read through a vector of strings and find the value 
 * matching the token name provided and return it as a double. 
 * @param TokenList The vector of strings containing the token list.  
 * @param sToken The token name to search for. 
 * @return the token pair value as a string. 
 */
std::string GetTokenValueToString(std::vector<std::string> TokenList,
                                  std::string sToken);




/**
 * This function will separate a csv string into a vector of strings.
 * @param sCSVLine 
 * @return A vector of strings. 
 */
std::vector<std::string> CSVTokenizer(std::string sCSVLine);
/**
 * This function will separate a string into a vector of strings.
 * @param sString A string of values.
 * @param sSeparator The separator charecter 
 * @return A vector of strings. 
 */
std::vector<std::string> Tokenizer(std::string sString, std::string sSeparator);

/**
 * This function will remove trailing and leading whitespace from a std:string.
 * @param s A trimmed string. 
 */
void Trim(std::string& s);
/**
 * This function will read a CSV formatted file into a vector of vectors of 
 * strings representing the Columns in the CSV file.
 * @param sCSVFile 
 * @return A vector of vectors of strings representing the columns in a file. 
 */
std::vector< std::vector<std::string> > CSVToVectorOfColumns(const openstudio::path& sCSVFile);
/**
 * This function will read a CSV formatted file into a vector of vectors of 
 * strings representing the rows in the CSV file.
 * @param sCSVFile 
 * @return A vector of vectors of strings representing the rows in a file. 
 */
std::vector< std::vector<std::string> > CSVToVectorOfRows(const openstudio::path& sCSVFile);


std::string GetLeaf(const openstudio::path& sFilePath);
std::string GetParentFolder(const openstudio::path& sFilePath, int iNumberUp=1);

std::vector<double> ToDouble( std::vector<std::string> );

std::vector<double> SplitToDouble(std::string line, std::string splitter);

bool FileExists(const openstudio::path& sPath);

#endif
