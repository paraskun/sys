#ifndef LANG_SCANNER_H
#define LANG_SCANNER_H

#include <istream>
#include <assert.h>

#include "token.h"
#include "value.h"
#include "map.h"

class Scanner {
    private:
        const char* buf;
        const char* beg;
        const char* cur;

        int row;
        int col;

        Map<std::string, Void>* key;
        Map<std::string, Void>* ops;

        Map<std::string, Value>* idf;
        Map<std::string, Value>* con;

        void Skip();

        Token NextIdf();
        Token NextNum();
        Token NextStr();

    public:
        Scanner(
            Map<std::string, Void>* key,
            Map<std::string, Void>* ops,
            Map<std::string, Value>* idf,
            Map<std::string, Value>* con
        ) {
            assert(key);
            assert(ops);
            assert(idf);
            assert(con);

            this->key = key;
            this->ops = ops;
            this->idf = idf;
            this->con = con;

            beg = 0;
            cur = 0;
            row = 0;
            col = 0;
        };

        void Load(const char* buf);
        Token Next();
};

#endif // LANG_SCANNER_H