
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../../vector/vector.hpp"
#include "../stack.hpp"

/* ************************************************************************** */

namespace lasd {

    /* ************************************************************************** */

    template<typename Data>
    class StackVec : virtual public Stack<Data>, virtual protected Vector<Data> {

     private:
        const unsigned long int chunkSize = 32;


     protected:
        using Vector<Data>::elements;

        unsigned long int top = -1;

     public:
        // Default constructor
        StackVec<Data>() : Vector<Data>(chunkSize) {  };
        

        /* ************************************************************************ */

        // Specific constructor

        // A stack obtained from a TraversableContainer
        StackVec(const TraversableContainer<Data>&);

        // A stack obtained from a MappableContainer
        StackVec(MappableContainer<Data> &&);

        /* ************************************************************************ */

        // Copy constructor
        inline StackVec(const StackVec<Data>& stack): Vector<Data>(stack) {
            top = stack.top;
        }

        // Move constructor
        inline StackVec(StackVec<Data>&& stack) noexcept : Vector<Data>(std::move(stack)) {
            top = stack.top;
            stack.Clear();
        }

        /* ************************************************************************ */

        // Destructor
        virtual ~StackVec() = default;

        /* ************************************************************************ */

        // Copy assignment
        virtual StackVec<Data> operator=(const StackVec<Data>&) noexcept;

        // Move assignment
        virtual StackVec<Data> operator=(StackVec<Data>&&) noexcept;

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const StackVec<Data>&) const noexcept;
        inline bool operator!=(const StackVec<Data>&) const noexcept { return !operator==(stack); };

        /* ************************************************************************ */

        // Specific member functions (inherited from Stack)

        // Override Stack member (non-mutable version; throw std::length_error when empty)
        virtual inline const Data& Top() const override { return Vector<Data>::operator[](top); };
        // Override Stack member (mutable version; throw std::length_error when empty)
        virtual inline Data& Top() override { return Vector<Data>::operator[](top); };
        // Override Stack member (throw std::length_error when empty)
        virtual inline void Pop() override;
        // Override Stack member (throw std::length_error when empty)
        virtual inline Data TopNPop() override { Data temp = Top(); Pop(); return temp; };

        // Override Stack member (copy of the value)
        virtual void Push(const Data&) override;

        // Override Stack member (move of the value)
        virtual void Push(Data&&) override;

        /* ************************************************************************ */

        // Specific member functions (inherited from Container)

        // Override Container member
        virtual inline bool Empty() const noexcept override { return top == -1; };

        // Override Container member
        virtual inline unsigned long int Size() const noexcept override { return top + 1; };

        /* ************************************************************************ */

        // Specific member function (inherited from ClearableContainer)

        // Override ClearableContainer member
        virtual void Clear() noexcept override;

        // Override ResizableContainer member
        virtual void Resize (const unsigned long newSize) noexcept override;


     protected:
        // Auxiliary functions, if necessary!
    };

    /* ************************************************************************** */

}// namespace lasd

#endif
