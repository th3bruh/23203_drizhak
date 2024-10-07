#include "flatmap.h"
#include "googletest/googletest/include/gtest/gtest.h"
#include <stdexcept>
#include <string>


TEST(FlatMapTest, Copy) {
  FlatMap f;
  FlatMap h;

  EXPECT_FALSE(f.insert("Alice", {22, 150}));
  EXPECT_FALSE(f.insert("Bob", {30, 162}));
  EXPECT_FALSE(f.insert("Cody", {25, 171}));
  EXPECT_FALSE(f.insert("Daniel", {25, 171}));
  EXPECT_FALSE(f.insert("Elise", {25, 171}));

  FlatMap g = FlatMap(f);
  h = f;

  EXPECT_TRUE(g.size() == 5);
  EXPECT_TRUE(g.contains("Alice"));
  EXPECT_TRUE(g.contains("Bob"));
  EXPECT_TRUE(g.contains("Cody"));
  EXPECT_TRUE(g.contains("Daniel"));
  EXPECT_TRUE(g.contains("Elise"));

  EXPECT_TRUE(h.size() == 5);
  EXPECT_TRUE(h.contains("Alice"));
  EXPECT_TRUE(h.contains("Bob"));
  EXPECT_TRUE(h.contains("Cody"));
  EXPECT_TRUE(h.contains("Daniel"));
  EXPECT_TRUE(g.contains("Elise"));

  f.clear();

  EXPECT_TRUE(g.contains("Bob"));
  EXPECT_TRUE(g.contains("Alice"));
  EXPECT_TRUE(g.contains("Cody"));
  EXPECT_TRUE(g.contains("Daniel"));
  EXPECT_TRUE(g.contains("Elise"));
}

TEST(FlatMapTest, Move) {
  FlatMap f;

  EXPECT_FALSE(f.insert("Alice", {22, 150}));
  EXPECT_FALSE(f.insert("Bob", {30, 162}));
  EXPECT_FALSE(f.insert("Cody", {25, 171}));
  EXPECT_FALSE(f.insert("Daniel", {25, 171}));
  EXPECT_FALSE(f.insert("Elise", {25, 171}));

  f = std::move(*&f);

  EXPECT_TRUE(f.contains("Alice"));
  EXPECT_TRUE(f.contains("Bob"));
  EXPECT_TRUE(f.contains("Cody"));
  EXPECT_TRUE(f.contains("Daniel"));
  EXPECT_TRUE(f.contains("Elise"));

  FlatMap g = std::move(f);

  EXPECT_TRUE(g.size() == 5);
  EXPECT_TRUE(g.contains("Alice"));
  EXPECT_TRUE(g.contains("Bob"));
  EXPECT_TRUE(g.contains("Cody"));
  EXPECT_TRUE(g.contains("Daniel"));
  EXPECT_TRUE(g.contains("Elise"));

  FlatMap h;
  h = std::move(g);

  EXPECT_TRUE(h.size() == 5);
  EXPECT_TRUE(h.contains("Alice"));
  EXPECT_TRUE(h.contains("Bob"));
  EXPECT_TRUE(h.contains("Cody"));
  EXPECT_TRUE(h.contains("Daniel"));
  EXPECT_TRUE(h.contains("Elise"));
}

TEST(FlatMapTest, Swap) {
  FlatMap f;
  FlatMap g;

  EXPECT_FALSE(f.insert("Alice", {22, 150}));
  EXPECT_FALSE(f.insert("Bob", {30, 162}));
  EXPECT_FALSE(f.insert("Cody", {25, 171}));
  EXPECT_FALSE(f.insert("Daniel", {25, 171}));
  EXPECT_FALSE(f.insert("Elise", {25, 171}));

  EXPECT_FALSE(g.insert("_Alice", {22, 150}));
  EXPECT_FALSE(g.insert("_Bob", {30, 162}));
  EXPECT_FALSE(g.insert("_Cody", {25, 171}));

  EXPECT_TRUE(f.size() == 5);
  EXPECT_TRUE(g.size() == 3);

  f.swap(g);

  EXPECT_TRUE(f.size() == 3);
  EXPECT_TRUE(g.size() == 5);

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

  EXPECT_FALSE(f.insert("Alice", {22, 150}));
  EXPECT_FALSE(f.insert("Bob", {30, 162}));
  EXPECT_FALSE(f.insert("Cody", {25, 171}));
  EXPECT_FALSE(f.insert("Daniel", {25, 171}));
  EXPECT_FALSE(f.insert("Elise", {25, 171}));

  EXPECT_FALSE(f.empty());
  f.clear();
  EXPECT_TRUE(f.empty());
}

TEST(FlatMapTest, InsertAndErase) {
  FlatMap f;

  EXPECT_FALSE(f.insert("Bob", {30, 162}));
  EXPECT_TRUE(f.contains("Bob"));
  EXPECT_FALSE(f.contains("Alice"));
  EXPECT_FALSE(f.empty());
  EXPECT_EQ(f.size(), 1);


  EXPECT_FALSE(f.insert("Alice", {22, 150}));
  EXPECT_TRUE(f.contains("Alice"));
  EXPECT_EQ(f.size(), 2);
  EXPECT_FALSE(f.erase("Alice"));
  EXPECT_FALSE(f.contains("Alice"));

  EXPECT_FALSE(f.insert("Cody", {25, 171}));
  EXPECT_TRUE(f.contains("Cody"));
  EXPECT_EQ(f.size(), 2);
  EXPECT_FALSE(f.erase("Cody"));
  EXPECT_FALSE(f.contains("Cody"));

  EXPECT_FALSE(f.erase("Bob"));
  EXPECT_FALSE(f.contains("Bob"));
  EXPECT_TRUE(f.erase("Bob"));
  EXPECT_TRUE(f.empty());

  EXPECT_FALSE(f.insert("Bob", {30, 162}));
  EXPECT_FALSE(f.insert("Cody", {25, 171}));
  EXPECT_FALSE(f.insert("Daniel", {25, 171}));
  EXPECT_FALSE(f.insert("Elise", {25, 171}));
  EXPECT_FALSE(f.insert("Bob1", {30, 162}));
  EXPECT_FALSE(f.insert("Cody1", {25, 171}));
  EXPECT_FALSE(f.insert("Daniel1", {25, 171}));
  EXPECT_FALSE(f.insert("Elise1", {25, 171}));
  EXPECT_EQ(f.size(), 8);

  EXPECT_FALSE(f.insert("Alice", {22, 150}));
  EXPECT_TRUE(f.contains("Alice"));
  EXPECT_EQ(f.size(), 9);
  EXPECT_FALSE(f.erase("Alice"));
  EXPECT_FALSE(f.contains("Alice"));
  EXPECT_EQ(f.size(), 8);

  EXPECT_FALSE(f.insert("Frank", {25, 171}));
  EXPECT_TRUE(f.contains("Frank"));
  EXPECT_EQ(f.size(), 9);
  EXPECT_FALSE(f.erase("Frank"));
  EXPECT_FALSE(f.contains("Frank"));
}

TEST(FlatMapTest, LargeInsertAndErase) {
  FlatMap f;
  EXPECT_FALSE(f.insert("Alice", {22, 150}));
  EXPECT_FALSE(f.insert("Bob", {30, 162}));
  EXPECT_FALSE(f.insert("Cody", {25, 171}));
  EXPECT_FALSE(f.insert("Daniel", {25, 171}));
  EXPECT_FALSE(f.insert("Elise", {25, 171}));

  EXPECT_TRUE(f.insert("Elise", {25, 171}));
  EXPECT_EQ(f.size(), 5);

  for (int i = 0; i < 128; ++i) {
    EXPECT_FALSE(f.insert(std::string("Alice") + std::to_string(i), {22, 150}));
  }
  EXPECT_TRUE(f.size() == 128 + 5);
  EXPECT_TRUE(f.contains("Alice127"));

  for (int i = 0; i < 128; ++i) {
    EXPECT_FALSE(f.erase(std::string("Alice") + std::to_string(i)));
  }
  EXPECT_TRUE(f.size() == 5);

  EXPECT_TRUE(f.contains("Bob"));
  EXPECT_FALSE(f.erase("Bob"));
  EXPECT_FALSE(f.contains("Bob"));
}

TEST(FlatMapTest, Subscript) {
  FlatMap f;

  EXPECT_FALSE(f.insert("Alice", {22, 150}));
  EXPECT_FALSE(f.insert("Bob", {30, 162}));
  EXPECT_FALSE(f.insert("Cody", {26, 171}));
  EXPECT_FALSE(f.insert("Daniel", {27, 172}));
  EXPECT_FALSE(f.insert("Elise", {28, 173}));

  EXPECT_EQ(f["Bob"].age, 30);
  EXPECT_EQ(f["Bob"].height, 162);
  EXPECT_EQ(f["Elise"].age, 28);
  EXPECT_EQ(f["Elise"].height, 173);
  EXPECT_EQ(f["Alice1"].age, 0);
  EXPECT_EQ(f["Alice2"].height, 0);
}

TEST(FlatMapTest, At) {
  FlatMap f;

  EXPECT_FALSE(f.insert("Alice", {22, 150}));
  EXPECT_FALSE(f.insert("Bob", {30, 162}));
  EXPECT_FALSE(f.insert("Cody", {26, 171}));
  EXPECT_FALSE(f.insert("Daniel", {27, 172}));
  EXPECT_FALSE(f.insert("Elise", {28, 173}));

  EXPECT_EQ(f.at("Alice").age, 22);
  EXPECT_EQ(f.at("Alice").height, 150);
  EXPECT_EQ(f.at("Elise").age, 28);
  EXPECT_EQ(f.at("Elise").height, 173);
  EXPECT_THROW(f.at("Alice1"), std::runtime_error);

  const FlatMap g = f;
  EXPECT_EQ(g.at("Alice").age, 22);
  EXPECT_EQ(g.at("Alice").height, 150);
  EXPECT_EQ(g.at("Elise").age, 28);
  EXPECT_EQ(g.at("Elise").height, 173);
  EXPECT_THROW(g.at("Alice1"), std::runtime_error);
}

TEST(FlatMapTest, Equals) {
  FlatMap f;
  FlatMap g;
  EXPECT_TRUE(f == g);

  EXPECT_FALSE(f.insert("Alice", {22, 150}));
  EXPECT_FALSE(f.insert("Bob", {30, 162}));
  EXPECT_FALSE(f.insert("Cody", {26, 171}));
  EXPECT_FALSE(f.insert("Daniel", {27, 172}));
  EXPECT_FALSE(f.insert("Elise", {28, 173}));
  FlatMap h = f;
  EXPECT_TRUE(f == h);

  EXPECT_FALSE(g.insert("Alice", {22, 150}));
  EXPECT_FALSE(g.insert("Bob", {30, 162}));
  EXPECT_FALSE(g.insert("Cody", {26, 171}));
  EXPECT_FALSE(g.insert("Daniel", {27, 172}));
  EXPECT_FALSE(g.insert("Elise", {28, 173}));

  EXPECT_TRUE(f == g);
  EXPECT_FALSE(g.insert("Alice1", {22, 150}));
  EXPECT_TRUE(f != g);
  EXPECT_FALSE(g.erase("Alice1"));
  EXPECT_TRUE(f == g);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
