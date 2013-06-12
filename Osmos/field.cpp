//
//  field.cpp
//  Osmos
//
//  Created by Дарья Кабанова on 12.06.13.
//  Copyright (c) 2013 Дарья Кабанова. All rights reserved.
//

#include "field.h"

Field::Field(int countOfObjects) {
    GLfloat color[3]={0.8,0.0,1.0};
    
    // Задать игрока
    
    this->v.push_back(CircleUser (10.0,10.0,12.0,color));
    
    // Посчитать распределение соперников
    
    
    
    // Записать в вектор соперников
    
    for (int i=1; i<countOfObjects; i++)
        this->v.push_back(CircleRival (i*20.0+10.0,i*20.0+10.0,10.0,color));

}

void Field::draw() {
    for (std::vector<Circle>::iterator i = v.begin(); i != v.end(); ++i)
        i->draw();
        
}