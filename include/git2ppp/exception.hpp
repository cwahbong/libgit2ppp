#ifndef INCLUDE_GIT2PPP_EXCEPTION_HPP
#define INCLUDE_GIT2PPP_EXCEPTION_HPP

#include "common.hpp"

#include <exception>
#include <string>

GIT2PPP_NAMESPACE_BEGIN

class GIT2PPP_API Exception: public std::exception {
public:
  Exception(int errCode) noexcept;
  virtual ~Exception();

  virtual const char * what() const noexcept;

private:
  int _errCode;
  const char * _errMessage;
};

void GIT2PPP_API ThrowOnError(int gitRet);

GIT2PPP_NAMESPACE_END

#endif // INCLUDE_GIT2PPP_EXCEPTION_HPP
