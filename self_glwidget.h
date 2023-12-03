#ifndef SELF_GLWIDGET_H
#define SELF_GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLShaderProgram>
#include "camera.h"
#include "sphere.h"
#include "cube.h"

class self_glWidget : public QOpenGLWidget ,protected QOpenGLFunctions_4_1_Core
{
    Q_OBJECT
public:
    self_glWidget(QWidget* parent);
    ~self_glWidget();
    void set_vertices();
    void set_uniform(const char* name,Mat4f value,unsigned int program_id);
    void set_uniform(const char* name,Vec4f value,unsigned int program_id);
    void rend();
    void add_model(BaseShape* shape,const QString & vertex_shader,const QString& fragment_shader,Vec3f m_vec = Vec3f::Zero(),Vec4f color=Vec4f::Random().array().abs());
    QOpenGLShaderProgram* set_shader(const QString& vertex_shader,const QString& fragment_shader);
    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void set_vertiecs();

    // QOpenGLWidget interface
protected:
    void resizeGL(int w, int h) override;
    void initializeGL() override;
    void paintGL() override;
private:
    Camera _camera;
    std::vector<BaseShape*> _models;
    std::vector<Vec3f> _m_vec;
    std::vector<Vec4f> _color_vec;
    std::vector<QOpenGLShaderProgram*> _program_ids;
    std::vector<unsigned int> _vaos;
    std::vector<unsigned int*> _vbos;
};

#endif // SELF_GLWIDGET_H
