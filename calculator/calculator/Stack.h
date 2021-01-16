#pragma once

//
// Created by aleks on 12/5/2019.
//

#ifndef CALCULATOR__STACK_H_
#define CALCULATOR__STACK_H_

#include <cassert>
#include <initializer_list>

#define size_of_increment 10

template <typename T>
class StackOnArray {
 public:
  StackOnArray();
  StackOnArray(const StackOnArray<T>& copied);
  StackOnArray(StackOnArray<T>&& transfered) noexcept;
  StackOnArray(std::initializer_list<T> L);

  ~StackOnArray();

  int Size();
  bool IsEmpty();
  void Push(const T& value);
  T* Top();
  T* Top() const;
  T Pop();

  bool operator==(const StackOnArray<T>& compared);
  bool operator!=(const StackOnArray<T>& compared);

 private:
  int size;
  int capacity = size_of_increment;
  T* data;
  int top;
  void expand();
};
template <typename T>
StackOnArray<T>::StackOnArray() {
  size = 0;
  top = -1;
  data = new T[size_of_increment];
  capacity = size_of_increment - 1;
}
template <typename T>
int StackOnArray<T>::Size() {
  return size;
}

template <typename T>
bool StackOnArray<T>::IsEmpty() {
  return size == 0;
}

template <typename T>
void StackOnArray<T>::Push(const T& value) {
  data[top + 1] = value;
  size++;
  top++;
  if (size - 1 == capacity) {
    (*this).expand();
  }
}

template <typename T>
void StackOnArray<T>::expand() {
  T* new_data = new T[capacity + size_of_increment];
  capacity += size_of_increment;
  for (int i = 0; i < size; i++) {
    new_data[i] = data[i];
  }
  delete[] data;
  data = new_data;
}
template <typename T>
T* StackOnArray<T>::Top() {
  return &data[top];
}

template <typename T>
T* StackOnArray<T>::Top() const {
  return &data[top];
}

template <typename T>
T StackOnArray<T>::Pop() {
  assert(size > 0 && "Size of Stack is zero");
  size--;
  T returned = data[top];
  data[top] = T();
  top--;
  return returned;
}
template <typename T>
bool StackOnArray<T>::operator==(const StackOnArray& compared) {
  if (size != compared.size) return false;
  for (int i = 0; i < size; i++) {
    if (data[i] != compared.data[i]) return false;
  }
  return true;
}

template <typename T>
bool StackOnArray<T>::operator!=(const StackOnArray& compared) {
  if (size != compared.size) return true;
  for (int i = 0; i < size; i++) {
    if (data[i] != compared.data[i]) return true;
  }
  return false;
}
template <typename T>
StackOnArray<T>::StackOnArray(const StackOnArray& copied)
    : capacity(copied.capacity), size(copied.size), top(copied.top) {
  T* newdata = new T[capacity];
  if (size > 0) {
    for (int i = 0; i < size; i++) {
      newdata[i] = copied.data[i];
    }
    delete[] data;
  }
  data = newdata;
}
template <typename T>
StackOnArray<T>::StackOnArray(StackOnArray<T>&& transfered) noexcept
    : size(transfered.size),
      capacity(transfered.capacity),
      top(transfered.top) {
  delete[] data;
  data = transfered.data;
  transfered.size = 0;
  transfered.capacity = 0;
  transfered.top = -1;
}

template <typename T>
StackOnArray<T>::StackOnArray(std::initializer_list<T> L) : size(0), top(-1) {
  data = new T[10];
  for (auto k : L) {
    Push(k);
  }
}

template <typename T>
StackOnArray<T>::~StackOnArray() {
  if (size != 0) {
    top = -1;
    size = 0;
    capacity = 0;
    delete[] data;
  }
}

#endif  // DYAVGO_PR_LAB11__STACKONARRAY_H_
