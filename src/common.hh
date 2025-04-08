#pragma once
#include <ranges> // stdr
#include <filesystem> // stdf
#include <string> // string
#include <string_view> // strview
#include <array> // Array
#include <vector> // List
#include <stack> // Stack
#include <queue> // Queue
#include <deque> // Deque
#include <forward_list> // LinkedList
#include <list> // DLinkedList
#include <unordered_set> // Set
#include <map> // Map
#include <set> // HashSet
#include <unordered_map> // HashMap
#include <memory> // UniquePtr, SharedPtr, WeakPtr
#include <functional> // Func
#include <optional> // Opt
#include <variant> // Variant
#include <tuple> // Tuple
#include <iostream> // cout, cerr, endl
#include <fstream> // fstream, ifstream, ofstream
#include <sstream> // istrstream, ostrstream, strstream
#include <mutex> // mutex, recursive_mutex, UniqueLock
#include <shared_mutex> // shared_mutex, SharedLock

namespace Parrot {
  namespace stdr = std::ranges;
  namespace stdf = std::filesystem;

  using usize = std::size_t;
  using schar = signed char;
  using uchar = unsigned char;
  using int8 = std::int8_t;
  using int16 = std::int16_t;
  using int32 = std::int32_t;
  using int64 = std::int64_t;
  using uint = unsigned int;
  using uint8 = std::uint8_t;
  using uint16 = std::uint16_t;
  using uint32 = std::uint32_t;
  using uint64 = std::uint64_t;
  using float32 = float;
  using float64 = double;
  using string = std::string;
  using strview = std::string_view;

  template<typename T>
  using Opt = std::optional<T>;
  template<typename T1, typename T2>
  using Pair = std::pair<T1, T2>;
  template<typename... Args>
  using Tuple = std::tuple<Args...>;
  template<typename... Args>
  using Variant = std::variant<Args...>;
  template<class T, class... Args>
  bool holds(const Variant<Args...>& variant);

  template<typename T, usize N>
  using Array = std::array<T, N>;
  template<typename T>
  using List = std::vector<T>;
  template<typename T>
  using Stack = std::stack<T>;
  template<typename T>
  using Queue = std::queue<T>;
  template<typename T>
  using Deque = std::deque<T>;
  template<typename T>
  using LinkedList = std::forward_list<T>;
  template<typename T>
  using DLinkedList = std::list<T>;
  template<typename T>
  using Set = std::set<T>;
  template<typename Key, typename Value>
  using Map = std::map<Key, Value>;
  template<typename T>
  using HashSet = std::unordered_set<T>;
  template<typename Key, typename Value>
  using HashMap = std::unordered_map<Key, Value>;

  template<typename T>
  using UniquePtr = std::unique_ptr<T>;
  template<typename T>
  using SharedPtr = std::shared_ptr<T>;
  template<typename T>
  using WeakPtr = std::weak_ptr<T>;

  template<class T>
  using Func = std::function<T>;

  using std::cout;
  using std::cerr;
  using std::endl;
  using std::istream;
  using std::ostream;
  using std::fstream;
  using std::ifstream;
  using std::ofstream;
  using strstream = std::stringstream;
  using istrstream = std::istringstream;
  using ostrstream = std::ostringstream;

  using std::mutex;
  using std::recursive_mutex;
  using std::shared_mutex;
  template<typename Mutex>
  using UniqueLock = std::unique_lock<Mutex>;
  template<typename Mutex>
  using SharedLock = std::shared_lock<Mutex>;
}
#include "common_impl.hh"