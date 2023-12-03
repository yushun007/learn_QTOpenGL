#ifndef BASESHAPE_H
#define BASESHAPE_H
#include "type.h"
#include <memory>
#include <QOpenGLFunctions_4_1_Core>
#include <QObject>

class BaseShape: public QOpenGLFunctions_4_1_Core,public QObject
{
public:
    enum model_type{
        LIGHT,
        MODEL
    };
    BaseShape(model_type type):_type(type){};
    virtual void init();
    virtual unsigned int vertices_length() const =0;
    virtual unsigned int indices_length() const =0;
    virtual void print()const = 0;
    virtual unsigned int triangle_vertices_num() const = 0;
    float* vertex_coordinates();
    unsigned int* indices();
    float* texture_coordinates();
    model_type get_type()const;
protected:
    virtual void calculate_vertices_coordinates() = 0;
    virtual void calculate_triangle_indices() =0;
    virtual void calculate_texture_coordinates() = 0;
    virtual unsigned int triangle_num() const = 0;
    virtual unsigned int vertex_num() const = 0;
protected:
    std::shared_ptr<TriangleIndices> _indices;
    std::shared_ptr<VertexCoordinates> _vertex_coordinates;
    std::shared_ptr<TextureCoordinates> _texture_coordinates;
    model_type _type;
};

#endif // BASESHAPE_H
