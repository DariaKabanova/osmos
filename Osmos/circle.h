//
//  Сircle.h
//  Osmos
//
//  Created by Дарья Кабанова on 12.06.13.
//  Copyright (c) 2013 Дарья Кабанова. All rights reserved.
//

#ifndef __Osmos___ircle__
#define __Osmos___ircle__

#include <iostream>
#include <OpenGL/OpenGL.h>

class Circle {
    public:
        Circle() {};
        ~Circle() {}
    
        void Draw(/*GLdouble x, GLdouble y*/);
        void Move();
};

//const


#endif /* defined(__Osmos___ircle__) */
