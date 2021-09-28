//
// Created by FY XUE on 2021/2/1.
//

#ifndef CVAS_CAR_STATUS_HPP
#define CVAS_CAR_STATUS_HPP

#include <vector>
#include <data.hpp>
#include <mutex>

[[noreturn]] void car_status(int camera_id, std::vector<CarStatusData>& msg_pool, std::mutex& locker);

#endif //CVAS_CAR_STATUS_HPP
