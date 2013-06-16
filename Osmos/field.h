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
    std::vector<Circle *> circles;
    
public:
    Field(int countOfObjects);
    ~Field() {circles.~vector();}
    void draw();
    int move();
    void mouseClick(GLfloat dx, GLfloat dy);
    void capture();
    
    GLfloat maxColor[3]={1.0,0.0,0.0};
    GLfloat minColor[3]={0.0,0.0,1.0};
    
    
};


#endif /* defined(__Osmos__field__) */
