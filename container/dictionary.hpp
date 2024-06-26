
#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

/* ************************************************************************** */

#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

    /* ************************************************************************** */

    template<typename Data>
    class DictionaryContainer : virtual public TestableContainer<Data> {

     protected:
        inline DictionaryContainer<Data>() = default;

     public:
        // Destructor
        virtual inline ~DictionaryContainer() = default;

        /* ************************************************************************ */

        // Copy assignment
        DictionaryContainer<Data> &operator=(const DictionaryContainer<Data> &) = delete;

        // Move assignment
        DictionaryContainer<Data> &operator=(DictionaryContainer<Data> &&) noexcept = delete;

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const DictionaryContainer<Data> &) const noexcept = delete;// Comparison of abstract types is not possible.
        bool operator!=(const DictionaryContainer<Data> &) const noexcept = delete;// Comparison of abstract types is not possible.

        /* ************************************************************************ */

        // Specific member functions

        // Copy of the value
        virtual bool Insert(const Data &) = 0;
        // Move of the value
        virtual bool Insert(Data &&) = 0;

        virtual bool Remove(const Data &) = 0;

        // Copy of the value; From TraversableContainer; True if all are inserted
        virtual bool InsertAll(const TraversableContainer<Data> &);
        // Move of the value; From MappableContainer; True if all are inserted
        virtual bool InsertAll(MappableContainer<Data> &&);
        // From TraversableContainer; True if all are removed
        virtual bool RemoveAll(const TraversableContainer<Data> &);

        // Copy of the value; From TraversableContainer; True if some is inserted
        virtual bool InsertSome(const TraversableContainer<Data> &);
        // Move of the value; From MappableContainer; True if some is inserted
        virtual bool InsertSome(MappableContainer<Data> &&);
        // From TraversableContainer; True if some is removed
        virtual bool RemoveSome(const TraversableContainer<Data> &);
    };

    /* ************************************************************************** */

}// namespace lasd

#include "dictionary.cpp"
#endif
