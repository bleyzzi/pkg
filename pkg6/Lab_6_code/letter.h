#ifndef LETTER_H
#define LETTER_H

#include <QMainWindow >

#include <QtOpenGL>
#include <QOpenGLFunctions>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QGLWidget>
#include <QOpenGLBuffer>


class letter : public QGLWidget
{
public:
   GLfloat xRot; // переменная хранит угол поворота вокруг оси X
   GLfloat yRot; // переменная хранит угол поворота вокруг оси Y
   GLfloat zRot; // переменная хранит угол поворота вокруг оси Z
   GLfloat zTra; // переменная хранит величину трансляции оси Z
   GLfloat nSca; // переменная отвечает за масштабирование обьекта
   int check=0;
   float angle =30;
   float x_transfer=1,y_transfer=1,z_transfer=1,x_scale=1,y_scale=2,z_scale=3;
   QColor colour;

   QPoint ptrMousePosition; // переменная хранит координату указателя мыши в момент нажатия
   void scale_plus();     // приблизить сцену
   void scale_minus();    // удалиться от сцены
   void rotate_up();      // повернуть сцену вверх
   void rotate_down();    // повернуть сцену вниз
   void rotate_left();    // повернуть сцену влево
   void rotate_right();   // повернуть сцену вправо
   void translate_down(); // транслировать сцену вниз
   void translate_up();   // транслировать сцену вверх
   void defaultScene();   // наблюдение сцены по умолчанию

   void drawAxis();       // построить оси координат

   void drawFigure();     // построить фигуру
   void setVertex(int idx, float k, float x, float y, float z);
   void setTriangle(int idx, int x1, int x2, int x3);
   void setQuad(int idxFirst, int x1, int x2, int x3, int x4);
   void getVertexArray();
   void getIndexArray();
   void draw_xy_projection();
   void draw_xz_projection();
   void draw_zy_projection();
   void draw_scaling();
   void draw_transfer();
   void draw_rotation_x();
   void draw_rotation_y();
   void draw_rotation_z();
  /*virtual*/ void initializeGL();                     // метод для проведения инициализаций, связанных с OpenGL
   /*virtual*/ void resizeGL(int nWidth, int nHeight);  // метод вызывается при изменении размеров окна виджета
   /*virtual*/ void paintGL();                          // метод, чтобы заново перерисовать содержимое виджета

   /*virtual*/ void mousePressEvent(QMouseEvent* pe);   // методы обработки события мыши при нажатии клавиши мыши
   /*virtual*/ void mouseMoveEvent(QMouseEvent* pe);    // методы обработки события мыши при перемещении мыши
   /*virtual*/ void mouseReleaseEvent(QMouseEvent* pe); // методы обработки событий мыши при отжатии клавиши мыши
   /*virtual*/ void wheelEvent(QWheelEvent* pe);        // метод обработки событий колесика мыши
   /*virtual*/ void keyPressEvent(QKeyEvent* pe);       // методы обработки события при нажатии определенной клавиши

public:
    letter(QWidget *parent = nullptr);

    static const int vertices = 24;
    static const int shapeSides = 4;
    static const int shapesNum = 16;
    static const int indexPoints = shapesNum * shapeSides;

    GLfloat** VertexArray = nullptr;
    GLubyte IndexArray[shapesNum][shapeSides];

    static const GLfloat vertexData[vertices][3];
virtual ~letter() = default;
};

#endif // LETTER_H
