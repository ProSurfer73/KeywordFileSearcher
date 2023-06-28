#include <iostream>
#include <cstdio>
#include <thread>
#include <windows.h>

#include "filesystem.hpp"
#include "closestr.hpp"
#include "history.hpp"
#include "keywords.hpp"
#include "operators.hpp"
#include "background.hpp"
#include "colors.hpp"


// Let's define the absolute path to Notepad++ inside the program.
#define NOTEPADPP_ABSOLUTE_PATH "C:\\Programs\\Notepad++\\notepad++.exe"



void filterFilepathByEnding(std::vector<std::string>& fileCollection, std::vector<std::string>& extensions, std::vector<struct SpecialOperators>& sop)
{
    // Let's check waht type of list it is
    bool listOfExtensionsToKeep = true;
    for(const auto& s : sop)
    {
        // lets exclude this
        if(s.exclusionCharacter)
        {
            listOfExtensionsToKeep = false;
        }
    }

    if(listOfExtensionsToKeep)
    {

    // Case 1: list of extensions to keep
    for(auto it = fileCollection.begin(); it!=fileCollection.end();)
    {
        // Is the extension of the file among the list of extensions to keep
        bool shouldKeep=false;

        for(unsigned i=0; i<extensions.size(); i++)
        {
            if((sop[i].insensitiveCharacter && hasEndingWhatever(*it, extensions[i]))
             ||(!sop[i].insensitiveCharacter && hasEnding(*it, extensions[i]))){
                shouldKeep = true;
                break;
            }
        }

        // Erase the filepath
        if(!shouldKeep)
            it = fileCollection.erase(it);
        else
            ++it;
    }

    }
    else
    {

    // Case 2: list of extensions to avoid

    for(auto it = fileCollection.begin(); it!=fileCollection.end();)
    {
        // Is the extension of the file among the list of extensions to keep
        bool shouldKeep=true;

        for(string& curExt : extensions)
        {
            if((curExt.front()=='#' && hasEndingWhatever(*it, curExt))
             ||(curExt.front()!='#' && hasEnding(*it, curExt))){
                shouldKeep = false;
                break;
            }
        }

        // Erase the filepath
        if(!shouldKeep)
            it = fileCollection.erase(it);
        else
            ++it;
    }

    }
}



void showHelp()
{
    cout << "\nKeyword prefix options:" << endl;
    cout << "'#' => case insensitive: you can mark a keyword no matter whether letter are  " << endl;
    cout << "'@' => ignore space: will match whether or not they are spaces between the characters." << endl;
    cout << "'!' => anti-keyword: will not match files containing this string." << endl;
    cout << "You can only use one prefix per keyword for the moment, using multiple of them is soon to be implemented.\n" << endl;

    cout << "At the end, you can type:" << endl;
    cout << "deleteall => delete all the files listed (dangerous, be careful)." << endl;
    cout << "restart => restart the program with another query." << endl;
    cout << "addend => add a string at the end of all the filenames list." << endl;
    cout << "deleteend => delete the end string inside all filenames of all files." << endl;
    cout << "errors => show all the list of all the files that could not be opened." << endl;
    cout << "openall => open all the files found at the right line in notepad++.\n" << endl;
}

void taskExploreDirectory(void *data[])
{
    explore_directory(*(static_cast<std::string*>(data[0])),
                      *((std::vector<std::string>*)data[1]));
}

void taskFilterPathEnding(void *data[])
{
    filterFilepathByEnding(*((std::vector<std::string>*)data[0]),
                           *((std::vector<std::string>*)data[1]),
                           *((std::vector<struct SpecialOperators>*)data[2]));
}

bool launchProgram(History& history);

int main()
{
    std::cout << "WELCOME TO KEYWORD SEARCHER." << endl;
    std::cout << "List files containing strings, filter by extension, inside a specified folder." << endl;
    std::cout << "You can type 'help' at any time to show special keyword options.\n" << endl;

    History history;

    try
    {
        // Let's launch and restart the program as long as the user wants to
        while(launchProgram(history));
    }

    // Let's catch exceptions from the standard library.
    catch(const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
        while(1);
    }

    // Let's catch unknown exceptions.
    catch(...)
    {
        std::cout << "!!unknown exception!!" << std::endl;
        while(1);
    }


    return 0;
}

bool launchProgram(History& history)
{
    history.showPossibilities("directories");

    reaskDirectory:

    std::cout << "Please type the directory: ";

    SetDefaultConsoleColor();

    string input;
    BackgroundTasksManager background;

    getline(cin, input);

    if(input.empty())
        return false;

    if(input == "help")
    {
        showHelp();
        goto reaskDirectory;
    }

    history.tryPossibilities(input, "directories");

    if(!directoryExists(input.c_str())) {
        std::cout << "/!\\ The directory you entered does not seem to exist, please retry. /!\\\n" << std::endl;
        goto reaskDirectory;
    }

    stringvec fileCollection;

    void *arg1[] = {&input, &fileCollection};
    background.addTask( taskExploreDirectory, arg1);




    // vector of keywords and their parameters
    std::vector<std::string> keywords;
    std::vector<struct SpecialOperators> sop, sop2;


    std::cout << std::endl;
    history.showPossibilities("search");

    bool savedDirectory=false;

    do
    {
        std::cout << "Please type a string you would like to search: ";

        if(!input.empty())
        {
            if(input == "help")
            {
                showHelp();
            }
            else if(savedDirectory)
            {
                history.tryPossibilities(input, "search");
                history.pushHistory("search", input);
                sop.push_back(analyseKeyword(input));
                keywords.emplace_back(input);
            }
            else
            {
                history.pushHistory("directories", input, true);
                savedDirectory = true;
            }
        }

        getline(cin, input);
    }
    while(!input.empty());

    stringvec extensionsToKeep;

    std::cout << std::endl;

    input.clear();

    history.showPossibilities("extension");

    do
    {
        cout << "Please type extension (or nothing to continue): ";

        if(!input.empty())
        {
            if(input == "help")
            {
                showHelp();
            }
            else
            {
                history.tryPossibilities(input, "extension");
                history.pushHistory("extension", input, true);
                sop2.push_back(analyseKeyword(input));
                extensionsToKeep.emplace_back(input);
            }
        }

        getline(cin, input);
    }
    while(!input.empty());



    // let's launch the path ending filtering task.
    void *arg2[] = {
        &fileCollection,
        &extensionsToKeep,
        &sop2
    };

    if(!extensionsToKeep.empty())
    {

        background.join();
        //background.addTask(taskFilterPathEnding, arg2);
        filterFilepathByEnding(fileCollection, extensionsToKeep, sop2);
    }


    //std::ofstream resultFile("C:\\Users\\divouxje\\Desktop\\output.txt");

    reask:

    cout << "\nType 1 to search and 2 to replace (+: print involved lines):" << endl;

    std::vector<std::string> warnings;

    getline(cin, input);

    unsigned nb=0;

    stringvec results;

    // search mode
    if(input == "1")
    {
        background.join();
        nb = searchKeywords(fileCollection, results, keywords, sop, cout, warnings);
    }
    else if(input == "1+")
    {
        background.join();

        if(keywords.empty())
            nb = searchKeywords(fileCollection, results, keywords, sop, cout, warnings);
        else
            nb = searchKeywordsWithLines(fileCollection, results, keywords, sop, cout, warnings);
    }

    // replace mode
    else if(input == "2")
    {
        history.showPossibilities("replace");

        cout << "Type the string to replace:" << endl;
        string str2;
        getline(cin, str2);

        history.tryPossibilities(str2, "replace");

        cout << "add localising number to it ? (type 'y' if okay)" << endl;
        getline(cin, input);

        background.join();

        //
        nb = replaceKeyword(fileCollection, keywords.front(), str2.c_str(), cout, sop, (input[0]=='y'), warnings);
    }

    // Incorrect input
    else
    {
        if(input == "help")
        {
            showHelp();
        }

        goto reask;
    }





    std::cout << nb << " results found." << std::endl;
    if(!warnings.empty())
        std::cout << "warning: " << warnings.size() << " files could not be opened." << std::endl;

    std::cout << "\nThanks for trusting Search&Replace program." << endl;
    std::cout << "Press enter to exit";
    if(!results.empty())
        std::cout << ", or notepad to open files in notepad++";
    if(!warnings.empty())
        std::cout << ", or 'errors' to show the list of files that could not be opened.";
    std::cout << std::endl;

    while(std::cout << "\n > " && getline(cin, input))
    {
        if(isRoughlyEqualTo("notepad",input))
        {
            // Let's launch notepad++ with all the files here

            // ! To be implemented !
        }
        else if(isRoughlyEqualTo("restart",input))
        {
            return true;
        }
        else if(isRoughlyEqualTo("errors", input))
        {
            // Let's display warnings

            std::cout << "Below, the list of files that could not be opened:" << std::endl;
            for(const std::string& s: warnings)
                std::cout << s << std::endl;
        }
        else if(input == "deleteall")
        {
            // Let's ask confirmation from the user
            std::cout << "Are you sure you wanna erase all the files listed above ?" << std::endl;
            std::cout << "Please type 'yes' to confirm." << std::endl;


            if(std::getline(std::cin, input) && input == "yes")
            {
                std::cout << "Please press enter to confirm every file being deleted." << std::endl;

                for(const std::string& s: fileCollection)
                {
                    std::cout << s;
                    std::getline(std::cin, input);

                    if(remove(s.c_str())!=0)
                        std::cout << "The file could not be deleted." << std::endl;
                }
            }
        }

        else if(input == "addend")
        {
            std::cout << "Please type the string you would to add at the end of the filename of the entries:" << std::endl;

            std::string newEnd;
            std::getline(std::cin, newEnd);

            if(newEnd.find(' ')!=std::string::npos)
            {
                std::cout << "there is a space, are you sure ?" << std::endl;
                std::getline(std::cin, input);
            }


            for(const std::string& s: fileCollection)
            {
                std::cout << s;
                std::getline(std::cin, input);

                if(rename(s.c_str(), (s+newEnd).c_str()) != 0)
                    std::cout << "Couldn't rename the file sorry :(" << std::endl;
            }
        }

        else if(input == "removeend")
        {
            std::cout << "Please type the end you would like to remove:";

            std::string oldEnd;
            std::getline(std::cin, oldEnd);

            for(unsigned i=0; i<fileCollection.size(); ++i)
            {
                string s = fileCollection[i];

                if(hasEnding(s, oldEnd))
                {
                    s.resize(s.size()-oldEnd.size());
                    std::cout << s;
                    std::getline(std::cin, input);

                    if(rename(fileCollection[i].c_str(), s.c_str()) != 0)
                        std::cout << "Can't rename that file :(" << std::endl;
                }
            }
        }

        else if(isRoughlyEqualTo("openall", input))
        {
            if(fileCollection.size() > 30)
            {
                std::cout << "Error: Too much file to open (number > 30) !" << endl;
            }
            else
            {
                std::string cmdLine;



                for(const std::string& s: fileCollection)
                {
                    // Let's open the source file here
                    ShellExecute(NULL, NULL, s.c_str(), NULL, NULL, SW_SHOWNORMAL);

                    STARTUPINFO si;
                    PROCESS_INFORMATION pi;

                    char *str = new char[s.size()+1];
                    strcpy(str, s.c_str());

                    CreateProcess(NOTEPADPP_ABSOLUTE_PATH,   // Name of program to execute
                                str,                      // Command line
                                NULL,                      // Process handle not inheritable
                                NULL,                      // Thread handle not inheritable
                                FALSE,                     // Set handle inheritance to FALSE
                                0,                         // No creation flags
                                NULL,                      // Use parent's environment block
                                NULL,                      // Use parent's starting directory
                                &si,                       // Pointer to STARTUPINFO structure
                                &pi);                      // Pointer to PROCESS_INFORMATION structure
                }
            }
        }


        else if( input.empty()
        || isRoughlyEqualTo("exit", input)
        || isRoughlyEqualTo("quit", input) )
        {
            break;
        }
    }





    return false;
}
