
#include "list.hpp"

namespace lasd {

    /* ************************************************************************** */

    /*** List<Data> class ***/

    /**|           |            |           |*/
    //  HEAD(front)   ->        ->TAIL(back)
    /**|           |            |           |*/
    template<typename Data>
    List<Data> List<Data>::operator=(const List<Data> &l) noexcept {
        if (this != &l) {
            Clear();
            if (!l.Empty()) {
                l.Traverse([this](const Data &val) { this.InsertAtBack(val); });
            }
        }

        return *this;
    };

    template<typename Data>
    List<Data> List<Data>::operator=(List<Data> &&l) noexcept {
        if (this != l) {
            Clear();
            if (!l.Empty()) {
                l.Map([this](Data &val) { this.InsertAtBack(val); });
            }
        }

        return *this;
    };

    template<typename Data>
    bool List<Data>::operator==(const List<Data> &l) const noexcept {
        if (size != l.size) {
            return false;
        }

        Node *n1 = head;
        Node *n2 = l.head;

        while (n1 != nullptr) {
            if (n1->data != n2->data) {
                return false;
            }

            n1 = n1->next;
            n2 = n2->next;
        }

        return true;
    };

    template<typename Data>
    bool List<Data>::operator!=(const List<Data> &l) const noexcept {
        return !operator==(l);
    }

    template<typename Data>
    void List<Data>::InsertAtFront(const Data &val) {
        head = new Node(val, head);
        this.size++;
    };

    template<typename Data>
    void List<Data>::InsertAtFront(Data &&val) {
        head = new Node(std::move(val), head);
        this.size++;
    };

    template<typename Data>
    void List<Data>::RemoveFromFront() {
        if (Empty()) {
            throw std::length_error("Cannot remove from an empty structure");
        }

        Node *temp = head;
        head = head->next;
        delete temp;
        this.size--;
        if(Empty()) {
            tail = nullptr;
        }
    };

    template<typename Data>
    Data List<Data>::FrontNRemove() {
        if (Empty()) {
            throw std::length_error("Cannot remove from an empty structure");
        }

        Data temp = head->data;
        RemoveFromFront();
        return temp;
    };

    template<typename Data>
    void List<Data>::InsertAtBack(const Data &val) {
        if (Empty()) {
            head = new Node(val);
            tail = head;
        } else {
            tail->next = new Node(val);
            tail = tail->next;
        }

        this.size++;
    };

    template<typename Data>
    void List<Data>::InsertAtBack(Data &&val) {
        if (Empty()) {
            head = new Node(std::move(val));
            tail = head;
        } else {
            tail->next = new Node(std::move(val));
            tail = tail->next;
        }

        this.size++;
    };

    template<typename Data>
    void List<Data>::Clear() noexcept {
        while (!Empty()) {
            RemoveFromFront();
        }
    };

    template<typename Data>
    bool List<Data>::Insert(const Data &val) {
        InsertAtBack(val);
        return true;
    };

    template<typename Data>
    bool List<Data>::Insert(Data &&val) {
        InsertAtBack(std::move(val));
        return true;
    }

    template<typename Data>
    bool List<Data>::Remove(const Data &val) {
        if (Empty()) { return false; }

        Node *temp = head;
        if (head->data == val) {
            RemoveFromFront();
            return true;
        }

        while (temp->next != nullptr) {
            if (temp->next->data == val) {
                Node *toDelete = temp->next;
                temp->next = temp->next->next;
                delete toDelete;
                this.size--;
                return true;
            }

            temp = temp->next;
        }

        return false;
    }

    template<typename Data>
    const Data &List<Data>::operator[](const unsigned long idx) const {
        if (Empty()) {
            throw std::out_of_range("Cannot access an empty structure");
        }

        if (idx >= size) {
            throw std::out_of_range("Index out of range");
        }

        Node *temp = head;
        for (unsigned long i = 0; i < idx; i++) {
            if (temp->next == nullptr) {
                throw std::out_of_range("Index out of range");
            }

            temp = temp->next;
        }

        return temp->data;
    }

    template<typename Data>
    Data &List<Data>::operator[](const unsigned long idx) {
        if (Empty()) {
            throw std::out_of_range("Cannot access an empty structure");
        }

        if (idx >= size) {
            throw std::out_of_range("Index out of range");
        }

        Node *temp = head;
        for (unsigned long i = 0; i < idx; i++) {
            if (temp->next == nullptr) {
                throw std::out_of_range("Index out of range");
            }

            temp = temp->next;
        }

        return temp->data;
    }

    template<typename Data>
    const Data &List<Data>::Front() const {
        if (Empty()) {
            throw std::length_error("Cannot access an empty structure");
        }

        return head->data;
    }

    template<typename Data>
    Data &List<Data>::Front() {
        if (Empty()) {
            throw std::length_error("Cannot access an empty structure");
        }

        return head->data;
    }

    template<typename Data>
    const Data &List<Data>::Back() const {
        if (Empty()) {
            throw std::length_error("Cannot access an empty structure");
        }

        return tail->data;
    }

    template<typename Data>
    Data &List<Data>::Back() {
        if (Empty()) {
            throw std::length_error("Cannot access an empty structure");
        }

        return tail->data;
    }

    template<typename Data>
    void List<Data>::Traverse(TraverseFun fun, Node& start) const {
        Node *temp = start ? start : head;
        while (temp != nullptr) {
            fun(temp->data);
            temp = temp->next;
        }
    }

    template<typename Data>
    void List<Data>::PreOrderTraverse(TraverseFun fun) const {
        Traverse(fun, head);
    }

    template<typename Data>
    void List<Data>::PostOrderTraverse(TraverseFun fun, Node& from) const {
        if (from == nullptr) {
            return;
        }

        PostOrderTraverse(fun, from->next);
        fun(from->data);
    }

    template<typename Data>
    void List<Data>::PostOrderTraverse(TraverseFun fun) const {
        PostOrderTraverse(fun, head);
    }

    template<typename Data>
    void List<Data>::Map(MapFun mapFun, Node& start) {
        Node *temp = start;
        while (temp != nullptr) {
            mapFun(temp->data);
            temp = temp->next;
        }
    }

    template<typename Data>
    void List<Data>::Map(MapFun mapFun) {
        Map(mapFun, head);
    }

    template<typename Data>
    void List<Data>::PreOrderMap(MapFun mapFun) {
        Map(mapFun, head);
    }

    template<typename Data>
    void List<Data>::PostOrderMap(MapFun mapFun, Node& from) {
        if (from == nullptr) {
            return;
        }

        PostOrderMap(mapFun, from->next);
        mapFun(from->data);
    }

    template<typename Data>
    void List<Data>::PostOrderMap(MapFun mapFun) {
        PostOrderMap(mapFun, head);
    }

    /* ************************************************************************** */

}// namespace lasd
