#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm>
#include <cassert>


template <class T>
class Matrix
//
// Provides a "2-dimensional" rectagular
// array-like structure for indexing using
// a pair of indices.
{
public:
  Matrix();

  Matrix (unsigned theLength1, unsigned theLength2);

  Matrix (const Matrix<T>&);

  ~Matrix();

  const Matrix<T>& operator= (const Matrix<T>&);


  // Indexing into the matrix: What we would like to do is allow
  // myMatrix[i,j]. But C++ allows operator[] only to take a single
  // parameter. But operator() can take whatever parameters we like.
  // So we can write myMatrix(i,j).
  T& operator() (int i1, int i2);
  const T& operator() (int i1, int i2) const;

  unsigned length1() const;
  unsigned length2() const;


  bool operator== (const Matrix<T>&) const;
  
  
private:
  T* data;
  unsigned _length1;
  unsigned _length2;
  
};


template <class T>
Matrix<T>::Matrix()
  : data(0), _length1(0), _length2(0)
{}


template <class T>
Matrix<T>::Matrix(unsigned theLength1, unsigned theLength2)
  : _length1(theLength1), _length2(theLength2)
{
  data = new T[theLength1*theLength2];
}


template <class T>
Matrix<T>::Matrix(const Matrix<T>& m)
  : _length1(m._length1), _length2(m._length2)
{
  data = new T[_length1*_length2];
  std::copy (m.data, m.data+_length1*_length2, data);
}


template <class T>
Matrix<T>::~Matrix()
{
  delete [] data;
}


template <class T>
const Matrix<T>& Matrix<T>::operator= (const Matrix<T>& m)
{
  if (this != &m)
  {
    if (_length1*_length2 < m._length1*m._length2)
    {
      delete [] data;
      data = new T[m._length1*m._length2];
    }
    _length1 = m._length1;
    _length2 = m._length2;
    copy (m.data, m.data+_length1*_length2, data);
  }
  return *this;
}



// Indexing into the matrix: What we would like to do is allow
// myMatrix[i,j]. But C++ allows operator[] only to take a single
// parameter. But operator() can take whatever parameters we like.
// So we can write myMatrix(i,j).
template <class T>
T& Matrix<T>::operator() (int i1, int i2)
{
  assert ((i1 >= 0) && ((unsigned)i1 < _length1));
  assert ((i2 >= 0) && ((unsigned)i2 < _length2));
  return data[i1 + _length1*i2];
}


template <class T>
const T& Matrix<T>::operator() (int i1, int i2) const
{
  assert ((i1 >= 0) && (i1 < _length1));
  assert ((i2 >= 0) && (i2 < _length2));
  return data[i1 + _length1*i2];
}


template <class T>
inline
unsigned Matrix<T>::length1() const
{
  return _length1;
}



template <class T>
inline
unsigned Matrix<T>::length2() const
{
  return _length2;
}


template <class T>
bool Matrix<T>::operator== (const Matrix<T>& m) const
{
  return (_length1 == m._length1)
    && (_length2 == m._length2)
    && equal (data, data+_length1*_length2, m.data);
}

#endif
