add_library(lang
    src/token.h
    src/value.h
    src/map.h

    src/map.cc
)

add_subdirectory(test)