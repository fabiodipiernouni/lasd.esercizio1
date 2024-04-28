
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

/* ************************************************************************** */

#include "../../vector/vector.hpp"
#include "../queue.hpp"

#define INIT_SIZE 32

/* ************************************************************************** */

namespace lasd {

    /* ************************************************************************** */

    template<typename Data>
    class QueueVec : virtual public Queue<Data>, virtual protected Vector<Data> {

     private:
        const unsigned long int chunkSize = INIT_SIZE;

        inline unsigned long int QueueLength() const { return (rear - front + size) % size; }

        inline unsigned long int QueueSize() const { return size; }

     protected:
        using Vector<Data>::elements;
        using Vector<Data>::size;

        long int front = -1;
        long int rear = -1;

     public:
        // Default constructor
        inline QueueVec<Data>() : Vector<Data>(INIT_SIZE){};

        /* ************************************************************************ */

        // Specific constructor

        // A stack obtained from a TraversableContainer
        inline QueueVec<Data>(const TraversableContainer<Data> &);
        // A stack obtained from a MappableContainer
        inline QueueVec<Data>(MappableContainer<Data> &&);

        /* ************************************************************************ */

        // Copy constructor
        // QueueVec(argument);
        inline QueueVec<Data>(const QueueVec<Data> &queue) : Vector<Data>(queue) {
            front = queue.front;
            rear = queue.rear;
        }

        // Move constructor
        // QueueVec(argument);
        inline QueueVec<Data>(QueueVec<Data> &&queue) noexcept : Vector<Data>(std::move(queue)) {
            front = queue.front;
            rear = queue.rear;
            queue.Clear();
        }

        /* ************************************************************************ */

        // Destructor
        virtual ~QueueVec() = default;

        /* ************************************************************************ */

        // Copy assignment
        inline QueueVec &operator=(const QueueVec &queue) {
            Vector<Data>::operator=(queue);
            front = queue.front;
            rear = queue.rear;
            return *this;
        }

        // Move assignment
        inline QueueVec &operator=(QueueVec &&queue) noexcept {
            Vector<Data>::operator=(std::move(queue));
            front = queue.front;
            rear = queue.rear;
            return *this;
        }

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const QueueVec &queue) const noexcept;
        inline bool operator!=(const QueueVec &queue) const noexcept;

        /* ************************************************************************ */

        // Specific member functions (inherited from Queue)

        // Override Queue member (non-mutable version; throw std::length_error when empty)
        virtual inline Data const &Head() const override;

        // Override Queue member (mutable version; throw std::length_error when empty)
        virtual inline Data &Head() override;

        // Override Queue member (throw std::length_error when empty)
        virtual void Dequeue() override;

        // throw std::length_error when empty
        using Queue<Data>::HeadNDequeue; // using not needed, just to make code more readable

        // Override Queue member (copy of the value)
        virtual void Enqueue(const Data &value) override;

        // Override Queue member (move of the value)
        virtual void Enqueue(Data &&value) override;

        /* ************************************************************************ */

        // Specific member functions (inherited from Container)

        // Override Container member
        virtual inline bool Empty() const noexcept override { return front == -1 && rear == -1; }

        // Override Container member
        virtual inline unsigned long Size() const noexcept override { return QueueLength(); }

        /* ************************************************************************ */

        // manca resize?

        // Override ClearableContainer member
        inline void Clear() noexcept override {
            front = -1;
            rear = -1;
            Vector<Data>::Clear();
            elements = new Data[chunkSize];
        }

        // Override ResizableContainer member
        virtual void Resize(const unsigned long newSize) noexcept override;

     protected:
        // Auxiliary functions, if necessary!
        inline bool Full() const noexcept { return ((rear + 1) % ((long)size)) == front; } // if rear circulary incremented is equal to front, means that the queue is full
    };

    /* ************************************************************************** */

}// namespace lasd

#include "queuevec.cpp"

#endif
