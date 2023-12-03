#include "cube.h"
#include <vector>

Cube::Cube()
{
    _hight = 1;
    _width = 1;
    _length = 1;
    _vertex_coordinates = std::make_shared<VertexCoordinates>(8);
    _indices = std::make_shared<TriangleIndices>(12);
}

Cube::Cube(float length, float width, float hight):_length(length),_width(width),_hight(hight)
{
    _vertex_coordinates = std::make_shared<VertexCoordinates>(8);
    _indices = std::make_shared<TriangleIndices>(12);
}

unsigned int Cube::vertices_length() const
{
    return vertex_num()*3*(sizeof(float));
}

unsigned int Cube::indices_length() const
{
    return triangle_vertices_num()*3*(sizeof(unsigned int));
}

void Cube::print() const
{
    _vertex_coordinates->print("cube vertex coordinate");
    _indices->print("cube triangle indices");
}

unsigned int Cube::triangle_vertices_num() const
{
    return 36;
}

void Cube::calculate_vertices_coordinates()
{
    float x = _length/2;
    float y = _width/2;
    float z = _hight/2;
    std::vector<float> trn= {x,y,-z};
    std::vector<float> tln= {-x,y,-z};
    std::vector<float> brn= {x,-y,-z};
    std::vector<float> bln= {-x,-y,-z};
    std::vector<float> trf= {x,y,z};
    std::vector<float> tlf= {-x,y,z};
    std::vector<float> brf= {x,-y,z};
    std::vector<float> blf= {-x,-y,z};
    _vertex_coordinates->push_back(trn);
    _vertex_coordinates->push_back(tln);
    _vertex_coordinates->push_back(brn);
    _vertex_coordinates->push_back(bln);
    _vertex_coordinates->push_back(trf);
    _vertex_coordinates->push_back(tlf);
    _vertex_coordinates->push_back(brf);
    _vertex_coordinates->push_back(blf);
}

void Cube::calculate_triangle_indices()
{
    std::vector<unsigned int> near_face_0={0,1,2};
    std::vector<unsigned int> near_face_1={1,3,2};
    std::vector<unsigned int> top_face_0={0,4,5};
    std::vector<unsigned int> top_face_1={0,5,1};
    std::vector<unsigned int> bottom_face_0={2,6,7};
    std::vector<unsigned int> bottom_face_1={2,7,3};
    std::vector<unsigned int> right_face_0={0,6,4};
    std::vector<unsigned int> right_face_1={0,2,6};
    std::vector<unsigned int> left_face_0={1,7,5};
    std::vector<unsigned int> left_face_1={1,7,3};
    std::vector<unsigned int> far_face_0={4,6,5};
    std::vector<unsigned int> far_face_1={5,7,6};
    _indices->push_back(near_face_0);
    _indices->push_back(near_face_1);
    _indices->push_back(right_face_0);
    _indices->push_back(right_face_1);
    _indices->push_back(left_face_0);
    _indices->push_back(left_face_1);
    _indices->push_back(top_face_0);
    _indices->push_back(top_face_1);
    _indices->push_back(bottom_face_0);
    _indices->push_back(bottom_face_1);
    _indices->push_back(far_face_0);
    _indices->push_back(far_face_1);
}

void Cube::calculate_texture_coordinates()
{
}

unsigned int Cube::triangle_num() const
{
    return 12;
}

unsigned int Cube::vertex_num() const
{
    return 8;
}
