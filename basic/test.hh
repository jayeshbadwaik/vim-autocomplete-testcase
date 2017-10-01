#ifndef TEST_HH
#define TEST_HH

class A {
  unsigned int i;

public:
  A(unsigned int j);
  unsigned int operator()() const { return i ; }
  A& operator+=(const A& k);
};

#include "test.impl"
#endif // TEST_HH
