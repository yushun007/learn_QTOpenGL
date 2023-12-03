#include "camera.h"

Camera::Camera()
{
    _camera_coordinate = Vec3f(0,2,10);
    _camera_up  = Vec3f(0,1,0);
    _camera_g = Vec3f(0,0,1);
    _camera_right = _camera_up.cross(_camera_g);
    _left = -0.05773502691896256;
    _right = 0.05773502691896256;
    _top = 0.05773502691896256;
    _bottom = -0.05773502691896256;
    _near = 0.1f;
    _far = 10000;
    create_view_mat();
    create_projection_mat();
}

Camera::Camera(Vec3f &camera_coordinate, Vec3f &camera_up, Vec3f &camera_g, float left, float right, float top, float bottom, float near, float far):_camera_coordinate(camera_coordinate),_camera_up(camera_up),_camera_g(camera_g),_left(left),_right(right),_top(top),_bottom(bottom),_near(near),_far(far)
{
    create_view_mat();
    create_projection_mat();
}

Camera::Camera(Vec3f &camera_coordinate, Vec3f &camera_up, Vec3f &camera_g, float _view_angle, float near, float far)
{


}

Mat4f Camera::view_mat() const{
    return _view_mat;
}

Mat4f Camera::projection_mat(){
    return _projection_mat;
}

void Camera::create_view_mat()
{
    _view_mat << _camera_right.transpose(), (-_camera_coordinate.dot(_camera_right)),
        _camera_up.transpose(), (-_camera_coordinate.dot(_camera_up)),
        _camera_g.transpose(), (-_camera_coordinate.dot(_camera_g)),
        0, 0, 0, 1;
}

void Camera::create_projection_mat()
{
    _projection_mat << 2 * _near / (_right - _left), 0, (_left + _right) / (_right - _left), 0,
        0, 2 * _near / (_top - _bottom), (_top + _bottom) / (_top - _bottom), 0,
        0, 0, (_near + _far) / (_near - _far), 2 * _far * _near / (_near - _far),
        0, 0, -1, 0;
}
