//
//  field.h
//  Osmos
//
//  Created by Дарья Кабанова on 12.06.13.
//  Copyright (c) 2013 Дарья Кабанова. All rights reserved.
//

#ifndef __Osmos__field__
#define __Osmos__field__

//#include <iostream>
#include <cstdlib>

#include "circle.h"
#include <vector>


class Field {
private:
    std::vector<Circle *> circles;// (51);
    
public:
    Field() {};
    //Field(int countOfObjects);
    Field(int countOfObjects, GLfloat windowWidth, GLfloat windowHeight, GLfloat *userColor, GLfloat *minColor, GLfloat *maxColor);
    ~Field() {}
    void draw();
    int move();
    void mouseClick(GLfloat dx, GLfloat dy);
    void capture();
    
    GLfloat maxColor[COUNT_OF_COLORS];//={1.0,0.0,0.0};
    GLfloat minColor[COUNT_OF_COLORS];//={0.0,0.0,1.0};
    GLfloat userColor[COUNT_OF_COLORS];
    
    
};


#endif /* defined(__Osmos__field__) */
