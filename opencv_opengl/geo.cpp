//
//  ecef.cpp
//  opencv_opengl
//
//  Created by ZENJU Daisuke on 2015/10/16.
//  Copyright © 2015年 ZENJU Daisuke. All rights reserved.
//

#include "geo.hpp"
#include <iostream>
#include <math.h>

// ECEFを計算する上で必要な式
double ECEF::NN(double p) {
    return (A / sqrt(1.0 - (E2) * (sin(p * PI / 180.0) * (sin(p * PI / 180.0) ))));
}

// 緯度経度高度をxに変換する
double ECEF::x(double latitude, double longitude, double height) {
    return (NN(latitude)+height) * cos(latitude * PI / 180) * cos(longitude * PI / 180);
}

// 緯度経度高度をyに変換する
double ECEF::y(double latitude, double longitude, double height) {
    return (NN(latitude)+height) * cos(latitude * PI / 180) * sin(longitude * PI / 180);
}

// 緯度経度高度をzに変換する
double ECEF::z(double latitude, double longitude, double height) {
    return (NN(latitude) * (1 - E2) + height) * sin(latitude * PI / 180);
}

// 二点間(x, y, z)の距離を求める(ユークリッド距離)
double ECEF::dist(double x0, double y0, double z0, double x1, double y1, double z1) {
    return sqrt(pow(x1 - x0, 2.0) + pow(y1 - y0, 2.0) + pow(z1 - z0, 2.0));
}


// 二点間の緯度と距離から方位角を求める
double Ship::angle(double lat0, double long0, double lat1, double long1, double distance) {
    double dLat = (lat1 - lat0) * 1852 * 60;
    double theta = fabs(deg(asin(dLat / distance)));
    
    int flag = quadrand(lat0, long0, lat1, long1);
    switch (flag) {
        // 第一象限
        case 1:
            theta = 90.0 - theta;
            break;
        // 第二象限
        case 2:
            theta = 90.0 + theta;
            break;
        // 第三象限
        case 3:
            theta = 270.0 - theta;
            break;
        // 第四象限
        case 4:
            theta = 360.0 - theta;
        default:
            break;
    }
    
    return theta;
}


// 二点間をベクトル化した時の象限の算出を行う
int Ship::quadrand(double lat0, double long0, double lat1, double long1) {
    int flag;
    double dLong = long1 - long0;
    double dLat = lat1 - lat0;
    if ((long1 > 90) && (long0 < 90)) {
        dLong *= (-1);
    }
    
    if (dLong >= 0) {
        if (dLat > 0)
            flag = 1;
        else
            flag = 4;
    } else {
        if (dLat > 0)
            flag = 2;
        else
            flag = 3;
    }
    
    return flag;
}


// "degree -> radian変換"
double Ship::rad(double degree) {
    const double PI = 3.1415926535898;
    return degree * PI / 180.0;
}

// "radian -> degree変換"
double Ship::deg(double radian) {
    const double PI = 3.1415926535898;
    return radian * 180.0 / PI;
}


// "正船首方向距離(y)メソッド"
double y(double distance, double shipAngle, double gazeDirection) {
    double theta = gazeDirection - shipAngle;
    double y = distance * cos(theta);
    return y;
}


// "正横方向距離(x)メソッド"
double x(double distance, double shipAngle, double gazeDirection) {
    double theta = gazeDirection - shipAngle;
    double x = distance * sin(theta);
    if (theta < 0)
        x *= (-1);
    return x;
}