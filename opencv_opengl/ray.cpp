//
//  ray.cpp
//  opencv_opengl
//
//  Created by ZENJU Daisuke on 2015/10/20.
//  Copyright © 2015年 ZENJU Daisuke. All rights reserved.
//

#include "ray.hpp"
#include <iostream>
#include <math.h>


// イメージセンサ内 x方向距離[m]
double Ray::xImageSensor(double x, double y, double focalLength, double xPx) {
    double xHalf = (focalLength * x) / y;
    double xImg = xHalf + (xPx / 2.0);
    return xImg;
}
    
// イメージセンサ内 x方向距離からpx数 算出
int Ray::xPixel(double xImageSensor, double widthImageSensor, int width) {
    double fpx = xImageSensor / widthImageSensor * width;
    int px = ceil(fpx);
    return px;
}

// イメージセンサ内 y方向距離からpx数 算出
int Ray::yPixel(double y, double height, double horizon, double focalLength, double px) {
    double theta = atan(height / y);
    double a = atan2(horizon * px, focalLength);
    double b = theta + a;
    int yImg = ceil((focalLength * tan(b)) / px);
    return yImg;
}