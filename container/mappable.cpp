#include "mappable.hpp"

namespace lasd {

/* ************************************************************************** */

/*** PreOrderMappableContainer class ***/

    void PreOrderMappableContainer::Map(MappableContainer::MapFun mapFun) {
        PreOrderMap(mapFun);
    }

/* ************************************************************************** */

/*** PostOrderMappableContainer class ***/

    void PostOrderMappableContainer::Map(MappableContainer::MapFun mapFun) {
        PostOrderMap(mapFun);
    }

/* ************************************************************************** */

    /*** InOrderMappableContainer class ***/

    void InOrderMappableContainer::Map(MappableContainer::MapFun mapFun) {
        InOrderMap(mapFun);
    }

/* ************************************************************************** */

    /*** BreadthOrderMappableContainer class ***/

    void BreadthOrderMappableContainer::Map(MappableContainer::MapFun mapFun) {
        BreadthOrderMap(mapFun);
    }
}
