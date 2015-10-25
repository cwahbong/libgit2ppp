#ifndef INCLUDE_GIT2PPP_ERROR_STORE_HPP
#define INCLUDE_GIT2PPP_ERROR_STORE_HPP

#include "common.hpp"

#include <memory>

GIT2PPP_NAMESPACE_BEGIN

class GIT2PPP_API ErrorStore {
public:
  struct GIT2PPP_INTERNAL_FWD Member;

  using ErrorCodeType = int;
  using ErrorClassType = int;
  using ErrorType = std::tuple<ErrorCodeType, ErrorClassType, std::string>;

  ~ErrorStore();

  bool HasError() const noexcept;
  ErrorType GetError() const noexcept;

protected:

  ErrorStore() noexcept;
  ErrorStore(const ErrorType & error) noexcept;
  ErrorStore(std::unique_ptr<Member> && m) noexcept;
  ErrorStore(const ErrorStore &) = delete;
  ErrorStore(ErrorStore &&) noexcept;

  ErrorStore & operator=(const ErrorStore &) = delete;
  ErrorStore & operator=(ErrorStore &&) noexcept;

  void SetError(const ErrorType & error) const noexcept;
  void SetSuccess() const noexcept;

private:
  std::unique_ptr<Member> m_;
};

GIT2PPP_NAMESPACE_END

#endif // INCLUDE_GIT2PPP_ERROR_STORE_HPP
