#include "sphere.h"

Sphere::Sphere(model_type type) :
    _slice_num(2), _slice_vertices_num(4), _radius(1), BaseShape(type) {
    _triangle_num = 2 * _slice_vertices_num + (_slice_num - 2) * 2;
    _vertex_num = (_slice_num - 1) * _slice_vertices_num + 2;
    _vertex_coordinates = std::make_shared<VertexCoordinates>(_vertex_num);
    _indices = std::make_shared<TriangleIndices>(_triangle_num);
}
Sphere::Sphere(unsigned int slice_num, unsigned int slice_vertices_num, unsigned int radius,model_type type) :
    _slice_num(slice_num), _slice_vertices_num(slice_vertices_num), _radius(radius), BaseShape(type) {
    std::cout << "init Sphere" << std::endl;
    _triangle_num = 2 * _slice_vertices_num + (_slice_num - 1) * _slice_vertices_num * 2;
    _vertex_num = (_slice_num - 1) * _slice_vertices_num + 2;
    _vertex_coordinates = std::make_shared<VertexCoordinates>(_vertex_num);
    _indices = std::make_shared<TriangleIndices>(_triangle_num);
}

Sphere::~Sphere()
{
}

unsigned int Sphere::vertices_length() const
{
    return _vertex_num*3*sizeof(float);
}

unsigned int Sphere::indices_length() const
{
    return _triangle_num*3*sizeof(unsigned int);
}

unsigned int Sphere::triangle_vertices_num() const
{
    return _triangle_num*3;
}

std::vector<float> Sphere::calculate_coordinate(float theta, float phi)
{
    float x = (float) _radius * cos(theta) * cos(phi);
    float y = (float) _radius * sin(theta);
    float z = (float) _radius * cos(theta) * sin(phi);
    std::vector<float> coordinate = {x, y, z};
    return coordinate;
}


void Sphere::calculate_vertices_coordinates()
{
    float base_theta = M_PI / _slice_num;
    float base_phi = 2 * M_PI / _slice_vertices_num;
    std::vector<float> first_vertices = {0, -(float) _radius, 0};
    _vertex_coordinates->push_back(first_vertices);
    for (int i = 1; i < _slice_num; i++) {
        float theta = -(M_PI / 2) + base_theta * i;
        for (int j = 0; j < _slice_vertices_num; j++) {
            float phi = j * base_phi;
            std::vector<float> coordinate = calculate_coordinate(theta, phi);
            _vertex_coordinates->push_back(coordinate);
        }
    }
    std::vector<float> last_vertices = {0, (float) _radius, 0};
    _vertex_coordinates->push_back(last_vertices);
}

void Sphere::calculate_triangle_indices()
{
    for (unsigned int i = 1; i <= _slice_vertices_num; i++) {
        if (i == _slice_vertices_num) {
            std::vector<unsigned int> value = {0, i, 1};
            _indices->push_back(value);
        } else {
            std::vector<unsigned int> value = {0, i, i + 1};
            _indices->push_back(value);
        }
    }
    for (int i = 0; i < _slice_num - 2; i++) {
        for (int j = 0; j < _slice_vertices_num; j++) {
            unsigned int a = i * _slice_vertices_num + 1 + j;
            unsigned int b = (i + 1) * _slice_vertices_num + 1 + j;
            unsigned int c = b + 1;
            unsigned int d = a + 1;
            if (a % _slice_vertices_num == 0) {
                d = i * _slice_vertices_num + 1;
                c = (i + 1) * _slice_vertices_num + 1;
            }
            std::vector<unsigned int> triangle_one = {a, b, c};
            std::vector<unsigned int> triangle_two = {a, c, d};
            _indices->push_back(triangle_one);
            _indices->push_back(triangle_two);
        }
    }
    unsigned int last_slice_index_start = _vertex_num - _slice_vertices_num - 1;
    for (int i = 0; i < _slice_vertices_num; i++) {
        if (i == _slice_vertices_num - 1) {
            std::vector<unsigned int> value = {last_slice_index_start + i, _vertex_num - 1,
                                               last_slice_index_start};
            _indices->push_back(value);
        } else {
            std::vector<unsigned int> value = {last_slice_index_start + i, _vertex_num - 1,
                                               last_slice_index_start + i + 1};
            _indices->push_back(value);
        }
    }
}

void Sphere::calculate_texture_coordinates()
{
}

unsigned int Sphere::triangle_num() const
{
    return _triangle_num;
}

unsigned int Sphere::vertex_num() const
{
    return _vertex_num;
}

void Sphere::print() const
{
    _vertex_coordinates->print("sphere vertices coordinates");
    _indices->print("sphere triangle indices");
}

