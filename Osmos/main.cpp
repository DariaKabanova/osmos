//
//  main.cpp
//  Osmos
//
//  Created by Дарья Кабанова on 11.06.13.
//  Copyright (c) 2013 Дарья Кабанова. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <OpenGL/OpenGL.h>
#include "circle.h"



// Функция нажатия на клавишу key
void keyDown(unsigned char key, int x, int y) {
    
}

GLfloat spin=0.0;
GLfloat color[3]={0.8,0.0,1.0};

Circle circle (200.0,300.0,50.0,color);

// Функция рисования окна
void display()
{
    // Очистка буфера цвета
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    
    circle.Draw();
    
    
    
    // Использование обмена буферов. Используется окно с двойной буферизацией.
    glutSwapBuffers();
}




// Функция перерисовки при изменении размеров окна
void reshape(int width, int height)
{
    // Перестройка вывода, установка области вывода изображения
    glViewport(0,0,width,height);
    
    // Загрузка матрицы проекции
    glMatrixMode(GL_PROJECTION);
    
    // Замена матрицы проекции единичной
    glLoadIdentity();
    
    // Установка ортогональной проекции
    gluOrtho2D(0,width,0,height);
    
    // Загрузка модельно-видовой матрицы
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
}

void idle(void) {
    // Очистка буфера цвета
    //glClear(GL_COLOR_BUFFER_BIT);

    spin=spin+1.0;
    if(spin>360.0) spin=spin-360.0;
    glutPostRedisplay();
    
    
    // Использование обмена буферов. Используется окно с двойной буферизацией.
    //glutSwapBuffers();
}


int main(int argc, char** argv)
{
    // Инициализация переменных состояния GLUT и открытие сессии с системой управления окнами
    glutInit(&argc, argv);
    
    // Установка начального состояния окна
    glutInitWindowSize(512, 512);
     
    // Установка режима состояния экрана RGBA
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    
    glutCreateWindow("Osmos");
    
    // Установка параметров экрана и переход в полноэкранный режим
    //glutGameModeString("800x600:32");
    //glutEnterGameMode();
    
    // Установка функции рисования для текущего окна
    glutDisplayFunc(display);
    
    glutKeyboardFunc(keyDown);
    
    
    
    // Установка функции изменения размеров окна
    glutReshapeFunc(reshape);
    
    // Установка функции обработки пустого события - glutIdleFunc(...) - необходимо для анимации
    glutIdleFunc(idle);
    
    // Установка цвета фона
    glClearColor(0,1,1,0.3);
    
    // Запуск механизма обработки событий
    glutMainLoop();
    
    return 0;
}



