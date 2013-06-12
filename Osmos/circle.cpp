//
//  Сircle.cpp
//  Osmos
//
//  Created by Дарья Кабанова on 12.06.13.
//  Copyright (c) 2013 Дарья Кабанова. All rights reserved.
//

#include "circle.h"
#include "math.h"
//#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

void Circle::Draw() {
    
    // Установка текущего цвета
    glColor3fv(color);
    
    // смещение центра круга
    glTranslatef(x, y, 0.0);
    
    // количество секторов, образующих круг
    int n=(int)(radius/2);
    
    GLfloat dy=0.0;
    GLfloat dx=radius;
    GLfloat d=0.0;
    
    // Рисование круга
    
    glBegin(GL_TRIANGLES);

    for (int i=0; i<n; i++) {
    
        glVertex2f(0.0, 0.0);
        glVertex2f(dx, dy);
        
        d=sinf(M_PI*2.0/(float)n*(i+1));
        dy=d*radius;
        dx=sqrtf(radius*radius-dy*dy);
        
        if (d<sinf(M_PI*2.0/(float)n*(i)))
            dx*=-1.0;
            
        glVertex2f(dx,dy);
        
    }
    glEnd();
    
    glTranslatef(x, y, 0.0);
}

void Circle::Move() {
    glTranslatef(10, 10,0);
}