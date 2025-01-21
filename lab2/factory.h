#pragma once

#include <algorithm>
#include <concepts>
#include <functional>
#include <iterator>
#include <map>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

template <class Key, class Func>
class Factory {
 public:
  static void RegisterCreator(const Key key, Func creator) {
    GetInstance()._map.insert(std::pair(key, creator));
  }

  template <class... ParamTypes>
    requires std::invocable<Func, ParamTypes&&...> &&
             std::is_pointer_v<std::invoke_result_t<Func, ParamTypes&&...>>
  static auto Create(Key key, ParamTypes&&... params) {
    using Type = std::unique_ptr<std::remove_pointer_t<std::invoke_result_t<Func, ParamTypes&&...>>>;
    return Type(
        GetInstance()._map.at(key)(
            std::forward<ParamTypes>(params)...));  // TODO: () or {}
  }

  static std::vector<Key> GetKeys() {
    std::vector<Key> keys;
    std::transform(GetInstance()._map.begin(), GetInstance()._map.end(),
                   std::back_inserter(keys),
                   [](auto& pair) { return pair.first; });
    return keys;
  }

 private:
  Factory() = default;

  static Factory& GetInstance() {
    static Factory f;
    return f;
  }

  static Factory f;
  std::map<std::string, Func> _map;
};

template <class Key, class Base, std::derived_from<Base> T, class... ParamTypes>
class Registrator {
 public:
  template <class... ConstParamTypes>
  Registrator(Key key, ConstParamTypes... const_params) {
    Factory<Key, std::function<Base*(ParamTypes...)>>::RegisterCreator(
        key, [const_params...](ParamTypes... params) {
          return new T{const_params..., params...};  // TODO: () or {}
        });
  }
};
