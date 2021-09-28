//
// Created by FY XUE on 2021/2/1.
//

#include "car_status.hpp"
using namespace cv;
using namespace std;
[[noreturn]] void car_status(int camera_id, std::vector<CarStatusData>& msg_pool, std::mutex& locker){
    VideoCapture capture;
    capture.open(camera_id);// 打开摄像头, 默认摄像头captureIndex=0
//cap.open("test_02.wmv");
    if( !capture.isOpened() )
        return ;
    capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    capture.set(CV_CAP_PROP_FPS, 10);
    Mat prevgray, gray, flow, frame;

    //calcOpticalFlowFarneback(prevgray, gray, flow, 0.5, 3, 15, 3, 5, 1.2, 0); //传入两帧
    //稠密光流

    capture>>frame;
    cvtColor(frame, gray, CV_BGR2GRAY);
    if( prevgray.data )
    {
        calcOpticalFlowFarneback(prevgray, gray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
        //auto *newstatus=new CarStatusData();
        CarStatusData newstatus;
        newstatus.set_car_status(motionjudge(flow));
        msg_pool.push_back(newstatus);
    }
    std::swap(prevgray, gray);

}

bool motionjudge(Mat flow){
    //EFFECT:judge if more than 90% of pixels are moving (direction not considered)
    int cnt=0;
    for (int i= 0; i < flow.rows; ++i)
    {
        for (int j = 0; j < flow.cols; ++j)
        {
            Vec2f flow_at_point = flow.at<Vec2f>(i, j);
            float fx = flow_at_point[0];
            float fy = flow_at_point[1];
            if(fx*fx+fy*fy>=100) cnt++;  //100 is rough forecast value
        }
    }
    return cnt > 640 * 480 * 0.9;
}