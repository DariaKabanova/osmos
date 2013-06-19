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
#include "field.h"
#include <string.h>
#include "parson.h"

#define FPS_VALUE       24

const char *filename = "/users/madmoron/Desktop/config.json";// расположение конфига

std::shared_ptr<Field> field;
int result=0;
bool stateClick=false;
int mouse_x=0;
int mouse_y=0;

GLubyte space[]=        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

// Установка шрифта
GLubyte letters[][13]={ {0x00,0x00,0xc3,0xc3,0xc3,0xc3,0xff,0xc3,0xc3,0xc3,0x66,0x3c,0x18},
                        {0x00,0x00,0xfe,0xc7,0xc3,0xc3,0xc7,0xfe,0xc7,0xc3,0xc3,0xc7,0xfe},
                        {0x00,0x00,0x7e,0x7e,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xe7,0x7e},
                        {0x00,0x00,0xfc,0xce,0xc7,0xc3,0xc3,0xc3,0xc3,0xc3,0xc7,0xce,0xfc},
                        {0x00,0x00,0xff,0xc0,0xc0,0xc0,0xc0,0xfc,0xc0,0xc0,0xc0,0xc0,0xff},
                        {0x00,0x00,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xfc,0xc0,0xc0,0xc0,0xff},
                        {0x00,0x00,0x7e,0x7e,0xc3,0xc3,0xcf,0xc0,0xc0,0xc0,0xc0,0xe7,0x7e},
                        {0x00,0x00,0xc3,0xc3,0xc3,0xc3,0xc3,0xff,0xc3,0xc3,0xc3,0xc3,0xc3},
                        {0x00,0x00,0x7e,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x7e},
                        {0x00,0x00,0x7c,0xee,0xc6,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06},
                        {0x00,0x00,0xc3,0xc6,0xcc,0xd8,0xf0,0xe0,0xf0,0xd8,0xcc,0xc6,0xc3},
                        {0x00,0x00,0xff,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0},
                        {0x00,0x00,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xdb,0xff,0xff,0xe7,0xc3},
                        {0x00,0x00,0xc7,0xc7,0xcf,0xcf,0xdf,0xdb,0xfb,0xf3,0xf3,0xe3,0xe3},
                        {0x00,0x00,0x7e,0xe7,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xe7,0x7e},
                        {0x00,0x00,0xc0,0xc0,0xc0,0xc0,0xc0,0xfe,0xc7,0xc3,0xc3,0xc7,0xfe},
                        {0x00,0x00,0x3f,0x6e,0xdf,0xdb,0xc3,0xc3,0xc3,0xc3,0xc3,0x66,0x3c},
                        {0x00,0x00,0xc3,0xc6,0xcc,0xd8,0xf0,0xfe,0xc7,0xc3,0xc3,0xc7,0xfe},
                        {0x00,0x00,0x7e,0xe7,0x03,0x03,0x07,0x7e,0xe0,0xc0,0xc0,0xe7,0x7e},
                        {0x00,0x00,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0xff},
                        {0x00,0x00,0x7e,0xe7,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3},
                        {0x00,0x00,0x18,0x3c,0x3c,0x66,0x66,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3},
                        {0x00,0x00,0xc3,0xe7,0xff,0xff,0xdb,0xdb,0xc3,0xc3,0xc3,0xc3,0xc3},
                        {0x00,0x00,0xc3,0x66,0x66,0x3c,0x3c,0x18,0x3c,0x3c,0x66,0x66,0xc3},
                        {0x00,0x00,0x18,0x18,0x18,0x18,0x18,0x18,0x3c,0x3c,0x66,0x66,0xc3},
                        {0x00,0x00,0xff,0xc0,0xc0,0x60,0x30,0x7e,0x0c,0x06,0x03,0x03,0xff}};
GLuint fontOffset;

void makeRasterFont() {
    GLuint i,j;
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    fontOffset=glGenLists(128);
    for(i=0,j='A';i<26;i++,j++)
    {
        glNewList(fontOffset+j,GL_COMPILE);
        glBitmap(8,13,0.0,2.0,10.0,0.0,letters[i]);
        glEndList();
    }
    glNewList(fontOffset+' ',GL_COMPILE);
    glBitmap(8,13,0.0,2.0,10.0,0.0,space);
    glEndList();
}
void init(void)
{
    glShadeModel(GL_FLAT);
    makeRasterFont();
    
    // JSON десерилизация
    JSON_Value *root_value;
    JSON_Object *object;

    root_value = json_parse_file(filename);
    
    object = json_value_get_object(root_value);
    
    JSON_Object *objectUser;
    objectUser=json_object_get_object(object, "user");
    
    JSON_Object *objectEnemy;
    objectEnemy=json_object_get_object(object, "enemy");
    
    JSON_Array *color;
    color=json_object_get_array(objectUser,"color");
    
    JSON_Array *color1;
    color1=json_object_get_array(objectEnemy,"color1");
    
    JSON_Array *color2;
    color2=json_object_get_array(objectEnemy,"color2");
    
    GLfloat userColor[3], enemyMinColor[3], enemyMaxColor[3];
    
    for (int i = 0; i < json_array_get_count(color); i++) {
        userColor[i]=(GLfloat)json_array_get_number(color, i);
        enemyMinColor[i]=(GLfloat)json_array_get_number(color1, i);
        enemyMaxColor[i]=(GLfloat)json_array_get_number(color2, i);
    }

    int countOfEnemies=(int)json_object_get_number(objectEnemy, "count");
    
    field=std::make_shared<Field> (countOfEnemies,userColor,enemyMinColor,enemyMaxColor);

}
// Напечатать надпись
void printString(char *s) {
    glPushAttrib(GL_LIST_BIT);
    glListBase(fontOffset);
    glCallLists(strlen(s),GL_UNSIGNED_BYTE,(GLubyte*)s);
    glPopAttrib();
}


// Функция рисования окна
void display()
{
    // Очистка буфера цвета
    glClear(GL_COLOR_BUFFER_BIT);
    
    field->draw();
    
    // Вывод сообщений о конце игры
    if (result) {
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos2i(WINDOW_WIDTH/2-70,WINDOW_HEIGHT/2);
        if (result==1)
            printString("YOU ARE A WINNER");
        if (result==2)      
            printString("YOU ARE A LOSER");
        glFlush();
    } 
    
    // Использование обмена буферов. Используется окно с двойной буферизацией.
    glutSwapBuffers();
}

void keyboard(unsigned char key,int x,int y) {
    switch((int)key) {
        case 27: {
            exit(0);
            break; }
        case 13: { //Заново начать игру
            field->startNewGame();
            result=0;
            break; }
        default: break;
    }
}

bool calculateWatch() {
    static float lastTime = 0.0f;
    float currentTime = glutGet(GLUT_ELAPSED_TIME)*0.001f;
    if (currentTime-lastTime >= 1.0f/FPS_VALUE) {
        lastTime = currentTime;
        return true;
    }
    return false;
    
}

void idle(void) {
    
    if (calculateWatch() && !result) {
        if (stateClick) field->mouseClick(mouse_x, WINDOW_HEIGHT-mouse_y);
        result=field->move();
        glutPostRedisplay(); //запуск функции display
    }
    
}

void mouseClick(int button, int state, int x, int y) {
    if (!state) {
        //field->mouseClick(x, WINDOW_HEIGHT-y);
        stateClick=true;
        mouse_x=x;
        mouse_y=y;
        
    }
    else stateClick=false;
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

int main(int argc, char** argv)
{
    // Инициализация переменных состояния GLUT и открытие сессии с системой управления окнами
    glutInit(&argc, argv);
    
    // Установка начального состояния окна
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
     
    // Установка режима состояния экрана RGBA
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    
    glutCreateWindow("Osmos");
    
    init();

    // Установка функции рисования для текущего окна
    glutDisplayFunc(display);
    
    // Установка функции обработки пустого события
    glutIdleFunc(idle);
    
    // Установка функции изменения размеров окна
    glutReshapeFunc(reshape);
    
    glutMouseFunc(mouseClick);
    
    glutKeyboardFunc(keyboard);
    
    // Установка цвета фона
    glClearColor(0.1,0.1,0.1,0.9);
    
    // Запуск механизма обработки событий
    glutMainLoop();
    
    return 0;
}



