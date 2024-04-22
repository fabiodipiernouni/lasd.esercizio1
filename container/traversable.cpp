#include "traversable.hpp"

namespace lasd {

/* ************************************************************************** */

/*** TraversableContainer class ***/

    template<typename Data>
    template<typename Accumulator>
    Accumulator TraversableContainer<Accumulator>::Fold(
            const std::function<Accumulator(const Accumulator &, const Data &)> &foldFun,
            const Accumulator &init) const {
        Accumulator acc = init;
        Traverse([&acc, &foldFun](const typename TraversableContainer<Data>::Data &data) {
            acc = foldFun(acc, data);
        });
        return acc;
    }

    template<typename Data>
    bool TraversableContainer<Data>::Exists(const Data &target) const {
        bool found = false;
        Traverse([&found, &target](const Data &data) {
            if (data == target) {
                found = true;
            }
        });
        return found;
    }

/* ************************************************************************** */

/*** PreOrderTraversableContainer class ***/

    template<typename Data>
    template<typename Accumulator>
    Accumulator PreOrderTraversableContainer<Accumulator>::PreOrderFold(
            const std::function<Accumulator(const Accumulator &, const Data &)> &fun, const Accumulator &acc) const {
        Accumulator accumulator = acc;
        Traverse([&fun, &accumulator](const Data &data) {
            accumulator = fun(accumulator, data);
        });
        return accumulator;
    }

    template<typename Data>
    void PreOrderTraversableContainer<Data>::Traverse(const std::function<void(const Data &)> &visit) const {
        PreOrderTraverse(visit);
    }

/* ************************************************************************** */

    /*** PostOrderTraversableContainer class ***/

    template<typename Data>
    template<typename Accumulator>
    Accumulator PostOrderTraversableContainer<Accumulator>::PostOrderFold(
            const std::function<Accumulator(const Accumulator &, const Data &)> &foldFun,
            const Accumulator &init) const {
        Accumulator accumulator = init;
        Traverse([&foldFun, &accumulator](const Data &data) {
            accumulator = foldFun(accumulator, data);
        });
        return accumulator;
    }

    template<typename Data>
    void PostOrderTraversableContainer<Data>::Traverse(const std::function<void(const Data &)> &visit) const {
        PostOrderTraverse(visit);
    }

/* ************************************************************************** */

    /*** InOrderTraversableContainer class ***/

    template<typename Data>
    template<typename Accumulator>
    Accumulator InOrderTraversableContainer<Accumulator>::InOrderFold(
            const std::function<Accumulator(const Accumulator &, const Data &)> &foldFun,
            const Accumulator &init) const {
        Accumulator accumulator = init;
        Traverse([&foldFun, &accumulator](const Data &data) {
            accumulator = foldFun(accumulator, data);
        });
        return accumulator;
    }

    template<typename Data>
    void InOrderTraversableContainer<Data>::Traverse(const std::function<void(const Data &)> &visit) const {
        InOrderTraverse(visit);
    }

/* ************************************************************************** */

    /*** BreadthOrderTraversableContainer class ***/

    template<typename Data>
    template<typename Accumulator>
    Accumulator BreadthOrderTraversableContainer<Accumulator>::BreadthOrderFold(
            const std::function<Accumulator(const Accumulator &, const Data &)> &foldFun,
            const Accumulator &init) const {
        Accumulator accumulator = init;
        Traverse([&foldFun, &accumulator](const Data &data) {
            accumulator = foldFun(accumulator, data);
        });
        return accumulator;
    }

    template<typename Data>
    void BreadthOrderTraversableContainer<Data>::Traverse(const std::function<void(const Data &)> &visit) const {
        BreadthOrderTraverse(visit);
    }

}
