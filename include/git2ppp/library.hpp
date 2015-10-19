#ifndef INCLUDE_GIT2PPP_LIBRARY_HPP
#define INCLUDE_GIT2PPP_LIBRARY_HPP

#include "common.hpp"

#include <tuple>

GIT2PPP_NAMESPACE_BEGIN

class GIT2PPP_API Library final {
public:
  using VersionType = std::tuple<int, int, int>;

  Library();
  Library(const Library &) = delete;
  Library & operator=(const Library &) = delete;
  ~Library();

  static bool IsThreadSupported();
  static bool IsHttpsSupported();
  static bool IsSshSupported();
  // TODO libgit2 options
  static VersionType Version();
  static const Library & Get();
};

GIT2PPP_NAMESPACE_END

#endif // INCLUDE_GIT2PPP_LIBRARY_HPP
