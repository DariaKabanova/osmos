//
//  field.h
//  Osmos
//
//  Created by Дарья Кабанова on 12.06.13.
//  Copyright (c) 2013 Дарья Кабанова. All rights reserved.
//

#ifndef __Osmos__field__
#define __Osmos__field__

#include <iostream>

#include "circle.h"
#include <vector>


class Field {
private: std::vector<Circle> v;
    
public:
    Field(int countOfObjects);
    void draw();
    
    
};


#endif /* defined(__Osmos__field__) */
