#pragma once

#include <concepts>
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <iostream>

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
    try {
    return std::unique_ptr<
        std::remove_pointer_t<std::invoke_result_t<Func, ParamTypes&&...>>>(
        GetInstance()._map.at(key)(std::forward<ParamTypes>(params)...));  // TODO: () or {}
    } catch(std::out_of_range error) {
      std::cout << key << std::endl;
      throw;
    }
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
        key, [const_params...](ParamTypes... params) {  // TODO: lambda capture
          return new T{const_params..., params...};     // TODO: () or {}
        });
  }
};
