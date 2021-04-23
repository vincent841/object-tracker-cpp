#ifndef __TASKMANAGER_H__
#define __TASKMANAGER_H__

#include "Poco/Notification.h"
#include "Poco/NotificationQueue.h"
#include "Poco/ThreadPool.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/Random.h"
#include "Poco/AutoPtr.h"
#include <iostream>
#include <map>

#include "Task.h"

using Poco::Notification;
using Poco::NotificationQueue;
using Poco::ThreadPool;
using Poco::Thread;
using Poco::Runnable;
using Poco::FastMutex;
using Poco::AutoPtr;

namespace AIDoop
{
    namespace ObjectTracker
    {
        class TaskManager
        {
        public:
            TaskManager();
            ~TaskManager();

            void registerTask(std::string taskname, Task* task);
            void startTask(std::string taskname);
            void joinAllTasks();
            void stopAll();

            Task* getTask(std::string taskname) { return _mapTasks[taskname]; }

        private:
            std::map<std::string, Task*> _mapTasks;
        };
    }
}






#endif // __TASKMANAGER_H__
