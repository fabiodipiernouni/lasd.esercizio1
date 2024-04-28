
#ifndef QUEUELST_HPP
#define QUEUELST_HPP

/* ************************************************************************** */

#include "../../list/list.hpp"
#include "../queue.hpp"

/* ************************************************************************** */

namespace lasd {

    /* ************************************************************************** */

    template<typename Data>
    class QueueLst : virtual public Queue<Data>, virtual protected List<Data> {

     public:
        // Default constructor
        inline QueueLst<Data>() = default;

        /* ************************************************************************ */

        // Specific constructor
        // A stack obtained from a TraversableContainer
        inline QueueLst(const TraversableContainer<Data> &tc) : Queue<Data>(), List<Data>(tc){};
        // A stack obtained from a MappableContainer
        inline QueueLst(MappableContainer<Data> &&mc) : Queue<Data>(), List<Data>(std::move(mc)){};

        /* ************************************************************************ */

        // Copy constructor
        inline QueueLst(const QueueLst<Data> &queue) : Queue<Data>(), List<Data>(queue){};

        // Move constructor
        inline QueueLst(QueueLst<Data> &&queue) noexcept : Queue<Data>(), List<Data>(std::move(queue)){};

        /* ************************************************************************ */

        // Destructor
        // ~QueueLst() specifier;
        virtual ~QueueLst() = default;

        /* ************************************************************************ */

        // Copy assignment
        virtual inline QueueLst &operator=(const QueueLst<Data> &queue) {
            List<Data>::operator=(queue);
            return *this;
        };

        // Move assignment
        virtual inline QueueLst &operator=(QueueLst<Data> &&) noexcept {
            List<Data>::operator=(std::move(queue));
            return *this;
        };

        /* ************************************************************************ */

        // Comparison operators
        virtual bool operator==(const QueueLst<Data> &) const noexcept {
            return List<Data>::operator==(queue);
        };

        virtual bool operator!=(const QueueLst<Data> &) const noexcept {
            return List<Data>::operator!=(queue);
        };

        /* ************************************************************************ */

        // Specific member functions (inherited from Queue)

        // throw std::length_error when empty
        virtual inline const Data &Head() const override;
        // throw std::length_error when empty
        virtual inline Data &Head() override ;
        // throw std::length_error when empty
        virtual inline void Dequeue() override;
        // throw std::length_error when empty
        virtual inline Data HeadNDequeue() override;

        // Override Queue member (copy of the value)
        virtual inline void Enqueue(const Data & val) override {
            List<Data>::InsertAtBack(val);
        };
        // Override Queue member (move of the value)
        virtual void Enqueue(Data && val) override {
            List<Data>::InsertAtBack(std::move(val));
        }
        /* ************************************************************************ */

        // Specific member function (inherited from ClearableContainer)
        using List<Data>::Clear;
    };

    /* ************************************************************************** */

}// namespace lasd

#endif
