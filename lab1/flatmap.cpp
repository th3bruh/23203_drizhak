#include <algorithm>
#include <stdexcept>
#include <string>

#include "flatmap.h"

struct FlatMap::Elem {
  Key k;
  Value v;

  Elem() = default;

  Elem(Key key, Value value) : k(key), v(value){}

  auto operator<=>(const Elem& b) const {
    return k <=> b.k;
  }
  friend bool operator==(const Elem& a, const Elem& b) {
    return a.k == b.k && a.v == b.v;
  }
};

FlatMap::FlatMap() : used(0),
                     allocated(INIT_ALLOCATED) {
  ptr = new Elem[INIT_ALLOCATED];
}

FlatMap::~FlatMap() {
  delete[] ptr;
  ptr = nullptr;
}

FlatMap::FlatMap(const FlatMap& b) : used(b.used),
                                     allocated(b.allocated) {
  ptr = new Elem[b.allocated];
  std::copy(b.ptr, b.ptr + b.used, ptr);
}

FlatMap::FlatMap(FlatMap&& b) : used(b.used),
                                allocated(b.allocated) {
  std::swap(ptr, b.ptr);
}

void FlatMap::swap(FlatMap& b) {
  std::swap(*this, b);
}

FlatMap& FlatMap::operator=(const FlatMap& b) {
  if (this == &b) return *this;

  reallocate(b.allocated);
  used = b.used;
  std::copy(b.ptr, b.ptr + b.used, ptr);

  return *this;
}

FlatMap& FlatMap::operator=(FlatMap&& b) {
  if (this == &b) return *this;

  delete[] ptr;
  ptr = b.ptr;
  used = b.used;
  allocated = b.allocated;

  b.ptr = nullptr;
  return *this;
}

void FlatMap::clear() {
  used = 0;
  reallocate(INIT_ALLOCATED);
}

bool FlatMap::erase(const Key& k) {
  Elem* pos = std::lower_bound(ptr, ptr+used, Elem(k, Value()));
  if (pos == ptr + used || pos->k != k) return 1;
  
  std::copy(pos + 1, ptr + used, pos);
  --used;
  
  if (used < allocated / (SCALE_FACTOR * SCALE_FACTOR) && INIT_ALLOCATED < allocated) reallocate(allocated / SCALE_FACTOR);
  return 0;
}

bool FlatMap::insert(const Key& k, const Value& v) {
  Elem* pos = std::lower_bound(ptr, ptr+used, Elem(k, Value()));
  const size_t idx = std::distance(ptr, pos);

  if (idx != used && pos->k == k) return 1;
  if (used >= allocated) reallocate(allocated * SCALE_FACTOR);

  std::copy_backward(ptr + idx, ptr + used, ptr + used + 1);
  ptr[idx] = {k, v};
  ++used;
  return 0;
};

bool FlatMap::contains(const Key& k) const {
  Elem* pos = std::lower_bound(ptr, ptr + used, Elem(k, Value()));
  return pos != ptr + used && pos->k == k;
}

Value& FlatMap::operator[](const Key& k) {
  Elem* pos = std::lower_bound(ptr, ptr+used, Elem(k, Value()));

  const size_t idx = std::distance(ptr, pos);
  if (idx != used && pos->k == k) return pos->v;

  insert(k, Value(), idx);
  return ptr[idx].v;
}

Value& FlatMap::at(const Key& k) {
  Elem* pos = std::lower_bound(ptr, ptr+used, Elem(k, Value()));

  if (pos == ptr + used || pos->k != k) throw std::runtime_error("invalid key: " + k);
  return pos->v;
}

const Value& FlatMap::at(const Key& k) const {
  const Elem* pos = std::lower_bound(ptr, ptr+used, Elem(k, Value()));

  if (pos == ptr + used || pos->k != k) throw std::runtime_error("invalid key: " + k);
  return pos->v;
}

bool operator==(const FlatMap& a, const FlatMap& b) {
  return a.used == b.used && std::equal(a.ptr, a.ptr + a.used, b.ptr);
}

bool operator!=(const FlatMap& a, const FlatMap& b) {
  return !(a == b);
}

void FlatMap::reallocate(size_t new_allocated) {
  Elem* new_ptr = new Elem[new_allocated];

  std::copy(ptr, ptr + used, new_ptr);

  delete[] ptr;
  ptr = new_ptr;
  allocated = new_allocated;
};

void FlatMap::insert(const Key& k, const Value& v, size_t idx) {
  if (used >= allocated) reallocate(allocated * SCALE_FACTOR);

  std::copy_backward(ptr + idx, ptr + used, ptr + used + 1);

  ptr[idx] = {k, v};
  ++used;
};
