#ifndef MULTIDIMENSIONDATA_H
#define MULTIDIMENSIONDATA_H
#include <vector>
#include <iostream>
#include <QDebug>

template<typename T,unsigned int _D>
class MultiDimensionData
{
public:
    MultiDimensionData(unsigned int element_num){
        _size = element_num;
        _length = _size*_D;
        _data = (T*)malloc(sizeof(T)*_length);
    }
    ~MultiDimensionData(){
        if(_data){
            free(_data);
            _data = nullptr;
        }
    }
    void push_back(std::vector<T> value){

        if(value.size() != _D){
            std::cerr<<"value except "<<_D<<" dimension,but give "<<value.size()<<" dimension value"<<std::endl;
            exit(-1);
        }
        for(int i = 0;i<_D;i++){
            _data[_end_index] = value[i];
            _end_index++;
        }
    }
    T* data() const{
        return _data;
    }
    void print(const std::string &info) const{

        std::cout<<"++++++++++++++"<<info<<"+++++++++++++++++++"<<std::endl;
        for (int i = 0; i < _size; i++) {
            for (int j = 0; j < _D; j++) {
                std::cout << _data[i * _D + j] << "  ";
            }
            std::cout << std::endl;
        }
    }
private:
    T* _data = nullptr;
    unsigned int _end_index =0;
    unsigned int _size;
    unsigned int _length;
};

#endif // MULTIDIMENSIONDATA_H
