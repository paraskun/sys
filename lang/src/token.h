#ifndef LANG_TOKEN_H
#define LANG_TOKEN_H

struct Token {
  enum TokenType {
    // Keywords
    TOK_IF = 0x00,
    TOK_ELSE = 0x10,

    // Operators
    TOK_LT = 0x01,
    TOK_GT = 0x11,
    TOK_EQ = 0x21,
    TOK_EEQ = 0x31,

    TOK_ADD = 0x41,
    TOK_SUB = 0x51,
    TOK_MUL = 0x61,

    TOK_LSH = 0x71,
    TOK_RSH = 0x81,

    // Identifier
    TOK_ID = 0x02,

    // Literal
    TOK_NUM = 0x03,
  } type;

  const char* sym;

  int len;
  int row;
  int col;
};

#endif  // LANG_TOKEN_H