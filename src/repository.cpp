#include "git2ppp/repository.hpp"

#include "git2ppp/library.hpp"

#include "repository_impl.hpp"

GIT2PPP_NAMESPACE_BEGIN

Repository::Repository(RepositoryImpl * pImpl):
  m_pImpl{pImpl}
{/* Empty. */}

Repository::~Repository()
{/* Empty. */}

std::unique_ptr<Config>
Repository::GetConfig() const
{
  return m_pImpl->GetConfig();
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
