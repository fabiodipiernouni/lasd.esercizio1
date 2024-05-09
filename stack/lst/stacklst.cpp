namespace lasd {

    /* ************************************************************************** */

    /*** StackLst class ***/

    template<typename Data>
    StackLst<Data>::StackLst(const TraversableContainer<Data> &container) noexcept {
        //std::cout << "Invocato StackLst<Data>::StackLst(const TraversableContainer<Data> &container)" << std::endl;
        container.Traverse([this](const Data &val) {
            //std::cout << "Pushing value: " << val << std::endl;
            this->List<Data>::InsertAtBack(val); });
    }

    template<typename Data>
    StackLst<Data>::StackLst(MappableContainer<Data> &&container) noexcept {
        //std::cout << "Invocato StackLst<Data>::StackLst(MappableContainer<Data> &&container)" << std::endl;
        container.Map([this](Data &val) { this->List<Data>::InsertAtBack(std::move(val)); });
    }

    template<typename Data>
    bool StackLst<Data>::operator==(const StackLst<Data> &stack) const noexcept { return List<Data>::operator==(stack); }
}