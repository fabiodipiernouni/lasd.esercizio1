
#ifndef TRAVERSABLE_HPP
#define TRAVERSABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "testable.hpp"

/* ************************************************************************** */

namespace lasd {

    /* ************************************************************************** */

    template<typename Data>
    class TraversableContainer : virtual public TestableContainer<Data> {

     protected:
        // constructor
        inline TraversableContainer<Data>() : TestableContainer<Data>() = default;

     public:
        // Destructor
        virtual inline ~TraversableContainer() = default;

        /* ************************************************************************ */

        // Copy assignment
        TraversableContainer<Data> &
        operator=(const TraversableContainer<Data> &) = delete;// Copy assignment of abstract types is not possible.

        // Move assignment
        TraversableContainer<Data> &operator=(TraversableContainer<Data> &&) noexcept = delete;// Move assignment of abstract types is not possible.

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const TraversableContainer<Data> &) const noexcept = delete;// Comparison of abstract types is not possible.
        bool operator!=(const TraversableContainer<Data> &) const noexcept = delete;// Comparison of abstract types is not possible.

        /* ************************************************************************ */

        // Specific member function

        using TraverseFun = std::function<void(const Data &)>;

        // type Traverse(arguments) specifiers;
        virtual void Traverse(TraverseFun) const = 0;

        template<typename Accumulator>
        using FoldFun = std::function<Accumulator(const Data &, const Accumulator &)>;

        template<typename Accumulator>
        Accumulator Fold(FoldFun<Accumulator>, const Accumulator &) const;

        /* ************************************************************************ */

        // Specific member function (inherited from TestableContainer)

        bool Exists(const Data &) const noexcept override;
    };

    /* ************************************************************************** */

    template<typename Data>
    class PreOrderTraversableContainer : virtual public TraversableContainer<Data> {

     protected:
        inline PreOrderTraversableContainer<Data>() : TraversableContainer<Data>() = default;

     public:
        // Destructor
        virtual inline ~PreOrderTraversableContainer() = default;

        /* ************************************************************************ */

        // Copy assignment
        PreOrderTraversableContainer<Data> &operator=(const PreOrderTraversableContainer<Data> &) = delete;// Copy assignment of abstract types is not possible.

        // Move assignment
        PreOrderTraversableContainer<Data> &operator=(PreOrderTraversableContainer<Data> &&) noexcept = delete;// Move assignment of abstract types is not possible.

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const PreOrderTraversableContainer<Data> &) const noexcept = delete;// Comparison of abstract types is not possible.
        bool operator!=(const PreOrderTraversableContainer<Data> &) const noexcept = delete;// Comparison of abstract types is not possible.

        /* ************************************************************************ */

        // Specific member function

        using typename TraversableContainer<Data>::TraverseFun;

        virtual void PreOrderTraverse(TraverseFun) const = 0;

        template<typename Accumulator>
        using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

        template<typename Accumulator>
        virtual Accumulator PreOrderFold(FoldFun<Accumulator>, const Accumulator &) const;

        /* ************************************************************************ */

        // Specific member function (inherited from TraversableContainer)

        virtual inline void Traverse(TraverseFun visit) const override {
            PreOrderTraverse(visit);
        }
    };

    /* ************************************************************************** */

    template<typename Data>
    class PostOrderTraversableContainer : virtual public TraversableContainer<Data> {

     protected:
        inline PostOrderTraversableContainer<Data>() : TraversableContainer<Data>() = default;

     public:
        // Destructor
        virtual inline ~PostOrderTraversableContainer() = default;

        /* ************************************************************************ */

        // Copy assignment
        PostOrderTraversableContainer<Data> &operator=(const PostOrderTraversableContainer<Data> &) = delete;// Copy assignment of abstract types is not possible.

        // Move assignment
        PostOrderTraversableContainer<Data> &operator=(PostOrderTraversableContainer<Data> &&) noexcept = delete;// Move assignment of abstract types is not possible.

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const PostOrderTraversableContainer<Data> &) const noexcept = delete;// Comparison of abstract types is not possible.
        bool operator!=(const PostOrderTraversableContainer<Data> &) const noexcept = delete;// Comparison of abstract types is not possible.

        /* ************************************************************************ */

        // Specific member function

        using typename TraversableContainer<Data>::TraverseFun;

        virtual void PostOrderTraverse(TraverseFun) const = 0;

        template<typename Accumulator>
        using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

        template<typename Accumulator>
        virtual Accumulator PostOrderFold(FoldFun<Accumulator>, const Accumulator &) const;

        /* ************************************************************************ */

        // Specific member function (inherited from TraversableContainer)

        virtual inline void Traverse(TraverseFun visit) const override {
            PostOrderTraverse(visit);
        }
    };

    /* ************************************************************************** */

    template<typename Data>
    class InOrderTraversableContainer : virtual public TraversableContainer<Data> {

     protected:
        inline InOrderTraversableContainer<Data>() : TraversableContainer<Data>() = default;

     public:
        // Destructor
        virtual inline ~InOrderTraversableContainer() = default;

        /* ************************************************************************ */

        // Copy assignment
        InOrderTraversableContainer<Data> &operator=(const InOrderTraversableContainer<Data> &) = delete;// Copy assignment of abstract types is not possible.

        // Move assignment
        InOrderTraversableContainer<Data> &operator=(InOrderTraversableContainer<Data> &&) noexcept = delete;// Move assignment of abstract types is not possible.

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const InOrderTraversableContainer<Data> &) const noexcept = delete;// Comparison of abstract types might be possible.
        bool operator!=(const InOrderTraversableContainer<Data> &) const noexcept = delete;// Comparison of abstract types might be possible.

        /* ************************************************************************ */

        // Specific member function

        using typename TraversableContainer<Data>::TraverseFun;

        virtual void InOrderTraverse(TraverseFun) const = 0;

        template<typename Accumulator>
        using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

        template<typename Accumulator>
        virtual Accumulator InOrderFold(FoldFun<Accumulator>, const Accumulator &) const;

        /* ************************************************************************ */

        virtual inline void Traverse(TraverseFun visit) const override {
            InOrderTraverse(visit);
        };
    };

    /* ************************************************************************** */

    template<typename Data>
    class BreadthTraversableContainer : virtual public TraversableContainer<Data> {

     protected:
        inline BreadthTraversableContainer<Data>() : TraversableContainer<Data>() = default;

     public:
        // Destructor
        virtual inline ~BreadthTraversableContainer() = default;

        /* ************************************************************************ */

        // Copy assignment
        BreadthTraversableContainer<Data> &operator=(const BreadthTraversableContainer<Data> &) = delete;// Copy assignment of abstract types is not possible.

        // Move assignment
        BreadthTraversableContainer<Data> &operator=(BreadthTraversableContainer<Data> &&) noexcept = delete;// Move assignment of abstract types is not possible.

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const BreadthTraversableContainer<Data> &) const noexcept = delete;// Comparison of abstract types might be possible.
        bool operator!=(const BreadthTraversableContainer<Data> &) const noexcept = delete;// Comparison of abstract types might be possible.

        /* ************************************************************************ */

        // Specific member function

        using typename TraversableContainer<Data>::TraverseFun;

        virtual void BreadthTraverse(TraverseFun) const = 0;

        template<typename Accumulator>
        using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

        template<typename Accumulator>
        virtual Accumulator BreadthFold(FoldFun<Accumulator>, const Accumulator &) const;

        /* ************************************************************************ */

        // Specific member function (inherited from TraversableContainer)

        virtual inline void Traverse(TraverseFun visit) const override {
            BreadthTraverse(visit);
        };
    };

    /* ************************************************************************** */

}// namespace lasd

#endif
