
#include "vector.hpp"

namespace lasd {

    /* ************************************************************************** */

    /*** Vector class ***/
    template<typename Data>
    Vector<Data>::Vector(const unsigned long int initialSize) : size(initialSize) {
        elements = new Data[initialSize];
    }

    template<typename Data>
    Vector<Data>::Vector(const TraversableContainer<Data> &container) : Vector(container.Size()) {
        unsigned long idx = 0;
        container.Traverse([this, &idx](const Data &val) { this->elements[idx++] = val; });
    }

    template<typename Data>
    Vector<Data>::Vector(const MappableContainer<Data> &container) : Vector(container.Size()) {
        unsigned long idx = 0;
        container.Map([this, &idx](Data &val) { this->elements[idx++] = std::move(val); });
    }

    template<typename Data>
    void Vector<Data>::Copy(const Vector &vector) {
        if (this.elements != nullptr) delete[] elements;

        size = vector.size;
        elements = new Data[size];
        for (unsigned long i = 0; i < size; i++) {
            elements[i] = vector.elements[i];
        }
    }

    template<typename Data>
    Vector<Data>::Vector(const Vector &vector) {
        this.Copy(vector);
    }

    template<typename Data>
    Vector<Data>::Vector(Vector &&vector) noexcept : size(vector.size), elements(vector.elements) {
        vector.size = 0;
        vector.elements = nullptr;
    }

    template<typename Data>
    Vector<Data>::~Vector() {
        if (elements != nullptr)
            delete[] elements;
    }

    template<typename Data>
    Vector<Data> &Vector<Data>::operator=(const Vector &vector) {
        if (this != &vector) {
            this.Copy(vector);
        }

        return *this;
    }

    template<typename Data>
    Vector<Data> &Vector<Data>::operator=(Vector &&vector) noexcept {
        if (this != &vector) {
            if (elements != nullptr) delete[] elements;

            size = vector.size;
            elements = vector.elements;

            vector.size = 0;
            vector.elements = nullptr;
        }

        return *this;
    }

    template<typename Data>
    bool Vector<Data>::operator==(const Vector &vector) const noexcept {
        if (size != vector.size) return false;

        for (unsigned long i = 0; i < size; i++) {
            if (elements[i] != vector.elements[i]) return false;
        }

        return true;
    }

    template<typename Data>
    void Vector<Data>::Clear() {
        if (elements != nullptr) delete[] elements;
        size = 0;
        elements = nullptr;
    }

    template<typename Data>
    void Vector<Data>::Resize(const unsigned long newSize) {
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
    inline SortableVector<Data> &SortableVector<Data>::operator=(const SortableVector &sv) {
        Vector<Data>::operator=(sv);
        return *this;
    };

    // Move assignment
    template<typename Data>
    inline SortableVector<Data> &SortableVector<Data>::operator=(SortableVector &&sv) noexcept {
        Vector<Data>::operator=(std::move(sv));
        return *this;
    };

}// namespace lasd
