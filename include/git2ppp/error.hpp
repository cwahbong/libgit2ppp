#ifndef INCLUDE_GIT2PPP_ERROR_HPP
#define INCLUDE_GIT2PPP_ERROR_HPP

#include "common.hpp"

#include "interface.hpp"

#include <memory>
#include <string>

GIT2PPP_NAMESPACE_BEGIN

using Git2Error = int;

class GIT2PPP_API Error final {
public:
  struct GIT2PPP_INTERNAL_FWD Member;

  Error(std::unique_ptr<Member> && m) noexcept;

  bool Empty() const noexcept;
  int Class() const noexcept;
  std::string Message() const noexcept;

private:
  std::unique_ptr<Member> m_;
};

class GIT2PPP_API ErrorInterface final: public Interface {
public:
  Error Last() const noexcept;
  void Clear() const noexcept;

private:
  ErrorInterface(const Library & library) noexcept;
  ~ErrorInterface();
};

GIT2PPP_NAMESPACE_END

#endif // INCLUDE_GIT2PPP_ERROR_HPP
