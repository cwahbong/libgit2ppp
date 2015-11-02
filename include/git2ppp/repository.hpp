#ifndef INCLUDE_GIT2PPP_REPOSITORY_HPP
#define INCLUDE_GIT2PPP_REPOSITORY_HPP

#include "common.hpp"

#include "error.hpp"
#include "interface.hpp"

#include <memory>
#include <utility>

GIT2PPP_NAMESPACE_BEGIN

class GIT2PPP_API_FWD Config;

class GIT2PPP_API Repository final {
public:
  struct GIT2PPP_INTERNAL_FWD Member;

  Repository(std::unique_ptr<Member> && m) noexcept;
  Repository(const Repository &) = delete;
  Repository(Repository &&) noexcept;
  ~Repository();

  Repository & operator=(const Repository &) = delete;
  Repository & operator=(Repository &&) noexcept;

  std::pair<Git2Error, Config> GetConfig() const noexcept;

private:
  std::unique_ptr<Member> m_;
};

class GIT2PPP_API RepositoryInterface final: public Interface {
public:
  static const RepositoryInterface & Get() noexcept;

  std::pair<Git2Error, Repository> Open(const std::string & path) const noexcept;

private:
  RepositoryInterface(const Library & library) noexcept;
  ~RepositoryInterface();
};

GIT2PPP_NAMESPACE_END

#endif // INCLUDE_GIT2PPP_REPOSITORY_HPP
