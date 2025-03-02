#ifndef LANG_TABLE_H
#define LANG_TABLE_H

#include "token.h"
#include "value.h"

struct Table {
 private:
  const char *kws;
  const char *ops;
  const char *cns;
  const char *ids;

 public:
  void Load();
  void Dump();

  bool Contains(Token tok);
  void Set(Token tok, Value val);

  Value Get(Token tok);
};

#endif  // LANG_TABLE_H