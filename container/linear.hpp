
#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************************************************************** */

#include "mappable.hpp"


/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    class LinearContainer
            : virtual public PreOrderMappableContainer<Data>, virtual public PostOrderMappableContainer<Data> {

    protected:

        inline LinearContainer() = default;

    public:

        // Destructor
        inline virtual ~LinearContainer() = default;


        /* ************************************************************************ */

        // Copy assignment
        LinearContainer<Data> &operator=(const LinearContainer<Data> &) = delete; // Copy assignment of abstract types is not possible.

        // Move assignment
        LinearContainer<Data> &operator=(LinearContainer<Data> &&) = delete; // Move assignment of abstract types is not possible.

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const LinearContainer<Data> &) const noexcept; // Comparison of abstract types is possible.
        bool operator!=(const LinearContainer<Data> &) const noexcept; // Comparison of abstract types is possible.

        /* ************************************************************************ */

        // Specific member functions

        virtual const Data& operator[](const unsigned long) const = 0;
        virtual Data& operator[](const unsigned long) = 0;

        virtual const Data& Front() const;
        virtual Data& Front();

        virtual const Data& Back() const;
        virtual Data& Back();

        /* ************************************************************************ */

        // Specific member function (inherited from TraversableContainer)

        using typename TraversableContainer<Data>::TraverseFun;

        void Traverse(TraverseFun) const override;

        /* ************************************************************************ */

        // Specific member function (inherited from PreOrderTraversableContainer)

        void PreOrderTraverse(TraverseFun) const override;

        /* ************************************************************************ */

        // Specific member function (inherited from PostOrderTraversableContainer)

        void PostOrderTraverse(TraverseFun) const override;

        /* ************************************************************************ */

        // Specific member function (inherited from MappableContainer)

        using typename MappableContainer<Data>::MapFun;

        void Map(MapFun) override;

        /* ************************************************************************ */

        // Specific member function (inherited from PreOrderMappableContainer)
        void PreOrderMap(MapFun) override;


        /* ************************************************************************ */

        // Specific member function (inherited from PostOrderMappableContainer)
        void PostOrderMap(MapFun) override;
    };

/* ************************************************************************** */

    template<typename Data>
    class SortableLinearContainer: public LinearContainer<Data> {

    private:

        void merge(unsigned long int s, unsigned long int m, unsigned long int e) noexcept;
        void mergeSort(unsigned long int s, unsigned long int e) noexcept;

    protected:

        inline SortableLinearContainer<Data>(): LinearContainer<Data>() = default;

    public:

        // Destructor
        inline virtual ~SortableLinearContainer() = default;

        /* ************************************************************************ */

        // Copy assignment
        SortableLinearContainer<Data>& operator=(const SortableLinearContainer<Data>&) = delete; // Copy assignment of abstract types is not possible.

        // Move assignment
        SortableLinearContainer<Data>& operator=(SortableLinearContainer<Data>&&) = delete; // Move assignment of abstract types is not possible.

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const SortableLinearContainer<Data>&) const noexcept; // Comparison of abstract types is possible.
        bool operator!=(const SortableLinearContainer<Data>&) const noexcept; // Comparison of abstract types is possible.

        /* ************************************************************************ */

        // Specific member function

        // type Sort() specifiers;
        inline void Sort() noexcept {
            if(Size() > 1)
                SortEntryProcess(0, Size() - 1);
        };


    protected:

        // DataComparison must returns 0 if the two data are equals, 1 if the first is greater than the second, -1 otherwise
        int DataComparison(const Data&, const Data&) const noexcept = 0;

        virtual inline void SortEntryProcess(unsigned long int start, unsigned long int end) noexcept {
            mergeSort(start, end);
        }
    };

/* ************************************************************************** */

}

#endif
