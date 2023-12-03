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
    template<typename T>
    void set_uniform(const char* name,T value);
    void rend();
    void add_model(BaseShape* shape);
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
    unsigned int _program_id;
    std::vector<unsigned int> _vaos;
    std::vector<unsigned int*> _vbos;
    QOpenGLShaderProgram _shader_program;
};

#endif // SELF_GLWIDGET_H
