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


Field::Field(int countOfRivals, GLfloat *userColor, GLfloat *minColor, GLfloat *maxColor) {
    
    std::copy(minColor, minColor + COUNT_OF_COLORS, this->minColor);
    std::copy(maxColor, maxColor + COUNT_OF_COLORS, this->maxColor);
    std::copy(userColor, userColor + COUNT_OF_COLORS, this->userColor);
    
    for (int i=0; i<COUNT_OF_COLORS; i++)
        midColor[i]=0.5*(maxColor[i]+minColor[i]);
    
    this->countOfRivals=countOfRivals;

    startNewGame();
}

Field::~Field() {
    circles.clear();
}

// Начало новой игры
void Field::startNewGame() {
    
    this->circles.clear();
    
    GLfloat radius=sqrtf(WINDOW_WIDTH*WINDOW_HEIGHT/countOfRivals/20); //5% пространства занято объектами
    
    // Создать игрока
    this->circles.push_back(std::make_shared<CircleUser> (WINDOW_WIDTH/2,WINDOW_HEIGHT/2,radius));
    this->circles.back()->setColor(userColor);
    
    // Посчитать распределение соперников, чтобы они не перекрывали друг друга
    srand(time(0));
    for (int i=0; i<countOfRivals; i++) {
        
        bool t=true;
        GLfloat x,y;
        while (t) {
            t=false;
            x=GLfloat(std::rand()%(WINDOW_WIDTH-2*(int)radius)+radius);
            y=GLfloat(std::rand()%(WINDOW_HEIGHT-2*(int)radius)+radius);
            for (auto j: circles) {
                if (sqrtf((x-j->getX())*(x-j->getX())+(y-j->getY())*(y-j->getY()))<2*radius+10.0) {
                    t=true;
                    break;
                }
            }
        }
        
        // Записать в вектор соперников
        this->circles.push_back(std::make_shared<CircleRival> (x,y,radius));
        this->circles.back()->setColor(midColor);
        
        // Установить скорость
        int multX=-1, multY=-1;
        if (rand()%2) multX=1;
        if (rand()%2) multY=1;
        this->circles.back()->move(10.0*multX,10.0*multY);
    }
}

// Перерисовка объектов
void Field::draw() {
    for (auto i: circles)
        i->draw();        
}

// Перемещение объектов и проверка поглощений
int Field::move() {
    // следующий за последним элементом в векторе circles
    auto n=circles.end();
    for (auto i = circles.begin(); i != n; ++i) {
        (*i)->motion();
        for (auto j = i+1; j != n; ++j) {
            // изменить направление скорости
            (*j)->changeDirection(**i);
            int flag=(*i)->capture(**j);
            if (flag==2) {// был поглощен j-ый
                circles.erase(j);
                n=circles.end();
                --j;
            }
            if (flag==1) {// был поглощен i-ый
                circles.erase(i);
                n=circles.end();
               
                if (i==circles.begin()) return 2;// Проигрыш
                break;
            }
        }        
    }
    // Проверка на победу
    GLfloat commonSquare=0.0;
    for (auto i = circles.begin()+1; i != n; ++i)
        commonSquare+=(*i)->getSquare();
    if ((*circles.begin())->getSquare()>commonSquare) { return 1;}// Победа
    
    // Проверка на поражение
    bool check=true;
    for (auto i = circles.begin()+1; i != n; ++i)
        if ((*i)->getSquare()<=(*circles.begin())->getSquare()) {
            check=false;
            break;
        }
    if (check) return 2;
    
    // Замена цвета в зависимости от радиуса
    GLfloat minRadius=(*circles.begin())->getRadius(), maxRadius=minRadius;
    for (auto i = circles.begin()+1; i != n; ++i) {
        //std::advance(i, 1);
        //найти максимальный и минимальный радиусы
        if ((*i)->getRadius() < minRadius) minRadius=(*i)->getRadius();
        if ((*i)->getRadius() > maxRadius) maxRadius=(*i)->getRadius();
    }
    
    // Радиус пользовательского объекта
    GLfloat userRadius=(*circles.begin())->getRadius();
    
    for (auto i=circles.begin()+1; i!=circles.end(); ++i) {
        if ((*i)->getRadius()==userRadius)
            (*i)->setColor(midColor);
        else {
            if ((*i)->getRadius()<=userRadius)
            (*i)->setColor(minRadius, userRadius, minColor, midColor);
        else (*i)->setColor(userRadius, maxRadius, midColor, maxColor);
        }
    }
    
    return 0;
}

// Событие клика мышки
void Field::mouseClick(GLfloat x, GLfloat y) {
    (*circles.begin())->move(x, y);
}



