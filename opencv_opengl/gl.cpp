//
//  glFunction.cpp
//  opencv_opengl
//
//  Created by ZENJU Daisuke on 2015/10/08.
//  Copyright © 2015年 ZENJU Daisuke. All rights reserved.
//

#include <math.h>
#include "geo.hpp"
#include "ray.hpp"
#include "gl.hpp"

/* グローバル変数 */

// カメラの場合
// Read Movie
//cv::VideoCapture capture(0);
cv::VideoCapture capture("/Users/zenju/Documents/seminar/AIS_GPS_Movie_20141113/Movie_originalData/001.mov");

// Set Window Size
int captureWidth = capture.get(CV_CAP_PROP_FRAME_WIDTH);
int captureHeight = capture.get(CV_CAP_PROP_FRAME_HEIGHT);

// Magnification Ratio
double widthMagnification;
double heightMagnification;

// 時間
int msec = 0;

// カメラパラメータ(focalLength[m], ImageSensor Size x[mm], y[mm])
typedef struct {
    double focalLength = 0.8 * pow(10, -3);
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
    int horizon = 540;
} picture_t;


// 船舶画像情報 構造体
typedef struct {
    int mmsi;
    int x;
    int y;
} shipPx_t;


// 船舶画像座標計算
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
    double shipZ = ship.z(distraction, shipAngle, own.direction);
    double shipX = ship.x(distraction, shipAngle, own.direction);
    
    /*
     double xImageSensor = ray.xImageSensor(shipX, shipY,
     camera.focalLength, camera.x);
     double xPixel = ray.xPixel(xImageSensor, camera.x, picture.width);
     double yPixel = ray.yPixel(shipY, own.height, picture.horizon,
     camera.focalLength,
     camera.y / (double)picture.height);
     */
    
    shipPx.mmsi = mmsi;
    shipPx.x = ray.shipPixel(shipX, shipZ, camera.focalLength, camera.x, picture.width);
    shipPx.y = ray.shipPixel(own.height, shipZ, camera.focalLength, camera.y, picture.height);
    
    return shipPx;
}


// openGL, openCV : 描画関数
void display(void) {
    
    camera_t camera;
    own_t own;
    picture_t picture;
    shipPx_t shipPx;
    
    // キャプチャ描画
    captureDraw(capture);
   
    // 水平線描画(紫)
    glColor3d(0.7, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2d(0, picture.horizon * heightMagnification);
    glVertex2d(captureWidth * widthMagnification, picture.horizon * heightMagnification);
    glEnd();
    
    
    
    
    double latitude = 35.262994;
    double longitude = 139.766697;
    double height = 0.0;
    
    // 二点間の緯度経度高度から距離を求める
    shipPx = shipPixel(1234567, latitude, longitude, height, camera, own, picture);
    std::cout << "[mmsi, x, y] = [" << shipPx.mmsi << ", " << shipPx.x
    << ", " << shipPx.y << "]" << std::endl;
    
    
    // 距離描画
    glColor3d(1.0, 0.0, 0.0);
    glPointSize(1.0);
    glBegin(GL_POINTS);
        glVertex2d(shipPx.x * widthMagnification, shipPx.y * heightMagnification);
    glEnd();
    
    
    glFlush();
    glutPostRedisplay();
}


// openGL : キーボード関数
void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'q':
        case 'Q':
        case '\033':
            exit(0);
            break;
            
        default:
            break;
    }
}


// openGL, openCV : キャプチャ & 描画関数
void captureDraw(cv::VideoCapture capture) {
    cv::Mat image;
    capture >> image;
    cv::flip(image, image, 0);
    cv::cvtColor(image, image, CV_BGR2RGB);
    
    glDrawPixels(image.cols, image.rows, GL_RGB, GL_UNSIGNED_BYTE, image.data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}


// openGL : リサイズ
void resize(int w, int h) {
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);
    
    // Calc Magnification
    widthMagnification = (double)w / (double)captureWidth;
    heightMagnification = (double)h / (double)captureHeight;
    glPixelZoom(widthMagnification, heightMagnification);
}


// 座標系変換(ウィンドウ -> ローカル)
double axisRatio(int point, int max) {
    double ratio = (double)point / (double)max;
    double answer = -1.0 + (ratio * 2.0);
    return answer;
}