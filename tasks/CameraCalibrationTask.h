#ifndef __CAMERACALIBRATIONTASK_H__
#define __CAMERACALIBRATIONTASK_H__

#include "Poco/Notification.h"
#include "Poco/NotificationQueue.h"
#include "Poco/ThreadPool.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/Random.h"
#include <iostream>
#include <string>

#include "taskbase/Task.h"
#include "taskbase/TaskNotification.h"

using Poco::Notification;
using Poco::NotificationQueue;
using Poco::ThreadPool;
using Poco::Thread;
using Poco::Runnable;
using Poco::Event;

using AIDoop::ObjectTracker::Task;

namespace AIDoop
{
    namespace ObjectTracker
    {
        class OpencvCamCalib;

		class CameraCalibration : public Task
        {
        public:
            CameraCalibration();
            virtual ~CameraCalibration();
            virtual void run();

            virtual void start();
            virtual void stop();

            bool getResult(void* pResult);

            //std::string getName() const { return _name; }
        private:
            bool checkDirectoryExists( const char* pzPath );
            std::string makeImageDirectory();

        private:
            void* _pResult;
            OpencvCamCalib* _pCamCalib;
            std::list<std::string> _listImageFiles;
            Poco::Event _evtStart;
            bool _threadExit;

        };
	}
};


#endif // __CAMERACALIBRATIONTASK_H__
