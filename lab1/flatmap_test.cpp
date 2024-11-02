#include "flatmap.h"
#include "googletest/googletest/include/gtest/gtest.h"
#include <stdexcept>
#include <string>


TEST(FlatMapTest, Copy) {
  FlatMap f;
  FlatMap h;

  EXPECT_TRUE(f.insert("Alice", {22, 150}));
  EXPECT_TRUE(f.insert("Bob", {30, 162}));
  EXPECT_TRUE(f.insert("Cody", {25, 171}));
  EXPECT_TRUE(f.insert("Daniel", {25, 171}));
  EXPECT_TRUE(f.insert("Elise", {25, 171}));

  f = *&f;
  FlatMap g = FlatMap(f);
  h = f;

  EXPECT_EQ(g.size(), 5u);
  EXPECT_TRUE(g.contains("Alice"));
  EXPECT_TRUE(g.contains("Bob"));
  EXPECT_TRUE(g.contains("Cody"));
  EXPECT_TRUE(g.contains("Daniel"));
  EXPECT_TRUE(g.contains("Elise"));

  EXPECT_EQ(h.size(), 5u);
  EXPECT_TRUE(h.contains("Alice"));
  EXPECT_TRUE(h.contains("Bob"));
  EXPECT_TRUE(h.contains("Cody"));
  EXPECT_TRUE(h.contains("Daniel"));
  EXPECT_TRUE(h.contains("Elise"));

  f.clear();

  EXPECT_TRUE(g.contains("Bob"));
  EXPECT_TRUE(g.contains("Alice"));
  EXPECT_TRUE(g.contains("Cody"));
  EXPECT_TRUE(g.contains("Daniel"));
  EXPECT_TRUE(g.contains("Elise"));

  FlatMap k;
  h = k;
  EXPECT_TRUE(h.empty());
}

TEST(FlatMapTest, Move) {
  FlatMap f;

  EXPECT_TRUE(f.insert("Alice", {22, 150}));
  EXPECT_TRUE(f.insert("Bob", {30, 162}));
  EXPECT_TRUE(f.insert("Cody", {25, 171}));
  EXPECT_TRUE(f.insert("Daniel", {25, 171}));
  EXPECT_TRUE(f.insert("Elise", {25, 171}));

  f = std::move(*&f);

  EXPECT_TRUE(f.contains("Alice"));
  EXPECT_TRUE(f.contains("Bob"));
  EXPECT_TRUE(f.contains("Cody"));
  EXPECT_TRUE(f.contains("Daniel"));
  EXPECT_TRUE(f.contains("Elise"));

  FlatMap g = std::move(f);

  EXPECT_EQ(g.size(), 5u);
  EXPECT_TRUE(g.contains("Alice"));
  EXPECT_TRUE(g.contains("Bob"));
  EXPECT_TRUE(g.contains("Cody"));
  EXPECT_TRUE(g.contains("Daniel"));
  EXPECT_TRUE(g.contains("Elise"));

  FlatMap h;
  h = std::move(g);

  EXPECT_EQ(h.size(), 5u);
  EXPECT_TRUE(h.contains("Alice"));
  EXPECT_TRUE(h.contains("Bob"));
  EXPECT_TRUE(h.contains("Cody"));
  EXPECT_TRUE(h.contains("Daniel"));
  EXPECT_TRUE(h.contains("Elise"));

  FlatMap k;
  h = std::move(k);

  EXPECT_TRUE(h.empty());
}

TEST(FlatMapTest, Swap) {
  FlatMap f;
  FlatMap g;

  EXPECT_TRUE(f.insert("Alice", {22, 150}));
  EXPECT_TRUE(f.insert("Bob", {30, 162}));
  EXPECT_TRUE(f.insert("Cody", {25, 171}));
  EXPECT_TRUE(f.insert("Daniel", {25, 171}));
  EXPECT_TRUE(f.insert("Elise", {25, 171}));

  EXPECT_TRUE(g.insert("_Alice", {22, 150}));
  EXPECT_TRUE(g.insert("_Bob", {30, 162}));
  EXPECT_TRUE(g.insert("_Cody", {25, 171}));

  EXPECT_EQ(f.size(), 5u);
  EXPECT_EQ(g.size(), 3u);

  f.swap(g);

  EXPECT_EQ(f.size(), 3u);
  EXPECT_EQ(g.size(), 5u);

  EXPECT_TRUE(f.contains("_Alice"));
  EXPECT_TRUE(f.contains("_Bob"));
  EXPECT_TRUE(f.contains("_Cody"));

  EXPECT_TRUE(g.contains("Alice"));
  EXPECT_TRUE(g.contains("Bob"));
  EXPECT_TRUE(g.contains("Cody"));
  EXPECT_TRUE(g.contains("Daniel"));
  EXPECT_TRUE(g.contains("Elise"));
}

TEST(FlatMapTest, Empty) {
  FlatMap f;
  EXPECT_TRUE(f.empty());

  EXPECT_TRUE(f.insert("Alice", {22, 150}));
  EXPECT_TRUE(f.insert("Bob", {30, 162}));
  EXPECT_TRUE(f.insert("Cody", {25, 171}));
  EXPECT_TRUE(f.insert("Daniel", {25, 171}));
  EXPECT_TRUE(f.insert("Elise", {25, 171}));

  EXPECT_FALSE(f.empty());
  f.clear();
  EXPECT_TRUE(f.empty());
}

TEST(FlatMapTest, UseAfterClear) {
  FlatMap f;

  EXPECT_TRUE(f.insert("Alice", {22, 150}));
  EXPECT_TRUE(f.insert("Bob", {30, 162}));
  EXPECT_TRUE(f.insert("Cody", {25, 171}));
  EXPECT_TRUE(f.insert("Daniel", {25, 171}));
  EXPECT_TRUE(f.insert("Elise", {25, 171}));

  f.clear();
  EXPECT_TRUE(f.empty());

  EXPECT_TRUE(f.insert("Alice", {22, 150}));
  EXPECT_TRUE(f.insert("Bob", {30, 162}));
  EXPECT_TRUE(f.insert("Cody", {25, 171}));
  EXPECT_TRUE(f.insert("Daniel", {25, 171}));
  EXPECT_TRUE(f.insert("Elise", {25, 171}));
  EXPECT_TRUE(f.insert("Alice1", {22, 150}));
  EXPECT_TRUE(f.insert("Bob1", {30, 162}));
  EXPECT_TRUE(f.insert("Cody1", {25, 171}));
  EXPECT_TRUE(f.insert("Daniel1", {25, 171}));
  EXPECT_TRUE(f.insert("Elise1", {25, 171}));

  EXPECT_FALSE(f.insert("Cody1", {25, 171}));

  FlatMap g;
  g = f;

  EXPECT_TRUE(g.contains("Alice1"));
  EXPECT_TRUE(g.contains("Bob1"));
  EXPECT_TRUE(g.contains("Cody1"));
  EXPECT_TRUE(g.contains("Daniel1"));
  EXPECT_TRUE(g.contains("Elise1"));
}

TEST(FlatMapTest, InsertAndErase) {
  FlatMap f;

  EXPECT_TRUE(f.insert("Bob", {30, 162}));
  EXPECT_TRUE(f.contains("Bob"));
  EXPECT_FALSE(f.contains("Alice"));
  EXPECT_FALSE(f.erase("Alice"));
  EXPECT_FALSE(f.empty());
  EXPECT_EQ(f.size(), 1u);


  EXPECT_TRUE(f.insert("Alice", {22, 150}));
  EXPECT_TRUE(f.contains("Alice"));
  EXPECT_EQ(f.size(), 2u);
  EXPECT_TRUE(f.erase("Alice"));
  EXPECT_FALSE(f.contains("Alice"));

  EXPECT_TRUE(f.insert("Cody", {25, 171}));
  EXPECT_TRUE(f.contains("Cody"));
  EXPECT_EQ(f.size(), 2u);
  EXPECT_TRUE(f.erase("Cody"));
  EXPECT_FALSE(f.contains("Cody"));

  EXPECT_TRUE(f.erase("Bob"));
  EXPECT_FALSE(f.contains("Bob"));
  EXPECT_FALSE(f.erase("Bob"));
  EXPECT_TRUE(f.empty());

  EXPECT_TRUE(f.insert("Bob", {30, 162}));
  EXPECT_TRUE(f.insert("Cody", {25, 171}));
  EXPECT_TRUE(f.insert("Daniel", {25, 171}));
  EXPECT_TRUE(f.insert("Elise", {25, 171}));
  EXPECT_TRUE(f.insert("Bob1", {30, 162}));
  EXPECT_TRUE(f.insert("Cody1", {25, 171}));
  EXPECT_TRUE(f.insert("Daniel1", {25, 171}));
  EXPECT_TRUE(f.insert("Elise1", {25, 171}));
  EXPECT_EQ(f.size(), 8u);

  EXPECT_TRUE(f.insert("Alice", {22, 150}));
  EXPECT_TRUE(f.contains("Alice"));
  EXPECT_EQ(f.size(), 9u);
  EXPECT_TRUE(f.erase("Alice"));
  EXPECT_FALSE(f.contains("Alice"));
  EXPECT_EQ(f.size(), 8u);

  EXPECT_TRUE(f.insert("Frank", {25, 171}));
  EXPECT_TRUE(f.contains("Frank"));
  EXPECT_EQ(f.size(), 9u);
  EXPECT_TRUE(f.erase("Frank"));
  EXPECT_FALSE(f.contains("Frank"));
}

TEST(FlatMapTest, LargeInsertAndErase) {
  FlatMap f;
  EXPECT_TRUE(f.insert("Alice", {22, 150}));
  EXPECT_TRUE(f.insert("Bob", {30, 162}));
  EXPECT_TRUE(f.insert("Cody", {25, 171}));
  EXPECT_TRUE(f.insert("Daniel", {25, 171}));
  EXPECT_TRUE(f.insert("Elise", {25, 171}));

  EXPECT_FALSE(f.insert("Elise", {25, 171}));
  EXPECT_EQ(f.size(), 5u);

  for (int i = 0; i < 128; ++i) {
    EXPECT_TRUE(f.insert(std::string("Alice") + std::to_string(i), {22, 150}));
  }
  EXPECT_EQ(f.size(), 128 + 5u);
  EXPECT_TRUE(f.contains("Alice127"));

  for (int i = 0; i < 128; ++i) {
    EXPECT_TRUE(f.erase(std::string("Alice") + std::to_string(i)));
  }
  EXPECT_EQ(f.size(), 5u);

  EXPECT_TRUE(f.contains("Bob"));
  EXPECT_TRUE(f.erase("Bob"));
  EXPECT_FALSE(f.contains("Bob"));
}

TEST(FlatMapTest, Subscript) {
  FlatMap f;

  EXPECT_TRUE(f.insert("Alice", {22, 150}));
  EXPECT_TRUE(f.insert("Bob", {30, 162}));
  EXPECT_TRUE(f.insert("Cody", {26, 171}));
  EXPECT_TRUE(f.insert("Elise", {28, 173}));

  EXPECT_EQ(f["Bob"].age, 30u);
  EXPECT_EQ(f["Bob"].height, 162u);

  f["Bob"] = Value{100, 200};
  EXPECT_EQ(f["Bob"].age, 100u);
  EXPECT_EQ(f["Bob"].height, 200u);

  EXPECT_EQ(f["Elise"].age, 28u);
  EXPECT_EQ(f["Elise"].height, 173u);
  EXPECT_TRUE(f["Alice1"] == Value());
  EXPECT_TRUE(f["Alice2"] == Value());
}

TEST(FlatMapTest, At) {
  FlatMap f;

  EXPECT_TRUE(f.insert("Alice", {22, 150}));
  EXPECT_TRUE(f.insert("Bob", {30, 162}));
  EXPECT_TRUE(f.insert("Cody", {26, 171}));
  EXPECT_TRUE(f.insert("Daniel", {27, 172}));
  EXPECT_TRUE(f.insert("Elise", {28, 173}));

  EXPECT_EQ(f.at("Alice").age, 22u);
  EXPECT_EQ(f.at("Alice").height, 150u);
  EXPECT_EQ(f.at("Elise").age, 28u);
  EXPECT_EQ(f.at("Elise").height, 173u);
  EXPECT_THROW(f.at("Alice1"), std::runtime_error);

  const FlatMap g = f;
  EXPECT_EQ(g.at("Alice").age, 22u);
  EXPECT_EQ(g.at("Alice").height, 150u);
  EXPECT_EQ(g.at("Elise").age, 28u);
  EXPECT_EQ(g.at("Elise").height, 173u);
  EXPECT_THROW((void)g.at("Alice1"), std::runtime_error);
}

TEST(FlatMapTest, Equals) {
  FlatMap f;
  FlatMap g;
  EXPECT_TRUE(f == g);

  EXPECT_TRUE(f.insert("Alice", {22, 150}));
  EXPECT_TRUE(f.insert("Bob", {30, 162}));
  EXPECT_TRUE(f.insert("Cody", {26, 171}));
  EXPECT_TRUE(f.insert("Daniel", {27, 172}));
  EXPECT_TRUE(f.insert("Elise", {28, 173}));

  EXPECT_TRUE(g.insert("Alice", {22, 150}));
  EXPECT_TRUE(g.insert("Bob", {30, 162}));
  EXPECT_TRUE(g.insert("Cody", {26, 171}));
  EXPECT_TRUE(g.insert("Daniel", {27, 172}));
  EXPECT_TRUE(g.insert("Elise", {28, 173}));

  EXPECT_TRUE(f == g);

  for (unsigned int i = 0; i < 128; ++i) {
    EXPECT_TRUE(f.insert(std::string("Alice") + std::to_string(i), {22, i}));
  }

  EXPECT_TRUE(f != g);

  for (unsigned int i = 0; i < 128; ++i) {
    EXPECT_TRUE(f.erase(std::string("Alice") + std::to_string(i)));
  }

  EXPECT_TRUE(f == g);

  FlatMap h = f;
  EXPECT_TRUE(f == h);
  EXPECT_TRUE(f == f);

  EXPECT_TRUE(g.insert("Alice1", {22, 150}));
  EXPECT_TRUE(f != g);
  EXPECT_TRUE(g.erase("Alice1"));
  EXPECT_TRUE(f == g);
  EXPECT_TRUE(g.erase("Elise"));
  EXPECT_TRUE(g.insert("Elise", {0, 173}));
  EXPECT_TRUE(f != g);
  EXPECT_TRUE(g.erase("Elise"));
  EXPECT_TRUE(g.insert("Elise", {28, 0}));
  EXPECT_TRUE(f != g);
  EXPECT_TRUE(g.erase("Elise"));
  EXPECT_TRUE(g.insert("Elise", {0, 0}));
  EXPECT_TRUE(f != g);

  FlatMap k;

  EXPECT_TRUE(k.insert("Alice", {22, 150}));
  EXPECT_TRUE(k.insert("Bob", {30, 162}));
  EXPECT_TRUE(k.insert("Cody", {26, 171}));
  EXPECT_TRUE(k.insert("Daniel", {27, 172}));
  EXPECT_TRUE(k.insert("Elise", {20, 173}));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
