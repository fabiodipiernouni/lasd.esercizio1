
#ifndef TESTABLE_HPP
#define TESTABLE_HPP

/* ************************************************************************** */

#include "container.hpp"


/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    class TestableContainer : virtual public Container {


    protected:

        inline TestableContainer<Data>(): Container() = default;

    public:

        // Destructor
        virtual inline ~TestableContainer() = default;

        /* ************************************************************************ */

        // Copy assignment
        TestableContainer<Data> &operator=(const TestableContainer<Data> &)

        noexcept = delete; // Copy assignment of abstract types is not possible.


        // Move assignment
        TestableContainer<Data> &operator=(TestableContainer<Data> &&)

        noexcept = delete; // Move assignment of abstract types is not possible.

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const TestableContainer<Data> &) const

        noexcept = delete; // Comparison of abstract types is not possible.

        bool operator!=(const TestableContainer<Data> &) const

        noexcept = delete; // Comparison of abstract types is not possible.

        /* ************************************************************************ */

        // Specific member function

        // type Exists(argument) specifiers; // (concrete function should not throw exceptions)
        virtual bool Exists(const Data &) const noexcept = 0;

    };

/* ************************************************************************** */

}

#endif
