#include "map.h"

#include "value.h"

using namespace std;

template <class K, class V, class H>
void Map<K, V, H>::Grow() {
  size_t cap = (this->cap + 1) * 2;
  Entry<K, V, H>** dat = new Entry<K, V, H>*[cap];

  for (size_t i = 0; i < cap; ++i)
    dat[i] = nullptr;

  for (size_t i = 0; i < this->cap; ++i)
    if (this->dat[i]) {
      size_t j = this->dat[i]->sig % cap;

      while (dat[j])
        j = (j + 1) % cap;

      dat[j] = this->dat[i];
    }

  delete[] this->dat;

  this->dat = dat;
  this->cap = cap;
}

template <class K, class V, class H>
Map<K, V, H>::~Map() {
  for (size_t i = 0; i < this->cap; ++i)
    if (dat[i])
      delete dat[i];

  delete[] dat;
}

template <class K, class V, class H>
Entry<K, V, H>* Map<K, V, H>::Set(K k, V v) {
  if (len + 1 > cap * 0.75)
    Grow();

  Entry<K, V, H>* ent = nullptr;

  size_t s = H{}(k);
  size_t i = s % cap;

  while ((ent = dat[i]) && s != ent->sig)
    i = (i + 1) % cap;

  if (!ent) {
    ent = new Entry<K, V, H>;

    ent->key = k;
    ent->val = v;
    ent->sig = s;
    ent->pos = len;

    dat[i] = ent;
    len += 1;
  } else
    ent->val = v;

  return ent;
}

template <class K, class V, class H>
Entry<K, V, H>* Map<K, V, H>::Get(K k) {
  Entry<K, V, H>* ent = nullptr;

  size_t s = H{}(k);
  size_t i = s % cap;

  while ((ent = dat[i]) && s != ent->sig)
    i = (i + 1) % cap;

  return ent;
}

template <class K, class V, class H>
size_t Map<K, V, H>::Size() {
  return len;
}

istream& operator>>(istream& is, char v) { return is >> &v; }
istream& operator>>(istream& is, Void& v) { return is; }
ostream& operator<<(ostream& os, const Void& v) { return os; }

istream& operator>>(istream& is, Value& v) {
  char type;

  is >> &type;

  switch (type) {
    case 'N':
      v.type = Value::NUM;
      return is >> v.as.num;
    case 'U':
      v.type = Value::UND;
      return is;
    default:
      __throw_invalid_argument("unknown value type");
  }
}

ostream& operator<<(ostream& os, const Value& v) {
  switch (v.type) {
    case Value::NUM:
      return os << 'N' << " " << v.as.num;
    case Value::UND:
      return os << 'U';
    default:
      __throw_invalid_argument("unknown value type");
  }
}

template <class K, class V, class H>
void Map<K, V, H>::Load(istream& is) {
  K k;
  V v;

  for (int i; is >> i; ++i) {
    is >> '|' >> k >> v;
    Set(k, v);
  }
}

template <class K, class V, class H>
void Map<K, V, H>::Dump(ostream& os) {
  vector<Entry<K, V>*> rows(len);

  for (size_t i = 0; i < cap; ++i)
    if (dat[i])
      rows[dat[i]->pos] = dat[i];

  for (size_t i = 0; i < len; ++i)
    os << rows[i]->pos << " | " << rows[i]->key << " " << rows[i]->val << endl;
}

template class Map<string, Void>;
template class Map<string, Value>;