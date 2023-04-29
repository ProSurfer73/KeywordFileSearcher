#ifndef HISTORY_HPP
#define HISTORY_HPP

#include <vector>
#include <deque>
#include <string>
#include <ostream>

/**< file path where the history is going to be automatically saved and loaded. */
#define HISTORY_FILEPATH "history.txt"

/**< the maximum number of entries per category. */
#define MAX_HISTORY_ENTRY 5


/**< class dealing with the history of entries typed by the user. */
class History
{
public:
    /** \brief Default constructor. Automatically loads history from HISTORY_FILEPATH.
     */
    // Automatically loads the file
    History();

    /** \brief load a file from history.
     *
     * \param str file path form which the history should be loaded.
     */
    bool loadFromFile(const std::string& str);

    /** \brief save history to a file.
     *
     * \param file path to which the history should be saved to.
     */
    bool saveToFile(const std::string& str);

    /** \brief to try to get the database corresponding to a category.
     *
     * \param str name of the category to which we want the database.
     * \return nullptr if the database for the category does not exist, or a pointer to the category database.
     */
    std::deque<std::string>* getTableFrom(const std::string& str);

    /** \brief try to add an entry to the history database (if the entry does not already exists).
     *
     * \param name name of the category to which the entry should be pushed.
     * \param value the value of the entry to be added.
     * \param caseInsensitive if true, entries will be compared case insensitively.
     */
    void pushHistory(const std::string& name, const std::string& value, bool caseInsensitive=false);

    /** \brief show the content of the database for a category.
     *
     * \param the category name.
     */
    void showPossibilities(const std::string& name);

    /** \brief try to replace shortcut number from the user input string to their respective value.
     *
     * \param userInput the string typed from the user. If it is an integer and if there exists a reaplcement string, it will be replaced.
     * \param name the category corresponding to it.
     * \return true if a replacement occured, false if not.
     */
    bool tryPossibilities(std::string& userInput, const std::string& name);

    /** \brief write the history content into a stream from the standard library.
     *
     * \param stream the stream to which the history content should be written to.
     */
    void writeContentToStream(std::ostream& stream);

private:
    /**< contains the history database. */
    std::vector< std::pair< std::string, std::deque<std::string> > > tables;
};



#endif // HISTORY_HPP
