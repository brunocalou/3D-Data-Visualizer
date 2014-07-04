#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <QGLWidget>
#include <QTimer>
#include "simplecamera.h"

class Simulator : public QGLWidget
{
    Q_OBJECT
public:
    explicit Simulator(QWidget *parent = 0);
    void    initializeGL();
    void    resizeGL(int w, int h);
    void    paintGL();

private:
    void    drawGrid(float size, float step);
    void    drawPoints(float scale = 1);
    QTimer  timer;
    std::vector <float> points;
    SimpleCamera camera;

    bool rotate_camera;
    bool first_time_rotating;
    int mouse_x, mouse_y;
    bool w_is_pressed,a_is_pressed,s_is_pressed,d_is_pressed;
    void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);
    void drawText(double x, double y, double z, QString txt);


signals:

public slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void moveCamera();
    void rotateCamera();
};

#endif // SIMULATOR_H
