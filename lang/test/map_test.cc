#include <gtest/gtest.h>
#include <lang/src/map.h>
#include <lang/src/value.h>

#include <fstream>
#include <string>

using namespace std;

TEST(Map, ReadKeywords) {
  Map<string, Void> map;
  Entry<string, Void>* ent;

  fstream in;
  in.open("dat/keywords.dat", fstream::in);

  ASSERT_NO_THROW(map.Load(in));

  ASSERT_NO_THROW(ent = map.Get("if"));
  ASSERT_EQ("if", ent->key);
  ASSERT_EQ(0, ent->pos);

  ASSERT_NO_THROW(ent = map.Get("else"));
  ASSERT_EQ("else", ent->key);
  ASSERT_EQ(1, ent->pos);

  ASSERT_NO_THROW(ent = map.Get("while"));
  ASSERT_EQ(nullptr, ent);
}

TEST(Map, ReadOperators) {
  Map<string, Void> map;
  Entry<string, Void>* ent;

  fstream in;
  in.open("dat/operators.dat", fstream::in);

  ASSERT_NO_THROW(map.Load(in));

  ASSERT_NO_THROW(ent = map.Get("<"));
  ASSERT_EQ("<", ent->key);
  ASSERT_EQ(0, ent->pos);

  ASSERT_NO_THROW(ent = map.Get(">"));
  ASSERT_EQ(">", ent->key);
  ASSERT_EQ(1, ent->pos);

  ASSERT_NO_THROW(ent = map.Get("=="));
  ASSERT_EQ("==", ent->key);
  ASSERT_EQ(2, ent->pos);

  ASSERT_NO_THROW(ent = map.Get("="));
  ASSERT_EQ("=", ent->key);
  ASSERT_EQ(3, ent->pos);

  ASSERT_NO_THROW(ent = map.Get("+"));
  ASSERT_EQ("+", ent->key);
  ASSERT_EQ(4, ent->pos);

  ASSERT_NO_THROW(ent = map.Get("-"));
  ASSERT_EQ("-", ent->key);
  ASSERT_EQ(5, ent->pos);

  ASSERT_NO_THROW(ent = map.Get("*"));
  ASSERT_EQ("*", ent->key);
  ASSERT_EQ(6, ent->pos);

  ASSERT_NO_THROW(ent = map.Get("<<"));
  ASSERT_EQ("<<", ent->key);
  ASSERT_EQ(7, ent->pos);

  ASSERT_NO_THROW(ent = map.Get(">>"));
  ASSERT_EQ(">>", ent->key);
  ASSERT_EQ(8, ent->pos);
}

TEST(Map, WriteIdentifiers) {
  Map<string, Value> map;

  ASSERT_NO_THROW(map.Set("age", Value{.type = Value::NUM, .as = {.num = 1106}}));
  ASSERT_NO_THROW(map.Set("phone", Value{.type = Value::NUM, .as = {.num = 911}}));
  ASSERT_NO_THROW(map.Set("phone", Value{.type = Value::NUM, .as = {.num = 112}}));
  ASSERT_NO_THROW(map.Set("name", Value{.type = Value::UND}));

  fstream out;
  out.open("dat/identifiers.dat", fstream::out);

  ASSERT_NO_THROW(map.Dump(out));
}

TEST(Map, WriteConstants) {
  Map<string, Value> map;

  ASSERT_NO_THROW(map.Set("1106", Value{.type = Value::NUM, .as = {.num = 1106}}));
  ASSERT_NO_THROW(map.Set("911", Value{.type = Value::NUM, .as = {.num = 911}}));

  fstream out;
  out.open("dat/constants.dat", fstream::out);

  ASSERT_NO_THROW(map.Dump(out));
}

TEST(Map, ReadIdentifiers) {
  Map<string, Value> map;
  Entry<string, Value>* ent;

  fstream in;
  in.open("dat/identifiers.dat", fstream::in);

  ASSERT_NO_THROW(map.Load(in));

  ASSERT_NO_THROW(ent = map.Get("age"));
  ASSERT_EQ("age", ent->key);
  ASSERT_EQ(0, ent->pos);
  ASSERT_EQ(Value::NUM, ent->val.type);
  ASSERT_EQ(1106, ent->val.as.num);

  ASSERT_NO_THROW(ent = map.Get("phone"));
  ASSERT_EQ("phone", ent->key);
  ASSERT_EQ(1, ent->pos);
  ASSERT_EQ(Value::NUM, ent->val.type);
  ASSERT_EQ(112, ent->val.as.num);

  ASSERT_NO_THROW(ent = map.Get("name"));
  ASSERT_EQ("name", ent->key);
  ASSERT_EQ(2, ent->pos);
  ASSERT_EQ(Value::UND, ent->val.type);
}

TEST(Map, ReadConstants) {
  Map<string, Value> map;
  Entry<string, Value>* ent;

  fstream in;
  in.open("dat/constants.dat", fstream::in);

  ASSERT_NO_THROW(map.Load(in));

  ASSERT_NO_THROW(ent = map.Get("1106"));
  ASSERT_EQ("1106", ent->key);
  ASSERT_EQ(0, ent->pos);
  ASSERT_EQ(Value::NUM, ent->val.type);
  ASSERT_EQ(1106, ent->val.as.num);

  ASSERT_NO_THROW(ent = map.Get("911"));
  ASSERT_EQ("911", ent->key);
  ASSERT_EQ(1, ent->pos);
  ASSERT_EQ(Value::NUM, ent->val.type);
  ASSERT_EQ(911, ent->val.as.num);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}