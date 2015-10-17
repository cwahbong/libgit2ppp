#include "git2ppp/exception.hpp"

#include <git2/errors.h>

GIT2PPP_NAMESPACE_BEGIN

Exception::Exception(int errCode) noexcept:
  _errCode(errCode),
  _errMessage(nullptr)
{
  const git_error * error = giterr_last();
  if (error) {
    _errMessage = error->message;
    giterr_clear();
  }
}

Exception::~Exception()
{/* Empty. */}

const char *
Exception::what() const noexcept
{
  return _errMessage;
}

void
ThrowOnError(int gitRet)
{
  if (gitRet < 0) {
    throw Exception(gitRet);
  }
}

GIT2PPP_NAMESPACE_END
