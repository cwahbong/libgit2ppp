#ifndef INCLUDE_GIT2PPP_INTERNAL_ERROR_HPP
#define INCLUDE_GIT2PPP_INTERNAL_ERROR_HPP

#include "git2ppp/error.hpp"

#include <git2/errors.h>

GIT2PPP_NAMESPACE_BEGIN

struct Error::Member {
  const git_error * pError;

  Member(const git_error * error) noexcept:
    pError(error)
  {/* Empty. */}

  Member(Member && member) noexcept:
    pError(member.pError)
    {
      member.pError = nullptr;
  }

  // git_error is managed by libgit2.
  ~Member() = default;
};

GIT2PPP_NAMESPACE_END

#endif // INCLUDE_GIT2PPP_INTERNAL_ERROR_HPP
