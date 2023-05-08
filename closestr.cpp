#include <cstring>
#include <sstream>
#include "closestr.hpp"

#ifdef ENABLE_CLOSESTR

bool isRoughlyEqualTo(const std::string& original, const std::string& current)
{
    int errors = 2;

    for(unsigned i=0, j=0;j<original.size(); ++i,++j)
    {
        if(i>=current.size())
        {
            errors -= 2;
        }
        else if(original[j]!=current[i])
        {
            if(current[i]==original[j+1])
            {
                errors--;
                j++;
            }
            else if(i>0 && current[i]==original[j-1])
            {
                errors--;
                j--;
            }
            else
            {
                errors -= 2;
            }
        }

        if(errors < 0) {
            return false;
        }
    }

    return true;
}

#else

bool isRoughlyEqualTo(const std::string& original, const std::string& current)
{
    return original == current;
}

#endif

bool hasEnding (std::string const &fullString, std::string const &ending)
{
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

// only works with ending that are case insensitive and that have been tampered with
bool hasEndingWhatever(const std::string& fullString, const std::string& ending)
{
    unsigned start = fullString.size()-ending.size();

    for(unsigned i=1; i<ending.size(); ++i){
        if(toupper(fullString[i+start])!=ending[i])
            return false;
    }
    return true;
}

// Let's check if the two strings ar eequal or not.
// we consider the characters to be case insensitive.
bool equalInsensitive(const std::string& str1, const std::string& str2)
{
    if(str1.size() != str2.size())
        return false;

    bool sameString = true;

    for(unsigned i=0; i<str1.size(); ++i)
    {
        if(toupper(str1[i])!=toupper(str2[i]))
            sameString = false;
    }

    return sameString;
}

void replace_all(
    std::string& s,
    std::string const& toReplace,
    std::string const& replaceWith
) {
    std::ostringstream oss;
    std::size_t pos = 0;
    std::size_t prevPos = pos;

    while (true) {
        prevPos = pos;
        pos = s.find(toReplace, pos);
        if (pos == std::string::npos)
            break;
        oss << s.substr(prevPos, pos - prevPos);
        oss << replaceWith;
        pos += toReplace.size();
    }

    oss << s.substr(prevPos);
    s = oss.str();
}
