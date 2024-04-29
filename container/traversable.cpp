namespace lasd {

/* ************************************************************************** */

/*** TraversableContainer class ***/
    template<typename Data>
    bool TraversableContainer<Data>::Exists(const Data &target) const noexcept {
        bool found = false;
        Traverse([&found, &target](const Data &data) {
            if (data == target) {
                found = true;
            }
        });
        return found;
    }

    template<typename Data>
    template<typename Accumulator>
    Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> foldFun, const Accumulator &init) const {
        Accumulator acc = init;
        Traverse([&acc, &foldFun](const typename TraversableContainer<Data>::Data &data) {
            acc = foldFun(acc, data);
        });
        return acc;
    }


/* ************************************************************************** */

/*** PreOrderTraversableContainer class ***/

    template<typename Data>
    template<typename Accumulator>
    Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> fun, const Accumulator &acc) const {
        //std::cout << "ATTENZIONE CHIAMO PreOrderTraversableContainer<Data>::PreOrderFold (size: " << this->Size() << ")" << std::endl;
        Accumulator accumulator = acc;
        PreOrderTraverse([&fun, &accumulator](const Data &data) {
            //std::cout << "ATTENZIONE accumulator prima: " << accumulator << std::endl;
            accumulator = fun(data, accumulator);
            //std::cout << "ATTENZIONE accumulator dopo: " << accumulator << std::endl;
        });
        return accumulator;
    }

/* ************************************************************************** */

    /*** PostOrderTraversableContainer class ***/

    template<typename Data>
    template<typename Accumulator>
    Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> foldFun, const Accumulator &init) const {
        std::cout << "Chiamo PostOrderTraversableContainer<Data>::PostOrderFold" << std::endl;
        Accumulator accumulator = init;
        PostOrderTraverse([&foldFun, &accumulator](const Data &data) {
            accumulator = foldFun(data, accumulator);
        });
        return accumulator;
    }

/* ************************************************************************** */

    /*** InOrderTraversableContainer class ***/

    template<typename Data>
    template<typename Accumulator>
    Accumulator InOrderTraversableContainer<Data>::InOrderFold(FoldFun<Accumulator> foldFun, const Accumulator &init) const {
        Accumulator accumulator = init;
        Traverse([&foldFun, &accumulator](const Data &data) {
            accumulator = foldFun(accumulator, data);
        });
        return accumulator;
    }

/* ************************************************************************** */

    /*** BreadthTraversableContainer class ***/

    template<typename Data>
    template<typename Accumulator>
    Accumulator BreadthTraversableContainer<Data>::BreadthFold(FoldFun<Accumulator> foldFun, const Accumulator &init) const {
        Accumulator accumulator = init;
        Traverse([&foldFun, &accumulator](const Data &data) {
            accumulator = foldFun(accumulator, data);
        });
        return accumulator;
    }
}
