#include "mappable.hpp"

namespace lasd {

    /* ************************************************************************** */

    /*** LinearContainer class ***/

    template<typename Data>
    bool LinearContainer<Data>::operator==(const LinearContainer<Data> &container) const noexcept {
        if (this->Size() != container.Size()) return false;

        for (unsigned long i{0}; i < this->Size(); i++) {
            if ((*this)[i] != container[i]) {
                return false;
            }
        }

        return true;
    }

    template<typename Data>
    bool LinearContainer<Data>::operator!=(const LinearContainer<Data> &container) const noexcept {
        return !(*this == container);
    }

    template<typename Data>
    Data &LinearContainer<Data>::Front() {
        if (this->Size() == 0)
            throw std::length_error("The container is empty, there is no front element");

        return (*this)[0];
    }

    template<typename Data>
    const Data &LinearContainer<Data>::Front() const {
        if (this->Size() == 0)
            throw std::length_error("The container is empty, there is no front element");

        return (*this)[0];
    }

    template<typename Data>
    Data &LinearContainer<Data>::Back() {
        if (this->Size() == 0)
            throw std::length_error("The container is empty, there is no back element");

        return (*this)[this->Size() - 1];
    }

    template<typename Data>
    const Data &LinearContainer<Data>::Back() const {
        if (this->Size() == 0)
            throw std::length_error("The container is empty, there is no back element");

        return (*this)[this->Size() - 1];
    }

    template<typename Data>
    void LinearContainer<Data>::Traverse(const typename TraversableContainer<Data>::TraverseFun traverseFun) const {
        for (unsigned long i{0}; i < this->Size(); i++) {
            traverseFun((*this)[i]);
        }
    }

    template<typename Data>
    void LinearContainer<Data>::PreOrderTraverse(const typename TraversableContainer<Data>::TraverseFun traverseFun) const {
        return this->Traverse(traverseFun);
    }

    template<typename Data>
    void LinearContainer<Data>::PostOrderTraverse(const typename TraversableContainer<Data>::TraverseFun traverseFun) const {
        if(this->Size() == 0) return;
        //std::cout << "ATTENZIONE LinearContainer<Data>::PostOrderTraverse size: " << this->size << std::endl;
        for (unsigned long i{this->size - 1}; i >= 0; i--) {
            //std::cout << "i: " << i << std::endl;
            traverseFun((*this)[i]);
            if(i == 0) break;
        }
    }

    template<typename Data>
    void LinearContainer<Data>::Map(typename MappableContainer<Data>::MapFun mf) {
        for (unsigned long i{0}; i < this->Size(); i++) {
            mf((*this)[i]);
        }
    }

    template<typename Data>
    void LinearContainer<Data>::PreOrderMap(typename MappableContainer<Data>::MapFun mf) {
        Map(mf);
    }

    template<typename Data>
    void LinearContainer<Data>::PostOrderMap(typename MappableContainer<Data>::MapFun mf) {
        for (unsigned long i{this->Size() - 1}; i >= 0; i--) {
            mf((*this)[i]);
            if(i == 0) break;
        }
    }

    /* ************************************************************************** */

    /*** SortableLinearContainer class ***/

    template<typename Data>
    bool SortableLinearContainer<Data>::operator==(const SortableLinearContainer<Data> &container) const noexcept {
        return LinearContainer<Data>::operator==(container);
    }

    template<typename Data>
    bool SortableLinearContainer<Data>::operator!=(const SortableLinearContainer<Data> &container) const noexcept {
        return LinearContainer<Data>::operator!=(container);
    }

    template<typename Data>
    void SortableLinearContainer<Data>::merge(unsigned long int s, unsigned long int m, unsigned long int e) noexcept {
        unsigned long int n1 = m - s + 1;
        unsigned long int n2 = e - m;
        Data *left = new Data[n1];
        Data *right = new Data[n2];

        for (unsigned long int i{0}; i < n1; i++) left[i] = (*this)[s + i];
        for (unsigned long int j{0}; j < n2; j++) right[j] = (*this)[m + 1 + j];

        unsigned long int i{0};
        unsigned long int j{0};
        unsigned long int k = s;

        while (i < n1 && j < n2) {
            if (DataComparison(left[i], right[j]) <= 0) {
                (*this)[k] = left[i];
                i++;
            } else {
                (*this)[k] = right[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            (*this)[k] = left[i];
            i++;
            k++;
        }

        while (j < n2) {
            (*this)[k] = right[j];
            j++;
            k++;
        }

        delete[] left;
        delete[] right;
    }

    template<typename Data>
    void SortableLinearContainer<Data>::mergeSort(unsigned long int s, unsigned long int e) noexcept {
        if (s >= e) return;

        unsigned long int m = s + (e - s) / 2;
        mergeSort(s, m);
        mergeSort(m + 1, e);

        merge(s, m, e);
    }
}// namespace lasd
