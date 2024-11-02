#include <algorithm>
#include <cstddef>
#include <iterator>
#include <stdexcept>

#include "flatmap.h"

namespace {
  template<typename T>
  T* lower_bound(T* first, T* last, const T& value) {
    size_t length = last - first;
    while (length > 0) {
      const size_t rem = length % 2;
      length /= 2;
      if (first[length] < value) {
        first += length + rem;
      }
    }
    return first;
  }
} //namespace

struct FlatMap::Elem {
  Key k;
  Value v;

  auto operator<(const Elem& b) const {
    return k < b.k;
  }
  friend bool operator==(const Elem& a, const Elem& b) {
    return a.k == b.k && a.v == b.v;
  }
};

FlatMap::FlatMap() : ptr(new Elem[INIT_ALLOCATED]),
                     allocated(INIT_ALLOCATED) {}

FlatMap::~FlatMap() {
  delete[] ptr;
  ptr = nullptr;
}

FlatMap::FlatMap(const FlatMap& b) : ptr(new Elem[b.allocated]),
                                     used(b.used),
                                     allocated(b.allocated) {
  std::copy(b.ptr, b.ptr + b.used, ptr);
}

FlatMap::FlatMap(FlatMap&& b) noexcept : ptr(b.ptr),
                                used(b.used),
                                allocated(b.allocated) {
  b.ptr = nullptr;
}

void FlatMap::swap(FlatMap& b) noexcept {
  std::swap(*this, b);
}

FlatMap& FlatMap::operator=(const FlatMap& b) {
  if (this == &b) {
    return *this;
  }

  reallocate(b.allocated, false);
  used = b.used;
  std::copy(b.ptr, b.ptr + b.used, ptr);

  return *this;
}

FlatMap& FlatMap::operator=(FlatMap&& b) noexcept {
  if (this == &b) {
    return *this; 
  }

  delete[] ptr;
  ptr = b.ptr;
  used = b.used;
  allocated = b.allocated;

  b.ptr = nullptr;
  return *this;
}

void FlatMap::clear() {
  used = 0;
  reallocate(INIT_ALLOCATED, false);
}

bool FlatMap::erase(const Key& k) {
  Elem* pos = lower_bound(ptr, ptr + used, Elem{k, Value()});
  if (pos == ptr + used || pos->k != k) {
    return false; 
  }
  
  std::copy(pos + 1, ptr + used, pos);
  --used;
  
  if (used < allocated / (SCALE_FACTOR * SCALE_FACTOR) && INIT_ALLOCATED < allocated) {
    reallocate(allocated / SCALE_FACTOR, true);
  }
  return true;
}

bool FlatMap::insert(const Key& k, const Value& v) {
  Elem* pos = lower_bound(ptr, ptr + used, Elem{k, Value()});
  const size_t idx = std::distance(ptr, pos);

  if (idx != used && pos->k == k) {
    return false; 
  }
  if (used >= allocated) {
    reallocate(allocated * SCALE_FACTOR, true);
  }

  std::copy_backward(ptr + idx, ptr + used, ptr + used + 1);
  ptr[idx] = {k, v};
  ++used;
  return true;
}

bool FlatMap::contains(const Key& k) const {
  Elem* pos = lower_bound(ptr, ptr + used, Elem{k, Value()});
  return pos != ptr + used && pos->k == k;
}

Value& FlatMap::operator[](const Key& k) {
  Elem* pos = lower_bound(ptr, ptr + used, Elem{k, Value()});

  const size_t idx = std::distance(ptr, pos);
  if (idx != used && pos->k == k) {
    return pos->v;
  }

  insert(k, Value(), idx);
  return ptr[idx].v;
}

const Value& FlatMap::at(const Key& k) const {
  Elem* pos = lower_bound(ptr, ptr + used, Elem{k, Value()});

  if (pos == ptr + used || pos->k != k) {
    throw std::runtime_error("invalid key: " + k);
  }
  return pos->v;
}

Value& FlatMap::at(const Key& k) {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
  return const_cast<Value &>(const_cast<const FlatMap&>(*this).at(k));
}

bool operator==(const FlatMap& a, const FlatMap& b) {
  return &a == &b ||
         (a.used == b.used &&
          std::equal(a.ptr, a.ptr + a.used, b.ptr));
}

bool operator!=(const FlatMap& a, const FlatMap& b) {
  return !(a == b);
}

void FlatMap::reallocate(size_t new_allocated, bool copy_contents) {
  Elem* new_ptr = new Elem[new_allocated];

  if (copy_contents) {
    //const size_t size = used < new_allocated ? used : new_allocated;
    //std::copy(ptr, ptr + size, new_ptr);
    std::copy(ptr, ptr + used, new_ptr);
  }

  delete[] ptr;
  ptr = new_ptr;
  allocated = new_allocated;
}

void FlatMap::insert(const Key& k, const Value& v, size_t idx) {
  if (used >= allocated) {
    reallocate(allocated * SCALE_FACTOR, true);
  }

  std::copy_backward(ptr + idx, ptr + used, ptr + used + 1);

  ptr[idx] = {k, v};
  ++used;
}

