#include "simplecamera.h"
#ifndef M_PI
#define M_PI 3.1415926535
#endif

#include <GL/freeglut.h>
#include <cmath>
#include <QDebug>

SimpleCamera::SimpleCamera(float view_width, float view_height,float move_vel, float rotate_vel)
{
    x = 0, y = 0, z = 0;
    yaw = 0;
    pitch = 0;
    this->view_width = view_width;
    this->view_height = view_height;
    this->rotate_vel = rotate_vel;
    this->move_vel = move_vel;
}

void SimpleCamera::lockCamera()
{
    if(pitch>90)
        pitch=90;
    if(pitch<-90)
        pitch=-90;
    if(yaw<0.0)
        yaw+=360.0;
    if(yaw>360.0)
        yaw-=360;
}

void SimpleCamera::moveCamera(float dist,float dir)
{
    float rad=(yaw+dir)*M_PI/180.0;
    x -= sin(rad)*dist;
    z -= cos(rad)*dist;
//    qDebug() << "x = " << x << " z = " << z;
}

void SimpleCamera::moveCameraUp(float dist,float dir)
{
    float rad=(pitch+dir)*M_PI/180.0;
    y += sin(rad)*dist;
//    qDebug() << "y = " << y;
}

void SimpleCamera::rotateCamera(int final_x, int final_y)
{

    int mid_x = view_width/2;
    int mid_y = view_height/2;

    yaw += rotate_vel*(mid_x-final_x);
    pitch += rotate_vel*(mid_y-final_y);
    lockCamera();

    glRotatef(-pitch,1.0,0.0,0.0);
    glRotatef(-yaw,0.0,1.0,0.0);
}

void SimpleCamera::rotateCamera()
{
    rotateCamera(view_width/2, view_height/2);
}

void SimpleCamera::updateCamera()
{
    glTranslatef(-x,-y,-z);
}

void SimpleCamera::moveRight()
{
    moveCamera(move_vel,270);
}

void SimpleCamera::moveLeft()
{
    moveCamera(move_vel,90.0);
}

void SimpleCamera::moveForward()
{
    if(pitch!=90 && pitch!=-90)
        moveCamera(move_vel,0.0);
    moveCameraUp(move_vel,0.0);
}

void SimpleCamera::moveBackward()
{
    if(pitch!=90 && pitch!=-90)
        moveCamera(move_vel,180.0);
    moveCameraUp(move_vel,180.0);
}
