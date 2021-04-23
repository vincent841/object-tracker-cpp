
#include "TaskManager.h"

using namespace AIDoop::ObjectTracker;

TaskManager::TaskManager()
{
}

TaskManager::~TaskManager()
{
}

void TaskManager::registerTask(std::string taskname, Task* task)
{
    _mapTasks[taskname] = task;
}

void TaskManager::startTask(std::string taskname)
{
    Task* pTask = _mapTasks[taskname];
    if(pTask != nullptr)
    {
        ThreadPool::defaultPool().start(*pTask);
    }
}

void TaskManager::stopAll()
{
    ThreadPool::defaultPool().stopAll();
}

void TaskManager::joinAllTasks()
{
    ThreadPool::defaultPool().joinAll();
}
