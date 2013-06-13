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

#include <iostream>
#include <algorithm>
#include <math.h>
#include <OpenGL/OpenGL.h>

class Circle {
public:
    Circle() {};
    Circle(GLfloat x, GLfloat y, GLfloat radius, GLfloat *color)
    {        
        this->x=x;
        this->y=y;
        this->radius=radius;
        std::copy(color, color + COUNT_OF_COLORS, this->color);
        this->firstSpeedX=0.0;
        firstSpeedY=0.0;
        //memcpy(this->color,color,sizeof(GLfloat)*COUNT_OF_COLORS);
    }
    ~Circle() {};
    
    void draw(/*GLdouble x, GLdouble y*/);
    void setNewParameters(GLfloat dx, GLfloat dy, GLfloat radius) {
        this->x=dx;
        this->y=dy;
        this->radius+=radius;
    }
    virtual void move(GLfloat x, GLfloat y) = 0;
    void hitTheWall(GLfloat newX, GLfloat newY);
    int capture(Circle *circle);
    
    const GLfloat getDistance(Circle *circle) {
        return sqrtf((x-circle->x)*(x-circle->x)+(y-circle->y)*(y-circle->y));
    }
    
    const GLfloat getSquare() {
        return radius*radius*M_PI;
    }
    
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
    
    void motion();
    
protected:
    const GLfloat k=1.0;
    GLfloat del=0.0;
    GLfloat x;
    GLfloat y;
    GLfloat radius;
    GLfloat color[COUNT_OF_COLORS];
    GLfloat firstSpeedX;
    GLfloat firstSpeedY;
    
};

class CircleRival: public Circle  {
public:
    CircleRival (GLfloat x, GLfloat y, GLfloat radius, GLfloat *color): Circle (x, y, radius, color) {};
    void move(GLfloat x, GLfloat y) {
        firstSpeedX=x;
        firstSpeedY=y;
    }
};

class CircleUser: public Circle {
public:
    CircleUser (GLfloat x, GLfloat y, GLfloat radius, GLfloat *color): Circle (x, y, radius, color) {};
    void move(GLfloat x, GLfloat y) { //координаты клика
        GLfloat Sx=2*this->x-x;
        GLfloat Sy=2*this->y-y;
        GLfloat S=sqrtf(Sx*Sx+Sy*Sy);
        
        del=0;
        
        GLfloat temp_x=sqrtf(2*S/k/radius)*x/(x*x+y*y);
        GLfloat temp_y=sqrtf(2*S/k/radius)*y/(x*x+y*y);
        
        if (this->x-x<0) temp_x*=-1;
        if (this->y-y<0) temp_y*=-1;
        
        firstSpeedX+=temp_x;
        firstSpeedY+=temp_y;

    }
};



#endif /* defined(__Osmos___ircle__) */
