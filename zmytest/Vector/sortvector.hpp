#include "../../vector/vector.hpp"


#ifndef LASD_ESERCIZIO1_ZMYTEST_TESTSERIES_TESTS_SORTVECTOR_HPP_
#define LASD_ESERCIZIO1_ZMYTEST_TESTSERIES_TESTS_SORTVECTOR_HPP_

template <typename Data>
void Sort(uint &testnum, uint &testerr, lasd::SortableVector<Data> &vec1, bool chk) {
    bool tst = true;
    testnum++;
    try {
        vec1.Sort();
        std::cout << " " << testnum << " (" << testerr << ") The vector is sorted: ";
        std::cout << ((tst = (tst == chk)) ? "Correct" : "Error") << "!" << std::endl;
    } catch (std::exception &exc) {
        std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
    }
    testerr += (1 - (uint)tst);
}


#endif