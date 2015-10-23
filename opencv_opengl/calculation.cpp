//
//  calculation.cpp
//  opencv_opengl
//
//  Created by ZENJU Daisuke on 2015/10/23.
//  Copyright © 2015年 ZENJU Daisuke. All rights reserved.
//

#include "calculation.hpp"
#include <math.h>


// AIVDM(Type1)のデータを読み込む, string型にsetする
aivdm_type1 Calc::readAivdmType1(std::string str) {
    aivdm_type1 nmea;
    
    int i = 0;
    std::string tmp[17];
    std::istringstream stream(str);
    while(getline(stream,tmp[i],','))
        ++i;
    
    nmea.time = std::atoi(tmp[0].c_str());
    nmea.messageType = std::atoi(tmp[1].c_str());
    nmea.repeatIndicator = std::atoi(tmp[2].c_str());
    nmea.mmsi = std::atoi(tmp[3].c_str());
    nmea.navigationStatus = tmp[4];
    nmea.rot = tmp[5];
    nmea.sog = std::atof(tmp[6].c_str());
    nmea.positionAccuracy = tmp[7];
    nmea.longitude = std::atof(tmp[8].c_str());
    nmea.latitude = std::atof(tmp[9].c_str());
    nmea.cog = std::atof(tmp[10].c_str());
    nmea.hdg = std::atoi(tmp[11].c_str());
    nmea.timeStamp = std::atoi(tmp[12].c_str());
    nmea.maneuverIndicator = tmp[13];
    nmea.spare = tmp[14];
    nmea.raimFlag = tmp[15];
    nmea.radioStatus = std::atoi(tmp[16].c_str());
    
    return nmea;
}


std::vector<aivdm_type1> Calc::readFile(std::string filepass) {
    aivdm_type1 aivdm;
    std::vector<aivdm_type1> type1;
    
    // ファイル読み込み(AIVDM(Type1))
    std::ifstream ifs(filepass);
    if (ifs.fail()) {
        std::cerr << "Error : Can't open this file." << std::endl;
    }
    
    std::string str;
    while(getline(ifs,str))
    {
        aivdm = readAivdmType1(str);
        type1.push_back(aivdm);
    }
    ifs.close();
    
    return type1;
}


// 指定経過時間における全船舶の位置情報取得
std::map<int, aivdm_type1> Calc::timeMap(int time, std::vector<aivdm_type1> type1) {
    std::map<int, aivdm_type1> data;
    int t = timeStamp(time, type1[1].time);
    
    for (int i = 0; i < type1.size(); ++i) {
        if (type1[i].time == t) {
            int m = type1[i].mmsi;
            data[m] = type1[i];
        } else if (type1[i].time > t) {
            break;
        }
    }
    
    return data;
}


// 経過時間を開始時刻からの時刻に変換
int Calc::timeStamp(int msec, int startTime) {
    int ss = msec / pow(10, 3);
    int h = (int)(ss / 3600);
    int m = (int)((ss - h * 3600) / 60);
    int s = (int)(ss - h * 3600 - m * 60);
    
    int hms = h * 10000 + m * 100 + s;
    return hms;
}