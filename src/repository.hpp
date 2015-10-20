#ifndef INCLUDE_GIT2PPP_INTERNAL_REPOSITORY_HPP
#define INCLUDE_GIT2PPP_INTERNAL_REPOSITORY_HPP

#include "git2ppp/repository.hpp"

#include <git2/repository.h>

GIT2PPP_NAMESPACE_BEGIN

struct Repository::Member {
  git_repository * pRepository;

  Member(git_repository * repository):
    pRepository{repository}
  {/* Empty. */}

  Member(Member && member):
    pRepository{member.pRepository}
  {
    member.pRepository = nullptr;
  }

  ~Member() {
    git_repository_free(pRepository);
  }
};

GIT2PPP_NAMESPACE_END

#endif // INCLUDE_GIT2PPP_INTERNAL_REPOSITORY_HPP
