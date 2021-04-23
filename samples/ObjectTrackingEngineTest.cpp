#include "Poco/Notification.h"
#include "Poco/NotificationQueue.h"
#include "Poco/ThreadPool.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/Random.h"
#include "Poco/AutoPtr.h"
#include <iostream>

#include "cameracalib/CameraCalibrationTask.h"
#include "task/TaskManager.h"

using Poco::Notification;
using Poco::NotificationQueue;
using Poco::ThreadPool;
using Poco::Thread;
using Poco::Runnable;
using Poco::FastMutex;
using Poco::AutoPtr;

using AIDoop::ObjectTracker::CameraCalibration;
using AIDoop::ObjectTracker::TaskManager;

FastMutex   AIDoop::ObjectTracker::Task::_mutex;

int testMain(int argc, char** argv)
{
    CameraCalibration ccTask;

	TaskManager* pTaskMgr = new TaskManager();
	pTaskMgr->startTask(ccTask);

    ccTask.enqueueNotif(new AIDoop::ObjectTracker::TaskNotification(100));

	Thread::sleep(1000);

	// stop all worker threads
	ccTask.joinAllNotif();
	pTaskMgr->stopAllTasks();

    return 0;
}
