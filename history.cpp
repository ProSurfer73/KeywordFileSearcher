#include <deque>
#include <fstream>
#include <algorithm>
#include <iostream>

#include "history.hpp"
#include "closestr.hpp" // case insensitive character comparaison.

static void clearSpaces(std::string& str)
{
    str.erase(std::remove_if(str.begin(), str.end(), isspace),str.end());
}



/*
 *  Class History
 */

History::History()
{
    loadFromFile(HISTORY_FILEPATH);
}

bool History::loadFromFile(const std::string& str)
{
    std::ifstream file(str);

    if(!file)
        return false;

    std::string lineRead;
    std::deque<std::string> *v = nullptr;

    while(getline(file, lineRead))
    {
        if(lineRead.size()>4 && lineRead.substr(0,4)=="==> ")
        {
            std::string toBeAdded = lineRead.substr(4);
            clearSpaces(toBeAdded);

            tables.emplace_back( std::move(toBeAdded), std::deque<std::string>());
            v = &(tables.back().second);
        }
        else if(v != nullptr && !lineRead.empty())
        {
            // Let's not push twice the same value
            if(std::find(v->begin(), v->end(), lineRead) == v->end())
                v->push_back(lineRead);
        }
    }

    return true;
}


bool History::saveToFile(const std::string& str)
{
    // let's open a file, in writing mode.
    std::ofstream file(str);

    // if the could not be opened.
    if(!file)
        return false;

    // let's write our history into it.
    writeContentToStream(file);
    return true;
}


std::deque<std::string>* History::getTableFrom(const std::string& str)
{
    for(auto& p: tables)
    {
        if(p.first == str)
            return &(p.second);
    }

    return nullptr;
}

void History::pushHistory(const std::string& name, const std::string& value, bool caseInsensitive)
{
    auto* p = this->getTableFrom(name);

    if(p != nullptr)
    {
        // Let's first check if this entry does not already exist
        for(auto it=p->begin(); it!=p->end(); ++it)
        {
            if((!caseInsensitive && *it == value)
             ||(caseInsensitive && equalInsensitive(value, *it)))
            {
                p->push_front(std::move(*it));
                p->erase(it);

                // Let's save the file
                if(!saveToFile(HISTORY_FILEPATH))
                    std::cout << "Can't save history !" << std::endl;

                return;
            }
        }

        if(p->size()>=MAX_HISTORY_ENTRY)
        {
            // Let's first try to erase already existing item
            bool hasBeenDeleted = false;
            for(auto it1 = p->begin(); it1 != p->end() && hasBeenDeleted ; ++it1) {
                for(auto it2 = p->begin() ; it2 != p->end() && hasBeenDeleted ; ++it2) {
                    // If we have seperate items having the same value
                    if(it1 != it2 && *it1 == *it2) {
                        it1 = p->erase(it1);
                        hasBeenDeleted = true;
                    }
                }
            }

            if(!hasBeenDeleted)
                p->pop_back();
        }

        // Let's push front
        p->push_front(value);
    }
    else
    {

        // let's add another table
        tables.emplace_back(name, std::deque<std::string>({value}));
    }

    // Let's save the file
    if(!saveToFile(HISTORY_FILEPATH))
        std::cout << "Error: Can't save history !" << std::endl;
}


void History::showPossibilities(const std::string& name)
{
    auto* p = this->getTableFrom(name);
    if(p != nullptr) {
        unsigned i=1;
        for(const std::string& s: *p){
            std::cout << i++ << ". " << s << std::endl;
        }
    }
}

bool History::tryPossibilities(std::string& userInput, const std::string& name)
{
    auto* p = this->getTableFrom(name);

    if(p != nullptr)
    {
        try
        {
            unsigned choice = std::stoul(userInput);

            if(choice >= 1 && choice <= p->size())
            {
                userInput = (*p)[choice-1];
            }

            return true;
        }
        catch(...)
        {}

    }

    return false;
}

void History::writeContentToStream(std::ostream& stream)
{
    for(const auto& p: tables)
    {
        stream << "==> " << p.first << std::endl;

        for(const std::string& s: p.second)
        {
            stream << s << std::endl;
        }
    }
}
