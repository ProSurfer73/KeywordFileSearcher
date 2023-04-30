#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

/// This class is dealing with tasks run in the background.

#include <queue>
#include <thread>
#include <mutex>

/**< A class dealing with tasks run in the background. */
class BackgroundTasksManager
{
public:
    /**< Let's specify what a pointer to a task function is. */
    typedef void (*TaskFunction)(void**);

    /** \brief add a new task to the queue, that will be run.
     *
     * \param function the addresss of the function corresponding to the task.
     * \param data a pointer to the data we want to pass to the function.
     */
    void addTask(TaskFunction function, void** data);

    /** \brief let's wait until all the tasks are completed.
     */
    void join();

private:
    /**< the list of tasks to be executed. */
    std::queue<std::pair<TaskFunction, void**> > tasksQueue;
    /**< the thread that will be run in the background. */
    std::thread backgroundThread;
    /**< mutex to protect the queue. */
    std::mutex mutex;

private:
    /** \brief function that will manage the execution of the tasks in the background.
     */
    void backgroundExecution();
};


#endif // BACKGROUND_HPP
