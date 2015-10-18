#include "repository_impl.hpp"

#include "git2ppp/exception.hpp"
#include "config_impl.hpp"

GIT2PPP_NAMESPACE_BEGIN

RepositoryImpl::RepositoryImpl(git_repository * repository):
  _repository{repository}
{/* Empty. */}

RepositoryImpl::~RepositoryImpl()
{
  git_repository_free(_repository);
}

std::unique_ptr<Config>
RepositoryImpl::GetConfig() const
{
  git_config * pConfig = nullptr;
  ThrowOnError(git_repository_config(&pConfig, _repository));
  return MakeConfig(pConfig);
}

GIT2PPP_NAMESPACE_END
