#ifndef __TASK_H__
#define __TASK_H__

#include "Poco/Notification.h"
#include "Poco/NotificationQueue.h"
#include "Poco/ThreadPool.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/Random.h"
#include "Poco/AutoPtr.h"
#include <iostream>
#include <string>

#include "taskbase/TaskNotification.h"

using Poco::Notification;
using Poco::NotificationQueue;
using Poco::ThreadPool;
using Poco::Thread;
using Poco::Runnable;
using Poco::Mutex;
using Poco::AutoPtr;

namespace AIDoop
{
    namespace ObjectTracker
    {
        class Task: public Runnable
        {
        public:
            Task(const std::string& name)
                : _name(name)
            {
            }

            virtual void init(){}
            virtual void run(){}
            virtual void start(){}
            virtual void stop(){}            

            //std::string getName() const { return _name; }
			void enqueueNotif(TaskNotification* ptr)
            {
                _queue.enqueueNotification(ptr);
            }

			void wakeupAllNotif()
            {
                _queue.wakeUpAll();
            }

            std::string getName() const { return _name; }
            
        protected:
            std::string        _name;
            static Poco::Mutex   _mutex;
            NotificationQueue  _queue;
        };
    }
}



#endif // __TASK_H__
