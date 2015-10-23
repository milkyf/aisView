//
//  calc.cpp
//  opencv_opengl
//
//  Created by ZENJU Daisuke on 2015/10/24.
//  Copyright © 2015年 ZENJU Daisuke. All rights reserved.
//

#include "aivdm.hpp"


// AIVDM(Type1)のデータを読み込む, string型にsetする
type1 Aivdm::readType1(std::string str) {
    type1 nmea;
    
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


// AIVDM(type1)のCSVを読み込んで, 多重mapにする
std::multimap<int, type1> Aivdm::readMap(std::string filepass) {
    type1 nmea;
    std::multimap<int, type1> mp;
    
    std::ifstream ifs(filepass);
    if (ifs.fail()) {
        std::cerr << "Error : Can't open this file." << std::endl;
        exit(0);
    }
    
    std::string str;
    while (getline(ifs, str)) {
        nmea = readType1(str);
        mp.insert(std::make_pair(nmea.time, nmea));
    }
    ifs.close();
    
    return mp;
}


// 直近までの時間における最新のAIVDM情報(Key : MMSI)
std::map<int, type1> Aivdm::latestMp(int time, std::multimap<int, type1> mp) {
    type1 nmea;
    std::map<int, type1> latest;
    
    auto sitr = mp.upper_bound(time);
    
    for (auto citr = mp.begin(); citr != sitr; ++citr) {
        nmea = citr->second;
        int mmsi = nmea.mmsi;
        latest[mmsi] = nmea;
    }
    
    return latest;
}


// 経過時間を開始時刻からの時刻に変換
int Aivdm::timeStamp(int msec, int startTime) {
    int ss = msec / pow(10, 3);
    int h = (int)(ss / 3600);
    int m = (int)((ss - h * 3600) / 60);
    int s = (int)(ss - h * 3600 - m * 60);
    
    int hms = h * 10000 + m * 100 + s;
    int hhmmss = hms + startTime;
    return hhmmss;
}
/*
 
     auto itr = data.find(234226);
     if (itr != data.end()) {
     std::cout << itr->first << " " << itr->second.mmsi << std::endl;
     }
     
     auto mtr = data.upper_bound(234226);
     if (mtr != data.end()) {
     std::cout << mtr->first << " " << mtr->second.mmsi << std::endl;
     }
     
     while (itr != mtr) {
     std::cout << itr->first << " " << itr->second.mmsi << std::endl;
     ++itr;
     }
    
    
    auto itr = data.upper_bound(234426);
    
    for (auto btr = data.begin(); btr != itr; ++btr) {
        aivdm = btr->second;
        int mmsi = aivdm.mmsi;
        now[mmsi] = aivdm;
    }
    
    for (auto btr = now.begin(); btr != now.end(); ++btr) {
        std::cout << btr->first << " " << btr->second.time << std::endl;
    }
    
    
    return 0;
}*/