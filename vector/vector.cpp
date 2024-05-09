namespace lasd {

    /* ************************************************************************** */

    /*** Vector class ***/
    template<typename Data>
    Vector<Data>::Vector(const unsigned long int initialSize) {
        //std::cout << "sto per allocare un array di Data da " << initialSize << " elementi" << std::endl;
        elements = new Data[initialSize];
        size = initialSize;
    }

    template<typename Data>
    Vector<Data>::Vector(const TraversableContainer<Data> &container) : Vector(container.TraversableContainer<Data>::Size()) {
        //std::cout << "Vector(Data) TraversableContainer constructor, container.size is " << container.TraversableContainer<Data>::Size() << std::endl;
        unsigned long int idx = 0;
        container.Traverse([this, &idx](const Data &val) { this->elements[idx++] = val; });
        //std::cout << "Vector(Data) TraversableContainer constructor, size now is " << this->size << std::endl;
    }

    template<typename Data>
    Vector<Data>::Vector(MappableContainer<Data> &&container) : Vector(container.MappableContainer<Data>::Size()) {
        //std::cout << "Vector(Data) MappableContainer constructor, container.size is " << container.MappableContainer<Data>::Size() << std::endl;
        unsigned long int idx = 0;
        container.Map([this, &idx](Data &val) { this->elements[idx++] = std::move(val); });
        //std::cout << "Vector(Data) MappableContainer constructor, size now is " << this->size << std::endl;
    }

    template<typename Data>
    void Vector<Data>::Copy(const Vector<Data> &vector) {

        //std::cout << "ATTENZIONE eseguo copia di un Vector con size " << vector.size << ", this->size: " << this->Vector<Data>::Size() << std::endl;
        //std::cout << "Array vector parametro: " << std::endl;
        //vector.PrintAll();

        //std::cout << "this->elements: " << elements << std::endl;
        //std::cout << "this->Vector<Data>::Size(): " << this->Vector<Data>::Size() << std::endl;

        if(vector.Vector<Data>::Size() == 0) {
            Vector<Data>::Clear();
            return;
        }

        if (elements == nullptr) {
            //std::cout << "elements is nullptr, calling new" << std::endl;
            elements = new Data[vector.size];
        }

        if (vector.Vector<Data>::Size() != this->Vector<Data>::Size()) {
            //std::cout << "vector.Vector<Data>::Size() != this->Vector<Data>::Size => " << vector.Vector<Data>::Size() << " != " << this->Vector<Data>::Size() << std::endl;
            Vector<Data>::Resize(vector.Vector<Data>::Size());
            //std::cout << "Resize effettuato, size attuale: " << this->Vector<Data>::Size() << std::endl;
        }

        for (unsigned long i = 0; i < this->Vector<Data>::Size(); i++) {
            elements[i] = vector.elements[i];
        }
    }

    template<typename Data>
    Vector<Data>::Vector(const Vector<Data> &vector) {
        //std::cout << "CALL COPY Vector<Data>::Vector(const Vector<Data> &vector)" << std::endl;
        this->Copy(vector);
    }

    template<typename Data>
    Vector<Data>::Vector(Vector<Data> &&vector) noexcept {
        //std::cout << "ATTENZIONE eseguo spostamento di un Vector con size " << vector.size << std::endl;
        //std::cout << std::endl << "parametro vector prima di swap: " << std::endl;
        //vector.PrintAll();
        std::swap(size, vector.size);
        std::swap(elements, vector.elements);
    }

    template<typename Data>
    Vector<Data> &Vector<Data>::operator=(const Vector<Data> &vector) {
        if (this != &vector) {
            //std::cout << "ATTENZIONE eseguo assegnamento di un Vector con size " << vector.size << std::endl;
            this->Copy(vector);
        }

        return *this;
    }

    template<typename Data>
    Vector<Data> &Vector<Data>::operator=(Vector<Data> &&vector) noexcept {

        std::swap(size, vector.size);
        std::swap(elements, vector.elements);

        return *this;
    }

    template<typename Data>
    bool Vector<Data>::operator==(const Vector<Data> &vector) const noexcept {
        if (this->Vector<Data>::Size() != vector.Vector<Data>::Size()) {
            //std::cout << "ATTENZIONE operator== ritorna false perchè size diversi: " << this->Vector<Data>::Size() << " != " << vector.Vector<Data>::Size() << std::endl;
            return false;
        }

        if(Vector<Data>::Size() > 0) {
            for (unsigned long i = 0; i < Vector<Data>::Size(); i++) {
                if (elements[i] != vector.elements[i]) return false;
            }
        }

        return true;
    }

    template<typename Data>
    void Vector<Data>::Clear() noexcept {
        //std::cout << "ATTENZIONE RICHIAMATO CLEAR eseguo delete[] di elements " << elements << std::endl;
        delete[] elements;
        size = 0;
        elements = nullptr;
        //std::cout << "ATTENZIONE ESEGUITO CLEAR di elements " << elements << std::endl;
    }

    template<typename Data>
    void Vector<Data>::Resize(const unsigned long newSize) noexcept {
        //std::cout << "ATTENZIONE eseguo ridimensionamento di un Vector con size " << size << " a " << newSize << std::endl;
        Data *newElements = new Data[newSize];
        unsigned long minSize = (size < newSize) ? size : newSize;

        for (unsigned long i = 0; i < minSize; i++) {
            newElements[i] = elements[i];
        }

        //std::cout << "ATTENZIONE effettuo delete[] di elements" << std::endl;
        delete[] elements;
        elements = nullptr;

        size = newSize;
        elements = newElements;
    }

    template<typename Data>
    const Data &Vector<Data>::operator[](const unsigned long idx) const {
        if (idx >= size) throw std::out_of_range("Index out of range");

        return elements[idx];
    }

    template<typename Data>
    Data &Vector<Data>::operator[](const unsigned long idx) {
        if (idx >= size) throw std::out_of_range("Index out of range");

        return elements[idx];
    }

    template<typename Data>
    const Data &Vector<Data>::Front() const {
        if (size == 0) throw std::length_error("The container is empty, there is no front element");

        return elements[0];
    }

    template<typename Data>
    Data &Vector<Data>::Front() {
        if (size == 0) throw std::length_error("The container is empty, there is no front element");

        return elements[0];
    }

    template<typename Data>
    const Data &Vector<Data>::Back() const {
        if (size == 0) throw std::length_error("The container is empty, there is no back element");

        return elements[size - 1];
    }

    template<typename Data>
    Data &Vector<Data>::Back() {
        if (size == 0) throw std::length_error("The container is empty, there is no back element");

        return elements[size - 1];
    }

    /* ************************************************************************** */

    /*** SortableVector class ***/

    // Copy assignment
    template<typename Data>
    inline SortableVector<Data> &SortableVector<Data>::operator=(const SortableVector<Data> &sv) {
        Vector<Data>::operator=(sv);
        return *this;
    };

    // Move assignment
    template<typename Data>
    inline SortableVector<Data> &SortableVector<Data>::operator=(SortableVector<Data> &&sv) noexcept {
        Vector<Data>::operator=(std::move(sv));
        return *this;
    };

}// namespace lasd
