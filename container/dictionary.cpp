namespace lasd {

    // Implementation of the DictionaryContainer class

    // Specific member functions

    template<typename Data>
    bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data> &c) {
        bool b{true};
        c.Traverse([this, &b](const Data &d) { b &= Insert(d); });
        return b;
    }

    template <typename Data>
    bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data>&& c)
    {
        bool b {true};
        c.Map([this, &b](Data& d) {
            //std::cout << "Inserting " << d << std::endl;
            b &= Insert(std::move(d));
            //std::cout << "b is " << (b?"true":"false") << std::endl;
        });
        return b;
    }

    template <typename Data>
    bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data>& c)
    {
        bool b {true};
        c.Traverse([this, &b](const Data& d) { b &= Remove(d); });
        return b;
    }

    template <typename Data>
    bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data>& c)
    {
        bool b {false};
        c.Traverse([this, &b](const Data& d) { b |= Insert(d); });
        return b;
    }

    template <typename Data>
    bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data>&& c)
    {
        bool b {false};
        c.Map([this, &b](Data& d) { b |= Insert(std::move(d)); });
        return b;
    }

    template <typename Data>
    bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data>& c)
    {
        bool b {false};
        c.Traverse([this, &b](const Data& d) { b |= Remove(d); });
        return b;
    }
}// namespace lasd
