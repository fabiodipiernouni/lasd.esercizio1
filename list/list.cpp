
#include "list.hpp"

namespace lasd {

    /* ************************************************************************** */

    /*** List<Data> class ***/

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

    bool List<Data>::operator!=(const List<Data> &l) const noexcept {
        return !operator==(l);
    }

    virtual void List<Data>::InsertAtFront(const Data &val) {
        head = new Node(val, head);
        this.size++;
    };

    virtual void List<Data>::InsertAtFront(Data &&val) {
        head = new Node(std::move(val), head);
        this.size++;
    };

    virtual void List<Data>::RemoveFromFront() {
        if (Empty()) {
            throw std::length_error("Cannot remove from an empty list");
        }

        Node *temp = head;
        head = head->next;
        delete temp;
        this.size--;
        if(Empty()) {
            tail = nullptr;
        }
    };

    virtual Data List<Data>::FrontNRemove() {
        if (Empty()) {
            throw std::length_error("Cannot remove from an empty list");
        }

        Data temp = head->data;
        RemoveFromFront();
        return temp;
    };

    virtual void List<Data>::InsertAtBack(const Data &val) {
        if (Empty()) {
            head = new Node(val);
            tail = head;
        } else {
            tail->next = new Node(val);
            tail = tail->next;
        }

        this.size++;
    };

    virtual void List<Data>::InsertAtBack(Data &&val) {
        if (Empty()) {
            head = new Node(std::move(val));
            tail = head;
        } else {
            tail->next = new Node(std::move(val));
            tail = tail->next;
        }

        this.size++;
    };

    virtual void List<Data>::Clear() noexcept override {
        while (!Empty()) {
            RemoveFromFront();
        }
    };

    virtual bool List<Data>::Insert(const Data &val) override {
        InsertAtBack(val);
        return true;
    };

    virtual bool List<Data>::Insert(Data &&val) override {
        InsertAtBack(std::move(val));
        return true;
    }

    virtual bool List<Data>::Remove(const Data &val) override {
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


    virtual const Data &List<Data>::operator[](const unsigned long idx) const override {
        if (Empty()) {
            throw std::out_of_range("Cannot access an empty list");
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

    virtual Data &List<Data>::operator[](const unsigned long idx) override {
        if (Empty()) {
            throw std::out_of_range("Cannot access an empty list");
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

    virtual const Data &List<Data>::Front() const override {
        if (Empty()) {
            throw std::length_error("Cannot access an empty list");
        }

        return head->data;
    }

    virtual Data &List<Data>::Front() override {
        if (Empty()) {
            throw std::length_error("Cannot access an empty list");
        }

        return head->data;
    }

    virtual const Data &List<Data>::Back() const override {
        if (Empty()) {
            throw std::length_error("Cannot access an empty list");
        }

        return tail->data;
    }

    virtual Data &List<Data>::Back() override {
        if (Empty()) {
            throw std::length_error("Cannot access an empty list");
        }

        return tail->data;
    }

    void List<Data>::Traverse(TraverseFun fun, Node& start) const {
        Node *temp = start ? start : head;
        while (temp != nullptr) {
            fun(temp->data);
            temp = temp->next;
        }
    }

    virtual void List<Data>::PreOrderTraverse(TraverseFun fun) const override {
        Traverse(fun, head);
    }

    void List<Data>::PostOrderTraverse(TraverseFun fun, Node& from) const {
        if (from == nullptr) {
            return;
        }

        PostOrderTraverse(fun, from->next);
        fun(from->data);
    }

    virtual void List<Data>::PostOrderTraverse(TraverseFun fun) const override {
        PostOrderTraverse(fun, head);
    }

    void List<Data>::Map(MapFun mapFun, Node& start) {
        Node *temp = start;
        while (temp != nullptr) {
            mapFun(temp->data);
            temp = temp->next;
        }
    }

    virtual void List<Data>::Map(MapFun mapFun) override {
        Map(mapFun, head);
    }

    virtual void List<Data>::PreOrderMap(MapFun mapFun) override {
        Map(mapFun, head);
    }

    void void List<Data>::PostOrderMap(MapFun mapFun, Node& from) {
        if (from == nullptr) {
            return;
        }

        PostOrderMap(mapFun, from->next);
        mapFun(from->data);
    }

    virtual void List<Data>::PostOrderMap(MapFun mapFun) override {
        PostOrderMap(mapFun, head);
    }

    /* ************************************************************************** */

}// namespace lasd
