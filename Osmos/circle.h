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
    ~Circle() {}
    
    void Draw(/*GLdouble x, GLdouble y*/);
    void Move();
    void setNewParameters(GLfloat x, GLfloat y, GLfloat radius) {
        this->x=x;
        this->y=y;
        this->radius=radius;
    }
    
private:
    GLfloat x;
    GLfloat y;
    GLfloat radius;
    GLfloat color[COUNT_OF_COLORS];
    
};

//const


#endif /* defined(__Osmos___ircle__) */
