//
//  Сircle.cpp
//  Osmos
//
//  Created by Дарья Кабанова on 12.06.13.
//  Copyright (c) 2013 Дарья Кабанова. All rights reserved.
//

#include "circle.h"
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
        firstSpeedX*=-1;
    }
    else if (newX+radius>WINDOW_WIDTH) {
        x=2*WINDOW_WIDTH-newX-2*radius;
        firstSpeedX*=-1;
    }
    else x=newX;
    if (newY-radius<0.0) {
        y = -newY+2*radius;
        firstSpeedY*=-1;
    }
    else if (newY+radius>WINDOW_HEIGHT) {
        y=2*WINDOW_WIDTH-newY-2*radius;
        firstSpeedY*=-1;
    }
    else y=newY;
    
    
}
 
int Circle::capture(Circle *circle) {
    GLfloat intersectionValue=radius+circle->radius-getDistance(circle);
    if (intersectionValue>0.0) {
        if (radius>=circle->radius) 
            increaseSquare(circle->getTheDifferenceSquares(intersectionValue));
        else
            circle->increaseSquare(getTheDifferenceSquares(intersectionValue));
        if (radius<=0.0) return 1;
        if (circle->radius<=0.0) return 2;
    }
    return 0;
}

// перерисовка в каждый момент времени
void Circle::motion() {
    GLfloat lx,ly;// Путь, совершенный за время
    del+=0.0001;
    
    
    lx=firstSpeedX/exp(del);//+(-radius*k*x/(x*x+y*y))*t*t/2;
    ly=firstSpeedY/exp(del);//+(-radius*k*y/(x*x+y*y))*t*t/2;
    

    
    hitTheWall(lx+x, ly+y);

}
