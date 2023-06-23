#include <cstring>
#include <iostream>
#include <algorithm>

#include "operators.hpp"

struct SpecialOperators analyseKeyword(std::string& keyword)
{
    // 1. Let's detect operators.

    struct SpecialOperators so;
    so.insensitiveCharacter = false;
    so.spaceIgnoreCharacter = false;
    so.exclusionCharacter = false;

    unsigned nb=0;

    for(char c: keyword)
    {
        if(c == '#')
        {
            so.insensitiveCharacter = true;
            nb++;
        }
        else if(c == '@')
        {
            so.spaceIgnoreCharacter = true;
            nb++;
        }
        else if(c == '!')
        {
            so.exclusionCharacter = true;
            nb++;
        }
        else
        {
            break;
        }
    }

    // 2. Let's delete these operators from the string itself.

    for(unsigned i=0; i<nb; ++i)
        keyword.erase(keyword.begin());

    // 3. Let's tamper the string.

    if(so.insensitiveCharacter)
    {
        // let's toupper the entire string.
        for(char& c: keyword)
        {
            c = toupper(c);
        }
    }
    if(so.spaceIgnoreCharacter)
    {
        // let's delete space characters from the string.
        keyword.erase(std::remove_if(keyword.begin(), keyword.end(), isspace),keyword.end());
    }

    return so;
}

bool matchKeywordToLine(const std::string& str, std::string& readLine, bool caseInsensitive, bool ignoreSpaces)
{
    // if we should ignore spaces with this string
    if(ignoreSpaces)
    {
        unsigned j=0;

        // let's compare the string while ignoring spaces.
        for(unsigned i=1; str[i]!='\0'; i++)
        {
            // if it is not letter or a number
            if(!isspace(str[i]))
            {
                // skip spaces
                while(isspace(readLine[j])) j++;

                // compare
                if(str[i] == readLine[j]
                ||(caseInsensitive && toupper(str[i])==readLine[j]))
                {
                    j++;
                }
                else
                    return false;

            }
        }

        return true;
    }

    // 2. if the string is contained
    return readLine.find(str) != std::string::npos;
}
