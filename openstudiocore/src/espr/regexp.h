/***************************************************************************
 *   Copyright (C) 2005 by Phylroy Lopez                                   *
 *   plopez@bert                                                           *
 *                                                                         *
 *                                                                         *
 ***************************************************************************/
#ifndef TREGEXPH
#define TREGEXPH

#include <string>
#include <iterator>
#include <map>
#include <vector>
#include <utility>

/**
 * This class allows you to perform a search and replace using regular 
 * expressions. This regular expression uses the boost implmentation. 
 * This requires the boost library libboost_regex to to linked to the project. 
 */

class TSearchAndReplace
{
private:
    /**
     *  This is the container that holds the search string (the key)and the 
     * replace string (the value). This is private and should only be 
     * manipulated by the AddSearchAndReplaceMap method.
     */
    std::map<std::string,std::string> SearchAndReplaceMap;

    /**
     * This is  the iterator for the conatainer. THis is required to iterate 
     * through each map entity. See the STL iterators for information on 
     * iterators. 
     */ 
    std::map<std::string,std::string>::iterator iter;
    /**
     * This methods simply loads a file into a std::string.
     */
    void load_file(std::string& s, std::istream& is);

public:

    /**
     * Use this method to add a search and replace map set. The the key 
     * variable contains the search regular expression.
     *
     * @param key This is the string that is to be replaced. Perl regular 
     * expressions are valid. Special Charecters must be escaped TWICE. Example 
     * a space would be "\\ ".
     * @param value Thisis the string that the key is replaced by. 
     */
    void AddSearchAndReplaceMap(std::string key, std::string value);


    /**
     * This is similar to the double string argument, but this accepts a vector 
     * of a pair of std::strings. 
     * @param vpssValue This is a std::pair<std::string , std::string> where 
     * the strings are the search and replace values. 
     */
    void AddSearchAndReplaceMap(
        std::vector< std::pair<std::string,std::string> > vpssValue);


    /**
     * Use this method to list the search and replace map (mostly for 
     * debugging) to console. 
     */
    void ListSearchAndReplaceMap();
    /**
     * This method will perform the search and replace items listed in 
     * SearchAndReplaceMap to the file given by the string. The output will 
     * either be to the same file or to a new file specified by the optional 
     * argument sOut_Filename.
     * @param sIn_Filename File to be parsed.
     * @param sOut_Filename Output file (if none given it will overwirte the 
     * original file.
     */
    int SearchAndReplaceFile(
        std::string sIn_Filename,
        std::string sOut_Filename="" );


};
std::vector<std::string>  RegexpMatch(std::string sExpression, std::string sString);

bool IsRegexpMatch(std::string sExpression, std::string sString);

#endif
