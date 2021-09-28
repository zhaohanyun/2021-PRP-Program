//
// Created by FY XUE on 2021/1/17.
//
#include <vector>
#include <thread>
#include <unistd.h>
#include <car_status.hpp>
#include <iostream>


#pragma ide diagnostic ignored "EndlessLoop"
int main(int argc, char** argv){
    std::mutex locker_car_status;
    std::vector<CarStatusData> msg_pool_car_status;

    //std::thread run_car_status(car_status, 0 /*change to your camera id*/,std::ref(msg_pool_car_status), std::ref(locker_car_status));

    for(double i=1;i<10;i++){
        compress_test(0,std::ref(msg_pool_car_status), std::ref(locker_car_status),1-i/10);
    }
//    compress_test(0,std::ref(msg_pool_car_status), std::ref(locker_car_status),0.9);

//    while (true){
//        usleep(500000);
//        locker_car_status.lock();
//        //std::cout << msg_pool_car_status.size() << " Messages!" << std::endl;
//        for (int i = 0; i < msg_pool_car_status.size(); ++i) {
//            std::cout << "idx: " << i << "\t->: " << msg_pool_car_status[i].get_car_status() << std::endl;
//        }
//        msg_pool_car_status.clear();
//        locker_car_status.unlock();
//    }

}
