#ifndef INCLUDE_GIT2PPP_LIBRARY_HPP
#define INCLUDE_GIT2PPP_LIBRARY_HPP

#include "common.hpp"

#include <tuple>

GIT2PPP_NAMESPACE_BEGIN

class GIT2PPP_API Library final {
public:
  using VersionType = std::tuple<int, int, int>;

  Library() noexcept;
  Library(const Library &) = delete;
  Library & operator=(const Library &) = delete;
  ~Library();

  bool IsValid() const noexcept;

  static bool IsThreadSupported() noexcept;
  static bool IsHttpsSupported() noexcept;
  static bool IsSshSupported() noexcept;
  // TODO libgit2 options
  static VersionType Version() noexcept;
  static const Library & Get() noexcept;

private:
  bool mValid;
};

GIT2PPP_NAMESPACE_END

#endif // INCLUDE_GIT2PPP_LIBRARY_HPP
