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
    //std::vector<int> vect;
    //vect.push_back(2);
    //for (int i=0; i<countOfObjects; i++)
    this->v.push_back(Circle (0.0,0.0,0.0,color));
        //Field::v.push_back(Circle (0.0,0.0,0.0,NULL));
}