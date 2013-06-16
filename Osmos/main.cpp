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

#define COUNT_OF_RIVALS 50
#define WINDOW_WIDTH    512
#define WINDOW_HEIGHT   512

//GLfloat spin=0.0;
//GLfloat color[3]={0.8,0.0,1.0};
//Circle circle (200.0,300.0,50.0,color);

const int windowWidth=512;
const int windowHeight=512;

GLubyte space[]=        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

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
}
void printString(char *s) {
    glPushAttrib(GL_LIST_BIT);
    glListBase(fontOffset);
    glCallLists(strlen(s),GL_UNSIGNED_BYTE,(GLubyte*)s);
    glPopAttrib();
}

int result=0;

Field field (COUNT_OF_RIVALS);



// Функция рисования окна
void display()
{
    // Очистка буфера цвета
    glClear(GL_COLOR_BUFFER_BIT);
    
    field.draw();
    
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
    /*switch((int)key) {
        case 27: {
            exit(0);
            break; }
        case 13: { //Заново начать игру
            Field field (COUNT_OF_RIVALS);
            break; }
        default: break;
    
    }*/
    if (key==27) {
        exit(0);
        //Field field (COUNT_OF_RIVALS);
    }
    else if (key==13) {

        //field.~Field();
        field=(COUNT_OF_RIVALS);
        result=0;
    }
}

void newGame() {
    
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
float FPS;

void calculateFPS() {
    static float framesPerSecond = 0.0f;    //наши фпс
    static float lastTime = 0.0f;           //Тут хранится время, прошедшее с последнего кадра
    static char strFrameRate[50] = {0};     //Строка для вывода
    //Тут мы получаем текущий tick count и умножаем его на 0.001 для конвертации из миллисекунд в секунды.
    float currentTime = glutGet(GLUT_ELAPSED_TIME)*0.001f; //Время в миллисекундах от glutInit
    
    //Увеличиваем счетчик кадров
    ++framesPerSecond;
    
    if (currentTime - lastTime > 1.0f) {
        lastTime = currentTime;
        
        // Установим FPS для вывода:
        FPS=framesPerSecond;
        
        //Сбросим FPS
        framesPerSecond = 0;
    }
}

void idle(void) {
    
    
    
    //Теперь вычтем из текущего времени последнее запомненное время. Если результат больше единицы,
    //это значит, что секунда прошла и нужно вывести новый FPS.
    calculateFPS();
    
    if (!result) {
        result=field.move();
        glutPostRedisplay(); //запуск функции display
        
        
    }
        
   
}

void mouseClick(int button, int state, int x, int y) {
    if (!state) {
        field.mouseClick(x, windowHeight-y);
    }
}

int main(int argc, char** argv)
{
    // Инициализация переменных состояния GLUT и открытие сессии с системой управления окнами
    glutInit(&argc, argv);
    
    // Установка начального состояния окна
    glutInitWindowSize(windowWidth, windowHeight);
     
    // Установка режима состояния экрана RGBA
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    
    glutCreateWindow("Osmos");
    
    init();
    
    // Установка параметров экрана и переход в полноэкранный режим
    //glutGameModeString("800x600:32");
    //glutEnterGameMode();
    
    // Установка функции рисования для текущего окна
    glutDisplayFunc(display);
    
    // Установка функции изменения размеров окна
    glutReshapeFunc(reshape);
    
    // Установка функции обработки пустого события - glutIdleFunc(...) - необходимо для анимации
    glutIdleFunc(idle);
    
    glutMouseFunc(mouseClick);
    
    glutKeyboardFunc(keyboard);
    
    // Установка цвета фона
    glClearColor(0.1,0.1,0.1,0.9);
    
    // Запуск механизма обработки событий
    glutMainLoop();
    
    return 0;
}



