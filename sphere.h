#ifndef SPHERE_H
#define SPHERE_H

#include "baseshape.h"
#include <QWidget>

class Sphere : public BaseShape
{
public:
    Sphere();
    Sphere(unsigned int slice_num,unsigned int slice_vertices_num,unsigned int raduis);
    ~Sphere();
    unsigned int vertices_length() const override;
    unsigned int indices_length() const override;
    unsigned int triangle_vertices_num() const override;
    void print()const override;
private:
    std::vector<float> calculate_coordinate(float theta,float phi);
private:
    unsigned int _vertex_num;
    unsigned int _triangle_num;
    unsigned int _slice_num;
    unsigned int _slice_vertices_num;
    unsigned int _radius;

    // BaseShape interface
protected:
    void calculate_vertices_coordinates() override;
    void calculate_triangle_indices() override;
    void calculate_texture_coordinates() override;
    unsigned int triangle_num() const override;
    unsigned int vertex_num() const override;

};

#endif // SPHERE_H
