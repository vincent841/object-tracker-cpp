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
using AIDoop::ObjectTracker::HandEyeCalibration;

using namespace cv;  

HandEyeCalibration::HandEyeCalibration() : Task("HandEyeCalibration")
{
}

HandEyeCalibration::~HandEyeCalibration() 
{
}

void HandEyeCalibration::run()
{
    VideoCapture cap(4);  
    if (!cap.isOpened())  
    {  
        return;
    }  
    
    Mat frame;  
    namedWindow("handeyecal", 1);  
  
    for (;;)  
    {  
        cap >> frame;  
  
        imshow("handeyecal", frame);  
  
        if (waitKey(20) >= 0) break;
    }

    destroyAllWindows();

    // std::cout << this->getName() << std::endl;

    // for(;;)
    // {
    //     Notification::Ptr pNf(_queue.waitDequeueNotification());
    //     if (pNf)
    //     {
    //         TaskNotification::Ptr pTaskNf = pNf.cast<TaskNotification>();
    //         if (pTaskNf)
    //         {
    //             {
    //                 FastMutex::ScopedLock lock(_mutex);
    //                 std::cout << _name << " got work notification " << pTaskNf->data() << std::endl;
    //             }
    //             Thread::sleep(100);
    //         }
    //     }
    //     else 
    //         break;				
    // }
}

// void HandEyeCalibration::enqueueNotif(TaskNotification* ptr)
// {
//     _queue.enqueueNotification(ptr);
// }

// void HandEyeCalibration::joinAllNotif()
// {
//     _queue.wakeUpAll();
// }
