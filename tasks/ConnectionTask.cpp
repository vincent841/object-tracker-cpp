#include "Poco/Notification.h"
#include "Poco/NotificationQueue.h"
#include "Poco/ThreadPool.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/Random.h"
#include "Poco/AutoPtr.h"
#include <iostream>

#include "HandEyeCalibrationTask.h"
#include "taskbase/Task.h"

#include "opencv2/opencv.hpp"

using Poco::Notification;
using Poco::NotificationQueue;
using Poco::ThreadPool;
using Poco::Thread;
using Poco::Runnable;
using Poco::FastMutex;
using Poco::AutoPtr;

using AIDoop::ObjectTracker::Task;
using AIDoop::ObjectTracker::Connection;

using namespace cv;  

Connection::Connection() : Task("Connection")
{
}

Connection::~Connection() 
{
}

void Connection::run()
{
}
