namespace lasd {

    /* ************************************************************************** */

    /*** List<Data> class ***/

    // Specific constructor
    template <typename Data>
    inline List<Data>::List(const TraversableContainer<Data>& container)
    {
        //std::cout << "Invocato costruttore con TraversableContainer" << std::endl;
        container.Traverse([this](const Data& d) { InsertAtBack(d); });
    }

    template <typename Data>
    inline List<Data>::List(MappableContainer<Data>&& container)
    {
        //std::cout << "Invocato costruttore con MappableContainer" << std::endl;
        container.Map([this](Data& d) { InsertAtBack(std::move(d)); });
    }

    // Copy operator
    template<typename Data>
    List<Data> List<Data>::operator=(const List<Data> &l) noexcept {
        //std::cout << "Invocato List<Data> operatore = (copy)" << std::endl;
        if (this != &l) {
            List<Data>::Clear();
            if (!l.Empty()) {
                l.Traverse([this](const Data &val) { this->InsertAtBack(val); });
            }
        }

        return *this;
    };

    // Move operator
    template<typename Data>
    List<Data> List<Data>::operator=(List<Data> &&l) noexcept {
        //std::cout << "Invocato List<Data> operatore = (move)" << std::endl;
        std::swap(head, l.head);
        std::swap(tail, l.tail);
        std::swap(size, l.size);

        return *this;
    };

    // Comparison operators
    template<typename Data>
    bool List<Data>::operator==(const List<Data> &l) const noexcept {
        //std::cout << "Invocato List<Data>::operator== di List" << std::endl;

        if (List<Data>::Size() != l.List<Data>::Size()) {
            //std::cout << "Size diversi" << std::endl;
            return false;
        }

        for(Node* n1 = head, *n2 = l.head; n1 != nullptr; n1 = n1->next, n2 = n2->next) {
            if (n1->data != n2->data) {
                //std::cout << "Dati diversi. n1 data = " << n1->data << " e n2 data = " << n2->data << std::endl;
                return false;
            }
        }

        return true;
    };

    template<typename Data>
    bool List<Data>::operator!=(const List<Data> &l) const noexcept {
        return !operator==(l);
    }

    template<typename Data>
    bool List<Data>::Exists(const Data& data) const noexcept {
        if(Empty()) return false;
        for(Node* temp = head; temp != nullptr; temp = temp->next) {
            if(temp->data == data) return true;
        }
        return false;
    }

    template<typename Data>
    void List<Data>::InsertAtFront(const Data &val) {
        //std::cout << "Prima di InsertAtFront Copy, head vale " << head << std::endl;
        head = new Node(val, head);
        if(this->size == 0) { tail = head; }
        //std::cout << "Dopo di InsertAtFront Copy, head vale " << head << std::endl;
        ChangeSize(1);
    };

    template<typename Data>
    void List<Data>::InsertAtFront(Data &&val) {
        //std::cout << "Prima di InsertAtFront Move, head vale " << head << std::endl;
        head = new Node(std::move(val), head);
        if(this->size == 0) { tail = head; }
        ChangeSize(1);
        //std::cout << "Dopo di InsertAtFront Move, head vale " << head << std::endl;
    };

    template<typename Data>
    void List<Data>::RemoveFromFront() {
        if (Empty()) {
            throw std::length_error("Cannot remove from an empty structure");
        }

        /*Node* r {head};
        size-- == 1 ? head = tail = nullptr : head = head->next;
        r->next = nullptr;
        delete r;*/

        Node *temp = head;
        if(List<Data>::Size() > 0) head = head->next;
        else head = tail = nullptr;

        temp->next = nullptr;
        delete temp;

        ChangeSize(-1);
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

        ChangeSize(1);
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

        ChangeSize(1);
    };

    template<typename Data>
    void List<Data>::Clear() noexcept {
        //std::cout << "ATTENZIONE RICHIAMATO LIST CLEAR (actual size: " << this->List<Data>::Size() << ")" << std::endl;

        while (!Empty()) {
            //std::cout << "LISTA NON VUOTA, prima di RemoveFromFront(), size: " << this->List<Data>::Size() << std::endl;
            RemoveFromFront();
            //std::cout << "LISTA NON VUOTA, dopo di RemoveFromFront(), size: " << this->List<Data>::Size() << std::endl;
        }

        head = nullptr;
        tail = nullptr;
    };

    template<typename Data>
    bool List<Data>::Insert(const Data &val) {
        if (!Exists(val)) {
            InsertAtBack(val);
            return true;
        }

        return false;
    };

    template<typename Data>
    bool List<Data>::Insert(Data &&val) {
        if(!Exists(val)) {
            InsertAtBack(std::move(val));
            return true;
        }

        return false;
    }

    template<typename Data>
    bool List<Data>::Remove(const Data &val) {
        //std::cout << "Invocata Remove const." << std::endl;
        if (Empty()) { return false; }

        if (head->data == val) {
            //std::cout << "Valore da rimuovere è in testa." << std::endl;
            RemoveFromFront();
            return true;
        }

        //std::cout << "Find del value da rimuovere." << std::endl;

        Node *temp = head;
        while (temp->next != nullptr) {
            if (temp->next->data == val) {
                //std::cout << "Trovato! Next: " << temp->next << std::endl;
                Node *toDelete = temp->next;
                temp->next = temp->next->next;
                //std::cout << "Aggiornato Next: " << temp->next << std::endl;

                toDelete->next = nullptr;
                delete toDelete;

                //std::cout << "Delete ok: " << temp->next << std::endl;

                if (temp->next == nullptr) {
                    //std::cout << "Next nullptr: " << std::endl;

                    tail = temp;
                }
                //std::cout << "Prima di ChangeSize(-1): " << this->List<Data>::Size() << std::endl;

                ChangeSize(-1);

                //std::cout << "Dopo di ChangeSize(-1): " << this->List<Data>::Size() << std::endl;

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
        //std::cout << "FRONT const invocato. Size = " << this->List<Data>::Size() << " e Empty è " << (Empty()?"true":"false") << std::endl;
        if (Empty()) {
            //std::cout << "Cannot access an empty structure" << std::endl;
            throw std::length_error("Cannot access an empty structure");
        }

        //std::cout << "head: " << head << std::endl;
        //std::cout << "head->data: " << head->data << std::endl;
        return head->data;
    }

    template<typename Data>
    Data &List<Data>::Front() {
        //std::cout << "FRONT non const invocato. Size = " << this->List<Data>::Size() << " e Empty è " << (Empty()?"true":"false") << std::endl;
        if (Empty()) {
            //std::cout << "Cannot access an empty structure" << std::endl;
            throw std::length_error("Cannot access an empty structure");
        }

        //std::cout << "head: " << head << std::endl;
        //std::cout << "head->data: " << head->data << std::endl;

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

    template <typename Data>
    inline void List<Data>::Traverse(TraverseFun f) const
    {
        PreOrderTraverse(f);
    }

    template<typename Data>
    void List<Data>::Traverse(TraverseFun fun, Node* start) const {
        Node *temp = start;
        while (temp != nullptr) {
            fun(temp->data);
            temp = temp->next;
        }
    }

    template<typename Data>
    void List<Data>::PreOrderTraverse(TraverseFun fun) const {
        //std::cout << "Invocato PreOrderTraverse" << std::endl;
        Traverse(fun, head);
    }

    template<typename Data>
    void List<Data>::PostOrderTraverse(TraverseFun fun, Node* from) const {
        //std::cout << std::endl << "ATTENZIONE List<Data>::PostOrderTraverse size: " << this->List<Data>::Size() << std::endl;

        if (from == nullptr) {
            //std::cout << "from is nullptr" << std::endl;
            return;
        }
        PostOrderTraverse(fun, from->next);
        //std::cout << "Calling fun on from " << from->data << std::endl;
        fun(from->data);
    }

    template<typename Data>
    void List<Data>::PostOrderTraverse(TraverseFun fun) const {
        //std::cout << "ATTENZIONE eseguo void List<Data>::PostOrderTraverse(TraverseFun fun) const" << std::endl;
        PostOrderTraverse(fun, head);
    }

    template<typename Data>
    void List<Data>::Map(MapFun mapFun, Node* start) {
        Node *temp = start;
        while (temp != nullptr) {
            mapFun(temp->data);
            temp = temp->next;
        }
    }

    template<typename Data>
    void List<Data>::Map(MapFun mapFun) {
        PreOrderMap(mapFun);
    }

    template<typename Data>
    void List<Data>::PreOrderMap(MapFun mapFun) {
        //std::cout << "Invocato PreOrderMap" << std::endl;
        Map(mapFun, head);
    }

    template<typename Data>
    void List<Data>::PostOrderMap(MapFun mapFun, Node* from) {
        if (from == nullptr) {
            return;
        }
        PostOrderMap(mapFun, from->next);
        mapFun(from->data);
    }

    template<typename Data>
    void List<Data>::PostOrderMap(MapFun mapFun) {
        //std::cout << "Invocato PostOrderMap" << std::endl;
        PostOrderMap(mapFun, head);
    }

    /* ************************************************************************** */

}// namespace lasd
