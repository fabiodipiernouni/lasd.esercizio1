#include <iostream>

namespace lasd {

    /* ************************************************************************** */

    /*** QueueVec class ***/

    template<typename Data>
    inline QueueVec<Data>::QueueVec(const TraversableContainer<Data> &container) {
        container.Traverse([this](const Data &val) { this->Enqueue(val); });
    }

    template<typename Data>
    inline QueueVec<Data>::QueueVec(MappableContainer<Data> &&container) {
        container.Map([this](Data &val) { this->Enqueue(std::move(val)); });
    }

    template<typename Data>
    inline Data const &QueueVec<Data>::Head() const {
        if (Empty()) {
            throw std::length_error("Queue is empty");
        }

        return elements[front];
    }

    template<typename Data>
    inline Data &QueueVec<Data>::Head() {
        if (Empty()) {
            throw std::length_error("Queue is empty");
        }

        return elements[front];
    }

    template<typename Data>
    void QueueVec<Data>::Enqueue(const Data &val) {

        if (Empty()) {
            front = 0;
            rear = 0;
        } else {
            if (Full()) { Resize(QueueSize() + chunkSize); }// if rear circulary incremented is equal to front, means that the queue is full

            rear = (rear + 1) % QueueSize();// Circular increment
        }

        elements[rear] = val;
    }

    template<typename Data>
    void QueueVec<Data>::Enqueue(Data &&val) {
        if (Empty()) {
            front = 0;
            rear = 0;
        } else {
            if (Full()) { Resize(QueueSize() + chunkSize); }// if rear circulary incremented is equal to front, means that the queue is full

            rear = (rear + 1) % QueueSize();// Circular increment
        }

        elements[rear] = std::move(val);
    }

    template<typename Data>
    void QueueVec<Data>::Dequeue() {
        if (Empty()) {
            throw std::length_error("Queue is empty");
        }

        if (front == rear) {
            this->Clear();
        } else {
            front = (front + 1) % QueueSize();// Circular increment
        }

        if ((QueueSize() - Size()) >= 2 * chunkSize) {
            Resize(QueueSize() - chunkSize);
        }
    }

    template<typename Data>
    void QueueVec<Data>::Resize(unsigned long newSize) noexcept {
        if (newSize % chunkSize != 0) {
            newSize = ((newSize / chunkSize) + 1) * chunkSize;// Round up to the nearest multiple of chunkSize
            std::cout << "WARNING - new size is not a multiple of chunk size, resizing to the nearest multiple of chunk size: " << newSize << std::endl;
        }

        try {
            Data *newElements = new Data[newSize];// Alloca un nuovo array

            // Copia i dati dall'array vecchio a quello nuovo
            for (size_t i = 0; i < this->Size(); ++i) {
                newElements[i] = std::move(elements[(front + i) % QueueSize()]);// Usa std::move per evitare copie inutili
            }

            delete[] elements;// Libera la memoria dell'array vecchio

            elements = newElements; // Imposta elements per puntare al nuovo array
            front = 0;              // Resetta front
            rear = this->Size() - 1;// Resetta rear
        } catch (std::bad_alloc &e) {
            std::cout << "ERROR - bad_alloc caught: " << e.what() << std::endl;
        }
    }

    template<typename Data>
    bool QueueVec<Data>::operator==(const QueueVec &queue) const noexcept {
        if (this->Size() != queue.Size()) {//Size is the number of the elements inside the queue
            return false;
        }

        for (unsigned long int i = 0; i < this->Size(); ++i) {
            if (elements[(front + i) % QueueSize()] != queue.elements[(queue.front + i) % queue.QueueSize()]) {
                return false;
            }
        }

        return true;
    }

    template<typename Data>
    inline bool QueueVec<Data>::operator!=(const QueueVec &queue) const noexcept {
        return !operator==(queue);
    }

    /* ************************************************************************** */

}// namespace lasd
