/**********************************************************************
*  Copyright (c) 2008-2015, Alliance for Sustainable Energy.  
*  All rights reserved.
*  
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*  
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*  
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

#include <boost/algorithm/string/trim.hpp>
#include <boost/regex/v4/basic_regex.hpp>
#include <boost/regex/v4/match_flags.hpp>
#include <boost/regex/v4/match_results.hpp>
#include <boost/regex/v4/perl_matcher_common.hpp>
#include <boost/regex/v4/perl_matcher_non_recursive.hpp>
#include <boost/regex/v4/regex.hpp>
#include <boost/regex/v4/regex_fwd.hpp>
#include <boost/regex/v4/regex_match.hpp>
#include <boost/regex/v4/regex_traits.hpp>
#include <boost/regex/v4/sub_match.hpp>
#include <algorithm>
#include <sstream>
#include <vector>

#include "CommentRegex.hpp"
#include "Comments.hpp"

namespace openstudio {

namespace detail {

  std::string makeCommentHelper(const std::string& str,
                                const std::string& linePrefix,
                                int indentSize) 
  {
    // istream for parsing, ostream for composing comment
    std::stringstream ss(str), comment;

    // helper variables
    boost::smatch m;
    std::string line;
    bool first = true;
    bool commentStarted = false;
    unsigned blankLineQueue = 0; // add blank lines in groups

    // parse and compose comment line-by-line
    while (std::getline(ss,line)) {
      // capture comment already marked as such
      if (boost::regex_match(line,m,commentRegex::editorCommentWhitespaceOnlyLine())) {
        line = std::string(m[1].first,m[1].second);
      }
      if (boost::regex_match(line,m,commentRegex::commentWhitespaceOnlyLine())) {
        line = std::string(m[1].first,m[1].second);
      }
      // handle blank lines separately
      if (boost::regex_match(line,commentRegex::whitespaceOnlyLine())) {
        if (commentStarted) { ++blankLineQueue; } // may need to prepend with linePrefix
        else { 
          // no comment yet--leave as pure blank line
          if (!first) { comment << std::endl; } 
        }
      }
      else { 
        // line has non-whitespace characters. prepend each queued blank line with linePrefix
        for (unsigned i = 0; i < blankLineQueue; ++i) {
          comment << std::endl << linePrefix;
        }
        blankLineQueue = 0;

        // align lefthand edge if not indented by at least indentSize
        std::string temp = boost::trim_left_copy(line);
        if (temp.size() > line.size() - indentSize) { line = temp; }
        // go to next line if this is not the first line
        if (!first) { comment << std::endl; }
        // write out comment line
        comment << linePrefix << line;
        commentStarted = true;
      }
      first = false;
    }

    // write out remaining blank lines w/o commenting them
    for (unsigned i = 0; i < blankLineQueue; ++i) {
      comment << std::endl;
    }

    // append std::endl if str ends with \n or \r
    if (!str.empty()) {
      boost::regex re("[\\n\\r]");
      if (boost::regex_match(str.end()-1,str.end(),re)) { 
        comment << std::endl; 
      }
    }

    return comment.str();

  }

} // detail

std::string makeComment(const std::string& str) {

  // make sure each line starts with !
  boost::smatch m;
  if (boost::regex_match(str,m,commentRegex::commentWhitespaceOnlyBlock())) {
    // already does, return as-is
    return str;
  }
  
  // prepend '! ' to each line, as needed
  return detail::makeCommentHelper(str,"! ",2);
}

std::string makeIdfEditorComment(const std::string& str) {
  // make sure each line starts with !-
  boost::smatch m;
  if (boost::regex_match(str,m,commentRegex::editorCommentWhitespaceOnlyBlock())) {
    // already does, return as-is
    return str;
  }
  
  // prepend '!- ' to each line, as needed
  return detail::makeCommentHelper(str,"!- ",2);
}

} // openstudio
