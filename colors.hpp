#ifndef COLORS_HPP
#define COLORS_HPP

// Function to change the color of the console.

#include <string>
#include <vector>

/** \brief this function prints a line of text to the console while underlining special keywords written into the text.
 *
 *  \param line the line of the text to be printed.
 *  \param keyword the keyword to be highlighted.
 */
void showLineWithKeyword(const std::string& line, const std::string& keyword);

/** \brief this function prints a line of text while coloring the keywords.
 *
 *  \param line the line of text to be highlighted.
 *  \param keywords a vector of keywords to be highlighted.
 */
void showLineWithKeyword(const std::string& line, const std::vector<std::string>& keywords);

/** \brief let's set the console colors to its default theme.
 */
void SetDefaultConsoleColor();

/** \brief let's set a special color to underline certain keywords.
 *
 *  \param colorConsole a number from 0 to 6, that corresponds to the color that should be given to the text of the console.
 */
void SetSpecialConsoleColor(unsigned consoleColor);


#endif // COLORS_HPP
