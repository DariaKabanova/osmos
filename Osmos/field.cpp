//
//  field.cpp
//  Osmos
//
//  Created by Дарья Кабанова on 12.06.13.
//  Copyright (c) 2013 Дарья Кабанова. All rights reserved.
//

#include "field.h"

Field::Field(int countOfObjects) {
    GLfloat colorRed[3]={1.0,0.0,0.0};
    GLfloat color[3]={0.8,0.0,1.0};
    
    // Задать игрока
    
    
    this->circles.push_back(new CircleUser (300.0,400.0,30.0,colorRed));
    
    // Посчитать распределение соперников
    
    
    
    // Записать в вектор соперников
    
    for (int i=0; i<countOfObjects; i++)
        this->circles.push_back(new CircleRival (i*40.0+30.0,i*40.0+30.0,20.0,color));

}

void Field::draw() {
    //capture();
    for (std::vector<Circle *>::iterator i = circles.begin(); i != circles.end(); ++i)
        (*i)->draw();
        
}

void Field::move() {
    for (std::vector<Circle *>::iterator i = circles.begin(); i != circles.end(); ++i)
        (*i)->motion();//(0.0,-1.0);
    
}

void Field::mouseClick(GLfloat x, GLfloat y) {
    (*circles.begin())->move(x, y);
    std::vector<Circle *>::iterator n=circles.end();
    for (std::vector<Circle *>::iterator j = circles.begin()+1; j != n; ++j) {

       int flag=(*circles.begin())->capture(*j);
        if (flag==2)
        {
            circles.erase(j);
            n=circles.end();
            j--;
        }
        
    }
    //capture();
}

void Field::capture() {
    for (std::vector<Circle *>::iterator i = circles.begin(); i != circles.end(); ++i) {
        for (std::vector<Circle *>::iterator j = i+1; j != circles.end(); ++j) {
            if (i!=j) {
                int flag=(*i)->capture(*j);

            }
        }
            
    }
        
}

