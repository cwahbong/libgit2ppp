#ifndef INCLUDE_GIT2PPP_REPOSITORY_IMPL_HPP
#define INCLUDE_GIT2PPP_REPOSITORY_IMPL_HPP

#include "git2ppp/config.hpp"
#include "git2ppp/repository.hpp"

#include <git2/repository.h>

GIT2PPP_NAMESPACE_BEGIN

class RepositoryImpl final {
public:
  RepositoryImpl(git_repository *);
  ~RepositoryImpl();

  std::unique_ptr<Config> GetConfig() const;

private:
  git_repository * const _repository;
};

GIT2PPP_NAMESPACE_END

#endif // INCLUDE_GIT2PPP_REPOSITORY_IMPL_HPP
