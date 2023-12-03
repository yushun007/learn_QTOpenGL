#ifndef CAMERA_H
#define CAMERA_H
#include <QObject>
#include "type.h"

class Camera:public QObject
{
    Q_OBJECT
public:
    Camera();
    Camera(Vec3f& camera_coordinate,Vec3f& camera_up,Vec3f& camera_g,float left,float right,float top,float bottom,float near,float far);
    Camera(Vec3f& camera_coordinate,Vec3f& camera_up,Vec3f& camera_g,float _view_angle,float near,float far);
    Mat4f view_mat() const;
    Mat4f projection_mat();
private:
    void create_view_mat();
    void create_projection_mat();
private:
    Mat4f _projection_mat;
    Mat4f _view_mat;
    Vec3f _camera_coordinate;
    Vec3f _camera_up;
    Vec3f _camera_g;
    Vec3f _camera_right;
    float _left,_right,_top,_bottom,_near,_far;
    float _view_angle;
};

#endif // CAMERA_H
