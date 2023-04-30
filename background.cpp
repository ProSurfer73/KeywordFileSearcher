#include "background.hpp"


void BackgroundTasksManager::addTask(TaskFunction function, void** data)
{
    // 1. let's add the task to the queue.
    mutex.lock();
    tasksQueue.push(std::make_pair(function, data) );
    mutex.unlock();

    // 2. let's run the corresponding thread (if not already run).
    if(!backgroundThread.joinable())
        backgroundThread = std::thread(&BackgroundTasksManager::backgroundExecution, this);
}

void BackgroundTasksManager::join()
{
    // Let's wait until our background task is finished.
    backgroundThread.join();
}

void BackgroundTasksManager::backgroundExecution()
{
    // As long as we have atsks to do.
    mutex.lock();
    while(!tasksQueue.empty())
    {
        // Let's get the task.
        std::pair<TaskFunction,void**> mypair = tasksQueue.front();
        mutex.unlock();

        // Let's run it.
        (*mypair.first)(mypair.second);

        // Finally, let's remove it from the queue.
        mutex.lock();
        tasksQueue.pop();
    }
    mutex.unlock();
}

