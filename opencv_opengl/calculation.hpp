//
//  calculation.hpp
//  opencv_opengl
//
//  Created by ZENJU Daisuke on 2015/10/23.
//  Copyright © 2015年 ZENJU Daisuke. All rights reserved.
//

#ifndef calculation_hpp
#define calculation_hpp

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

struct aivdm_type1 {
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


class Calc{
private:
    // AIVDM(Type1)のデータを読み込む, string型にsetする
    aivdm_type1 readAivdmType1(std::string str);
    
public:
    std::map<int, aivdm_type1> timeMap(int time, std::vector<aivdm_type1> type1);
    std::vector<aivdm_type1> readFile(std::string filepass);
    
    std::map<int, aivdm_type1> readMap(int time, std::string filepass) {
        std::vector<aivdm_type1> type1;
        std::map<int, aivdm_type1> data;
        
        type1 = readFile(filepass);
        data = timeMap(time, type1);
        
        return data;
    }
    
    int timeStamp(int msec, int startTime);
    
};

#endif /* calculation_hpp */
