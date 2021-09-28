//
// Created by FY XUE on 2021/1/17.
//

#ifndef CVAS_ERROR_FLAGS_HPP
#define CVAS_ERROR_FLAGS_HPP

#define E_FINE 0x0

#define E_CAMERA0 0x1
#define E_CAMERA1 0x2
#define E_CAMERA2 0x4
#define E_CAMERA3 0x8

#define E_DETECTOR 0x10
#define E_ARC_FACE 0x20
//#define E_ 0x40
//#define E_ 0x80
//
//#define E_ 0x100
//#define E_ 0x200
//#define E_ 0x400
//#define E_ 0x800

#define E_PERSON_STATUS 0x1000
#define E_CAR_STATUS 0x2000
#define E_DUSTBIN_STATUS 0x4000
#define E_NULL 0x8000 /*None Content, every thing is default*/

#endif //CVAS_ERROR_FLAGS_HPP
