#include <iostream>
#include "closestr.hpp" // in order to include tamperWith function.
#include "filesystem.hpp"
#include "keywords.hpp"

using std::string;

void addNumberToStr(std::string& str, unsigned number)
{
    char strnum[15];

    if(number < 10)
        snprintf(strnum, 15, "000%u", number);
    else if(number < 100)
        snprintf(strnum, 15, "00%u", number);
    else if(number < 1000)
        snprintf(strnum, 15, "0%u", number);
    else
        snprintf(strnum, 15, "%u", number);

    str += strnum;
}


/** \brief Look and list the files containing the keyword
 *
 * \param the list of the files to be looked at
 * \param the list of keywords to be searched
 * \param the output stream where the path to the found files will be printed
 * \return the number of files having at least one occurences
 *
 */
unsigned searchKeywords(stringvec& fileCollection, stringvec& results, stringvec& keywords,
            std::vector<struct SpecialOperators>& sop,
            std::ostream& output, std::vector<std::string>& warnings)
{
    unsigned nbOccurences = 0;

    for(string& str1: fileCollection)
    {
        try
        {
            if( keywords.empty() || readFile(str1, keywords, sop) )
            {
                output << str1 << std::endl;
                results.push_back(str1);
                nbOccurences++;
            }
        }
        catch(const FileException& e) {
            // we couldn't open this file, so let's add it to the warning list
            warnings.push_back(str1);
        }
    }

    return nbOccurences;
}


unsigned searchKeywordsWithLines(stringvec& fileCollection, stringvec& results, stringvec& keywords,
         const std::vector<struct SpecialOperators>& sop, std::ostream& output, stringvec& warnings)
{
    unsigned nbOccurences = 0;

    for(string& str1: fileCollection)
    {
        try
        {
            if(keywords.empty() || readFileWithLine(str1, keywords, sop, output)){
                results.push_back(str1);
                nbOccurences++;
            }
        }
        catch(const FileException& e)
        {
            warnings.push_back(str1);
        }
    }

    return nbOccurences;
}

/** \brief Replace keywords (can add occurence number)
 *
 * \param fileCol
 * \param
 * \return
 *
 */
unsigned replaceKeyword(const stringvec& fileCollection, const string& keywordSearched,
                        const char* keywordReplaced, std::ostream& output,
                        std::vector<struct SpecialOperators>& sop,
                        bool addNumberAtTheEnd, stringvec& warnings)
{
    unsigned nbOccurences=0;

    std::string real(keywordReplaced);
    std::vector<std::string> tmp = {keywordSearched};

    for(const string& str1: fileCollection)
    {
        if(addNumberAtTheEnd){
            // Copy the initial string
            real = keywordReplaced;

            // Add the number string to it all
            addNumberToStr(real, nbOccurences);
        }

        try
        {

        if(readFile(str1, tmp, sop)
        && replaceKeywordFile(str1, keywordSearched, real)){
            output << str1 << endl;
            nbOccurences++;
        }

        }
        catch(const FileException& e)
        {
            warnings.push_back(str1);
        }
    }

    return nbOccurences;
}

