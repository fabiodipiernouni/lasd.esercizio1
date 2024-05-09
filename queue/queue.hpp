
#ifndef QUEUE_HPP
#define QUEUE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Queue: virtual public ClearableContainer {

protected:

  inline Queue<Data>() = default;

public:

  // Destructor
  virtual ~Queue() = default;

  /* ************************************************************************ */

  // Copy assignment
  virtual Queue& operator=(const Queue&) noexcept = delete;

  // Move assignment
  virtual Queue& operator=(Queue&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  virtual bool operator==(const Queue&) const noexcept = delete;
  virtual bool operator!=(const Queue&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // not mutable version, throw std::length_error when empty
  virtual Data const& Head() const = 0;

  // mutable version, throw std::length_error when empty
  virtual Data& Head() = 0;

  // throw std::length_error when empty
  virtual void Dequeue() = 0;

  // throw std::length_error when empty
  virtual inline Data HeadNDequeue() {
    Data temp = Head();
    Dequeue();
    return temp;
  };

  // type Enqueue(argument) specifiers; // Copy of the value
  virtual void Enqueue(const Data&) = 0;
  // type Enqueue(argument) specifiers; // Move of the value
  virtual void Enqueue(Data&&) = 0;
};

/* ************************************************************************** */

}

#endif
