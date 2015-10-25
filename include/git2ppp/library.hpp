#ifndef INCLUDE_GIT2PPP_LIBRARY_HPP
#define INCLUDE_GIT2PPP_LIBRARY_HPP

#include "common.hpp"

#include "error_store.hpp"

#include <tuple>

GIT2PPP_NAMESPACE_BEGIN

class GIT2PPP_API Library final: public ErrorStore {
public:
  using VersionType = std::tuple<int, int, int>;

  Library() noexcept;
  Library(const Library &) = delete;
  Library & operator=(const Library &) = delete;
  ~Library();

  static bool IsThreadSupported() noexcept;
  static bool IsHttpsSupported() noexcept;
  static bool IsSshSupported() noexcept;
  // TODO libgit2 options
  static VersionType Version() noexcept;
  static const Library & Get() noexcept;
};

GIT2PPP_NAMESPACE_END

#endif // INCLUDE_GIT2PPP_LIBRARY_HPP
