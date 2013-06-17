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
    Field(int countOfRivals, GLfloat windowWidth, GLfloat windowHeight, GLfloat *userColor, GLfloat *minColor, GLfloat *maxColor);
    ~Field() {
        for (std::vector<Circle *>::iterator i = circles.begin()+1; i != circles.end(); ++i)
            delete (CircleRival*)(*i);
        delete (CircleUser*)(*circles.begin());
        circles.clear();
    }
    // Перерисока объектов
    void draw();
    
    // Перемещение объектов и проверка поглощений
    int move();
    
    // Событие клика мышки
    void mouseClick(GLfloat dx, GLfloat dy);
    
    // Начать новую игру
    void startNewGame();
 
protected:
    GLfloat maxColor[COUNT_OF_COLORS];  /* цвет самого большого объекта */
    GLfloat minColor[COUNT_OF_COLORS];  /* цвет самого маленького объекта */
    GLfloat userColor[COUNT_OF_COLORS]; /* цвет пользовательского объекта */
    GLfloat windowWidth;                /* ширина окна */
    GLfloat windowHeight;               /* высота окна */
    int countOfRivals;                  /* количество противников */
    
    
    
};


#endif /* defined(__Osmos__field__) */
