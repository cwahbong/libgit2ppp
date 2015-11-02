#include "git2ppp/library.hpp"

#include <git2.h>

GIT2PPP_NAMESPACE_BEGIN

Library::Library() noexcept:
  mValid(git_libgit2_init() == 0)
{/* Empty. */}

Library::~Library()
{
  git_libgit2_shutdown();
}

bool
Library::IsValid() const noexcept
{
  return mValid;
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
