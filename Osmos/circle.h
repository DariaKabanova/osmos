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
    void hitTheWall();
    
protected:
    GLfloat x;
    GLfloat y;
    GLfloat radius;
    GLfloat color[COUNT_OF_COLORS];
    
};

class CircleRival: public Circle  {
public:
    CircleRival (GLfloat x, GLfloat y, GLfloat radius, GLfloat *color): Circle (x, y, radius, color) {};
    virtual void move(GLfloat x, GLfloat y) {
        this->x+=x;
    }
};

class CircleUser: public Circle {
public:
    CircleUser (GLfloat x, GLfloat y, GLfloat radius, GLfloat *color): Circle (x, y, radius, color) {};
    void move(GLfloat x, GLfloat y) {
        this->x+=this->x-x;
        this->y+=this->y-y;
    }
};

//const


#endif /* defined(__Osmos___ircle__) */
