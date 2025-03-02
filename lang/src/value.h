#ifndef LANG_VALUE_H
#define LANG_VALUE_H

struct Value {
  enum ValueType {
    VAL_NUM,
  } type;

  union {
    long long num;
  } as;
};

#endif  // LANG_VALUE_H