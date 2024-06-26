
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/dictionary.hpp"
#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

    /* ************************************************************************** */

    template<typename Data>
    class List : virtual public ClearableContainer, virtual public LinearContainer<Data>, virtual public DictionaryContainer<Data> {
     private:
        inline void ChangeSize(int i) {
            this->size += i;
            if(this->size == 1) tail = head;
            if(this->size == 0) tail = head = nullptr;
        }

     protected:
        using Container::size;

        struct Node {

            Data data;
            Node *next;

            inline Node(const Data &val, Node *n = nullptr) : data(val), next(n) {}
            inline Node(Data &&val, Node *n = nullptr) noexcept : data(std::move(val)), next(n) {}

            /* ********************************************************************** */

            /* ********************************************************************** */

            // Destructor
            virtual ~Node() {
                if (next != nullptr) {
                    delete next;
                }
            };

            /* ********************************************************************** */

            // Comparison operators

            // operator==(argument) specifiers;
            inline bool operator==(const Node &n) const noexcept {
                return data == n.data;
            }

            // operator!=(argument) specifiers;
            inline bool operator!=(const Node &n) const noexcept {
                return !(this->operator==(n));
            }

            /* ********************************************************************** */

            // Specific member functions

            inline Node &operator=(const Node &n) noexcept {
                if (this != &n) {
                    data = n.data;
                    next = n.next;
                }
                return *this;
            }

            inline Node &operator=(Node &&n) noexcept {
                if (this != &n) {
                    data = std::move(n.data);
                    next = n.next;
                    n.next = nullptr;
                }
                return *this;
            }
        };

        Node *head = nullptr;
        Node *tail = nullptr;

     public:
        // Default constructor
        inline List<Data>() = default;

        // Specific constructor
        inline List(const TraversableContainer<Data>&);
        inline List(MappableContainer<Data>&&);

        /* ************************************************************************ */

        // Copy constructor
        inline List<Data>(const List<Data> &l) noexcept {
            //std::cout << "Invocato costruttore List<Data> const" << std::endl << std::endl;
            //std::cout << "l.Size: " << l.Size() << std::endl;
            //std::cout << "l.List<Data>::Size: " << l.List<Data>::Size() << std::endl;
            //std::cout << "l is empty? " << (l.Empty() == 1?"Yes" : "No") << std::endl;
            if(l.Empty()) return;
            l.Traverse([this](const Data &val) {
                //std::cout << "Inserting at Front " << val << std::endl;
                this->InsertAtBack(val); });
        };

        // Move constructor
        inline List<Data>(List<Data> &&l) noexcept {
            std::swap(head, l.head);
            std::swap(tail, l.tail);
            std::swap(size, l.size);
        };

        /* ************************************************************************ */

        // Destructor
        inline ~List() { this->Clear(); };

        /* ************************************************************************ */

        // Copy assignment
        virtual List<Data> operator=(const List<Data> &l) noexcept;

        // Move assignment
        virtual List<Data> operator=(List<Data> &&l) noexcept;

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const List<Data> &l) const noexcept;
        bool operator!=(const List<Data> &l) const noexcept;

        /* ************************************************************************ */

        // Specific member functions

        // Copy of the value
        virtual void InsertAtFront(const Data &);
        // Move of the value
        virtual void InsertAtFront(Data &&);

        // throw std::length_error when empty
        virtual void RemoveFromFront();

        // throw std::length_error when empty
        virtual Data FrontNRemove();

        // // Copy of the value
        virtual void InsertAtBack(const Data &val);

        // // Move of the value
        virtual void InsertAtBack(Data &&val);

        /* ************************************************************************ */

        // Specific member function (inherited from ClearableContainer)

        virtual void Clear() noexcept override;

        // Specific member function (inherited from TestableContainer)
        virtual bool Exists(const Data&) const noexcept override;

        // Specific member functions (inherited from DictionaryContainer)

        // Copy of the value
        virtual bool Insert(const Data &val) override;

        // Move of the value
        virtual bool Insert(Data &&) override;

        virtual bool Remove(const Data &) override;

        /* ************************************************************************ */

        // Specific member functions (inherited from LinearContainer)

        // throw std::out_of_range when out of range
        virtual const Data &operator[](const unsigned long) const override;

        // throw std::out_of_range when out of range
        virtual Data &operator[](const unsigned long) override;

        // throw std::length_error when empty
        virtual const Data &Front() const override;

        // throw std::length_error when empty
        virtual Data &Front() override;

        // throw std::length_error when empty
        virtual const Data &Back() const override;

        // throw std::length_error when empty
        virtual Data &Back() override;

        /* ************************************************************************ */

        // Specific member function (inherited from TraversableContainer)

        using typename TraversableContainer<Data>::TraverseFun;

        virtual void Traverse(TraverseFun) const override;

        /* ************************************************************************ */

        // Specific member function (inherited from PreOrderTraversableContainer)

        virtual void PreOrderTraverse(TraverseFun) const override;

        /* ************************************************************************ */

        // Specific member function (inherited from PostOrderTraversableContainer)

        virtual void PostOrderTraverse(TraverseFun) const override;

        /* ************************************************************************ */

        // Specific member function (inherited from MappableContainer)

        using typename MappableContainer<Data>::MapFun;

        virtual void Map(MapFun) override;

        /* ************************************************************************ */

        // Specific member function (inherited from PreOrderMappableContainer)

        virtual void PreOrderMap(MapFun) override;

        /* ************************************************************************ */

        // Specific member function (inherited from PostOrderMappableContainer)

        virtual void PostOrderMap(MapFun) override;

        /*virtual inline void PrintAll() const {
            if(Empty()) {
                //std::cout << "PRINT ALL - Empty list" << std::endl;
                return;
            }

            //std::cout << "Printing list " << this << " of size " << Size() << std::endl;
            unsigned long int i = 0;
            for(Node* w = head; w != nullptr; w = w->next) {
                //std::cout << "Ele " << i++ << ": " << w->data << std::endl;
            }

            //std::cout << std::endl;
        }*/

     protected:
        // Auxiliary functions
        void Traverse(TraverseFun, Node*) const;
        void PostOrderTraverse(TraverseFun, Node*) const;
        void Map(MapFun, Node*);
        void PostOrderMap(MapFun, Node*);
    };

    /* ************************************************************************** */

}// namespace lasd

#include "list.cpp"

#endif
