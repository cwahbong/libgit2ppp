#include "git2ppp/library.hpp"

#include "error_store.hpp"

#include <git2.h>

GIT2PPP_NAMESPACE_BEGIN

Library::Library() noexcept:
  ErrorStore{}
{
  RETURN_ON_ERROR(git_libgit2_init());
}

Library::~Library()
{
  git_libgit2_shutdown();
}

bool
Library::IsThreadSupported() noexcept
{
  return git_libgit2_features() & GIT_FEATURE_THREADS;
}

bool
Library::IsHttpsSupported() noexcept
{
  return git_libgit2_features() & GIT_FEATURE_HTTPS;
}

bool
Library::IsSshSupported() noexcept
{
  return git_libgit2_features() & GIT_FEATURE_SSH;
}

Library::VersionType
Library::Version() noexcept
{
  Library::VersionType version;
  git_libgit2_version(&std::get<0>(version), &std::get<1>(version), &std::get<2>(version));
  return version;
}

const Library &
Library::Get() noexcept
{
  thread_local Library library;
  return library;
}

GIT2PPP_NAMESPACE_END
