//
//  glFunction.hpp
//  opencv_opengl
//
//  Created by ZENJU Daisuke on 2015/10/08.
//  Copyright © 2015年 ZENJU Daisuke. All rights reserved.
//

#ifndef glFunction_hpp
#define glFunction_hpp

#include <iostream>
#include <GLUT/GLUT.h>
#include <opencv2/opencv.hpp>

void readCSV(std::string filepass);
void display(void);
void keyboard(unsigned char key, int x, int y);
void captureDraw(cv::VideoCapture capture);
void resize(int w, int h);
double axisRatio(int point, int max);

#endif /* glFunction_hpp */
