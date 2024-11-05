#pragma once

#include <string>

using Key = std::string;

struct Value {
  unsigned int age = 0;
  unsigned int height = 0;

  friend bool operator==(const Value& a, const Value& b) {
    return a.age == b.age && a.height == b.height;
  }
  friend bool operator!=(const Value& a, const Value& b) {
    return !(a == b);
  }
};


class FlatMap {
public:
  FlatMap();

  ~FlatMap(); 

  FlatMap(const FlatMap& b);
  FlatMap(FlatMap&& b) noexcept;

  void swap(FlatMap& b) noexcept;

  FlatMap& operator=(const FlatMap& b);

  FlatMap& operator=(FlatMap&& b) noexcept;

  // Removes all elements
  void clear();

  // Removes element with key k 
  // returns 1 on success, 0 otherwise
  bool erase(const Key& k);

  // Inserts element with key k and value v
  // returns 1 on success, 0 otherwise
  bool insert(const Key& k, const Value& v);

  // returns 1 if element with key k is in flatmap, 0 otherwise
  [[nodiscard]] bool contains(const Key& k) const;

  // Returns reference to the value of element with key k.
  // If no such element is in flatmap, creates new element with k and default value and returns reference to it
  Value& operator[](const Key& k);

  // Returns reference to the value of element with key k.
  // Throws std::runtime_error if no such element is in flatmap 
  Value& at(const Key& k);
  [[nodiscard]] const Value& at(const Key& k) const;

  [[nodiscard]] size_t size() const {
    return used;
  }
  [[nodiscard]] bool empty() const {
    return !used;
  };

  friend bool operator==(const FlatMap& a, const FlatMap& b);
  friend bool operator!=(const FlatMap& a, const FlatMap& b);

private:
  struct Elem;

  void reallocate(size_t new_allocated, bool copy_contents);
  void insert(const Key& k, const Value& v, size_t idx);

  static const size_t INIT_ALLOCATED = 4;
  static const size_t SCALE_FACTOR = 2;

  Elem* ptr = nullptr;
  size_t used = 0;
  size_t allocated = INIT_ALLOCATED;
};
