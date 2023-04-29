#ifndef OPERATORS_HPP
#define OPERATORS_HPP

#include <string>

/** Brief: This file will contain management of operators '@', '#' **/

struct SpecialOperators
{
    bool exclusionCharacter; // character '!'
    bool insensitiveCharacter; // character '#'
    bool spaceIgnoreCharacter; // character '@'
};

/** \brief detect special operators at the beggining of the string.
 *
 * \param keyword the keyword string. special operators at the begining of it will be deleted. it will touppered if the operator '#' is used.
 * \return the list of special operators detected at the begining of the string.
 */
struct SpecialOperators analyseKeyword(std::string& keyword);


/** \brief check if  a line contains a specific keyword or not.
 *
 * \param str the keyword.
 * \param readLine the line.
 * \param caseInsensitive comparison parameter.
 * \param ignoreSpaces comparison parameter.
 * \return true if the line contains the keyword, false if it does not.
 */
bool matchKeywordToLine(const std::string& str, std::string& readLine, bool caseInsensitive, bool ignoreSpaces);


#endif // OPERATORS_HPP
