//
// Created by FY XUE on 2021/2/1.
//
#include "car_status.hpp"
#include <iostream>
#include "opencv4/opencv2/opencv.hpp"

using namespace cv;
using namespace std;

bool motionjudge(Mat flow);

void car_status(int camera_id, std::vector <CarStatusData> &msg_pool, std::mutex &locker/*, VideoCapture &capture*/) {
    VideoCapture capture;
    //VideoCapture outputCapture;
    //capture.open(camera_id);
    capture.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    capture.open("/home/zhaohanyun/Desktop/git_cv/cvas/moving.mp4");
    if(!capture.isOpened()) {
        cerr << "can not open camera" << endl;
    }

    //cout<<capture.get(cv::CAP_PROP_FRAME_WIDTH);


//    enum  	cv::InterpolationFlags {
//        cv::INTER_NEAREST = 0,
//        cv::INTER_LINEAR = 1,
//        cv::INTER_CUBIC = 2,
//        cv::INTER_AREA = 3,
//        cv::INTER_LANCZOS4 = 4,
//        cv::INTER_LINEAR_EXACT = 5,
//        cv::INTER_NEAREST_EXACT = 6,
//        cv::INTER_MAX = 7,
//        cv::WARP_FILL_OUTLIERS = 8,
//        cv::WARP_INVERSE_MAP = 16
//    }
    Mat prevgray, gray, flow, cflow, frame,inframe;
    static int framecnt=0;
    while(true) {
        //outputCapture >> frame;
        capture >> inframe;
        if(inframe.total()<=0) {cout<<"end "<<framecnt<<endl; break;}
        resize(inframe, frame, cv::Size(320,240), 0, 0,1);
        cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        //imshow("original", frame);
        if (prevgray.data) {
            calcOpticalFlowFarneback(prevgray, gray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);//optical_flow method
            cvtColor(prevgray, cflow, cv::COLOR_GRAY2BGR);

            CarStatusData newstatus;
            newstatus.set_car_status(motionjudge(flow));
            if (!msg_pool.empty()) {
                msg_pool.clear();
            }
            //if (newstatus.get_car_status() == 1) {
                msg_pool.push_back(newstatus);
            //}

        }
        std::swap(prevgray, gray);
        if (waitKey(10) >= 0)
            break;

    }
    capture.release();
}

bool motionjudge(Mat flow){
    //EFFECT:judge if more than 50% of pixels are moving (direction not considered)
    int cnt=0;
    //cout<<flow.rows<<" rows"<<flow.cols<<" cols"<<endl;
    for (int i= 0; i < flow.rows; ++i)
    {
        for (int j = 0; j < flow.cols; ++j)
        {
            Vec2f flow_at_point = flow.at<Vec2f>(i, j);
            float fx = flow_at_point[0];
            float fy = flow_at_point[1];
            // cout<<fx<<" "<<fy<<endl;
            if(fx*fx+fy*fy>=0.25) ++cnt;  //not sure
        }
    }
    //cout<<cnt<<endl;
    return cnt > flow.rows * flow.cols * 0.5;
}

void compress_test(int camera_id, std::vector <CarStatusData> &msg_pool, std::mutex &locker,double compressRate) {
    VideoCapture capture;
    VideoCapture captureCom;
    capture.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    capture.open("/home/zhaohanyun/Desktop/git_cv/cvas/moving.mp4");
    captureCom.open("/home/zhaohanyun/Desktop/git_cv/cvas/movingCom.mp4");
    if(!capture.isOpened()) {
        cerr << "can not open camera" << endl;
    }
    Mat prevgray, gray, flow, cflow, frame,  inframe;
    Mat prevgrayCom, grayCom, flowCom, cflowCom,frameCompressed, inframeCom;
    double framecnt=0;
    double equalcnt=0;
    while(true) {
        //outputCapture >> frame;
        capture >> inframe;
        captureCom >> inframeCom;
        if(inframe.total()<=0) {cout<<"totol sample frame:"<<framecnt<<endl; cout<<"rate:"<<compressRate<<" accuracy:"<<equalcnt/framecnt*100<<"%"<<endl; break;}
        resize(inframe, frame, cv::Size(640,480), 0, 0,1);
        //resize(frame,frameCompressed,cv::Size(640*compressRate,480*compressRate),0,0,1);
        resize(inframeCom,frameCompressed,cv::Size(640,480),0,0,1);
        cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cvtColor(frameCompressed, grayCom, cv::COLOR_BGR2GRAY);
        //imshow("original", frame);
        if (prevgray.data && prevgrayCom.data) {
            framecnt++;
            calcOpticalFlowFarneback(prevgray, gray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);//optical_flow method
            cvtColor(prevgray, cflow, cv::COLOR_GRAY2BGR);
            calcOpticalFlowFarneback(prevgrayCom, grayCom, flowCom, 0.5, 3, 15, 3, 5, 1.2, 0);//optical_flow method
            cvtColor(prevgrayCom, cflowCom, cv::COLOR_GRAY2BGR);

            //cout<<"origin:"<<motionjudge(flow)<<" compressed:"<<motionjudge(flowCom)<<endl;
            if (motionjudge(flow)==motionjudge(flowCom)) equalcnt++;
        }
        std::swap(prevgray, gray);
        std::swap(prevgrayCom,grayCom);
//        if (waitKey(10) >= 0)
//            break;

    }
    capture.release();
}

