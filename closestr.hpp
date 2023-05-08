#ifndef CLOSESTR_HPP
#define CLOSESTR_HPP

/**< File containing basic operations with strings. */

#include <string>
#include <vector>

// Let's enable it
#define ENABLE_CLOSESTR

/** \brief Checks if two strings are roughly equal to one another (that means a few characters apart).
 *
 * \param original the first string.
 * \param current the second string.
 * \return true if they correspond to each other, false otherwise.
 */
bool isRoughlyEqualTo(const std::string& original, const std::string& current);

/** \brief check if a  string contains at the end the string provided, case sensitively.
 *
 * \param fullString the main string.
 * \param ending the ending.
 * \return true if the string contains the ending, false otherwise.
 */
bool hasEnding (std::string const &fullString, std::string const &ending);

/** \brief check if a  string contains at the end the string provided, case insensitively.
 *
 * \param fullString the main string.
 * \param ending the ending.
 * \return true if the string contains the ending, false otherwise.
 */
bool hasEndingWhatever(const std::string& fullString, const std::string& ending);

/** \brief Checks if two strings are equal, case insensitively.
  * \param str1 the first string.
  * \param str2 the second string.
  * \return true if str1 equal str2 case insensitively, otherwise false.
  */
bool equalInsensitive(const std::string& str1, const std::string& str2);

/** \brief replace a string by another string inside of a string.
 *
 * \param s the string to be modified.
 * \param toReplace the text to will be deleted and replaced.
 * \param replaceWith the text we are going to replace with the old one.
 */
void replace_all(std::string& s, std::string const& toReplace, std::string const& replaceWith);

/** \brief Delete space characters from a given string.
 *
 * \param str the string to be modified.
 */
void clearSpaces(std::string& str);

#endif // CLOSESTR_HPP
