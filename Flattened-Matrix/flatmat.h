#include <iostream>
#include "Array.h"

template <class X> class row
{

  private:
  int size;
  int offset;
  X* start;

public:
  X& operator[](int index)
  {
    return *(start + index);
  }

  row(){};

  row(int size, X* start)
  {
    this->size = size;
    this->start = start;
  }
};

template <class X> class Matrix 
{

private:

  int width;
  int height;
  X* data;

  row<X>* rows;

public:

  row<X>& operator[](int index)
  {
    return (rows[index]);
  }

  Matrix() {};
  Matrix(int width, int height)
  {
    this->width = width;
    this->height = height;
    this->data = new X[width * height];

    rows = new row<X>[height];

    for(int i = 0; i < height; i++)
    {
      rows[i] = row<X>(width, &(data[i * width]));
    }

  }


  ~Matrix() {};

};