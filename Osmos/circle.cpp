//
//  Сircle.cpp
//  Osmos
//
//  Created by Дарья Кабанова on 12.06.13.
//  Copyright (c) 2013 Дарья Кабанова. All rights reserved.
//

#include "circle.h"
#include <GLUT/GLUT.h>



// Рисование объекта
void Circle::draw() {
    
    // Установка текущего цвета
    glColor3fv(color);
    
    // Рисование круга при помощи полигона
    /*
    // количество секторов, образующих круг
    int n=(int)(radius);
    
    GLfloat angle;
      
    glBegin(GL_POLYGON);
    
    for (int i=0; i<n; i++) {
        angle=2*M_PI*(float)i/n;
        glVertex2f(cosf(angle)*radius+x, sinf(angle)*radius+y);
    }
    glEnd();*/
    
    // Рисования круга при квадрического объекта
    
    glTranslatef(x, y, 0.0);
    
    GLUquadricObj *quadricObj=gluNewQuadric();
    GLint slices=(GLint)(radius/4+10);// количество граней правильного многоугольника
    
    gluDisk (quadricObj, 0.0, radius, slices, 1);
    gluDeleteQuadric (quadricObj);
    
    glTranslatef(-x, -y, 0.0);
    
}

// Проверка столкновений с границами окна
void Circle::hitTheWall(GLfloat newX, GLfloat newY) {
    
    if (newX-radius<0.0) {
        x = -newX+2*radius;
        speedX*=-1;
    }
    else if (newX+radius>WINDOW_WIDTH) {
        x=2*WINDOW_WIDTH-newX-2*radius;
        speedX*=-1;
    }
    else x=newX;
    if (newY-radius<0.0) {
        y = -newY+2*radius;
        speedY*=-1;
    }
    else if (newY+radius>WINDOW_HEIGHT) {
        y=2*WINDOW_WIDTH-newY-2*radius;
        speedY*=-1;
    }
    else y=newY;
    
    
}

// Проверка поглощений объектов
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

// Установить цвет, который зависит от размера объекта
void Circle::setColor(GLfloat minRadius, GLfloat maxRadius, GLfloat *minColor, GLfloat *maxColor) {
    GLfloat valueOfNormalized=0.5;
    if (minRadius!=maxRadius)
        valueOfNormalized=(radius-minRadius)/(maxRadius-minRadius);
    for (int i=0; i<3; i++)
        color[i]=valueOfNormalized*(maxColor[i] - minColor[i])+minColor[i];
}

// Перемещение объекта
void CircleUser::motion() {
    GLfloat lx,ly;// Путь, совершенный за время
    deceleration+=0.0001;
    
    lx=speedX/exp(deceleration);//+(-radius*k*x/(x*x+y*y))*t*t/2;
    ly=speedY/exp(deceleration);//+(-radius*k*y/(x*x+y*y))*t*t/2;
        
    hitTheWall(lx+x, ly+y);

}

// Работа со скоростью объекта
void CircleUser::move(GLfloat x, GLfloat y) { //координаты клика
    GLfloat Sx=2*this->x-x;
    GLfloat Sy=2*this->y-y;
    GLfloat S=sqrtf(Sx*Sx+Sy*Sy);
    
    deceleration=0.0;
    
    GLfloat temp_x=sqrtf(2*S/massIndex/radius)*x/(x*x+y*y);
    GLfloat temp_y=sqrtf(2*S/massIndex/radius)*y/(x*x+y*y);
    
    if (this->x-x<0) temp_x*=-1;
    if (this->y-y<0) temp_y*=-1;
    
    speedX+=temp_x;
    speedY+=temp_y;
}

// Перемещение объекта
void CircleRival::motion() {
    
    GLfloat lx,ly;
    GLfloat deceleration=0.0001;

    lx=speedX/exp(deceleration)/radius;
    ly=speedY/exp(deceleration)/radius;
    
    hitTheWall(lx+x, ly+y);
    
}
