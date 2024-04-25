#include "dictionary.hpp"

namespace lasd {

    // Implementation of the DictionaryContainer class

    // Specific member functions

    template<typename Data>
    bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data> &c) {
        bool b{true};
        c.Traverse([this, &b](const Data &d) { b &= Insert(d); });
        return b;
    }
}// namespace lasd
