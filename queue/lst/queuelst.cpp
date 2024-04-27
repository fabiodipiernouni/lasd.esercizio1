
#include "queuelst.hpp"

namespace lasd {

    /* ************************************************************************** */
    /*** QueueLst class ***/

    // throw std::length_error when empty
    template<typename Data>
    inline const Data &QueueLst<Data>::Head() const {
        if (Empty()) {
            throw std::length_error("Cannot access the head of an empty queue");
        }
        return List<Data>::Front();
    };

    // throw std::length_error when empty
    template<typename Data>
    inline Data &QueueLst<Data>::Head() {
        if (Empty()) {
            throw std::length_error("Cannot access the head of an empty queue");
        }
        return List<Data>::Front();
    };
    // throw std::length_error when empty
    template<typename Data>
    inline void QueueLst<Data>::Dequeue() {
        if (Empty()) {
            throw std::length_error("Cannot dequeue from an empty queue");
        }
        List<Data>::RemoveFromFront();
    };
    // throw std::length_error when empty
    template<typename Data>
    inline Data QueueLst<Data>::HeadNDequeue() {
        if (Empty()) {
            throw std::length_error("Cannot access the head of an empty queue");
        }
        return List<Data>::FrontNRemove();
    };

    /* ************************************************************************** */

}// namespace lasd
