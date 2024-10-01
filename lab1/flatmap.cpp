#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <cstring>
#include <cstdlib>


typedef std::string Key;

struct Value {
  unsigned int age;
  unsigned int weight;
};

struct Elem {
  Key k;
  Value v;
};

static bool compare_elem(const Elem &a, const Elem &b) {
  return a.k < b.k;
}

class FlatMap
{
public:

  FlatMap() {
    ptr = new Elem[init_allocated];
    used = 0;
    allocated = init_allocated;
  };

  ~FlatMap() {
    delete[] ptr;
  };

  FlatMap(const FlatMap& b) {
    ptr = new Elem[b.allocated];
    used = b.used;
    allocated = b.allocated;

    std::copy(b.ptr, b.ptr + b.used, ptr);
  }

  FlatMap(FlatMap&& b) {
    ptr = b.ptr;
    used = b.used;
    allocated = b.allocated;

    b.ptr = nullptr;

    std::cout << "move" << std::endl;
  }


  // Обменивает значения двух флетмап.
  // Подумайте, зачем нужен этот метод, при наличии стандартной функции
  // std::swap.
  void swap(FlatMap& b) {
    FlatMap tmp = std::move(b);
    b = std::move(*this);
    *this = std::move(tmp);
  }

  FlatMap& operator=(const FlatMap& b) {
    ptr = new Elem[b.allocated];
    used = b.used;
    allocated = b.allocated;

    std::copy(b.ptr, b.ptr + b.used, ptr);

    return *this;
  }

  FlatMap& operator=(FlatMap&& b) {
    ptr = b.ptr;
    used = b.used;
    allocated = b.allocated;

    b.ptr = nullptr;

    return *this;
  }


  // Очищает контейнер.
  void clear() {
    used = 0;
    allocated = init_allocated;
    delete[] ptr;
    ptr = new Elem[init_allocated];
  }
  // Удаляет элемент по заданному ключу.
  bool erase(const Key& k) {
    Elem* pos = std::lower_bound(ptr, ptr+used, (Elem){k, {0, 0}}, compare_elem);

    if (pos->k != k) return 1;
    pos->~Elem();
    
    std::copy(pos + 1, ptr + used, pos);
    --used;
    return 0;
  }

  // Вставка в контейнер. Возвращаемое значение - успешность вставки.

  bool insert(const Key& k, const Value& v) {
    if (expand_if_needed()) return 1;

    Elem* pos = std::lower_bound(ptr, ptr+used, (Elem){k, {0, 0}}, compare_elem);
    std::copy_backward(pos, ptr + used, ptr + used + 1);

    *pos = {k, v};
    ++used;

    std::cout << "k: " << k << std::endl;
    for (size_t i = 0; i < used; ++i) {
      std::cout << (ptr+i)->k << std::endl;
    }

    return 0;
  };

  // Проверка наличия значения по заданному ключу.
  bool contains(const Key& k) const {
    Elem* pos = std::lower_bound(ptr, ptr+used, (Elem){k, {0, 0}}, compare_elem);

    return pos->k == k;
  }

  // Возвращает значение по ключу. Небезопасный метод.
  // В случае отсутствия ключа в контейнере, следует вставить в контейнер
  // значение, созданное конструктором по умолчанию и вернуть ссылку на него. 
  Value& operator[](const Key& k) {
    Elem* pos = std::lower_bound(ptr, ptr+used, (Elem){k, {0, 0}}, compare_elem);

    int idx = std::distance(ptr, pos);
    if (pos->k == k) return pos->v;

    if (insert(k, Value())) {
      //do what? 
    }
    return ptr[idx].v;
  }

  // Возвращает значение по ключу. Бросает исключение при неудаче.
  Value& at(const Key& k) {
    Elem* pos = std::lower_bound(ptr, ptr+used, (Elem){k, {0, 0}}, compare_elem);

    if (pos->k != k) throw std::runtime_error("invalid key: " + k);
    return pos->v;
  }
  const Value& at(const Key& k) const {
    Elem* pos = std::lower_bound(ptr, ptr+used, (Elem){k, {0, 0}}, compare_elem);

    if (pos->k != k) throw std::runtime_error("invalid key: " + k);
    return pos->v;
  }

  size_t size() const {
    return used;
  }
  bool empty() const {
    return !used;
  };

  friend bool operator==(const FlatMap& a, const FlatMap& b);
  friend bool operator!=(const FlatMap& a, const FlatMap& b);

private:
  bool expand_if_needed() {
    if (used < allocated) return 0;

    std::cout << allocated << std::endl;
    std::cout << sizeof(Elem) * allocated * 2 << std::endl;

    Elem* new_ptr = new Elem[allocated *= 2];

    std::copy(ptr, ptr + used, new_ptr);

    delete[] ptr;

    ptr = new_ptr;

    /*Elem* tmp_ptr = (Elem*)std::realloc(ptr, sizeof(Elem) * allocated * 2); segfaults
    if (nullptr == tmp_ptr) return 1;

    ptr = tmp_ptr;
    allocated *= 2;*/

    for (size_t i = 0; i < used; ++i) {
      std::cout << (ptr+i)->k << std::endl;
    }

    return 0;
  };

  static const size_t init_allocated = 4;
  //Key* keys;
  //Value* values;
  Elem* ptr;
  size_t used;
  size_t allocated;
};

int main(){
  std::cout << "sizeof(Key): " << sizeof(Key) << std::endl;
  std::cout << "sizeof(Value): " << sizeof(Value) << std::endl;
  std::cout << "sizeof(Elem): " << sizeof(Elem) << std::endl;
  FlatMap f;
  f.insert("abc", {1, 1});
  f.insert("acc", {1, 1});
  f.insert("adc", {1, 1});
  f.insert("aec", {1, 1});
  f.insert("afc", {1, 1});

  return 0;
}
