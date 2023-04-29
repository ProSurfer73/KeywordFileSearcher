#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <string>
#include <vector>

using namespace std;

/**< definition shortcut, as std::vector<std::string> is a long thing to type. */
typedef std::vector<std::string> stringvec;

// Functions available

/** \brief check if a directory exists.
 *
 * \param folder path of the directory.
 * \return true if it exists, false otherwise.
 */
bool directoryExists(const char* basepath);

/** \brief check if a file match one of the specified keyword.
 *
 * \param path the file path.
 * \param words the list of keywords.
 * \param sop the list of special operators related to each keyword.
 *          For example if a keyword is marked case insensitive,
 *          'Line of the file' and keyword 'FILE' are going to match.
 * \return true if the keyword was found according to its properties, false otherwise.
 */
bool readFile(const string& path, stringvec& words, std::vector<struct SpecialOperators>& sop);


/** \brief list all the files contained inside a directory and its subdirectories.
 *
 * \param dirname the folder path of the directory.
 * \param files the list of files found are going to be added to this array.
 */
void explore_directory(std::string dirname, std::vector<std::string>& files);


/** \brief replace one keyword by another inside a specified file.
 *
 * \param path the file path of the file.
 * \param initialKeyword
 * \param finalKeyword
 * \return true if the initial keyword is found, false otherwise.
 */
bool replaceKeywordFile(const string& path, const string& initialKeyword, const string& finalKeyword);


/** \brief check if a file match one of the specified keyword (while priting the lines containing the keyword to the output stream).
 *
 * \param path the file path.
 * \param words the list of keywords.
 * \param sop the list of special operators related to each keyword.
 *          For example if a keyword is marked case insensitive,
 *          'Line of the file' and keyword 'FILE' are going to match.
 * \return true if the keyword was found according to its properties, false otherwise.
 */
bool readFileWithLine(std::string& path, const stringvec& words, const std::vector<struct SpecialOperators>& sop, std::ostream& output);


// When a file could not be opened, an exception of this type is launched.
class FileException
{
    // For optimization reasons, we don't reference the name of the file inside the exception.
    const char* what();
};

#endif // FILESYSTEM_HPP

