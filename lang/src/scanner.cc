#include "scanner.h"

void Scanner::Load(const char* buf) {
    this->buf = buf;
}

Token Scanner::Next() {
    Skip();

    char cur = *this->cur;

    if (std::isdigit(cur))
        return NextNum();

    if (std::isalpha(cur))
        return NextIdf();

    Token tok = Token{
        .type = Token::OPS,

        .ent = 0,
        .row = this->row,
        .col = this->col,
    };

    switch (cur)
    {
    case '<':
        if (*(this->cur + 1) == '<')
            tok.ent = ops->Get("<<")->pos;
        else 
            tok.ent = ops->Get("<")->pos;

        break;
    case '>':
        if (*(this->cur + 1) == '>')
            tok.ent = ops->Get(">>")->pos;
        else 
            tok.ent = ops->Get(">")->pos;

        break;

    case '=':
        if (*(this->cur + 1) == '=')
            tok.ent = ops->Get("==")->pos;
        else 
            tok.ent = ops->Get("=")->pos;

        break;
    case '+':
        tok.ent = ops->Get("+")->pos;
        break;
    case '-':
        tok.ent = ops->Get("-")->pos;
        break;
    case '*':
        tok.ent = ops->Get("*")->pos;
        break;
    default:
        tok.type = Token::ERR;
        break;
    }

    return tok;
}

void Scanner::Skip() {
    for (;;) {
        if (*cur == ' ') {
            cur++;
            col++;

            continue;
        }

        if (*cur == '\n') {
            cur++;
            row++;
            col = 1;

            continue;
        }

        break;
    }

    beg = cur;
}

Token Scanner::NextNum() {
    Token tok = Token {
        .type = Token::NUM,

        .ent = 0,
        .row = this->row,
        .col = this->col,
    };

    long long num = 0;

    while (std::isdigit(*cur)) {
        num = num * 10 + (*cur - '0');
        cur++;
    }

    Entry<std::string, Value>* ent = con->Get(std::string(beg, cur - beg));

    if (!ent)
        ent = con->Set(std::string(beg, cur - beg + 1), Value{
            .type = Value::NUM,
            .as.num = num,
        });

    tok.ent = ent->pos;

    return tok;
}

Token Scanner::NextIdf() {
    Token tok = Token {
        .type = Token::IDF,

        .ent = 0,
        .row = this->row,
        .col = this->col,
    };

    while (std::isdigit(*cur) || std::isalpha(*cur))
        cur++;

    key->Get(std::string(beg, cur - beg + 1));

    return tok;
}