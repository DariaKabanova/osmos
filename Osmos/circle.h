//
//  Сircle.h
//  Osmos
//
//  Created by Дарья Кабанова on 12.06.13.
//  Copyright (c) 2013 Дарья Кабанова. All rights reserved.
//

#ifndef __Osmos___ircle__
#define __Osmos___ircle__

#define COUNT_OF_COLORS 3
#define WINDOW_WIDTH    512
#define WINDOW_HEIGHT   512

#include <iostream>
#include <algorithm>
#include <math.h>
#include <OpenGL/OpenGL.h>

class Circle {
public:
    Circle() {};
    Circle(GLfloat x, GLfloat y, GLfloat radius)
    {        
        this->x=x;
        this->y=y;
        this->radius=radius;

    }
    ~Circle() {};
    
    // Нарисовать объект
    void draw();
    
    // Установить новые параметры для объекта
    void setNewParameters(GLfloat dx, GLfloat dy, GLfloat radius) {
        this->x=dx;
        this->y=dy;
        this->radius+=radius;
    }
    
    // Работа со скоростью объекта
    virtual void move(GLfloat x, GLfloat y) = 0;
    
    // Отталкивание от стен
    void hitTheWall(GLfloat newX, GLfloat newY);
    
    // Проверка поглощения объекта
    int capture(Circle *circle);
    
    // Изменить направление скорости, если радиус circle больше, чем у this
    void changeDirection(Circle * circle) {
        if (circle->getRadius()>radius) { // Убегает, если больше
            if ((x-circle->getX()<0 && speedX>0) || (x-circle->getX()>0 && speedX<0)) speedX*=-1;
            if ((y-circle->getY()<0 && speedY>0) || (y-circle->getY()>0 && speedY<0)) speedY*=-1;
        }
    }
    
    // Расстояние до другого объекта
    const GLfloat getDistance(Circle *circle) {
        return sqrtf((x-circle->x)*(x-circle->x)+(y-circle->y)*(y-circle->y));
    }
    
    // Площадь объекта
    const GLfloat getSquare() {
        return radius*radius*M_PI;
    }
    
    // Радиус
    const GLfloat getRadius() {
        return radius;
    }
    
    // Установить цвет
    void setColor(GLfloat *color) {
        std::copy(color, color + COUNT_OF_COLORS, this->color);
    }
    
    // Установить цвет, который зависит от размера объекта
    void setColor(GLfloat minRadius, GLfloat maxRadius, GLfloat *minColor, GLfloat *maxColor);
    
    // Получить разницу площадей при уменьшении диаметра
    GLfloat getTheDifferenceSquares(GLfloat dRadius) {
        GLfloat lastSquare=getSquare();
        this->radius-=dRadius;
        return lastSquare-getSquare();
    }
    
    // Увеличить площадь объекта на deltaSquare
    void increaseSquare(GLfloat dSquare) {
        radius = sqrtf((getSquare() + dSquare)/M_PI);
    }
    
    // Перемещение объекта
    virtual void motion() = 0;
    
    // Возратить координаты объекта
    const GLfloat getX() {return x;}
    const GLfloat getY() {return y;}
    
    
    
protected:
    GLfloat x;                         
    GLfloat y;
    GLfloat radius;                 /* радиус объекта */
    GLfloat color[COUNT_OF_COLORS]; /* цвет объекта */
    GLfloat speedX=0.0;             /* проекция скорости объекта на ось X */
    GLfloat speedY=0.0;             /* проекция скорости объекта на ось Y */
    
};

class CircleRival: public Circle  {
public:
    CircleRival (GLfloat x, GLfloat y, GLfloat radius): Circle (x, y, radius) {};
    
    // Работа со скоростью объекта
    void move(GLfloat x, GLfloat y) {
        speedX=x;
        speedY=y;
    }
    
    // Перемещение объекта
    void motion();
    
    
};

class CircleUser: public Circle {
public:
    CircleUser (GLfloat x, GLfloat y, GLfloat radius): Circle (x, y, radius) {};
    
    // Работа со скоростью объекта
    void move(GLfloat x, GLfloat y);
    
    // Перемещение объекта
    void motion();
protected:
    const GLfloat massIndex=50;  /* коэффициент для получения массы при помощи радиуса */
    GLfloat deceleration=0.0;       /* коэффициент замедления */
};



#endif /* defined(__Osmos___ircle__) */
