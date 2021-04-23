#ifndef __WORKNOTIFICATION_H__
#define __WORKNOTIFICATION_H__

#include "Poco/Notification.h"
#include "Poco/NotificationQueue.h"
#include "Poco/ThreadPool.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/Random.h"
#include "Poco/AutoPtr.h"
#include <iostream>
#include <list>

#include "taskbase/Task.h"

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
        // TODO: make data more detail
		class TaskNotification: public Notification
			// The notification sent to worker threads.
		{
		public:
			typedef AutoPtr<TaskNotification> Ptr;
			
			TaskNotification(int data):
				_data(data)
			{
			}
			
			int data() const
			{
				return _data;
			}

		private:
			int _data;
		};
	}
}


#endif // __WORKNOTIFICATION_H__