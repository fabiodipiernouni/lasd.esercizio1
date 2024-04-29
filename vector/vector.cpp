namespace lasd {

    /* ************************************************************************** */

    /*** Vector class ***/
    template<typename Data>
    Vector<Data>::Vector(const unsigned long int initialSize) {
        elements = new Data[initialSize];
        size = initialSize;
    }

    template<typename Data>
    Vector<Data>::Vector(const TraversableContainer<Data> &container) : Vector(container.Size()) {
        //std::cout  << "Vector(Data) TraversableContainer constructor, container.size is " << container.Size() << std::endl;
        container.Traverse([this](const Data &val) { this->elements[this->size++] = val; });
        //std::cout << "Vector(Data) TraversableContainer constructor, size now is " << this->size << std::endl;
    }

    template<typename Data>
    Vector<Data>::Vector(MappableContainer<Data> &&container) : Vector(container.Size()) {
        //std::cout  << "Vector(Data) MappableContainer constructor, container.size is " << container.Size() << std::endl;
        container.Map([this](Data &val) { this->elements[this->size++] = std::move(val); });
        //std::cout << "Vector(Data) MappableContainer constructor, size now is " << this->size << std::endl;
    }

    template<typename Data>
    void Vector<Data>::Copy(const Vector<Data> &vector) {

        //std::cout << "ATTENZIONE eseguo copia di un Vector con size " << vector.size << std::endl;
        if (this->elements != nullptr) delete[] elements;

        size = vector.size;
        elements = new Data[size];
        for (unsigned long i = 0; i < size; i++) {
            elements[i] = vector.elements[i];
        }
    }

    template<typename Data>
    Vector<Data>::Vector(const Vector<Data> &vector) {
        this->Copy(vector);
    }

    template<typename Data>
    Vector<Data>::Vector(Vector<Data> &&vector) noexcept {
        //std::cout << "ATTENZIONE eseguo spostamento di un Vector con size " << vector.size << std::endl;
        std::swap(size, vector.size);
        std::swap(elements, vector.elements);
    }

    template<typename Data>
    Vector<Data>::~Vector() {
        if (elements != nullptr) {
            delete[] elements;
            elements = nullptr;
        }
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
        if (this != &vector) {
            //std::cout << "ATTENZIONE eseguo assegnamento con spostamento di un Vector con size " << vector.size << std::endl;
            if (elements != nullptr) delete[] elements;

            size = vector.size;
            elements = std::move(vector.elements);
        }

        return *this;
    }

    template<typename Data>
    bool Vector<Data>::operator==(const Vector<Data> &vector) const noexcept {
        if (size != vector.size) return false;

        for (unsigned long i = 0; i < size; i++) {
            if (elements[i] != vector.elements[i]) return false;
        }

        return true;
    }

    template<typename Data>
    void Vector<Data>::Clear() noexcept {
        if (elements != nullptr) delete[] elements;
        size = 0;
        elements = nullptr;
    }

    template<typename Data>
    void Vector<Data>::Resize(const unsigned long newSize) noexcept {
        Data *newElements = new Data[newSize];
        unsigned long minSize = (size < newSize) ? size : newSize;

        for (unsigned long i = 0; i < minSize; i++) {
            newElements[i] = elements[i];
        }

        if (elements != nullptr) delete[] elements;

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
