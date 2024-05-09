
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */

namespace lasd {

    /* ************************************************************************** */

    class Container {

     protected:
        unsigned long int size;

        /* ************************************************************************ */

        // Default constructor
        inline Container() : size(0){};

     public:
        // Destructor
        virtual inline ~Container() = default;

        /* ************************************************************************ */

        // Copy assignment
        Container &operator=(const Container &) noexcept = delete;// Copy assignment of abstract types is not possible.

        // Move assignment
        Container &operator=(Container &&) noexcept = delete;// Move assignment of abstract types is not possible.

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const Container &) const noexcept = delete;// Comparison of abstract types is not possible.
        bool operator!=(const Container &) const noexcept = delete;// Comparison of abstract types is not possible.

        /* ************************************************************************ */

        // Specific member functions

        // (concrete function should not throw exceptions)

        virtual inline bool Empty() const noexcept { return size == 0; }

        // (concrete function should not throw exceptions)
        virtual inline unsigned long int Size() const noexcept { return size; }
    };

    /* ************************************************************************** */

    class ClearableContainer : virtual public Container {

     protected:
        inline ClearableContainer() = default;

     public:
        // Destructor
        virtual inline ~ClearableContainer() = default;

        /* ************************************************************************ */

        // Copy assignment
        ClearableContainer &operator=(const ClearableContainer &) noexcept = delete;// Copy assignment of abstract types is not possible.

        // Move assignment
        ClearableContainer &operator=(ClearableContainer &&) noexcept = delete;

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const ClearableContainer &) const noexcept = delete;// Comparison of abstract types is not possible.
        bool operator!=(const ClearableContainer &) const noexcept = delete;// Comparison of abstract types is not possible.

        // Specific member functions

        // type Clear() specifiers;
        virtual void Clear() noexcept = 0;
    };

    /* ************************************************************************** */

    class ResizableContainer : virtual public ClearableContainer {

     protected:
        inline ResizableContainer() = default;

     public:
        // Destructor
        virtual inline ~ResizableContainer() = default;

        /* ************************************************************************ */

        // Copy assignment
        ResizableContainer &operator=(const ResizableContainer &) noexcept = delete;// Copy assignment of abstract types is not possible.

        // Move assignment
        ResizableContainer &operator=(ResizableContainer &&) noexcept = delete;// Move assignment of abstract types is not possible.

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const ResizableContainer &) const noexcept = delete;// Comparison of abstract types is not possible.

        bool operator!=(const ResizableContainer &) const noexcept = delete;// Comparison of abstract types is not possible.

        /* ************************************************************************ */

        virtual void Resize(unsigned long int) noexcept = 0;

        /* ************************************************************************ */

        //because the Clear in ClearableContainer is marked with noexcept, this function must be marked with noexcept as well
        inline void Clear() noexcept override { Resize(0); }
    };

}// namespace lasd

#endif
