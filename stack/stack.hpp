
#ifndef STACK_HPP
#define STACK_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Stack: public Container<Data> {

private:

  // ...

protected:

  inline Stack(): Container<Data>{} = default; // Default constructor

public:

  // Destructor
  virtual ~Stack() = default;

  /* ************************************************************************ */

  // Copy assignment
  // Copy assignment of abstract types is not possible.
  virtual Stack& operator=(const Stack&) noexcept = delete; // Copy assignment

  // Move assignment
  // Move assignment of abstract types is not possible.
  virtual Stack& operator=(Stack&&) noexcept = delete; // Move assignment

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.
  virtual bool operator==(const Stack&) const noexcept = delete;
  virtual bool operator!=(const Stack&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // type Top() specifiers; // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual inline Data const & Top() const = 0;
  // type Top() specifiers; // (mutable version; concrete function must throw std::length_error when empty)
  virtual inline Data & Top() = 0;
  // type Pop() specifiers; // (concrete function must throw std::length_error when empty)
  virtual void Pop() = 0;
  // type TopNPop() specifiers; // (concrete function must throw std::length_error when empty)
  virtual inline Data TopNPop() {
    Data temp = Top();
    Pop();
    return temp;
  };
  // type Push(argument) specifiers; // Copy of the value
  virtual void Push(const Data &) = 0;
  // type Push(argument) specifiers; // Move of the value
  virtual void Push(Data &&) = 0;
};

/* ************************************************************************** */

}

#endif
