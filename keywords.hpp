#ifndef KEYWORDS_HPP
#define KEYWORDS_HPP

#include <string>
#include <vector>

typedef std::vector<std::string> stringvec;


/** \brief add a number from 0 to 1000 at the end of the string provided. The format of the number written contains 4 digits.
 *          example: 0001 0014 1402.
 * \param the string to which we want to add the number.
 * \param a number between 0 and 9999.
 */
void addNumberToStr(std::string& str, unsigned number);

/** \brief search for keywords inside a file collection.
 *
 * \param fileCollection the list of files that are going to be scanned.
 * \param results the list of files in which one of the keyword is going to be found is going to be added to this array.
 * \param sop contains the properties related to each keyword.
 * \param output contains an output stream in which the file in which the keyword is found are going ot be shown in real time.
 * \param warnings contains the list of files that could not be opened for some reason.
 * \return the number of keywords found.
 */
unsigned searchKeywords(stringvec& fileCollection, stringvec& results, stringvec& keywords,
            std::vector<struct SpecialOperators>& sop,
            std::ostream& output, std::vector<std::string>& warnings);

/** \brief search for keywords, while printing lines at which the keywords were found.
 *
 * \param fileCollection the list of files that are going to be scanned.
 * \param results the list of files in which one of the keyword is going to be found is going to be added to this array.
 * \param sop contains the properties related to each keyword.
 * \param output contains an output stream in which the file in which the keyword is found are going ot be shown in real time.
 * \param warnings contains the list of files that could not be opened for some reason.
 * \return the number of keywords found.
 */
unsigned searchKeywordsWithLines(stringvec& fileCollection, stringvec& results, stringvec& keywords,
         const std::vector<struct SpecialOperators>& sop, std::ostream& output, stringvec& warnings);


/** \brief replace a keyword by another inside a file collection.
 *
 * \param fileCollection the file collection.
 * \param keywordSearched the keyword we want to see replaced.
 * \param keywordReplaced the keyword that is going to replace the old one.
 * \return the number of files in which the keyword was replaced.
 */
unsigned replaceKeyword(const stringvec& fileCollection, const string& keywordSearched,
                        const char* keywordReplaced, std::ostream& output,
                        std::vector<struct SpecialOperators>& sop,
                        bool addNumberAtTheEnd, stringvec& warnings);


#endif // KEYWORDS_HPP
