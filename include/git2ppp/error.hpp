#ifndef INCLUDE_GIT2PPP_ERROR_HPP
#define INCLUDE_GIT2PPP_ERROR_HPP

#include "common.hpp"

#include "interface.hpp"

#include <memory>
#include <string>
#include <tuple>

GIT2PPP_NAMESPACE_BEGIN

using Git2Error = int;

template <class ValueType>
class GIT2PPP_API Returned final: private std::tuple<Git2Error, ValueType>{
public:
  static_assert(!std::is_reference<ValueType>::value, "ValueType must not be reference.");

  using std::tuple<Git2Error, ValueType>::tuple;

  Git2Error Error() const noexcept {
    return std::get<0>(*this);
  }

  const ValueType & Ref() const noexcept {
    return std::get<1>(*this);
  }

  ValueType && Take() noexcept {
    return std::get<1>(std::move(*this));
  }
};

template <>
class GIT2PPP_API Returned<void> final: private std::tuple<Git2Error> {
public:
  using std::tuple<Git2Error>::tuple;

  Returned(Git2Error error): std::tuple<Git2Error>(error) {}

  Git2Error Error() const noexcept {
    return std::get<0>(*this);
  }

  void Ref() const noexcept {}
  void Take() noexcept {}
};

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
