namespace lasd {

    /* ************************************************************************** */

    /*** StackVec class ***/

    template<typename Data>
    inline StackVec<Data>::StackVec(const TraversableContainer<Data> &container) {
        container.Traverse([this](const Data &val) { this->Push(val); });
    }

    template<typename Data>
    inline StackVec<Data>::StackVec(MappableContainer<Data> &&container) {
        container.Map([this](Data &val) { this->Push(std::move(val)); });
    }

    template<typename Data>
    inline StackVec<Data> & StackVec<Data>::operator=(const StackVec<Data> &stack) noexcept {

        //std::cout << "Richiamata assegnazione const di stack (" << &stack << ") (size " << stack.RealSize() << ")" << "in this (" << this << ")(size " << this->RealSize() << ")" << std::endl;

        //std::cout << "this->Size(): " << this->Size() << std::endl;
        //std::cout << "stack.Size(): " << stack.Size() << std::endl;
        //std::cout << "this->RealSize(): " << this->RealSize() << std::endl;
        //std::cout << "stack.RealSize(): " << stack.RealSize() << std::endl;
        //std::cout << "this->size: " << this->size << std::endl;
        //std::cout << "stack.size: " << stack.size << std::endl;

        //std::cout << "Print parameter 'stack':" << std::endl;

        //stack.PrintAll();

        if (this == &stack) return *this;

        if (stack.Empty()) {
            if (!this->Empty()) Clear();
            return *this;
        }

        if (stack.RealSize() > this->RealSize()) Resize(stack.RealSize());

        this->Clear();

        for (unsigned long int i = 0; i < stack.Size(); i++) {
            Push(stack.elements[i]);
        }

        //std::cout << "Push terminata, size e stampa this:" << std::endl;

        //std::cout << "this->Size(): " << this->Size() << std::endl;
        //std::cout << "this->RealSize(): " << this->RealSize() << std::endl;
        //std::cout << "this->size: " << this->size << std::endl;

        //this->PrintAll();

        return *this;
    }

    template<typename Data>
    inline StackVec<Data> & StackVec<Data>::operator=(StackVec<Data> &&stack) noexcept {
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
        if (top != stack.top) return false;
        if (stack.Empty() && this->Empty()) return true;

        for (long int i = 0; i <= top; i++) {
            if (elements[i] != stack.elements[i]) return false;
        }
        return true;
    }

    template<typename Data>
    void StackVec<Data>::Pop() {
        //std::cout << "Popping " << Top() << std::endl;
        if (Empty()) {
            throw std::length_error("Stack is empty");
        }

        top--;

        if ((RealSize() - top) >= 2 * chunkSize) {
            //std::cout << "WARNING - resizing stack" << std::endl;
            Resize(RealSize() - chunkSize);
        }
    }

    template<typename Data>
    void StackVec<Data>::Push(const Data &val) {
        //std::cout << "Pushing const " << val << std::endl;
        if (Full() || RealSize() == 0) {
            //std::cout << "WARNING - resizing stack" << std::endl;
            Resize(RealSize() + chunkSize);
        }

        elements[++top] = val;
    }

    template<typename Data>
    void StackVec<Data>::Push(Data &&val) {
        //std::cout << "Pushing move " << val << std::endl;
        if (Full() || RealSize() == 0) {
            //std::cout << "WARNING - resizing stack" << std::endl;
            Resize(RealSize() + chunkSize);
        }

        elements[++top] = std::move(val);
    }

    template<typename Data>
    void StackVec<Data>::Resize(unsigned long newSize) noexcept {

        //std::cout << "Check SIZES" << std::endl;

        //std::cout << "this->RealSize: " << RealSize() << std::endl;
        //std::cout << "this->Size(): " << this->Size() << std::endl;
        //std::cout << "this->size: " << this->size << std::endl;
        //std::cout << "newSize: " << newSize << std::endl;

        //std::cout << "Resizing stack from " << RealSize() << " to " << newSize << std::endl;
        if (newSize % chunkSize != 0) {
            newSize = ((newSize / chunkSize) + 1) * chunkSize;// Round up to the nearest multiple of chunkSize
            //std::cout << "WARNING - new size is not a multiple of chunk size, resizing to the nearest multiple of chunk size: " << newSize << std::endl;
        }

        if(newSize == RealSize()) return;

        try {
            //std::cout << "Invocating Vector<Data>::Resize(" << newSize << ")" << std::endl;
            Vector<Data>::Resize(newSize);
            //std::cout << "Resized stack, actual size: " << RealSize() << std::endl;
        } catch (const std::bad_alloc &e) {
            std::cerr << e.what() << '\n';
        }
    }

}// namespace lasd
