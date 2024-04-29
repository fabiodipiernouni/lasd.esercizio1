
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

    /* ************************************************************************** */

    template<typename Data>
    class Vector : virtual public ResizableContainer, virtual public LinearContainer<Data> {

     protected:
        using Container::size;
        Data *elements = nullptr;

     public:
        // Default constructor
        inline Vector<Data>() { this->size = 0;};

        /* ************************************************************************ */

        // Specific constructors

        // A vector with a given initial dimension
        Vector(const unsigned long int);

        // A vector obtained from a TraversableContainer
        Vector(const TraversableContainer<Data> &);

        // A vector obtained from a MappableContainer
        Vector(MappableContainer<Data> &&);

        /* ************************************************************************ */

        // Copy constructor
        Vector(const Vector<Data> &);

        // Move constructor
        Vector(Vector<Data> &&) noexcept;

        /* ************************************************************************ */

        // Destructor
        virtual ~Vector();

        /* ************************************************************************ */

        // Copy assignment
        Vector<Data> &operator=(const Vector<Data> &);

        // Move assignment
        Vector<Data> &operator=(Vector<Data> &&) noexcept;

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const Vector<Data> &) const noexcept;
        inline bool operator!=(const Vector<Data> &other) const noexcept { return !operator==(other); };

        /* ************************************************************************ */

        // Specific member function (inherited from ClearableContainer)

        // ClearableContainer member
        virtual void Clear() noexcept override;

        /* ************************************************************************ */

        // Specific member function (inherited from ResizableContainer)

        // ResizableContainer member
        virtual void Resize(const unsigned long int) noexcept override;

        /* ************************************************************************ */

        // Specific member functions (inherited from LinearContainer)

        // LinearContainer member (throw std::out_of_range when out of range)
        virtual const Data &operator[](const unsigned long) const override;
        // LinearContainer member (throw std::out_of_range when out of range)
        virtual Data &operator[](const unsigned long) override;

        // LinearContainer member (throw std::length_error when empty)
        virtual const Data &Front() const override;
        // LinearContainer member (throw std::length_error when empty)
        virtual Data &Front() override;

        // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
        virtual const Data &Back() const override;
        // Override (Mutable) LinearContainer member (must throw std::length_error when empty)
        virtual Data &Back() override;

        virtual inline void PrintAll() {
            unsigned long int i = 0;
            this->Traverse([&i](const Data &data) { std::cout << "ARRAY - DATO" << i << " : " << data << std::endl; });
        }


     protected:
        // Auxiliary functions, if necessary!

        virtual void Copy(const Vector &);
    };

    /* ************************************************************************** */

    template<typename Data>
    class SortableVector : virtual public Vector<Data>, virtual public SortableLinearContainer<Data> {

     protected:
        // Type for comparison function
        using ComparisonFunction = std::function<int(const Data &, const Data &)>;

        // Property for comparison function
        ComparisonFunction compare{nullptr};

        using Container::size;
        using Vector<Data>::elements;

     public:
        // Default constructor
        inline SortableVector<Data>() = default;

        /* ************************************************************************ */

        inline SortableVector<Data>(ComparisonFunction compareDataFunction) : Vector<Data>(), SortableLinearContainer<Data>() {
            compare = compareDataFunction;
        };

        // Specific constructors

        // A vector with a given initial dimension
        inline SortableVector(const unsigned long int size) : Vector<Data>(size), SortableLinearContainer<Data>(){};

        // A vector obtained from a TraversableContainer
        inline SortableVector(const TraversableContainer<Data> &container) : Vector<Data>(container), SortableLinearContainer<Data>(){};

        // A vector obtained from a MappableContainer
        inline SortableVector(MappableContainer<Data> &&container) : Vector<Data>(std::move(container)) {};

        /* ************************************************************************ */

        // Copy constructor
        inline SortableVector(const SortableVector<Data> &sv) : Vector<Data>(sv){};

        // Move constructor
        inline SortableVector(SortableVector<Data> &&sv) noexcept : Vector<Data>(std::move(sv)){};

        /* ************************************************************************ */

        // Destructor
        virtual ~SortableVector() = default;

        /* ************************************************************************ */

        // Copy assignment
        inline SortableVector<Data> &operator=(const SortableVector<Data> &);

        // Move assignment
        inline SortableVector<Data> &operator=(SortableVector<Data> &&) noexcept;


     protected:
        int DataComparison(const Data &dataLeft, const Data &dataRight) const noexcept override {
            if (compare != nullptr) {
                return compare(dataLeft, dataRight);
            } else {
                // This means that Data implements > and < operators, so compare doesn't need to be defined
                return dataLeft == dataRight ? 0 : (dataLeft < dataRight ? -1 : 1);
            }
        }
    };

    /* ************************************************************************** */

}// namespace lasd

#include "vector.cpp"

#endif
