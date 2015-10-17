#include "git2ppp/library.hpp"

#include "git2ppp/exception.hpp"

#include <git2.h>

GIT2PPP_NAMESPACE_BEGIN

Library::Library()
{
  ThrowOnError(git_libgit2_init());
}

Library::~Library()
{
  git_libgit2_shutdown();
}

bool
Library::IsThreadSupported()
{
  return git_libgit2_features() & GIT_FEATURE_THREADS;
}

bool
Library::IsHttpsSupported()
{
  return git_libgit2_features() & GIT_FEATURE_HTTPS;
}

bool
Library::IsSshSupported()
{
  return git_libgit2_features() & GIT_FEATURE_SSH;
}

Library::VersionType
Library::Version()
{
  Library::VersionType version;
  git_libgit2_version(&std::get<0>(version), &std::get<1>(version), &std::get<2>(version));
  return version;
}

const Library &
Library::Get()
{
  thread_local Library library;
  return library;
}

GIT2PPP_NAMESPACE_END
