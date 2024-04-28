#include "stacklst.hpp"

namespace lasd {

    /* ************************************************************************** */

    /*** StackLst class ***/

    template<typename Data>
    StackLst<Data>::StackLst(const TraversableContainer<Data> &container) noexcept {
        container.Map([this](const Data &val) { this->Push(val); });
    }

    template<typename Data>
    StackLst<Data>::StackLst(MappableContainer<Data> &&container) noexcept {
        container.Map([this](Data &&val) { this->Push(std::move(val)); });
    }

    template<typename Data>
    bool StackLst<Data>::operator==(const StackLst<Data> &stack) const noexcept { return List<Data>::operator==(stack); }
}