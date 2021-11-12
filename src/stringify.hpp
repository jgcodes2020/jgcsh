#ifndef _STRINGIFY_HPP_
#define _STRINGIFY_HPP_
#include <iostream>
#include <iterator>
#include <string>
#include <type_traits>
#include <vector>

namespace details {
  template <typename...>
  using void_t = void;

  template <typename T, typename = void>
  struct has_container_types : std::false_type {};

  template <typename T>
  struct has_container_types<
    T, void_t<typename T::const_iterator, typename T::size_type>>
      : std::true_type {};

  template <typename T, typename = void>
  struct has_begin_end : std::false_type {};

  template <typename T>
  struct has_begin_end<
    T,
    std::enable_if_t<
      std::is_same_v<
        decltype(std::declval<const T>().begin()),
        typename T::const_iterator> &&
      std::is_same_v<
        decltype(std::declval<const T>().end()), typename T::const_iterator>>>
      : std::true_type {};

  template <typename T, typename = void>
  struct has_size : std::false_type {};

  template <typename T>
  struct has_size<
    T,
    std::enable_if_t<std::is_same_v<
      decltype(std::declval<const T>().size()), typename T::size_type>>>
      : std::true_type {};

  template <typename T>
  constexpr bool has_container_types_v = has_container_types<T>::value;

  template <typename T>
  constexpr bool has_begin_end_v = has_begin_end<T>::value;

  template <typename T>
  constexpr bool has_size_v = has_size<T>::value;

  template <typename T>
  constexpr bool is_container_v = has_container_types_v<T>&& has_begin_end_v<T>;

  template <typename T>
  struct is_string : std::false_type {};

  template <typename CharT, typename Traits>
  struct is_string<std::basic_string<CharT, Traits>> : std::true_type {};
  
  template<typename T>
  constexpr bool is_string_v = is_string<T>::value;

}  // namespace details

// Generic container stringification
template <typename T, typename = std::enable_if_t<details::is_container_v<T> && !details::is_string_v<T>>>
std::ostream& operator<<(std::ostream& out, const T& cont) {
  out << "[";
  for (auto it = cont.begin(); it != cont.end(); it++) {
    if (it != cont.begin())
      out << ", ";
    out << *it;
  }
  return out << "]";
  
}
#endif