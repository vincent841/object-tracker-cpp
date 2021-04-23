#include "Poco/Notification.h"
#include "Poco/NotificationQueue.h"
#include "Poco/ThreadPool.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/Random.h"
#include "Poco/AutoPtr.h"
#include <iostream>

#include "tasks/CameraCalibrationTask.h"
#include "tasks/HandEyeCalibrationTask.h"
#include "taskbase/TaskManager.h"
#include "connection/RoboticsConnection.h"

#include "Entry.h"

using Poco::Notification;
using Poco::NotificationQueue;
using Poco::ThreadPool;
using Poco::Thread;
using Poco::Runnable;
using Poco::Mutex;
using Poco::AutoPtr;

using AIDoop::ObjectTracker::CameraCalibration;
using AIDoop::ObjectTracker::HandEyeCalibration;
using AIDoop::ObjectTracker::TaskManager;
using AIDoop::ObjectTracker::RoboticsConnection;

Mutex AIDoop::ObjectTracker::Task::_mutex;

int mainTemp(int argc, char** argv)
{
    // test robotics conection here
    RoboticsConnection* pRconnect = new RoboticsConnection("127.0.0.1", "3000");
    std::cout << "sigin in: " << pRconnect->signin() << std::endl;

    // initialize task manager and register tasks
    INIT_TASKMGR();
    REGISTER_TASK(pTaskMgr, "cc", CameraCalibration);
    REGISTER_TASK(pTaskMgr, "he", HandEyeCalibration);
    pTaskMgr->startTask("cc");

    ////////////////////////////////////////////////////////////////
    // TEST CODES
    for(;;)
    {
        // receive data outside... 
        char in = std::cin.get();

        // start a task by the received command or packet data
        switch(in)
        {
            case '0':
            {
                Task* pTask = pTaskMgr->getTask("cc");
                pTask->start();
                
                break;
            }
            case '1':
            {
                pTaskMgr->startTask("he");
                break;                
            }
            case '2':
            {
                pTaskMgr->stopAll();
                break;                
            }            
            default:
                break;
        }

        Thread::sleep(200);
    }


    pTaskMgr->joinAllTasks();
}

