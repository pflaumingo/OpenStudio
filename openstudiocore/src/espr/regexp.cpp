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


#include "regexp.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/regex.hpp>


void TSearchAndReplace::AddSearchAndReplaceMap(std::string key, std::string value)
{
    SearchAndReplaceMap[key] = value;
};

void TSearchAndReplace::ListSearchAndReplaceMap()
{
    for(iter = SearchAndReplaceMap.begin(); iter != SearchAndReplaceMap.end(); iter++)
    {
      //        std::cout << "\'"<<(*iter).first << "\' replaced by  \'" << iter->second <<"\'" << std::endl;
    }

};

void TSearchAndReplace::AddSearchAndReplaceMap(std::vector< std::pair<std::string, std::string> > vpssValue)
{
    std::vector< std::pair<std::string, std::string> >::iterator iter = vpssValue.begin();
    while (iter != vpssValue.end())
    {
        AddSearchAndReplaceMap(iter->first, iter->second);
        iter++;
    }
};




void TSearchAndReplace::load_file(std::string& s, std::istream& is)
{
    s.erase();
    if(is.bad()) return;
    s.reserve(is.rdbuf()->in_avail());
    char c;
    while(is.get(c))
    {
        if(s.capacity() == s.size())
            s.reserve(s.capacity() * 3);
        s.append(1, c);
    }
};

int TSearchAndReplace::SearchAndReplaceFile(std::string sIn_Filename,std::string sOut_Filename)
{
    if (sOut_Filename == "")
    {
        sOut_Filename = sIn_Filename;
    }
    try{
        std::string sSearchList = "";
        std::string sReplaceList = "";
        int iCounter = 0;

        for(iter = SearchAndReplaceMap.begin(); iter != SearchAndReplaceMap.end(); iter++)
        {
            iCounter += 1;
            char  sbuffer[10];
            sprintf_s(sbuffer,"%d",iCounter);
            if (iter != SearchAndReplaceMap.begin())
            {
                sSearchList += "|";
            }
            sSearchList +=std::string("(") + (*iter).first +  std::string(")")  ;

            sReplaceList += std::string("(\?") + std::string(sbuffer) + std::string("(") + iter->second + std::string("))");

        }

        boost::regex e1;
        e1.assign(sSearchList.c_str());
        // Debug output
        //std::cout << "Processing file " << sIn_Filename << std::endl;
        // open file.
        std::ifstream fs(sIn_Filename.c_str());
        //Load file into a string.
        std::string in;
        load_file(in, fs);
        //Close file stream.
        fs.close();
        // Open output file.
        std::ofstream os(sOut_Filename.c_str());
        std::ostream_iterator<char> out(os);
        boost::regex_replace(out, in.begin(), in.end(), e1, sReplaceList, boost::match_default | boost::format_all);
        os.close();
    }
    catch(...)
    { return -1; }
    return 0;
};


std::vector<std::string>  RegexpMatch(std::string sExpression, std::string sString)
{
    std::vector<std::string> vsReturn;
    boost::regex re;
    boost::cmatch matches;
    try
    {
        // Assignment and construction initialize the FSM used
        // for regexp parsing

        re = sExpression;
    }
    catch (boost::regex_error& e)
    {
        std::cout << sExpression<< " is not a valid regular expression: \""
        << e.what() << "\"" << std::endl;
    }

    if (boost::regex_match(sString.c_str(), matches, re))
    {
        // matches[0] contains the original string.  matches[n]
        // contains a sub_match object for each matching
        // subexpression
        for (unsigned int i = 1; i < matches.size(); i++)
        {
            // sub_match::first and sub_match::second are iterators that
            // refer to the first and one past the last chars of the
            // matching subexpression
            std::string match(matches[i].first, matches[i].second);
            vsReturn.push_back(match);
        }
    }
    else
    {
        //std::cerr << "The regexp \"" << re << "\" does not match \"" << sString << "\"" << std::endl;
    }
    return vsReturn;
}

bool  IsRegexpMatch(std::string sExpression, std::string sString)
{
    std::vector<std::string> vsReturn;
    boost::regex re;
    boost::cmatch matches;
    try
    {
        // Assignment and construction initialize the FSM used
        // for regexp parsing

        re = sExpression;
    }
    catch (boost::regex_error& e)
    {
        std::cout << sExpression<< " is not a valid regular expression: \""
        << e.what() << "\"" << std::endl;
    }

    if (boost::regex_match(sString.c_str(), matches, re))
    {
      return true;
    }
    else
    {
        return false;
    }

}



