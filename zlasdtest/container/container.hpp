
#ifndef CONTAINERTEST_HPP
#define CONTAINERTEST_HPP

#include "../../container/container.hpp"
typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;



/* ************************************************************************** */

// Container member functions!

void Empty(uint&, uint&, const lasd::Container&, bool);

void Size(uint&, uint&, const lasd::Container&, bool, ulong);

/* ************************************************************************** */

#endif
