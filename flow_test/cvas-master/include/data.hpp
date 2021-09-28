//
// Created by FY XUE on 2021/2/1.
//

#ifndef CVAS_DATA_HPP
#define CVAS_DATA_HPP

#include <vector>
#include <opencv2/opencv.hpp>

typedef unsigned char byte;


class BaseData{
protected:
    int flag;
    long long timestamp;
    std::vector<CvImage> frames;
    int camera_id;
public:
    BaseData();
    ~BaseData();
    void add_image(CvImage image);
    void add_error(int error);
    void set_timestamp(long long timestamp);
    void set_camera_id(int camera_id);
    void clear_error();
    int get_flag();
    int get_camera_id();
    std::vector<long long> get_frames();
    long long get_timestamp();
};


class CarStatusData: public BaseData{
private:
    int car_status;
    float speed;
public:
    CarStatusData();
    void set_car_status(int car_status);
    void set_speed(float speed);
    int get_car_status();
    float get_speed();
};


#endif //CVAS_DATA_HPP
