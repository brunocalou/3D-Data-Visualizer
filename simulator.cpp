#include "simulator.h"
//#include <GL/glut.h>
//#include <GL/gl.h>
//#include <glm/glm.hpp>
//#include <QGLFunctions>

#include <QDebug>
#include <QMouseEvent>
#include <QGLWidget>
#include <cmath>
#include "datafile.h"

Simulator::Simulator(QWidget *parent) :
    QGLWidget(parent), camera(this->width(),this->height(),0.2,0.2)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(moveCamera()));
    timer.start(16);


    DataFile dataFile;
    dataFile.setDirectoryPath(".");
    dataFile.setUpFile("gps.txt");
//    dataFile.setUpFile("Log_Sat_05_07_2014_22:56:24.txt");

    //Uncomment the following lines to fill up file

//    dataFile.removeFile();
//    std::vector<float> a;
//    for(int i = -3.141*100*2; i < 3.141*100*2; i++)
//    {
//        float j = i/100.0;
//        a.push_back(cos(pow(j,2))*j);
//        a.push_back(j);
//        a.push_back(sin(pow(j,2))*j);
//        dataFile.writeData("g",a);
//        a.clear();
//    }

//    dataFile.reloadFile();

    //Load Data
    dataFile.loadData("g", points);
//    dataFile.loadData("55,6,1", points);

    this->grabKeyboard();
//    parent->installEventFilter(this);
    rotate_camera = false;
    first_time_rotating = true;
    w_is_pressed = false;
    a_is_pressed = false;
    s_is_pressed = false;
    d_is_pressed = false;
}
void Simulator::initializeGL()
{
    glClearColor(0.1725, 0.1725, 0.1725,1);
//    glEnable(GL_COLOR);
    glEnable(GL_DEPTH_TEST);
}

void Simulator::resizeGL(int w, int h)
{
//    initializeGLFunctions();
//    geometries.init();

    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(45, (float) w/h, 0.1, 100.0);
    perspectiveGL(45,(float) w/h, 0.1, 100.0);
//    projection.
    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    gluLookAt(0,0,7,0,0,0,0,1,0);
    camera.view_width = w;
    camera.view_height = h;
}

void Simulator::paintGL()
{
    glClearColor(0.1725, 0.1725, 0.1725,1);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);


    glColor3f(1,1,1);
    glLoadIdentity();
//    drawText(0,0,0,"MATRIX");
    camera.rotateCamera();
    camera.updateCamera();
    glPushMatrix();
        glRotatef(-90,1,0,0);
        drawGrid(10,1);
        glColor3f(0,1,0);
        drawPoints();
    glPopMatrix();


}
void Simulator::perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
    // Replaces gluPerspective. Sets the frustum to perspective mode.
    // fovY     - Field of vision in degrees in the y direction
    // aspect   - Aspect ratio of the viewport
    // zNear    - The near clipping distance
    // zFar     - The far clipping distance
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;
    fH = tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;
    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}

void Simulator::drawText(double x, double y, double z, QString txt)
{
//    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glPushMatrix();
    glRotatef(10,1,0,0);
    glTranslatef(0,0,5);

    qglColor(Qt::white);
    renderText(x, y, z, txt, QFont("Arial", 12, QFont::Bold, false) );
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
}
void Simulator::drawGrid(float size, float step)
{
    glPushMatrix();
        glTranslatef(-size/2,-size/2,0);
        glBegin(GL_LINES);
            for(float i = 0; i <= size; i+= step)
            {
                glVertex3f(i,0,0);
                glVertex3f(i,size,0);
                glVertex3f(0,i,0);
                glVertex3f(size,i,0);
            }
        glEnd();
    glPopMatrix();
}

void Simulator::drawPoints(float scale)
{
    if(points.empty())
    {
        return ;
    }
//    int stride = 6*sizeof(float);//6 numbers per vector
    int stride = 0;//Compacted vector
    glPushMatrix();
    glScalef(scale, scale, scale);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,stride,&points.at(0));
    glDrawArrays(GL_LINE_STRIP,0,points.size()/3);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
}

void Simulator::mousePressEvent(QMouseEvent *event)
{
//    if(event->button() == Qt::MidButton)
//    {
        rotate_camera = true;
        first_time_rotating = true;
        QCursor::setPos(mapToGlobal(QPoint(this->width()/2,this->height()/2)));
        this->setCursor(Qt::BlankCursor);
//    }
}

void Simulator::mouseReleaseEvent(QMouseEvent *event)
{
//    if(event->button() == Qt::MidButton)
//    {
        rotate_camera = false;
        first_time_rotating = true;
        this->unsetCursor();
//    }
}

void Simulator::mouseMoveEvent(QMouseEvent *event)
{
    if(rotate_camera)
    {
        mouse_x = event->x();
        mouse_y = event->y();
        QCursor::setPos(mapToGlobal(QPoint(this->width()/2,this->height()/2)));
        rotateCamera();
    }
}

void Simulator::rotateCamera()
{
    if(first_time_rotating)
    {
        mouse_x = this->width()/2;
        mouse_y = this->height()/2;
        first_time_rotating = false;
    }
    else
    {
        camera.rotateCamera(mouse_x, mouse_y);
    }
}

void Simulator::moveCamera()
{
    if(w_is_pressed)
    {
        camera.moveForward();
    }
    if(s_is_pressed)
    {
        camera.moveBackward();
    }
    if(a_is_pressed)
    {
        camera.moveLeft();
    }
    if(d_is_pressed)
    {
        camera.moveRight();
    }
    camera.updateCamera();
}

void Simulator::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        w_is_pressed = true;
    }
    if(event->key() == Qt::Key_S)
    {
        s_is_pressed = true;
    }
    if(event->key() == Qt::Key_A)
    {
        a_is_pressed = true;
    }
    if(event->key() == Qt::Key_D)
    {
        d_is_pressed = true;
    }
}

void Simulator::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        w_is_pressed = false;
    }
    if(event->key() == Qt::Key_S)
    {
        s_is_pressed = false;
    }
    if(event->key() == Qt::Key_A)
    {
        a_is_pressed = false;
    }
    if(event->key() == Qt::Key_D)
    {
        d_is_pressed = false;
    }
}
