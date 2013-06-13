//
//  Сircle.cpp
//  Osmos
//
//  Created by Дарья Кабанова on 12.06.13.
//  Copyright (c) 2013 Дарья Кабанова. All rights reserved.
//

#include "circle.h"
#include "math.h"
#include <GLUT/GLUT.h>

#define WINDOW_WIDTH    512
#define WINDOW_HEIGHT   512

void Circle::draw() {
    
    // Установка текущего цвета
    glColor3fv(color);
    
    // количество секторов, образующих круг
    int n=(int)(radius);
    
    GLfloat angle;
    
    // Рисование круга
    
    glBegin(GL_POLYGON);
    
    for (int i=0; i<n; i++) {
        angle=2*M_PI*(float)i/n;
        glVertex2f(cosf(angle)*radius+x, sinf(angle)*radius+y);
    }
    glEnd();
}

// Проверка столкновений с границами окна
void Circle::hitTheWall(GLfloat newX, GLfloat newY) {
    if (newX-radius<0.0) {
        x = -newX+2*radius;
    }
    else if (newX+radius>WINDOW_WIDTH) {
        x=2*WINDOW_WIDTH-newX-2*radius;
    }
    else x=newX;
    if (newY-radius<0.0) {
        y = -newY+2*radius;
    }
    else if (newY+radius>WINDOW_HEIGHT) {
        y=2*WINDOW_WIDTH-newY-2*radius;
    }
    else y=newY;
   
}
 
void Circle::capture(Circle *circle) {

}
