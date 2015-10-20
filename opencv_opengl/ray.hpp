//
//  ray.hpp
//  opencv_opengl
//
//  Created by ZENJU Daisuke on 2015/10/20.
//  Copyright © 2015年 ZENJU Daisuke. All rights reserved.
//

#ifndef ray_hpp
#define ray_hpp

class Ray{
private:
    
public:
    /****** 三浦さんプログラム使用 *************
    // イメージセンサ内 x方向距離[mm]
    double xImageSensor(double x, double y, double focalLength, double xPx);
    
    // イメージセンサ内 x方向距離からpx数 算出
    int xPixel(double xImageSensor, double widthImageSensor, int width);
    
    // イメージセンサ内 y方向距離[mm]
    int yPixel(double y, double height, double horizon, double focalLength, double px);
     ********************************/
    
    int shipPixel(double position, double z, double focalLength, double sensorSize, double imageLength);
};

#endif /* ray_hpp */
