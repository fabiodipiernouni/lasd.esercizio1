
#ifndef MAPPABLE_HPP
#define MAPPABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "traversable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    class MappableContainer : virtual public TraversableContainer<Data>


    private:

    // ...

    protected:

    inline MappableContainer() = default;

    public:

    // Destructor
    inline virtual ~MappableContainer() = default;


    /* ************************************************************************ */

    // Copy assignment
    MappableContainer<Data> &operator=(const MappableContainer<Data> &) = delete;

    // Move assignment
    MappableContainer<Data> &operator=(MappableContainer < Data > && )
    = delete;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const MappableContainer<Data> &) const = delete;

    bool operator!=(const MappableContainer<Data> &) const = delete;

    /* ************************************************************************ */

    // Specific member function

    using MapFun = std::function<void(Data & )>;

    virtual void Map(MapFun) = 0;

};

/* ************************************************************************** */

template<typename Data>
class PreOrderMappableContainer: public MappableContainer<Data>, public PreOrderTraversableContainer<Data>{

private:

    // ...

protected:

    // constructor
    inline PreOrderMappableContainer(): MappableContainer<Data>(), PreOrderTraversableContainer<Data>() = default;

public:

    // Destructor
    inline virtual ~PreOrderMappableContainer() = default;


    /* ************************************************************************ */

    // Copy assignment
    PreOrderMappableContainer<Data> &operator=(const PreOrderMappableContainer<Data> &) = delete; // Copy assignment of abstract types is not possible.

    // Move assignment
    PreOrderMappableContainer<Data> &operator=(PreOrderMappableContainer<Data> &&) = delete; // Move assignment of abstract types is not possible.

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const PreOrderMappableContainer<Data> &) const = delete; // Comparison of abstract types is not possible.
    bool operator!=(const PreOrderMappableContainer<Data> &) const = delete; // Comparison of abstract types is not possible.


    /* ************************************************************************ */

    // Specific member function

    using typename MappableContainer<Data>::MapFun;

    // type PreOrderMap(argument) specifiers;
    void PreOrderMap(MapFun) = 0;

    /* ************************************************************************ */

    // Specific member function (inherited from MappableContainer)

    // type Map(argument) specifiers; // Override MappableContainer member

};

/* ************************************************************************** */

template<typename Data>
class PostOrderMappableContainer {
    // Must extend MappableContainer<Data>,
    //             PostOrderTraversableContainer<Data>

private:

    // ...

protected:

    // ...

public:

    // Destructor
    // ~PostOrderMappableContainer() specifiers

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types is not possible.

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types is not possible.

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.

    /* ************************************************************************ */

    // Specific member function

    // using typename MappableContainer<Data>::MapFun;

    // type PostOrderMap(argument) specifiers;

    /* ************************************************************************ */

    // Specific member function (inherited from MappableContainer)

    // type Map(argument) specifiers; // Override MappableContainer member

};

/* ************************************************************************** */

template<typename Data>
class InOrderMappableContainer {
    // Must extend MappableContainer<Data>,
    //             InOrderTraversableContainer<Data>

private:

    // ...

protected:

    // ...

public:

    // Destructor
    // ~InOrderMappableContainer() specifiers

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types is not possible.

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types is not possible.

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.

    /* ************************************************************************ */

    // Specific member function

    // using typename MappableContainer<Data>::MapFun;

    // type InOrderMap(argument) specifiers;

    /* ************************************************************************ */

    // Specific member function (inherited from MappableContainer)

    // type Map(argument) specifiers; // Override MappableContainer member

};

/* ************************************************************************** */

template<typename Data>
class BreadthMappableContainer {
    // Must extend MappableContainer<Data>,
    //             BreadthTraversableContainer<Data>

private:

    // ...

protected:

    // ...

public:

    // Destructor
    // ~BreadthMappableContainer() specifiers

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types is not possible.

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types is not possible.

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.

    /* ************************************************************************ */

    // Specific member function

    // using typename MappableContainer<Data>::MapFun;

    // type BreadthMap(argument) specifiers;

    /* ************************************************************************ */

    // Specific member function (inherited from MappableContainer)

    // type Map(argument) specifiers; // Override MappableContainer member

};

/* ************************************************************************** */

}

#include "mappable.cpp"

#endif
