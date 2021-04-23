#include "Poco/Notification.h"
#include "Poco/NotificationQueue.h"
#include "Poco/ThreadPool.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/Random.h"
#include "Poco/AutoPtr.h"
#include <stdio.h>
#include <iostream>
#include <sys/stat.h>
#include <string>
#include <unistd.h>
#include <dirent.h>

#include "CameraCalibrationTask.h"
#include "taskbase/Task.h"

#include "opencv2/opencv.hpp"

#include "opencv/CameraCalibrationOpenCV.h"

using Poco::Notification;
using Poco::NotificationQueue;
using Poco::ThreadPool;
using Poco::Thread;
using Poco::Runnable;
using Poco::Mutex;
using Poco::AutoPtr;

using AIDoop::ObjectTracker::Task;
using AIDoop::ObjectTracker::CameraCalibration;
using AIDoop::ObjectTracker::OpencvCamCalib;

using namespace cv;  

CameraCalibration::CameraCalibration() 
    : Task("CameraCalibration"), _pCamCalib(NULL), _threadExit(false)
{
    _pCamCalib = new OpencvCamCalib(10, 7);
    _pCamCalib->initialize();
}

CameraCalibration::~CameraCalibration() 
{
    if(_pCamCalib)
        delete _pCamCalib;
}


bool CameraCalibration::checkDirectoryExists( const char* pzPath )
{
    if ( pzPath == NULL) return false;

    DIR *pDir;
    bool bExists = false;

    pDir = opendir (pzPath);

    if (pDir != NULL)
    {
        bExists = true;    
        (void) closedir (pDir);
    }

    return bExists;
}

std::string CameraCalibration::makeImageDirectory()
{
  char buf[256] = {0,};
  time_t now = time(0);
  struct tm tstruct;
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y%m%d%H%M%S", &tstruct);
  std::string dirName(buf);

  getcwd(buf, sizeof(buf));
  std::string strDir("/Captured/");
  std::string strDest;

  try
  {
    bool bDirExists = checkDirectoryExists(strDir.c_str());
    if( bDirExists == false )
        mkdir(strDir.c_str(), 0777);

    strDest = std::string(buf) + strDir + dirName;

    bDirExists = checkDirectoryExists(strDest.c_str());
    if( bDirExists == false)
    {
      std::cout << mkdir(strDest.c_str(), 0777) << std::endl;
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }

  return strDest;
}

void CameraCalibration::start()
{
    _evtStart.set();
}

void CameraCalibration::stop()
{
    _evtStart.reset();
    _threadExit = true;
}

void CameraCalibration::run()
{
    Poco::Mutex::ScopedLock lock(_mutex);

    VideoCapture cap(4);  
    if (!cap.isOpened())  
    {  
        std::cout << "can't open the camera.." << std::endl;
    }  

    namedWindow("cameracal", 1);  

    std::string destDir = makeImageDirectory();
    Mat frame;

    int idxFile = 0;

    for(;;)
    {
        _evtStart.wait();
        if(_threadExit == true)
            break;

        for (;;)  
        {  
            try
            {
                cap >> frame;

                imshow("camera1", frame);

                unsigned int key = waitKey(1);
                if( (key == 'q') || (key == 'Q') )
                    break;

                switch(key)
                {
                    case 'c':
                    case 'C':
                    {
                        // make a directory name using the current time
                        //char buf[256];
                        std::string fname = std::to_string(idxFile++);
                        fname += ".jpg";
                        fname  = destDir + "/" + fname;

                        _listImageFiles.push_back(fname);
                        imwrite(fname.c_str(), frame);
                        break;
                    }

                    case 'g':
                    case 'G':
                    {
                        //_pCamCalib->
                        for(auto const& fn : _listImageFiles)
                        {
                            std::cout << fn << std::endl;

                            Mat jpgImage;
                            jpgImage = imread(fn, IMREAD_COLOR);

                            _pCamCalib->findChessboard(jpgImage, true);
                        }

                        _pCamCalib->runCalibration();
                        break;
                    }

                    default:
                        break;
                }

                // handles notifications
                Notification::Ptr pNf(_queue.waitDequeueNotification(1));
                if (pNf)
                {
                    TaskNotification::Ptr pTaskNf = pNf.cast<TaskNotification>();
                    if (pTaskNf)
                    {
                        {
                            std::cout << _name << "got a notification " << pTaskNf->data() << std::endl;
                        }
                    }
                }
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }        
        }

        destroyAllWindows();    
    }
}

bool CameraCalibration::getResult(void* pResult)
{
    // TODO: return camera matrix 
    pResult = this->_pResult;

    return true;
}

// void CameraCalibration::enqueueNotif(TaskNotification* ptr)
// {
//     _queue.enqueueNotification(ptr);
// }

// void CameraCalibration::joinAllNotif()
// {
//     _queue.wakeUpAll();
// }
