#include "repository.hpp"

#include "git2ppp/exception.hpp"
#include "git2ppp/library.hpp"

#include "config.hpp"
#include "memory.hpp"

#include <git2/config.h>
#include <git2/repository.h>

GIT2PPP_NAMESPACE_BEGIN

Repository::Repository(std::unique_ptr<Member> && m):
  m_{std::move(m)}
{/* Empty. */}

Repository::~Repository()
{/* Empty. */}

std::unique_ptr<Config>
Repository::GetConfig() const
{
  git_config * pConfig = nullptr;
  ThrowOnError(git_repository_config(&pConfig, m_->pRepository));
  return Wrap<Config, git_config>(pConfig);
}

RepositoryInterface::RepositoryInterface(const Library & library):
  Interface(library)
{/* Empty. */}

RepositoryInterface::~RepositoryInterface()
{/* Empty. */}

const RepositoryInterface &
RepositoryInterface::Get()
{
  thread_local const RepositoryInterface interface(Library::Get());
  return interface;
}

GIT2PPP_NAMESPACE_END
