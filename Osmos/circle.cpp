//
//  Сircle.cpp
//  Osmos
//
//  Created by Дарья Кабанова on 12.06.13.
//  Copyright (c) 2013 Дарья Кабанова. All rights reserved.
//

#include "circle.h"
//#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

void Circle::Draw() {
    // Установка текущего цвета
    glColor3f(1, 0, 0);
    
    // Задание примитива
    glBegin(GL_TRIANGLES);
    
    // Установка вершин
    glVertex2f(10, 10);
    glVertex2f(250, 400);
    glVertex2f(400, 10);
    
    glEnd();
}

void Circle::Move() {
    glTranslatef(10, 10,0);
}