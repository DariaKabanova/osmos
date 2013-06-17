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

Field::Field(int countOfRivals, GLfloat windowWidth, GLfloat windowHeight, GLfloat *userColor, GLfloat *minColor, GLfloat *maxColor) {
    
    std::copy(minColor, minColor + COUNT_OF_COLORS, this->minColor);
    std::copy(maxColor, maxColor + COUNT_OF_COLORS, this->maxColor);
    std::copy(userColor, userColor + COUNT_OF_COLORS, this->userColor);
    this->windowWidth=windowWidth;
    this->windowHeight=windowHeight;
    this->countOfRivals=countOfRivals;

    startNewGame();
}

// Начало новой игры
void Field::startNewGame() {
    
    this->circles.clear();
    
    GLfloat radius=sqrtf(windowHeight*windowWidth/countOfRivals/20); //5% пространства занято объектами
    
    // Создать игрока
    this->circles.push_back(new CircleUser (512/2,512/2,radius,userColor));
    
    // Посчитать распределение соперников, чтобы они не перекрывали друг друга
    srand(time(0));
    for (int i=0; i<countOfRivals; i++) {
        
        bool t=true;
        GLfloat x,y;
        while (t) {
            t=false;
            x=GLfloat(std::rand()%(512-2*(int)radius)+radius);
            y=GLfloat(std::rand()%(512-2*(int)radius)+radius);
            for (std::vector<Circle *>::iterator j = circles.begin(); j != circles.end(); ++j) {
                if (sqrtf((x-(*j)->getX())*(x-(*j)->getX())+(y-(*j)->getY())*(y-(*j)->getY()))<2*radius+10.0) {
                    t=true;
                    break;
                }
            }
        }
        
        // Записать в вектор соперников
        this->circles.push_back(new CircleRival (x,y,radius,userColor));
        this->circles.back()->setColor(radius, radius, minColor, maxColor);
        
        // Установить скорость
        int multX=-1, multY=-1;
        if (rand()%2) multX=1;
        if (rand()%2) multY=1;
        this->circles.back()->move(10.0*multX,10.0*multY);
    }
}

// Перерисовка объектов
void Field::draw() {
    for (std::vector<Circle *>::iterator i = circles.begin(); i != circles.end(); ++i)
        (*i)->draw();        
}

// Перемещение объектов и проверка поглощений
int Field::move() {
    // следующий за последним элементом в векторе circles
    std::vector<Circle *>::iterator n=circles.end();
    for (std::vector<Circle *>::iterator i = circles.begin(); i != n; ++i) {
        (*i)->motion();
        for (std::vector<Circle *>::iterator j = i+1; j != n; ++j) {
            // изменить направление скорости
            (*j)->changeDirection(*i);
            int flag=(*i)->capture(*j);
            if (flag==2) {// был поглощен j-ый
                circles.erase(j);
                n=circles.end();
                j--;
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
    for (std::vector<Circle *>::iterator i = circles.begin()+1; i != n; ++i)
        commonSquare+=(*i)->getSquare();
    if ((*circles.begin())->getSquare()>commonSquare) { return 1;}// Победа
    
    // Замена цвета в зависимости от радиуса
    GLfloat minRadius=(*circles.begin())->getRadius(), maxRadius=minRadius;
    for (std::vector<Circle *>::iterator i = circles.begin()+1; i != n; ++i) {
        //найти максимальный и минимальный радиусы
        if ((*i)->getRadius() < minRadius) minRadius=(*i)->getRadius();
        if ((*i)->getRadius() > maxRadius) maxRadius=(*i)->getRadius();
    }
    
    // Радиус пользовательского объекта
    GLfloat userRadius=(*circles.begin())->getRadius();
    
    for (std::vector<Circle *>::iterator i = circles.begin()+1; i != n; ++i) {
        if ((*i)->getRadius()<userRadius) (*i)->setColor(minRadius, userRadius, minColor, maxColor);
        else (*i)->setColor(userRadius, maxRadius, minColor, maxColor);
    }
    
    return 0;
}

// Событие клика мышки
void Field::mouseClick(GLfloat x, GLfloat y) {
    (*circles.begin())->move(x, y);
}



