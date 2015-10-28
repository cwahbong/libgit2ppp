#include "repository.hpp"

#include "git2ppp/library.hpp"

#include "config.hpp"
#include "error_store.hpp"
#include "memory.hpp"

#include <git2/config.h>
#include <git2/errors.h>
#include <git2/repository.h>

GIT2PPP_NAMESPACE_BEGIN

Repository::Repository(std::unique_ptr<Member> && m) noexcept:
  ErrorStore{},
  m_{std::move(m)}
{/* Empty. */}

Repository::Repository(const ErrorType & error) noexcept:
  ErrorStore{error},
  m_{new(std::nothrow) Member{nullptr}}
{/* Empty. */}

Repository::Repository(Repository && rhs) noexcept:
  ErrorStore{std::move(rhs)},
  m_{std::move(rhs.m_)}
{/* Empty. */}

Repository::~Repository()
{/* Empty. */}

Repository &
Repository::operator=(Repository && rhs) noexcept
{
  if (this != &rhs) {
    ErrorStore::operator=(std::move(rhs));
    this->m_ = std::move(rhs.m_);
  }
  return *this;
}

Config
Repository::GetConfig() const noexcept
{
  if (!m_ || !m_->pRepository) {
    return Config(GetError());
  }
  git_config * pConfig = nullptr;
  int ret = git_repository_config(&pConfig, m_->pRepository);
  if (ret < 0) {
    const git_error * pError = giterr_last();
    return Config(std::make_tuple(ret, pError->klass, pError->message));
  }
  return Wrap<Config, git_config>(pConfig);
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

Repository
RepositoryInterface::Open(const std::string & path) const noexcept
{
  git_repository * pRepository = nullptr;
  RETURN_STORE_ON_ERROR(Repository, git_repository_open(&pRepository, path.c_str()));
  return Wrap<Repository, git_repository>(pRepository);
}

GIT2PPP_NAMESPACE_END
