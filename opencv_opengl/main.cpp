//
//  main.cpp
//  opencv_opengl
//
//  Created by ZENJU Daisuke on 2015/09/30.
//  Copyright © 2015年 ZENJU Daisuke. All rights reserved.
//

#include <iostream>
#include <math.h>
#include "geo.hpp"
#include "ray.hpp"


// カメラパラメータ(focalLength[m], ImageSensor Size x[mm], y[mm])
typedef struct {
    double focalLength = 18 * pow(10, -3);
    double x = 23.5 * pow(10, -3);
    double y = 15.6 * pow(10, -3);
} camera_t;

// 撮影ポイントパラメータ(latitude, longitude, height[m])
typedef struct {
    double latitude = 35.311755;
    double longitude = 139.785922;
    double height = 23.0;
    double direction = 180.0;
} own_t;

// イメージパラメータ(width[px], height[px], horizon[px])
typedef struct {
    int width = 1920;
    int height = 1080;
    int horizon = 596;
} picture_t;


// 船舶画像情報 構造体
typedef struct {
    int mmsi;
    int x;
    int y;
} shipPx_t;


shipPx_t shipPixel(int mmsi, double otherLatitude,
                 double otherLongitude, double otherHeight,
                 camera_t camera, own_t own, picture_t picture) {
    ECEF ecef;
    Ship ship;
    Ray ray;
    
    //camera_t camera;
    //own_t own;
    //picture_t picture;
    shipPx_t shipPx;
    
    double x0 = ecef.x(own.latitude, own.longitude, own.height);
    double y0 = ecef.y(own.latitude, own.longitude, own.height);
    double z0 = ecef.z(own.latitude, own.longitude, own.height);
    double x1 = ecef.x(otherLatitude, otherLongitude, otherLongitude);
    double y1 = ecef.y(otherLatitude, otherLongitude, otherLongitude);
    double z1 = ecef.z(otherLatitude, otherLongitude, otherLongitude);
    
    double distraction = ecef.dist(x0, y0, z0, x1, y1, z1);
    double shipAngle = ship.angle(own.latitude, own.longitude,
                                  otherLatitude, otherLongitude, distraction);
    double shipY = ship.y(distraction, shipAngle, own.direction);
    double shipX = ship.x(distraction, shipAngle, own.direction);
    
    double xImageSensor = ray.xImageSensor(shipX, shipY,
                                           camera.focalLength, camera.x);
    double xPixel = ray.xPixel(xImageSensor, camera.x, picture.width);
    double yPixel = ray.yPixel(shipY, own.height, picture.horizon,
                               camera.focalLength,
                               camera.y / (double)picture.height);
    
    shipPx.mmsi = mmsi;
    shipPx.x = xPixel;
    shipPx.y = yPixel;
    
    return shipPx;
}


int main() {
    camera_t camera;
    own_t own;
    picture_t picture;
    shipPx_t shipPx;
    
    double latitude = 35.262994;
    double longitude = 139.766697;
    double height = 0.0;
    
    // 二点間の緯度経度高度から距離を求める
    shipPx = shipPixel(1234567, latitude, longitude, height, camera, own, picture);
    std::cout << "[mmsi, x, y] = [" << shipPx.mmsi << ", " << shipPx.x
                                    << ", " << shipPx.y << "]" << std::endl;
    
    
    
    return 0;
}