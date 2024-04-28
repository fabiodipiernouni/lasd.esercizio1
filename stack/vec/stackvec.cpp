namespace lasd {

    /* ************************************************************************** */

    /*** StackVec class ***/

    template<typename Data>
    inline StackVec<Data>::StackVec(const TraversableContainer<Data> &container) {
        container.Traverse([this](const Data &val) { this->Push(val); });
    }

    template<typename Data>
    inline StackVec<Data>::StackVec(MappableContainer<Data> &&container) {
        container.Map([this](Data &&val) { this->Push(std::move(val)); });
    }

    template<typename Data>
    inline StackVec<Data> StackVec<Data>::operator=(const StackVec<Data> &stack) noexcept {
        if (this != &stack) {
            Clear();

            if (Size() != stack.Size()) {
                Resize(stack.Size());
            }

            if (!stack.Empty()) {
                unsigned long int idx = 0;
                stack.StackVec<Data>::Traverse([this, &idx](const Data &val) { this->elements[idx++] = val; });
            }
        }

        return *this;
    }

    template<typename Data>
    inline StackVec<Data> StackVec<Data>::operator=(StackVec<Data> &&stack) noexcept {
        if (this != &stack) {
            this->Clear();
            std::swap(elements, stack.elements);
            std::swap(this->size, stack.size);
            std::swap(top, stack.top);
        }

        return *this;
    }

    template<typename Data>
    bool StackVec<Data>::operator==(const StackVec<Data> &stack) const noexcept {
        return Vector<Data>::operator==(stack);
    }

    template<typename Data>
    void StackVec<Data>::Pop() {
        if (Empty()) {
            throw std::length_error("Stack is empty");
        }

        if (top == 0) Clear();
        else
            top--;

        if ((Size() - top) >= 2 * chunkSize) {
            Resize(Size() - chunkSize);
        }
    }

    template<typename Data>
    void StackVec<Data>::Push(const Data &val) {
        if (Full()) {
            Resize(Size() + chunkSize);
        }

        elements[++top] = val;
    }

    template<typename Data>
    void StackVec<Data>::Push(Data &&val) {
        if (Full()) {
            Resize(Size() + chunkSize);
        }

        elements[++top] = std::move(val);
    }

    template<typename Data>
    void StackVec<Data>::Resize(unsigned long newSize) noexcept {
        if (newSize % chunkSize != 0) {
            newSize = ((newSize / chunkSize) + 1) * chunkSize;// Round up to the nearest multiple of chunkSize
            std::cout << "WARNING - new size is not a multiple of chunk size, resizing to the nearest multiple of chunk size: " << newSize << std::endl;
        }

        try {
            Vector<Data>::Resize(newSize);
        } catch (const std::bad_alloc &e) {
            std::cerr << e.what() << '\n';
        }
    }

    template<typename Data>
    void StackVec<Data>::Clear() noexcept {
        Vector<Data>::Clear();
        top = -1;
    }

}// namespace lasd
