
#ifndef __CAMERACALIBRATIONOPENCV_H__
#define __CAMERACALIBRATIONOPENCV_H__

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

namespace AIDoop
{
    namespace ObjectTracker
    {
        class OpencvCamCalib
        {
        public:
            OpencvCamCalib(int board_width, int board_height);

            void initialize();
            int findChessboard(Mat &view, bool reg = false);
            bool runCalibration();
            bool loadCalibrationData();

        private:
            const Size boardSize;
            const Size2f squareSize;
            vector<vector<Point2f>> imagePoints;
            Size imageSize;

            Mat _matCamera;
            Mat _matDistort;
        };
    }
}


#endif // __CAMERACALIBRATIONOPENCV_H__

