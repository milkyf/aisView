//
//  calc.hpp
//  opencv_opengl
//
//  Created by ZENJU Daisuke on 2015/10/24.
//  Copyright © 2015年 ZENJU Daisuke. All rights reserved.
//

#ifndef calc_hpp
#define calc_hpp

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <math.h>

struct type1 {
    int time;
    int messageType;
    int repeatIndicator;
    int mmsi;
    std::string navigationStatus;
    std::string rot;
    double sog;
    std::string positionAccuracy;
    double longitude;
    double latitude;
    double cog;
    int hdg;
    int timeStamp;
    std::string maneuverIndicator;
    std::string spare;
    std::string raimFlag;
    int radioStatus;
};



class Aivdm {
private:
    type1 readType1(std::string str);
public:
    std::multimap<int, type1> readMap(std::string filepass);
    std::map<int, type1> latestMp(int time, std::multimap<int, type1> mp);
    int timeStamp(int msec, int startTime);
};


#endif /* calc_hpp */
