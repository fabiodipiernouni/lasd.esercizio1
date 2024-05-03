
#ifndef STACK_HPP
#define STACK_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Stack: virtual public ClearableContainer {

protected:

  inline Stack() = default; // Default constructor

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
  // Comparison of abstract types is not possible.
  virtual bool operator==(const Stack&) const noexcept = delete;
  virtual bool operator!=(const Stack&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // (non-mutable version; throw std::length_error when empty)
  virtual inline Data const & Top() const = 0;
  // (mutable version; throw std::length_error when empty)
  virtual inline Data & Top() = 0;
  // throw std::length_error when empty
  virtual void Pop() = 0;
  // throw std::length_error when empty
  virtual inline Data TopNPop() {
    Data temp = Top();
    Pop();
    return temp;
  };
  // Copy of the value
  virtual void Push(const Data &) = 0;
  // Move of the value
  virtual void Push(Data &&) = 0;
};

/* ************************************************************************** */

}

#endif
