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
#include <memory>


class Field {
private:
    std::vector<std::shared_ptr<Circle>> circles;
    
public:
    Field(int countOfRivals,GLfloat *userColor, GLfloat *minColor, GLfloat *maxColor);
    ~Field() {
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
    int countOfRivals;                  /* количество противников */
    
    
    
};


#endif /* defined(__Osmos__field__) */
