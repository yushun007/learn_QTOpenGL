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
    for(int i = 0;i<_program_ids.size();i++){
        if(_program_ids[i]){
            delete _program_ids[i];
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

    for(int i =0;i<_models.size();i++){
        _program_ids[i]->bind();
        GLenum error = glGetError();
        while(error!=GL_NO_ERROR){
            std::cout<<"useProgram "<<_program_ids[i]<<" error:"<<error<<std::endl;
            error = glGetError();
        }
        glBindVertexArray(_vaos[i]);
        Mat4f model_mat = Mat4f::Identity();
        model_mat.block<3,1>(0,3) = _m_vec[i];
        set_uniform("projection_mat",_camera.projection_mat(),_program_ids[i]->programId());
        set_uniform("view_mat",_camera.view_mat(),_program_ids[i]->programId());
        set_uniform("model_mat",model_mat,_program_ids[i]->programId());
        Vec4f light_color;
        light_color<<1,1,1,1;
        if(_models[i]->get_type() == BaseShape::MODEL){
            set_uniform("color",_color_vec[i],_program_ids[i]->programId());
            set_uniform("light",light_color,_program_ids[i]->programId());
        }else{
            set_uniform("light",light_color,_program_ids[i]->programId());
        }
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glDrawElements(GL_TRIANGLES,_models[i]->triangle_vertices_num(),GL_UNSIGNED_INT,0);
    }

}

void self_glWidget::add_model(BaseShape* shape,const QString& vertex_shader,const QString& fragment_shader,Vec3f m_vec,Vec4f color)
{
    std::cout<<"model_vec:\n"<<m_vec<<std::endl;
    auto* program_id = set_shader(vertex_shader,fragment_shader);
    _program_ids.push_back(program_id);
    _models.push_back(shape);
    _m_vec.push_back(m_vec);
    _color_vec.push_back(color);
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
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearColor(0.f,0.2,0.2,1.f);
    srand((unsigned int)time(NULL));
    Sphere* sphere_1 = new Sphere(50,50,1,BaseShape::LIGHT);
    sphere_1->init();
    Vec3f sphere_vec_1;
    sphere_vec_1<<5,9,-10;
    add_model(sphere_1,":/vertex.vert",":/light.frag",sphere_vec_1);

    Sphere* sphere_0 = new Sphere(50,50,2,BaseShape::MODEL);
    sphere_0->init();
    Vec4f _color;
    _color<<1.0,0.8,0.4,1.f;
    add_model(sphere_0,":/vertex.vert",":/cube.frag",Vec3f::Zero(),_color);
//    Cube* cube_0 = new Cube(2,2,2,BaseShape::MODEL);
//    cube_0->init();
//    add_model(cube_0,":/vertex.vert",":/cube.frag");
    set_vertices();
}

void self_glWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void self_glWidget::paintGL()
{
    static int count = 0;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    GLenum error = glGetError();
    std::cout<<"error:"<<error<<std::endl;
    count++;
    std::cout<<"rend count :"<<count<<std::endl;
    rend();
}

void self_glWidget::set_uniform(const char *name,Mat4f value,unsigned int program_id)
{
    glUniformMatrix4fv(glGetUniformLocation(program_id,name),1,GL_FALSE,value.data());
}

QOpenGLShaderProgram* self_glWidget::set_shader(const QString &vertex_shader, const QString &fragment_shader) {
    auto* shaderProgram = new QOpenGLShaderProgram();
    int success;
    success = shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex,vertex_shader);
    if(!success){
        std::cerr<<"shader "<<vertex_shader.toStdString()<<" error:"<<shaderProgram->log().toStdString();
    }
    success = shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment,fragment_shader);
    if(!success){
        std::cerr<<"shader "<<vertex_shader.toStdString()<<" error:"<<shaderProgram->log().toStdString();
    }
    success = shaderProgram->link();
    if(!success){
        std::cerr<<"shader "<<vertex_shader.toStdString()<<" error:"<<shaderProgram->log().toStdString();
    }
    return shaderProgram;
}

void self_glWidget::set_uniform(const char *name, Vec4f value,unsigned int program_id)
{
    glUniform4fv(glGetUniformLocation(program_id,name),1,value.data());
}
