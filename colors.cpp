#include "colors.hpp"

// let's include windows api
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>


#if defined(__WIN32)||defined(__WIN64)


static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


void SetDefaultConsoleColor(void)
{
    // By default, the text is white and the background is black.
    SetConsoleTextAttribute(hConsole,
                            FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
                          //| BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}

void SetSpecialConsoleColor(unsigned colorConsole)
{
    // By default, the text is red and the background is black.

    WORD mycolor=FOREGROUND_RED;

    switch(colorConsole%6)
    {
    case 0: mycolor=FOREGROUND_RED; break;
    case 1: mycolor=FOREGROUND_GREEN; break;
    case 2: mycolor=FOREGROUND_BLUE; break;
    case 3: mycolor=FOREGROUND_RED|FOREGROUND_GREEN; break;
    case 4: mycolor=FOREGROUND_RED|FOREGROUND_BLUE; break;
    case 5: mycolor=FOREGROUND_BLUE|FOREGROUND_GREEN; break;
    }

    SetConsoleTextAttribute(hConsole, mycolor);
                          //| BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}

void showLineWithKeyword(const std::string& line, const std::string& keyword)
{
    size_t ff;
    unsigned pos=0;

    SetDefaultConsoleColor();

    while(pos < line.size())
    {
        ff = line.find(keyword, pos);

        if(ff == std::string::npos)
        {
            for(; pos<line.size(); ++pos)
            {
                std::cout << line[pos];
            }
        }
        else
        {
            for(; pos<ff; ++pos)
            {
                std::cout << line[pos];
            }

            SetSpecialConsoleColor(0);

            std::cout << keyword;

            SetDefaultConsoleColor();

            pos += keyword.size();
        }
    }


}

void showLineWithKeyword(const std::string& line, const std::vector<std::string>& keywords)
{
    size_t ff;
    unsigned pos = 0;

    SetDefaultConsoleColor();

    while(pos < line.size())
    {

        // let's find the nearest keyword.

        ff=10000;
        unsigned keywordNumber=0;
        for(unsigned i=0; i<keywords.size(); i++)
        {
            unsigned tmp = line.find(keywords[i], pos);

            if(tmp < ff)
            {
                ff = tmp;
                keywordNumber = i;
            }
        }

        if(ff == 10000)
            ff = std::string::npos;



        if(ff == std::string::npos)
        {
            for(; pos<line.size(); ++pos)
            {
                std::cout << line[pos];
            }
        }
        else
        {
            for(; pos<ff; ++pos)
            {
                std::cout << line[pos];
            }

            SetSpecialConsoleColor(keywordNumber);

            std::cout << keywords[keywordNumber];

            SetDefaultConsoleColor();

            pos += keywords[keywordNumber].size();
        }
    }
}

#else

void SetDefaultConsoleColor(void){}
void SetSpecialConsoleColor(void){}

void showLineWithKeyword(const std::string& line, const std::vector<std::string>& keywords)
{
    std::cout << line;
}

#endif


