#ifndef LANG_STORE_H
#define LANG_STORE_H

#include <iostream>
#include <vector>

struct Void {};

template <class K, class V, class H = std::hash<K>>
struct Entry {
  K key;
  V val;

  size_t pos;
  size_t sig;
};

template <class K, class V, class H = std::hash<K>>
struct Map {
 private:
  size_t len;
  size_t cap;

  Entry<K, V, H>** dat;

  void Grow();

 public:
  Map() : len{0}, cap{0}, dat{0} {}
  ~Map();

  Entry<K, V, H>* Set(K k, V v);
  Entry<K, V, H>* Get(K k);

  void Load(std::istream&);
  void Dump(std::ostream&);

  size_t Size();
};

#endif  // LANG_STORE_H