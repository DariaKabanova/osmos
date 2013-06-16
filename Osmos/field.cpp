//
//  field.cpp
//  Osmos
//
//  Created by Дарья Кабанова on 12.06.13.
//  Copyright (c) 2013 Дарья Кабанова. All rights reserved.
//

#include "field.h"
#include <iostream>
#include <time.h>

Field::Field(int countOfObjects) {
    GLfloat colorRed[3]={1.0,0.0,0.0};
    GLfloat color[3]={0.8,0.0,1.0};
    
    // Задать игрока
    
    
    this->circles.push_back(new CircleUser (512/2,512/2,20.0,colorRed));

    GLfloat radiusRival=20.0;
    
    // Посчитать распределение соперников
    srand(time(0));
    for (int i=0; i<countOfObjects; i++) {

        bool t=true;
        GLfloat x,y;
        while (t) {
            t=false;
            
            x=GLfloat(std::rand()%(512-2*(int)radiusRival)+radiusRival);
            y=GLfloat(std::rand()%(512-2*(int)radiusRival)+radiusRival);
            for (std::vector<Circle *>::iterator j = circles.begin(); j != circles.end(); ++j) {
                if (sqrtf((x-(*j)->getX())*(x-(*j)->getX())+(y-(*j)->getY())*(y-(*j)->getY()))<2*radiusRival+10.0) {
                    t=true;
                    break;
                }
            }
        
        }
        // Записать в вектор соперников
        this->circles.push_back(new CircleRival (x,y,radiusRival,color));
        int multX=-1, multY=-1;
        if (rand()%2) multX=1;
        if (rand()%2) multY=1;
        this->circles.back()->move(0.1*multX,0.1*multY);
    }
    

}

void Field::draw() {
    for (std::vector<Circle *>::iterator i = circles.begin(); i != circles.end(); ++i)
        (*i)->draw();        
}

int Field::move() {
    std::vector<Circle *>::iterator n=circles.end();
    for (std::vector<Circle *>::iterator i = circles.begin(); i != n; ++i) {
        (*i)->motion();
        for (std::vector<Circle *>::iterator j = i+1; j != n; ++j) {
            // изменить направление скорости
            (*j)->changeDirection(*i);
            int flag=(*i)->capture(*j);
            if (flag==2)
            {
                circles.erase(j);
                n=circles.end();
                j--;
            }
            if (flag==1) {return 2;}// Поражение
        }        
    }
    // Проверка на победу
    GLfloat commonSquare=0.0;
    for (std::vector<Circle *>::iterator i = circles.begin()+1; i != n; ++i)
        commonSquare+=(*i)->getSquare();
    if ((*circles.begin())->getSquare()>commonSquare) { return 1;}// Победа
    return 0;
}

void Field::mouseClick(GLfloat x, GLfloat y) {
    (*circles.begin())->move(x, y);
}



