namespace lasd {

/* ************************************************************************** */

/*** PreOrderMappableContainer class ***/

    template<typename Data>
    void PreOrderMappableContainer<Data>::Map(MappableContainer<Data>::MapFun mapFun) {
        PreOrderMap(mapFun);
    }

/* ************************************************************************** */

/*** PostOrderMappableContainer class ***/

    template<typename Data>
    void PostOrderMappableContainer<Data>::Map(MappableContainer<Data>::MapFun mapFun) {
        PostOrderMap(mapFun);
    }

/* ************************************************************************** */

    /*** InOrderMappableContainer class ***/

    template<typename Data>
    void InOrderMappableContainer<Data>::Map(MappableContainer<Data>::MapFun mapFun) {
        InOrderMap(mapFun);
    }

/* ************************************************************************** */

    /*** BreadthMappableContainer class ***/

    template<typename Data>
    void BreadthMappableContainer<Data>::Map(MappableContainer<Data>::MapFun mapFun) {
        BreadthMap(mapFun);
    }
}
