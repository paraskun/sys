#ifndef LANG_VALUE_H
#define LANG_VALUE_H

#include <iostream>

struct Value {
  enum ValueType {
    NUM,
    UND,
  } type;

  union {
    long long num;
  } as;
};

#endif  // LANG_VALUE_H