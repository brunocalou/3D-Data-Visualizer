#ifndef SIMPLECAMERA_H
#define SIMPLECAMERA_H

class SimpleCamera
{
public:
    SimpleCamera(float view_width, float view_height, float move_vel=1, float rotate_vel=1);
    void lockCamera();
    void moveCameraUp(float dist,float dir);
    void rotateCamera(int final_x, int final_y);
    void rotateCamera();
    void updateCamera();
    float view_width, view_height;
    float rotate_vel;
    float move_vel;

    void moveRight();
    void moveLeft();
    void moveForward();
    void moveBackward();

private:

    float x,y,z;
    float yaw;
    float pitch;

    void moveCamera(float dist,float dir);

};

#endif // SIMPLECAMERA_H
