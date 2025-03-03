#ifndef LANG_TOKEN_H
#define LANG_TOKEN_H

#include <iostream>

struct Token {
  enum TokenType {
    KEY,
    OPS,
    NUM,
    IDF,
    ERR,
  } type;

  size_t ent;
  size_t row;
  size_t col;
};

#endif  // LANG_TOKEN_H