#include "baseshape.h"


void BaseShape::init()
{
    calculate_vertices_coordinates();
    calculate_triangle_indices();
    calculate_texture_coordinates();
}

float *BaseShape::vertex_coordinates()
{
    return _vertex_coordinates->data();
}

unsigned int *BaseShape::indices()
{
    return _indices->data();
}

float *BaseShape::texture_coordinates()
{
    return _texture_coordinates->data();
}

BaseShape::model_type BaseShape::get_type() const {
    return _type;
}
