
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
        inline DictionaryContainer<Data>() : TestableContainer<Data>() = default;

     public:
        // Destructor
        virtual inline ~DictionaryContainer() = default;

        /* ************************************************************************ */

        // Copy assignment
        DictionaryContainer<Data> &operator=(const DictionaryContainer<Data> &) = delete;

        // Move assignment
        DictionaryContainer<Data> &operator=(DictionaryContainer<Data> &&)

            noexcept = delete;

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const DictionaryContainer<Data> &) const noexcept = delete;// Comparison of abstract types is not possible.
        bool operator!=(const DictionaryContainer<Data> &) const noexcept = delete;// Comparison of abstract types is not possible.

        /* ************************************************************************ */

        // Specific member functions

        // type Insert(argument) specifiers; // Copy of the value
        virtual bool Insert(const Data &) = 0;
        // type Insert(argument) specifiers; // Move of the value
        virtual bool Insert(Data &&) = 0;
        // type Remove(argument) specifiers;
        virtual bool Remove(const Data &) = 0;

        // type InsertAll(argument) specifiers; // Copy of the value; From TraversableContainer; True if all are inserted
        virtual inline bool InsertAll(const TraversableContainer<Data> &);
        // type InsertAll(argument) specifiers; // Move of the value; From MappableContainer; True if all are inserted
        virtual inline bool InsertAll(MappableContainer<Data> &&);
        // type RemoveAll(argument) specifiers; // From TraversableContainer; True if all are removed
        virtual inline bool RemoveAll(const TraversableContainer<Data> &);

        // type InsertSome(argument) specifiers; // Copy of the value; From TraversableContainer; True if some is inserted
        virtual inline bool InsertSome(const TraversableContainer<Data> &);
        // type InsertSome(argument) specifiers; // Move of the value; From MappableContainer; True if some is inserted
        virtual inline bool InsertSome(MappableContainer<Data> &&);
        // type RemoveSome(argument) specifiers; // From TraversableContainer; True if some is removed
        virtual inline bool RemoveSome(const TraversableContainer<Data> &);
    };

    /* ************************************************************************** */

}// namespace lasd

#endif
