#include "self_glwidget.h"
#include <QKeyEvent>

self_glWidget::self_glWidget(QWidget* parent):QOpenGLWidget(parent)
{
}

self_glWidget::~self_glWidget()
{
    for(int i = 0;i<_vbos.size();i++){
        glDeleteVertexArrays(1,&_vaos[i]);
        glDeleteBuffers(2,_vbos[i]);
        if(_vbos[i]){
            delete [] _vbos[i];
        }
    }
    for(int i = 0;i<_models.size();i++){
        if(_models[i]){
            delete _models[i];
        }
    }
}

void self_glWidget::set_vertices()
{
    for(int i = 0;i<_models.size();i++){
        unsigned int vao;
        glGenVertexArrays(1,&vao);
        glBindVertexArray(vao);
        _vaos.push_back(vao);
        unsigned int *vbo = new unsigned int[2];
        glGenBuffers(2,vbo);
        _vbos.push_back(vbo);
        glBindBuffer(GL_ARRAY_BUFFER,vbo[0]);
        glBufferData(GL_ARRAY_BUFFER,_models[i]->vertices_length(),_models[i]->vertex_coordinates(),GL_STATIC_DRAW);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*3,0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vbo[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,_models[i]->indices_length(),_models[i]->indices(),GL_STATIC_DRAW);
    }
}

void self_glWidget::rend()
{
    std::cout<<"rend"<<std::endl;
    glUseProgram(_program_id);
    _shader_program.bind();
    for(int i =0;i<_models.size();i++){
        std::cout<<"i:"<<i<<std::endl;
        glBindVertexArray(_vaos[i]);
        std::cout<<"bind vertex array"<<std::endl;
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        std::cout<<"glPolygonMode"<<std::endl;
        glDrawElements(GL_TRIANGLES,_models[i]->triangle_vertices_num(),GL_UNSIGNED_INT,0);
        std::cout<<"glDrawElements"<<std::endl;
    }

}

void self_glWidget::add_model(BaseShape* shape)
{
    _models.push_back(shape);
}


void self_glWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Escape:
        exit(0);
        break;
    default:
        break;
    }
}

void self_glWidget::initializeGL()
{
    if(!initializeOpenGLFunctions()){
        std::cerr<<"init openGL function failed!"<<std::endl;
        exit(-1);
    }
    int success;
    success = _shader_program.addShaderFromSourceFile(QOpenGLShader::Vertex,":/vertex.vert");
    success = _shader_program.addShaderFromSourceFile(QOpenGLShader::Fragment,":/fragment.frag");
    _shader_program.link();
    _shader_program.bind();
    Sphere* sphere_0 = new Sphere(3,4,4);
    sphere_0->init();
    add_model(sphere_0);
    Sphere* sphere_1 = new Sphere(10,10,1);
    sphere_1->init();
    add_model(sphere_1);

    Cube* cube_0 = new Cube(2,2,2);
    cube_0->init();
    add_model(cube_0);
    Cube* cube_1 = new Cube(4,4,4);
    cube_1->init();
    add_model(cube_1);
    _program_id = _shader_program.programId();
    set_uniform("projection_mat",_camera.projection_mat());
    set_uniform("mv_mat",_camera.view_mat());
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearColor(1.0,0.8,0.5,1.f);
    set_vertices();
}

void self_glWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void self_glWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    GLenum error = glGetError();
    while(error!=GL_NO_ERROR){
        std::cerr<<"glClear error:"<<error<<std::endl;
        error = glGetError();
    }
    std::cout<<"start to rend"<<std::endl;
    rend();
}

template<typename T>
void self_glWidget::set_uniform(const char *name, T value)
{
    glUniformMatrix4fv(glGetUniformLocation(_program_id,name),1,GL_FALSE,value.data());
}
