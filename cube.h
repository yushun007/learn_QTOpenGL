#ifndef CUBE_H
#define CUBE_H

#include "baseshape.h"


class Cube : public BaseShape
{
    Q_OBJECT
public:
    Cube(model_type type);
    Cube(float length,float width,float hight,model_type type);
private:
    float _width;
    float _hight;
    float _length;

    // BaseShape interface
public:
    unsigned int vertices_length() const override;
    unsigned int indices_length() const override;
    void print() const override;
    unsigned int triangle_vertices_num() const override;

protected:
    void calculate_vertices_coordinates() override;
    void calculate_triangle_indices() override;
    void calculate_texture_coordinates() override;
    unsigned int triangle_num() const override;
    unsigned int vertex_num() const override;
};

#endif // CUBE_H
