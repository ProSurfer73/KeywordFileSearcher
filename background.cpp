#include "background.hpp"

#include <iostream>
#include <windows.h>


void BackgroundTasksManager::addTask(TaskFunction function, void** data)
{
    /*std::cout << "debug: add task." << std::endl;
    Sleep(4000);*/

    // 1. let's add the task to the queue.
    mutex.lock();
    bool wasEmpty = tasksQueue.empty();
    tasksQueue.push( std::make_pair(function, data) );

    // 2. let's run the corresponding thread (if not already run).
    if(wasEmpty && !backgroundThread.joinable())
    {
        backgroundThread = std::thread(&BackgroundTasksManager::backgroundExecution, this);
    }
    mutex.unlock();
}

void BackgroundTasksManager::join()
{
    // Let's wait until our background task is finished.
    if(backgroundThread.joinable())
        backgroundThread.join();
}

#include <windows.h>

void BackgroundTasksManager::backgroundExecution()
{
    /*std::cout << "debug: background execution." << std::endl;
    Sleep(4000);*/

    // As long as we have tasks to do.
    mutex.lock();

    while(!tasksQueue.empty())
    {
        // Let's get the task, and remove it from the queue.
        std::pair<TaskFunction,void**> mypair = tasksQueue.front();
        tasksQueue.pop();
        mutex.unlock();

        // Let's run it.
        /*std::cout << "debug: execute the function." << std::endl;
        Sleep(4000);*/
        (*mypair.first)(mypair.second);

        mutex.lock();
    }

    mutex.unlock();
}

