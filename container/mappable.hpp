
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
    class MappableContainer : virtual public TraversableContainer<Data> {


    private:

    protected:

        inline MappableContainer() = default;

    public:

        // Destructor
        inline virtual ~

        MappableContainer() = default;


        /* ************************************************************************ */

        // Copy assignment
        MappableContainer<Data> &operator=(const MappableContainer<Data> &) = delete;

        // Move assignment
        MappableContainer<Data> &operator=(MappableContainer<Data> &&)
        = delete;

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const MappableContainer<Data> &) const = delete;

        bool operator!=(const MappableContainer<Data> &) const = delete;

        /* ************************************************************************ */

        // Specific member function

        using MapFun = std::function<void(Data &)>;

        virtual void Map(MapFun) = 0;

    };

/* ************************************************************************** */

    template<typename Data>
    class PreOrderMappableContainer : public MappableContainer<Data>, public PreOrderTraversableContainer<Data> {


    protected:

        // constructor
        inline PreOrderMappableContainer() : MappableContainer<Data>(), PreOrderTraversableContainer<Data>()

        = default;

    public:

        // Destructor
        inline virtual ~PreOrderMappableContainer() = default;


        /* ************************************************************************ */

        // Copy assignment
        PreOrderMappableContainer<Data> &
        operator=(
                const PreOrderMappableContainer<Data> &) = delete; // Copy assignment of abstract types is not possible.

        // Move assignment
        PreOrderMappableContainer<Data> &
        operator=(PreOrderMappableContainer<Data> &&) = delete; // Move assignment of abstract types is not possible.

        /* ************************************************************************ */

        // Comparison operators
        bool
        operator==(
                const PreOrderMappableContainer<Data> &) const = delete; // Comparison of abstract types is not possible.
        bool
        operator!=(
                const PreOrderMappableContainer<Data> &) const = delete; // Comparison of abstract types is not possible.


        /* ************************************************************************ */

        // Specific member function

        using typename MappableContainer<Data>::MapFun;

        // type PreOrderMap(argument) specifiers;
        virtual void PreOrderMap(MapFun) = 0;

        /* ************************************************************************ */

        // Specific member function (inherited from MappableContainer)

        // type Map(argument) specifiers; // Override MappableContainer member
        void Map(MapFun) override;
    };

/* ************************************************************************** */

    template<typename Data>
    class PostOrderMappableContainer : public MappableContainer<Data>, public PostOrderTraversableContainer<Data> {

    protected:

        // constructor
        inline PostOrderMappableContainer() : MappableContainer<Data>(), PostOrderTraversableContainer<Data>()

        = default;

    public:

        // Destructor
        inline virtual ~PostOrderMappableContainer() = default;


        /* ************************************************************************ */

        // Copy assignment
        PostOrderMappableContainer<Data> &
        operator=(
                const PostOrderMappableContainer<Data> &) = delete; // Copy assignment of abstract types is not possible.

        // Move assignment
        PostOrderMappableContainer<Data> &
        operator=(PostOrderMappableContainer<Data> &&) = delete; // Move assignment of abstract types is not possible.

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(
                const PostOrderMappableContainer<Data> &) const = delete; // Comparison of abstract types is not possible.
        bool operator!=(
                const PostOrderMappableContainer<Data> &) const = delete; // Comparison of abstract types is not possible.

        /* ************************************************************************ */

        // Specific member function

        using typename MappableContainer<Data>::MapFun;

        virtual void PostOrderMap(MapFun) = 0;

        /* ************************************************************************ */

        // Specific member function (inherited from MappableContainer)

        void Map(MapFun) override;
    };

/* ************************************************************************** */

    template<typename Data>
    class InOrderMappableContainer : public MappableContainer<Data>, public InOrderTraversableContainer<Data> {

    protected:

        // constructor
        inline InOrderMappableContainer() : MappableContainer<Data>(), InOrderTraversableContainer<Data>()

        = default;

    public:

        // Destructor
        inline virtual ~InOrderMappableContainer() = default;

        /* ************************************************************************ */

        // Copy assignment
        InOrderMappableContainer<Data> &
        operator=(
                const InOrderMappableContainer<Data> &) = delete; // Copy assignment of abstract types is not possible.

        // Move assignment
        InOrderMappableContainer<Data> &
        operator=(InOrderMappableContainer<Data> &&) = delete; // Move assignment of abstract types is not possible.

        /* ************************************************************************ */

        // Comparison operators
        bool
        operator==(
                const InOrderMappableContainer<Data> &) const = delete; // Comparison of abstract types is not possible.
        bool
        operator!=(
                const InOrderMappableContainer<Data> &) const = delete; // Comparison of abstract types is not possible.

        /* ************************************************************************ */

        // Specific member function

        using typename MappableContainer<Data>::MapFun;

        // type InOrderMap(argument) specifiers;
        virtual void InOrderMap(MapFun) = 0;

        /* ************************************************************************ */

        // Specific member function (inherited from MappableContainer)

        // type Map(argument) specifiers; // Override MappableContainer member
        void Map(MapFun) override;
    };

/* ************************************************************************** */

    template<typename Data>
    class BreadthMappableContainer : public MappableContainer<Data>, public BreadthTraversableContainer<Data> {

    protected:

        // constructor
        inline BreadthMappableContainer() : MappableContainer<Data>(), BreadthTraversableContainer<Data>()

        = default;

    public:

        // Destructor
        inline virtual ~BreadthMappableContainer() = default;


        /* ************************************************************************ */

        // Copy assignment
        BreadthMappableContainer<Data> &
        operator=(
                const BreadthMappableContainer<Data> &) = delete; // Copy assignment of abstract types is not possible.

        // Move assignment
        BreadthMappableContainer<Data> &
        operator=(BreadthMappableContainer<Data> &&) = delete; // Move assignment of abstract types is not possible.


        /* ************************************************************************ */

        // Comparison operators
        bool
        operator==(
                const BreadthMappableContainer<Data> &) const = delete; // Comparison of abstract types is not possible.
        bool
        operator!=(
                const BreadthMappableContainer<Data> &) const = delete; // Comparison of abstract types is not possible.

        /* ************************************************************************ */

        // Specific member function

        using typename MappableContainer<Data>::MapFun;

        // type BreadthMap(argument) specifiers;
        virtual void BreadthMap(MapFun) = 0;

        /* ************************************************************************ */

        // Specific member function (inherited from MappableContainer)

        // type Map(argument) specifiers; // Override MappableContainer member
        void Map(MapFun) override;

    };

/* ************************************************************************** */

}

#endif
