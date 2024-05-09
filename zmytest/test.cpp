
#include <iostream>

#include "../zlasdtest/container/container.hpp"
#include "../zlasdtest/container/dictionary.hpp"
#include "../zlasdtest/container/linear.hpp"
#include "../zlasdtest/container/mappable.hpp"
#include "../zlasdtest/container/testable.hpp"
#include "../zlasdtest/container/traversable.hpp"

#include "container/container.hpp"
// #include "container/traversable.hpp"
#include "utils/automobile.hpp"

#include "../zlasdtest/vector/vector.hpp"

#include "../zlasdtest/list/list.hpp"

#include "../stack/lst/stacklst.hpp"
#include "../stack/vec/stackvec.hpp"
#include "../zlasdtest/stack/stack.hpp"

#include "../queue/lst/queuelst.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../zlasdtest/queue/queue.hpp"
#include "vector/sortvector.hpp"

/* ************************************************************************** */

#include <functional>
#include <iostream>

/* ************************************************************************** */

using namespace std;
using TestFun = function<void(unsigned int &, unsigned int &)>;

unsigned int testnum = 0;
unsigned int testerr = 0;

/* ************************************************************************** */

/* ************************************************************************** */

void my_car_tests(unsigned int &testnum, unsigned int &testerr) {
    unsigned int loctestnum{0};
    unsigned int loctesterr{0};
    cout << endl << "Begin of My Vector<Automobile> Test:" << endl;

    try {
        lasd::SortableVector<Automobile> vec1;
        Empty(loctestnum, loctesterr, vec1, true);
        Automobile car1 = Automobile(2021, Automobile::CarType::COUPE, "Citroen", "C4", "4564554");
        SetAt(loctestnum, loctesterr, vec1, false, 0, car1);
        vec1.Resize(5);
        SetAt(loctestnum, loctesterr, vec1, true, 0, car1);
        Empty(loctestnum, loctesterr, vec1, false);
        Automobile car2 = Automobile(car1);
        lasd::SortableVector<Automobile> vec2;
        vec2.Resize(5);
        car2.setModel("C3");
        car2.setYearOfProduction(2020);
        SetAt(loctestnum, loctesterr, vec1, true, 1, car2);
        SetAt(loctestnum, loctesterr, vec2, true, 0, car2);
        SetAt(loctestnum, loctesterr, vec2, true, 1, car1);
        EqualVector(loctestnum, loctesterr, vec1, vec2, false);
        Sort(loctestnum, loctesterr, vec1, true);
        Sort(loctestnum, loctesterr, vec2, true);
        EqualVector(loctestnum, loctesterr, vec1, vec2, true);
    } catch (...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }

    cout << "End of Vector<Automobile> Test! (Errors/Tests: " << loctesterr << "/"
         << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

template <typename Que>
void my_car_tests_complex(Que &queue1, unsigned int &testnum, unsigned int &testerr) {
    unsigned int loctestnum{0};
    unsigned int loctesterr{0};
    cout << endl << "Begin of My Complex Automobile Test:" << endl;

    try {
        lasd::SortableVector<Automobile> vec1(2);
        lasd::List<Automobile> list1;

        // Creazione di diversi modelli di automobili
        Automobile car1 = Automobile(2021, Automobile::CarType::COUPE, "Citroen", "C4", "4564554");
        Automobile car2 = Automobile(2020, Automobile::CarType::SEDAN, "BMW", "3 Series", "1234567");
        Automobile car3 = Automobile(2019, Automobile::CarType::SUV, "Audi", "Q5", "7891011");
        Automobile car4 = Automobile(2022, Automobile::CarType::HATCHBACK, "Volkswagen", "Golf", "12131415");

        // Inserimento delle automobili nei contenitori

        SetFront(loctestnum, loctesterr, vec1, true, car1);
        SetBack(loctestnum, loctesterr, vec1, true, car2);
        InsertAtFront(loctestnum, loctesterr, list1, true, car3);
        InsertAtBack(loctestnum, loctesterr, list1, true, car4);
        EnqueueC(loctestnum, loctesterr, queue1, car1);
        EnqueueC(loctestnum, loctesterr, queue1, car2);
        EnqueueC(loctestnum, loctesterr, queue1, car3);
        EnqueueC(loctestnum, loctesterr, queue1, car4);

        // Verifica che i contenitori non siano vuoti
        Empty(loctestnum, loctesterr, vec1, false);
        Empty(loctestnum, loctesterr, list1, false);
        Empty(loctestnum, loctesterr, queue1, false);

        // Ordinamento del vettore
        Sort(loctestnum, loctesterr, vec1, true);

        // Rimozione di elementi dalla lista e dalla coda
        RemoveFromFront(loctestnum, loctesterr, list1, true);

        Dequeue(loctestnum, loctesterr, queue1, true);

        // Verifica delle dimensioni dei contenitori dopo le operazioni di rimozione
        Size(loctestnum, loctesterr, vec1, true, 2);
        Size(loctestnum, loctesterr, list1, true, 1);
        Size(loctestnum, loctesterr, queue1, true, 3);

        Que queue2(queue1);
        EqualQueue(loctestnum, loctesterr, queue1, queue2, true);
    } catch (...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }

    cout << "End of Complex Automobile Test! (Errors/Tests: " << loctesterr << "/"
         << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void my_car_tests_c(unsigned int &testnum, unsigned int &testerr) {
    lasd::QueueVec<Automobile> quevec;
    cout << endl << "Begin of My QueueVec<Automobile> Test:" << endl;
    my_car_tests_complex(quevec, testnum, testerr);
    lasd::QueueLst<Automobile> quelst;
    cout << endl << "Begin of My QueueLst<Automobile> Test:" << endl;
    my_car_tests_complex(quelst, testnum, testerr);

    cout << "End of My Car Test! (Errors/Tests: " << testerr << "/" << testnum << ")" << endl;
}

void my_vector_int(unsigned int &testnum, unsigned int &testerr) {
  unsigned int loctestnum{0};
  unsigned int loctesterr{0};
  cout << endl << "Begin of My Vector<int> Test:" << endl;
  try {
    // creo vettore vuoto
    lasd::SortableVector<int> vec1;
    // controllo che sia vuoto
    Empty(loctestnum, loctesterr, vec1, true);
    // creo vettore di size 5
    lasd::SortableVector<int> vec2(5);
    // copio vettore di size > 0 in vettore di size 0
    vec1 = vec2;
    // controllo che il vettore copiato non sia vuoto
    Empty(loctestnum, loctesterr, vec1, false);
    // controllo che il vettore copiato e il sorgente siano identici
    EqualVector(loctestnum, loctesterr, vec1, vec2, true);
    // nuovo vettore vuoto
    lasd::SortableVector<int> vec3;
    // copio vettore con size 0 in vettore con size > 0
    vec2 = vec3;
    // controllo size
    Size(loctestnum, loctesterr, vec2, true, 0);
    // controllo che i vettori siano diversi
    EqualVector(loctestnum, loctesterr, vec1, vec2, false);
    // controllo che i vettori siano uguali
    EqualVector(loctestnum, loctesterr, vec2, vec3, true);
    // non posso settare in un vettore di size 0
    SetAt(loctestnum, loctesterr, vec3, false, 0, 0);
    // resize
    vec3.Resize(5);
    Size(loctestnum, loctesterr, vec3, true, 5);
    SetAt(loctestnum, loctesterr, vec3, true, 0, 5);
    SetAt(loctestnum, loctesterr, vec3, true, 1, 4);
    SetAt(loctestnum, loctesterr, vec3, true, 2, 3);
    SetAt(loctestnum, loctesterr, vec3, true, 3, 2);
    SetAt(loctestnum, loctesterr, vec3, true, 4, 1);
    SetAt(loctestnum, loctesterr, vec3, false, 5, 1);
    Empty(loctestnum, loctesterr, vec2, true);
    Size(loctestnum, loctesterr, vec2, true, 0);
    vec2 = (move(vec3));
    Size(loctestnum, loctesterr, vec3, true, 0);

    Traverse(loctestnum, loctesterr, vec2, true, TraversePrint<int>);
    GetAt(loctestnum, loctesterr, vec2, false, 0, 1);
    GetAt(loctestnum, loctesterr, vec2, false, 1, 2);
    GetAt(loctestnum, loctesterr, vec2, true, 2, 3);
    GetAt(loctestnum, loctesterr, vec2, false, 3, 4);
    GetAt(loctestnum, loctesterr, vec2, false, 4, 5);

    Empty(loctestnum, loctesterr, vec3, true);
    vec2.Sort();

    Traverse(loctestnum, loctesterr, vec2, true, TraversePrint<int>);
    GetAt(loctestnum, loctesterr, vec2, true, 0, 1);
    GetAt(loctestnum, loctesterr, vec2, true, 1, 2);
    GetAt(loctestnum, loctesterr, vec2, true, 2, 3);
    GetAt(loctestnum, loctesterr, vec2, true, 3, 4);
    GetAt(loctestnum, loctesterr, vec2, true, 4, 5);

    vec2.Sort();

    Traverse(loctestnum, loctesterr, vec2, true, TraversePrint<int>);
    GetAt(loctestnum, loctesterr, vec2, true, 0, 1);
    GetAt(loctestnum, loctesterr, vec2, true, 1, 2);
    GetAt(loctestnum, loctesterr, vec2, true, 2, 3);
    GetAt(loctestnum, loctesterr, vec2, true, 3, 4);
    GetAt(loctestnum, loctesterr, vec2, true, 4, 5);

    vec2.Resize(2);
    GetAt(loctestnum, loctesterr, vec2, false, 2, 1);

    lasd::SortableVector<int> vec4(vec2);
    Empty(loctestnum, loctesterr, vec2, false);
    lasd::SortableVector<int> vec5(move(vec2));
    Empty(loctestnum, loctesterr, vec2, true);
    EqualVector(loctestnum, loctesterr, vec4, vec5, true);
    lasd::SortableVector<int> vec6;
    EqualVector(loctestnum, loctesterr, vec2, vec6, true);
    vec4.Resize(1);
    EqualVector(loctestnum, loctesterr, vec4, vec5, false);
    vec4.Resize(2);
    SetAt(loctestnum, loctesterr, vec4, true, 1, 2);
    Traverse(loctestnum, loctesterr, vec4, true, TraversePrint<int>);
    Traverse(loctestnum, loctesterr, vec5, true, TraversePrint<int>);
    EqualVector(loctestnum, loctesterr, vec4, vec5, true);
    vec4.Resize(10);
    SetAt(loctestnum, loctesterr, vec4, true, 0, 1);
    SetAt(loctestnum, loctesterr, vec4, true, 1, 1);
    SetAt(loctestnum, loctesterr, vec4, true, 2, 1);
    SetAt(loctestnum, loctesterr, vec4, true, 3, 1);
    SetAt(loctestnum, loctesterr, vec4, true, 4, 1);
    SetAt(loctestnum, loctesterr, vec4, true, 5, 1);
    SetAt(loctestnum, loctesterr, vec4, true, 6, 1);
    SetAt(loctestnum, loctesterr, vec4, true, 7, 1);
    SetAt(loctestnum, loctesterr, vec4, true, 8, 1);
    SetAt(loctestnum, loctesterr, vec4, true, 9, 1);
    Traverse(loctestnum, loctesterr, vec4, true, TraversePrint<int>);
    Fold(loctestnum, loctesterr, vec4, true, FoldAdd<int>, 0, 10);
    Map(loctestnum, loctesterr, vec4, true, [](int &i) { ++i; });
    Traverse(loctestnum, loctesterr, vec4, true, TraversePrint<int>);
    Fold(loctestnum, loctesterr, vec4, true, FoldAdd<int>, 0, 20);
    unsigned long int pos{0};
    Map(loctestnum, loctesterr, vec4, true, [&pos](int &i) { i += pos++; });
    Traverse(loctestnum, loctesterr, vec4, true, TraversePrint<int>);
    Fold(loctestnum, loctesterr, vec4, true, FoldParity, 0, 1);
    lasd::List<int> lst(vec4);
    lasd::SortableVector<int> vec7(lst);
    EqualVector(loctestnum, loctesterr, vec4, vec7, true);
    Traverse(loctestnum, loctesterr, vec7, true, TraversePrint<int>);
    vec1 = vec5;
    lasd::SortableVector<int> vec8(move(lst));
    EqualVector(loctestnum, loctesterr, vec7, vec8, true);
    vec5 = move(vec7);
    Traverse(loctestnum, loctesterr, vec7, true, TraversePrint<int>);
    EqualVector(loctestnum, loctesterr, vec4, vec5, true);
    EqualVector(loctestnum, loctesterr, vec4, vec8, true);
    EqualVector(loctestnum, loctesterr, vec5, vec8, true);
    Empty(loctestnum, loctesterr, lst, false);
    Empty(loctestnum, loctesterr, vec7, false);
    EqualVector(loctestnum, loctesterr, vec1, vec7, true);
    NonEqualVector(loctestnum, loctesterr, vec1, vec7, false);
    Exists(loctestnum, loctesterr, vec7, true, 1);
    Exists(loctestnum, loctesterr, vec7, false, 12);
    Traverse(loctestnum, loctesterr, vec4, true, TraversePrint<int>);
    pos = 0;
    FoldPreOrder(
        loctestnum, loctesterr, vec4, true,
        [&pos](const int &i, const double &a) {
          return pos++ % 2 ? a - i : a + i;
        },
        0, -5);
    pos = 0;
    FoldPostOrder(
        loctestnum, loctesterr, vec4, true,
        [&pos](const int &i, const double &a) {
          return pos++ % 2 ? a - i : a + i;
        },
        0, 5);
    vec5.Clear();
    Size(loctestnum, loctesterr, vec5, true, 0);
    EqualVector(loctestnum, loctesterr, vec5, vec7, false);
    NonEqualVector(loctestnum, loctesterr, vec5, vec7, true);
    Exists(loctestnum, loctesterr, vec5, false, 1);
    GetAt(loctestnum, loctesterr, vec5, false, 0, 0);
    SetAt(loctestnum, loctesterr, vec5, false, 0, 0);
  } catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector<int> Test! (Errors/Tests: " << loctesterr << "/"
       << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void my_vector_int_alternative(unsigned int &testnum, unsigned int &testerr) {
    unsigned int loctestnum{0};
    unsigned int loctesterr{0};
    cout << endl << "Begin of My Vector<int> Alternative Test:" << endl;
    try {
        // creo vettore di size 10
        lasd::SortableVector<int> vec1(10);
        // controllo che non sia vuoto
        Empty(loctestnum, loctesterr, vec1, false);
        // popolo il vettore con valori da 1 a 10
        for (int i = 0; i < 10; ++i) {
            SetAt(loctestnum, loctesterr, vec1, true, i, i+1);
        }
        // controllo che il vettore sia ordinato
        Sort(loctestnum, loctesterr, vec1, true);
        // creo un nuovo vettore copiando il vec1
        lasd::SortableVector<int> vec2(vec1);
        // controllo che i vettori siano uguali
        EqualVector(loctestnum, loctesterr, vec1, vec2, true);
        // modifico un elemento di vec2
        SetAt(loctestnum, loctesterr, vec2, true, 5, 50);
        // controllo che i vettori siano diversi
        EqualVector(loctestnum, loctesterr, vec1, vec2, false);
        // ordino vec2
        Sort(loctestnum, loctesterr, vec2, true);
        // controllo che l'elemento modificato sia al posto giusto
        GetAt(loctestnum, loctesterr, vec2, true, 9, 50);
        // svuoto vec1
        Clear(loctestnum, loctesterr, vec1, true);
        // controllo che vec1 sia vuoto
        Empty(loctestnum, loctesterr, vec1, true);
        // controllo che vec2 non sia vuoto
        Empty(loctestnum, loctesterr, vec2, false);
    } catch (...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of Vector<int> Alternative Test! (Errors/Tests: " << loctesterr << "/"
         << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

/* ************************************************************************** */

void my_vector_test(unsigned int &testnum, unsigned int &testerr) {
    my_vector_int_alternative(testnum, testerr);
}

/* ************************************************************************** */

void my_list_int(unsigned int &testnum, unsigned int &testerr) {
  unsigned int loctesterr{0};
  unsigned int loctestnum{0};
  cout << endl << "Begin of My List<int> Test:" << endl;
  try {
    lasd::List<int> lst1;
    Empty(loctestnum, loctesterr, lst1, true);
    lasd::Vector<int> vec1(5);
    SetAt(loctestnum, loctesterr, vec1, true, 0, 1);
    SetAt(loctestnum, loctesterr, vec1, true, 1, 2);
    SetAt(loctestnum, loctesterr, vec1, true, 2, 3);
    SetAt(loctestnum, loctesterr, vec1, true, 3, 4);
    SetAt(loctestnum, loctesterr, vec1, true, 4, 5);
    InsertAllC(loctestnum, loctesterr, lst1, true, vec1);
    InsertAllC(loctestnum, loctesterr, lst1, false, vec1);
    InsertSomeC(loctestnum, loctesterr, lst1, false, vec1);

    lasd::List<int> lst2;
    SetAt(loctestnum, loctesterr, vec1, true, 0, 2);
    InsertAllC(loctestnum, loctesterr, lst2, false, vec1);
    Traverse(loctestnum, loctesterr, vec1, true, TraversePrint<int>);
    lst2.Clear();
    Empty(loctestnum, loctesterr, lst2, true);
    Size(loctestnum, loctesterr, lst2, true, 0);
    Traverse(loctestnum, loctesterr, vec1, true, TraversePrint<int>);
    InsertAllM(loctestnum, loctesterr, lst2, false, move(vec1));
    Traverse(loctestnum, loctesterr, lst2, true, TraversePrint<int>);
    Traverse(loctestnum, loctesterr, vec1, true, TraversePrint<int>);
    lst2.Clear();
    SetAt(loctestnum, loctesterr, vec1, true, 0, 1);
    SetAt(loctestnum, loctesterr, vec1, true, 1, 2);
    SetAt(loctestnum, loctesterr, vec1, true, 2, 3);
    SetAt(loctestnum, loctesterr, vec1, true, 3, 4);
    SetAt(loctestnum, loctesterr, vec1, true, 4, 5);
    SetAt(loctestnum, loctesterr, vec1, true, 0, 1);
    Traverse(loctestnum, loctesterr, vec1, true, TraversePrint<int>);
    Traverse(loctestnum, loctesterr, lst2, true, TraversePrint<int>);
    InsertAllM(loctestnum, loctesterr, lst2, true, move(vec1));
    Traverse(loctestnum, loctesterr, lst2, true, TraversePrint<int>);
    SetAt(loctestnum, loctesterr, vec1, true, 0, 1);
    SetAt(loctestnum, loctesterr, vec1, true, 1, 2);
    SetAt(loctestnum, loctesterr, vec1, true, 2, 3);
    SetAt(loctestnum, loctesterr, vec1, true, 3, 4);
    SetAt(loctestnum, loctesterr, vec1, true, 4, 5);
    RemoveAll(loctestnum, loctesterr, lst2, true, vec1);
    Traverse(loctestnum, loctesterr, lst2, true, TraversePrint<int>);
    Empty(loctestnum, loctesterr, lst2, true);
    InsertSomeM(loctestnum, loctesterr, lst2, true, move(vec1));
    for (unsigned long int i {0}; i < vec1.Size(); ++i) vec1[i] = 1;
    RemoveAll(loctestnum, loctesterr, lst2, false, vec1);
  } catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of My Vector<int> Test! (Errors/Tests: " << loctesterr << "/"
       << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void my_list_int_alternative(unsigned int &testnum, unsigned int &testerr) {
    unsigned int loctestnum{0};
    unsigned int loctesterr{0};
    cout << endl << "Begin of My List<int> Alternative Test:" << endl;
    try {
        lasd::List<int> lst1;
        Empty(loctestnum, loctesterr, lst1, true);
        lasd::Vector<int> vec1(10);
        for (int i = 0; i < 10; ++i) {
            SetAt(loctestnum, loctesterr, vec1, true, i, i+1);
        }
        InsertAllC(loctestnum, loctesterr, lst1, true, vec1);
        lasd::List<int> lst2;
        for (int i = 0; i < 10; ++i) {
            SetAt(loctestnum, loctesterr, vec1, true, i, i+1);
        }
        InsertAllC(loctestnum, loctesterr, lst2, true, vec1);
        Clear(loctestnum, loctesterr, lst2, true);
        Empty(loctestnum, loctesterr, lst2, true);
        InsertAllM(loctestnum, loctesterr, lst2, true, move(vec1));
        Clear(loctestnum, loctesterr, vec1, true);
        Resize(loctestnum, loctesterr, vec1, true, 10);
        for (int i = 0; i < 10; ++i) {
            SetAt(loctestnum, loctesterr, vec1, true, i, i+1);
        }
        Clear(loctestnum, loctesterr, lst1, true);
        InsertAllM(loctestnum, loctesterr, lst1, true, move(vec1));//40
        RemoveAll(loctestnum, loctesterr, lst2, true, lst1);
        Clear(loctestnum, loctesterr, lst2, true);
        Clear(loctestnum, loctesterr, vec1, true);
        Empty(loctestnum, loctesterr, lst2, true);
        Empty(loctestnum, loctesterr, vec1, true);
        Resize(loctestnum, loctesterr, vec1, true, 10);
        for (int i = 0; i < 10; ++i) {
            SetAt(loctestnum, loctesterr, vec1, true, i, i+1);
        }
        InsertAllM(loctestnum, loctesterr, lst2, true, move(vec1));
        RemoveAll(loctestnum, loctesterr, lst1, true, lst2);
        Empty(loctestnum, loctesterr, lst1, true);
        for (int i = 0; i < 10; ++i) {
            SetAt(loctestnum, loctesterr, vec1, true, i, i+1);
        }
        InsertAllM(loctestnum, loctesterr, lst1, true, move(vec1));
        RemoveAll(loctestnum, loctesterr, lst2, true, lst1);
        Empty(loctestnum, loctesterr, lst2, true);
    } catch (...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of List<int> Alternative Test! (Errors/Tests: " << loctesterr << "/"
         << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void my_list_test(unsigned int &testnum, unsigned int &testerr) {
  my_list_int_alternative(testnum, testerr);
}

/* ************************************************************************** */

template <typename Que>
void queuetestint(Que &que, unsigned int &testnum, unsigned int &testerr) {
  unsigned int loctesterr{0};
  unsigned int loctestnum{0};
  try {

    Empty(loctestnum, loctesterr, que, true);
    Que que2;
    Que que3(que2);
    Que que4(move(que2));
    Empty(loctestnum, loctesterr, que2, true);
    Empty(loctestnum, loctesterr, que3, true);
    Empty(loctestnum, loctesterr, que4, true);

    EnqueueM(loctestnum, loctesterr, que3, 4);
    EnqueueM(loctestnum, loctesterr, que3, 5);
    EnqueueM(loctestnum, loctesterr, que3, 6);

    EnqueueC(loctestnum, loctesterr, que, 1);
    EnqueueC(loctestnum, loctesterr, que, 2);
    EnqueueC(loctestnum, loctesterr, que, 3);

    EqualQueue(loctestnum, loctesterr, que, que3, false);

    EnqueueM(loctestnum, loctesterr, que, 4);
    EnqueueM(loctestnum, loctesterr, que, 5);
    EnqueueM(loctestnum, loctesterr, que, 6);
    EnqueueM(loctestnum, loctesterr, que, 7);
    EnqueueM(loctestnum, loctesterr, que, 8);
    EnqueueM(loctestnum, loctesterr, que, 9);
    EnqueueM(loctestnum, loctesterr, que, 10);
    EnqueueM(loctestnum, loctesterr, que, 11);
    EnqueueM(loctestnum, loctesterr, que, 12);
    EnqueueM(loctestnum, loctesterr, que, 13);
    EnqueueM(loctestnum, loctesterr, que, 14);
    EnqueueM(loctestnum, loctesterr, que, 15);
    EnqueueM(loctestnum, loctesterr, que, 16);
    Size(loctestnum, loctesterr, que, true, 16);

    Dequeue(loctestnum, loctesterr, que, true);
    EnqueueC(loctestnum, loctesterr, que, 1);
    HeadNDequeue(loctestnum, loctesterr, que, true, 2);
    Head(loctestnum, loctesterr, que, true, 3);
    EnqueueC(loctestnum, loctesterr, que, 1);
    EnqueueC(loctestnum, loctesterr, que, 2);
    EnqueueC(loctestnum, loctesterr, que, 3);
    EnqueueC(loctestnum, loctesterr, que, 4);
    EnqueueC(loctestnum, loctesterr, que, 5);
    EnqueueC(loctestnum, loctesterr, que, 6);
    EnqueueC(loctestnum, loctesterr, que, 7);

    for (int i = 0; i < 30; i++) {
      EnqueueC(loctestnum, loctesterr, que, i);
    }

    for (int i = 0; i < 60; i++) {
      bool chk = !(que.Empty());
      Dequeue(loctestnum, loctesterr, que, chk);
      if (!(i % 10))
        EnqueueC(loctestnum, loctesterr, que, i);
    }
    EnqueueC(loctestnum, loctesterr, que, 1);

  } catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of My Queue<int> Test! (Errors/Tests: " << loctesterr << "/"
       << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

template <typename Que>
void queuetestint_alternative(Que &que, unsigned int &testnum, unsigned int &testerr) {
    unsigned int loctesterr{0};
    unsigned int loctestnum{0};
    try {
        Empty(loctestnum, loctesterr, que, true);
        Que que2;
        Que que3(que2);
        Que que4(move(que2));
        Empty(loctestnum, loctesterr, que2, true);
        Empty(loctestnum, loctesterr, que3, true);
        Empty(loctestnum, loctesterr, que4, true);

        for (int i = 0; i < 10; i++) {
            EnqueueC(loctestnum, loctesterr, que, i);
        }

        Size(loctestnum, loctesterr, que, true, 10);

        for (int i = 0; i < 5; i++) {
            Dequeue(loctestnum, loctesterr, que, true);
        }

        Size(loctestnum, loctesterr, que, true, 5);

        for (int i = 10; i < 20; i++) {
            EnqueueC(loctestnum, loctesterr, que, i);
        }

        Size(loctestnum, loctesterr, que, true, 15);

        while (!que.Empty()) {
            Dequeue(loctestnum, loctesterr, que, true);
        }

        Size(loctestnum, loctesterr, que, true, 0);

    } catch (...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of My Queue<int> Alternative Test! (Errors/Tests: " << loctesterr << "/"
         << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

template <typename Que>
void queueteststr(Que &que, unsigned int &testnum, unsigned int &testerr) {
  unsigned int loctesterr{0};
  unsigned int loctestnum{0};
  try {

    Empty(loctestnum, loctesterr, que, true);
    Que que2;
    Que que3(que2);
    Que que4(move(que2));
    Empty(loctestnum, loctesterr, que2, true);
    Empty(loctestnum, loctesterr, que3, true);
    Empty(loctestnum, loctesterr, que4, true);

    EnqueueC(loctestnum, loctesterr, que3, std::string("apamaa"));
    EnqueueC(loctestnum, loctesterr, que3, std::string("bapamda"));
    EnqueueC(loctestnum, loctesterr, que3, std::string("capadaa"));

    EnqueueC(loctestnum, loctesterr, que, std::string("1"));
    EnqueueC(loctestnum, loctesterr, que, std::string("2"));
    EnqueueC(loctestnum, loctesterr, que, std::string("3"));

    EqualQueue(loctestnum, loctesterr, que, que3, false);

    EnqueueC(loctestnum, loctesterr, que, std::string("4"));
    EnqueueC(loctestnum, loctesterr, que, std::string("5"));
    EnqueueC(loctestnum, loctesterr, que, std::string("6"));
    EnqueueC(loctestnum, loctesterr, que, std::string("7"));
    EnqueueC(loctestnum, loctesterr, que, std::string("8"));

    Dequeue(loctestnum, loctesterr, que, true);
    EnqueueC(loctestnum, loctesterr, que, std::string("1"));
    HeadNDequeue(loctestnum, loctesterr, que, true, std::string("2"));
    Head(loctestnum, loctesterr, que, true, std::string("3"));

    lasd::Vector<string> vec(8);

    // TODO
    // Ricca dava warning perche avevi usato int per i, ho cambiato
    for (unsigned long int i = 0; i < vec.Size(); ++i)
      SetAt(loctestnum, loctesterr, vec, true, i, to_string(i + 1));

    Que que5(vec);
    Que que6(move(vec));
    Empty(loctestnum, loctesterr, vec, false);

    EqualQueue(loctestnum, loctesterr, que, que5, false);
    EqualQueue(loctestnum, loctesterr, que5, que6, true);

    EnqueueC(loctestnum, loctesterr, que3, std::string("3"));
    EnqueueC(loctestnum, loctesterr, que3, std::string("4"));
    EnqueueC(loctestnum, loctesterr, que3, std::string("5"));
    EnqueueC(loctestnum, loctesterr, que3, std::string("6"));
    EnqueueC(loctestnum, loctesterr, que3, std::string("7"));
    EnqueueC(loctestnum, loctesterr, que3, std::string("8"));
    EnqueueC(loctestnum, loctesterr, que3, std::string("1"));

    EqualQueue(loctestnum, loctesterr, que, que3, false);

    Dequeue(loctestnum, loctesterr, que3, true);
    Dequeue(loctestnum, loctesterr, que3, true);
    Dequeue(loctestnum, loctesterr, que3, true);

    EqualQueue(loctestnum, loctesterr, que, que3, true);

    for (int i = 0; i < 30; i++) {
      EnqueueC(loctestnum, loctesterr, que, to_string(i));
    }
  } catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of My Queue<string> Test! (Errors/Tests: " << loctesterr << "/"
       << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

template <typename Que>
void queueteststr_alternative(Que &que, unsigned int &testnum, unsigned int &testerr) {
    unsigned int loctesterr{0};
    unsigned int loctestnum{0};
    try {
        Empty(loctestnum, loctesterr, que, true);
        Que que2;
        Que que3(que2);
        Que que4(move(que2));
        Empty(loctestnum, loctesterr, que2, true);
        Empty(loctestnum, loctesterr, que3, true);
        Empty(loctestnum, loctesterr, que4, true);

        for (int i = 0; i < 10; i++) {
            EnqueueC(loctestnum, loctesterr, que, std::string("str" + std::to_string(i)));
        }

        Size(loctestnum, loctesterr, que, true, 10);

        for (int i = 0; i < 5; i++) {
            Dequeue(loctestnum, loctesterr, que, true);
        }

        Size(loctestnum, loctesterr, que, true, 5);

        for (int i = 10; i < 20; i++) {
            EnqueueC(loctestnum, loctesterr, que, std::string("str" + std::to_string(i)));
        }

        Size(loctestnum, loctesterr, que, true, 15);

        while (!que.Empty()) {
            Dequeue(loctestnum, loctesterr, que, true);
        }

        Size(loctestnum, loctesterr, que, true, 0);

    } catch (...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of My Queue<string> Alternative Test! (Errors/Tests: " << loctesterr << "/"
         << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void my_queue_int(unsigned int &testnum, unsigned int &testerr) {
  lasd::QueueVec<int> quevec;
  cout << endl << "Begin of My QueueVec<int> Test:" << endl;
  queuetestint_alternative(quevec, testnum, testerr);
  lasd::QueueLst<int> quelst;
  cout << endl << "Begin of My QueueLst<int> Test:" << endl;
  queuetestint_alternative(quelst, testnum, testerr);

  cout << "End of My Queue<int> Test! (Errors/Tests: " << testerr << "/"
       << testnum << ")" << endl;
}

void my_queue_str(unsigned int &testnum, unsigned int &testerr) {
  lasd::QueueVec<string> quevecstr;
  cout << endl << "Begin of My Queue<string> Test:" << endl;
  queueteststr_alternative(quevecstr, testnum, testerr);
  lasd::QueueLst<string> quelststr;
  cout << endl << "Begin of My Queue<string> Test:" << endl;
  queueteststr_alternative(quelststr, testnum, testerr);

  cout << "End of My Queue<string> Test! (Errors/Tests: " << testerr << "/"
       << testnum << ")" << endl;
}

void my_queue_test(unsigned int &testnum, unsigned int &testerr) {

  my_queue_int(testnum, testerr);
  my_queue_str(testnum, testerr);
}

/* **************************************************************************
 */

void run(TestFun test) {
  unsigned int loctestnum = 0, loctesterr = 0;
  test(loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
}

string comment(const float accuracy) {
  if (accuracy == 100)
    return "HAIL TO C++ GOD!";
  if (accuracy >= 90)
    return "AMAZING!";
  if (accuracy >= 75)
    return "THAT'S HOW IT'S DONE!";
  if (accuracy >= 50)
    return "WE HAVE A NEW CONTENDER!";
  if (accuracy >= 25)
    return "BETTER NOT SHIP THIS TO MOGAVERO!";
  if (accuracy >= 10)
    return "GO WATCH C++ TUTORIAL BRO!";
  if (accuracy > 0)
    return "EVEN ZUCKEMBERG WAS A DROPOUT YOU KNOW?";
  return "WTF JUST HAPPENED????";
}

void mytest() {
  cout << endl
       << "#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Custom LASD tests "
          "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#"
       << endl;
  unsigned int testpassed = 0;
  double accuracy;

  /*~~~~~~~~~~~~~~~~~~~ Run Test Here ~~~~~~~~~~~~~~~~~~~*/

  run(my_vector_test);

  run(my_list_test);

  run(my_queue_test);

  run(my_car_tests_c);

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

  testpassed = testnum - testerr;
  accuracy = testpassed == testnum ? 100.00 : 100.00 * testpassed / testnum;

  cout << endl
       << endl
       << "    #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << comment(accuracy)
       << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#" << endl;

  cout << endl
       << "Exercise 1 Results: Passed/Tests: " << testpassed << "/" << testnum
       << " (" << accuracy << "%)" << endl;
}
