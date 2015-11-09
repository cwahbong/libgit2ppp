#include "repository.hpp"

#include "git2ppp/library.hpp"

#include "config.hpp"
#include "memory.hpp"

#include <git2/config.h>
#include <git2/errors.h>
#include <git2/repository.h>

GIT2PPP_NAMESPACE_BEGIN

Repository::Repository(std::unique_ptr<Member> && m) noexcept:
  m_{std::move(m)}
{/* Empty. */}

Repository::Repository(Repository &&) noexcept = default;

Repository::~Repository() = default;

Repository &
Repository::operator=(Repository && rhs) noexcept
{
  if (this != &rhs) {
    this->m_ = std::move(rhs.m_);
  }
  return *this;
}

Returned<Config>
Repository::GetConfig() const noexcept
{
  if (!m_ || !m_->pRepository) {
    return std::make_pair(GIT_EUSER, Wrap<Config, git_config>(nullptr));
  }
  git_config * pConfig = nullptr;
  const Git2Error ret = git_repository_config(&pConfig, m_->pRepository);
  return std::make_pair(ret, Wrap<Config, git_config>(pConfig));
}

RepositoryInterface::RepositoryInterface(const Library & library) noexcept:
  Interface(library)
{/* Empty. */}

RepositoryInterface::~RepositoryInterface()
{/* Empty. */}

const RepositoryInterface &
RepositoryInterface::Get() noexcept
{
  thread_local const RepositoryInterface interface(Library::Get());
  return interface;
}

Returned<Repository>
RepositoryInterface::Open(const std::string & path) const noexcept
{
  git_repository * pRepository = nullptr;
  const Git2Error ret = git_repository_open(&pRepository, path.c_str());
  return std::make_pair(ret, Wrap<Repository, git_repository>(pRepository));
}

GIT2PPP_NAMESPACE_END
