//
// Created by FY XUE on 2021/2/1.
//
#include <data.hpp>
#include <error_flags.hpp>

BaseData::BaseData(){
    flag = E_NULL;
    camera_id = -1;
    frames = std::vector<CvImage>();
}

BaseData::~BaseData() {
    return;
}

void BaseData::clear_error() {
    flag = E_FINE;
}

void BaseData::add_error(int flag) {
    this->flag = this->flag & flag;
}

void BaseData::add_image(CvImage image) {
    frames.push_back(image);
}

int BaseData::get_flag() {
    return flag;
}

int BaseData::get_camera_id() {
    return camera_id;
}

std::vector<CvImage> BaseData::get_frames() {
    return frames;
}

void BaseData::set_timestamp(long long timestamp) {
    this->timestamp = timestamp;
}

long long BaseData::get_timestamp() {
    return timestamp;
}

void BaseData::set_camera_id(int camera_id) {
    this->camera_id = camera_id;
}

CarStatusData::CarStatusData() {
    this->flag = E_CAR_STATUS;
    this->speed = -1.0;
    this->car_status = -1;
    this->camera_id = -1;
    this->frames = std::vector<CvImage>();
}

void CarStatusData::set_car_status(int car_status) {
    this->car_status = car_status;
}

void CarStatusData::set_speed(float speed) {
    this->speed = speed;
}

int CarStatusData::get_car_status() {
    return car_status;
}

float CarStatusData::get_speed() {
    return speed;
}

