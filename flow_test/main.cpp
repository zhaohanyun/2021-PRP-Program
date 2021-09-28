#include <iostream>
#include "opencv2/opencv.hpp"
#include <vector>
#include "data.hpp"
#include <thread>
#include <unistd.h>
#include <mutex>
#include <iostream>


//set(OpenCV_DIR D:\\Program Files (x86)\\opencv\\opencv\\mingw-build)
//find_package(OpenCV_REQUIRED)
//include_directories(${OpenCV_INCLUDE_DIRS})
//target_link_libraries(flow_test ${OpenCV_LIBS})
using namespace cv;
using namespace std;


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

void car_status(int camera_id, std::vector<CarStatusData>& msg_pool, Mutex& locker){
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


int main(int argc, char** argv){
    std::mutex locker_car_status;
    std::vector<CarStatusData> msg_pool_car_status;

    std::thread run_car_status(car_status, 0  /*change to your camera id*/, std::ref(locker_car_status), std::ref(msg_pool_car_status));

    while (true){
        sleep(5);
        locker_car_status.lock();
        std::cout << msg_pool_car_status.size() << " Messages!" << std::endl;
        for (int i = 0; i < msg_pool_car_status.size(); ++i) {
            std::cout << "idx: " << i << "\t->: " << msg_pool_car_status[i].get_speed() << std::endl;
        }
        msg_pool_car_status.clear();
        locker_car_status.unlock();
    }
    return 0;
}

