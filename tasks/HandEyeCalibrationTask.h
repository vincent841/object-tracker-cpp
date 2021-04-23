#ifndef __HANDEYECALIBRATIONTASK_H__
#define __HANDEYECALIBRATIONTASK_H__

#include "Poco/Notification.h"
#include "Poco/NotificationQueue.h"
#include "Poco/ThreadPool.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/Random.h"
#include "Poco/AutoPtr.h"
#include <iostream>

#include "taskbase/Task.h"
#include "taskbase/TaskNotification.h"

using Poco::Notification;
using Poco::NotificationQueue;
using Poco::ThreadPool;
using Poco::Thread;
using Poco::Runnable;
using Poco::FastMutex;
using Poco::AutoPtr;

using AIDoop::ObjectTracker::Task;

namespace AIDoop
{
    namespace ObjectTracker
    {
		class HandEyeCalibration : public Task
        {
        public:
            HandEyeCalibration();
            virtual ~HandEyeCalibration();
            virtual void run();
        };
	}
};


#endif // __HANDEYECALIBRATIONTASK_H__
