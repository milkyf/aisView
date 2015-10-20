//
//  ecef.hpp
//  opencv_opengl
//
//  Created by ZENJU Daisuke on 2015/10/16.
//  Copyright © 2015年 ZENJU Daisuke. All rights reserved.
//


#ifndef ecef_hpp
#define ecef_hpp


// "ECEF計算クラス"
// 緯度軽度高度 -> ECEF(x, y, z)変換
// ECEF(x, y, z)の二点間の距離計算
class  ECEF {
private:
    const double PI = 3.1415926535898;
    const double A	= 6378137.0;
    const double ONE_F = 298.257223563;
    const double B	= A * (1.0 - 1.0 / ONE_F);
    const double E2	 = (1.0 / ONE_F) * (2 - (1.0 / ONE_F));
    const double ED2 = E2 * A * A / (B * B);
    double NN(double p);
    
public:
    double x(double latitude, double longitude, double height);
    double y(double latitude, double longitude, double height);
    double z(double latitude, double longitude, double height);
    double dist(double x0, double y0, double z0, double x1, double y1, double z1);
};


class Ship {
private:
    // "deg -> radメソッド"
    double rad(double degree);
    // "rad -> degメソッド"
    double deg(double radian);
    // "象限の算出メソッド"
    int quadrand(double lat0, double long0, double lat1, double long1);
    
public:
    // "方位角計算メソッド"
    double angle(double lat0, double long0, double lat1, double long1, double distance);
    // "正船首方向距離(y)メソッド"
    double y(double distance, double shipAngle, double gazeDirection);
    // "正横方向距離(x)メソッド"
    double x(double distance, double shipAngle, double gazeDirection);
};






#endif /* ecef_hpp */