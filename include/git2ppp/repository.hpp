#ifndef INCLUDE_GIT2PPP_REPOSITORY_HPP
#define INCLUDE_GIT2PPP_REPOSITORY_HPP

#include "common.hpp"

#include "error_store.hpp"
#include "interface.hpp"

#include <memory>

GIT2PPP_NAMESPACE_BEGIN

class GIT2PPP_API_FWD Config;

class GIT2PPP_API Repository final: public ErrorStore {
public:
  struct GIT2PPP_INTERNAL_FWD Member;

  Repository(std::unique_ptr<Member> && m) noexcept;
  Repository(const ErrorType & error) noexcept;
  Repository(const Repository &) = delete;
  Repository(Repository &&) noexcept;
  ~Repository();

  Repository & operator=(const Repository &) = delete;
  Repository & operator=(Repository &&) noexcept;

  Config GetConfig() const noexcept;

private:
  std::unique_ptr<Member> m_;
};

class GIT2PPP_API RepositoryInterface final: public Interface {
public:
  static const RepositoryInterface & Get() noexcept;

private:
  RepositoryInterface(const Library & library) noexcept;
  ~RepositoryInterface();
};

GIT2PPP_NAMESPACE_END

#endif // INCLUDE_GIT2PPP_REPOSITORY_HPP
