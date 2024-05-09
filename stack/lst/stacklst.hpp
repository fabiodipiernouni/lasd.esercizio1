
#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../../list/list.hpp"
#include "../stack.hpp"

/* ************************************************************************** */

namespace lasd {

    /* ************************************************************************** */

    template<typename Data>
    class StackLst : virtual public Stack<Data>, virtual protected List<Data> {

     private:
     protected:
        using List<Data>::head;
        using List<Data>::tail;

     public:
        // Default constructor
        inline StackLst() = default;

        /* ************************************************************************ */

        // Specific constructor
        // StackLst(argument) specifiers; // A stack obtained from a TraversableContainer
        inline StackLst(const TraversableContainer<Data> &) noexcept;
        // StackLst(argument) specifiers; // A stack obtained from a MappableContainer
        inline StackLst(MappableContainer<Data> &&) noexcept;

        /* ************************************************************************ */

        // Copy constructor
        inline StackLst(const StackLst<Data> &stack) : List<Data>(stack) {
            //std::cout << "Invocato costruttore copia const." << std::endl;
        }

        // Move constructor
        inline StackLst(StackLst<Data> &&stack) noexcept : List<Data>(std::move(stack)) {
            //std::cout << "Invocato costruttore copia move." << std::endl;
        }

        /* ************************************************************************ */

        // Destructor
        virtual ~StackLst() = default;

        /* ************************************************************************ */

        // Copy assignment
        // type operator=(argument);
        virtual inline StackLst<Data>& operator=(const StackLst<Data>& stack) noexcept {
            List<Data>::operator=(stack);
            return *this;
        }

        // Move assignment
        // type operator=(argument);
        virtual inline StackLst<Data>& operator=(StackLst<Data>&& stack) noexcept {
            List<Data>::operator=(std::move(stack));
            return *this;
        }

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const StackLst<Data>&) const noexcept;
        inline bool operator!=(const StackLst<Data>& stack) const noexcept { return !operator==(stack); }

        /* ************************************************************************ */

        // Specific member functions (inherited from Stack)

        // Override Stack member (non-mutable version; throw std::length_error when empty)
        inline const Data& Top() const override { return List<Data>::Front(); }
            
        // Override Stack member (non-mutable version; throw std::length_error when empty)
        inline Data& Top() override { return List<Data>::Front(); }

        // Override Stack member (throw std::length_error when empty)
        inline void Pop() override { List<Data>::RemoveFromFront(); }

        // Override Stack member (throw std::length_error when empty)
        inline Data TopNPop() override { return List<Data>::FrontNRemove(); }

        // Override Stack member (copy of the value)
        inline void Push(const Data& value) override {
            //std::cout << "Richiamato StackLst<Data>::Push(Copy) per value " << value << std::endl;
            List<Data>::InsertAtFront(value); }

        // Override Stack member (move of the value)
        inline void Push(Data&& value) override {
            //std::cout << "Richiamato StackLst<Data>::Push(Copy) per value " << value << std::endl;
            List<Data>::InsertAtFront(std::move(value)); }

        /* ************************************************************************ */

        // Specific member function (inherited from ClearableContainer)

        using List<Data>::Clear;

        /*virtual inline void PrintAll() const override {
            //std::cout << "Printing StackLst elements:" << std::endl;
            List<Data>::PrintAll();
        }*/

     protected:
        // Auxiliary functions, if necessary!
    };

    /* ************************************************************************** */

}// namespace lasd

#include "stacklst.cpp"

#endif
