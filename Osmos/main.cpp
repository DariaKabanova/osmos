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

void keyDown(int key) {
    
}

// Функция рисования окна
void display()
{
    /* clear the color buffer (resets everything to black) */
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Установка текущего цвета
    glColor3f(1, 0, 0);
    
    /* start drawing triangles, each triangle takes 3 vertices */
    glBegin(GL_TRIANGLES);
    
    /* give the 3 triangle vertex coordinates 1 at a time */
    glVertex2f(10, 10);
    glVertex2f(250, 400);
    glVertex2f(400, 10);
    
    /* tell OpenGL we're done drawing triangles */
    glEnd();
    
    // Использование обмена буферов. Используется окно с двойной буферизацией.
    glutSwapBuffers();
}

// Функция перерисовки при изменении размеров окна
void reshape(int width, int height)
{
    // Перестройка вывода
     
    glViewport(0,0,width,height);
    
    // switch to the projection matrix
    glMatrixMode(GL_PROJECTION);
    
    // clear the projection matrix
    glLoadIdentity();
    
    // set the camera view, orthographic projection in 2D 
    gluOrtho2D(0,width,0,height);
    
    // switch back to the model view matrix 
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv)
{
    // Инициализация переменных состояния GLUT и открытие сессии с системой управления окнами
    glutInit(&argc, argv);
    
    // Установка начального состояния окна
    glutInitWindowSize(512, 512);
     
    // Установка режима состояния экрана RGBA
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    
    glutCreateWindow("Osmos");
    
    // Установка функции рисования для текущего окна
    glutDisplayFunc(display);
    
    glutKeyboardFunc(keyDown);
    
    // Установка функции обработки пустого события - glutIdleFunc(...) - необходимо для анимации
    
    // Установка функции изменения размеров окна
    glutReshapeFunc(reshape);
    
    // Установка цвета фона
    glClearColor(0,1,1,0.3);
    
    // Запуск механизма обработки событий
    glutMainLoop();
    
    return 0;
}



