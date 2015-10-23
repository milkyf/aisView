//
//  main.cpp
//  opencv_opengl
//
//  Created by ZENJU Daisuke on 2015/09/30.
//  Copyright © 2015年 ZENJU Daisuke. All rights reserved.
//

#include <iostream>
#include "gl.hpp"


// ディスプレイサイズ
#define displayWidth 1280
#define displayHeight 800

// mainメソッド
int main(int argc, char *argv[]) {
    
    readCSV("/Users/zenju/Documents/XcodeProject/aivdm/dec1.csv");
    
    glutInit(&argc, argv);
    
    // OpenGL : Window設定
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(displayWidth, displayHeight);
    glutCreateWindow("AIS Viewer");
    
    // OpenGL : 任意関数
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(resize);
    
    // OpenGL : ループ
    glutMainLoop();
    
    return 0;
}