#ifndef INCLUDE_GIT2PPP_REPOSITORY_HPP
#define INCLUDE_GIT2PPP_REPOSITORY_HPP

#include "common.hpp"
#include "interface.hpp"

#include <memory>

GIT2PPP_NAMESPACE_BEGIN

class GIT2PPP_API_FWD Config;

class GIT2PPP_API Repository final {
public:
  struct GIT2PPP_INTERNAL_FWD Member;

  Repository(std::unique_ptr<Member> && m);
  ~Repository();

  std::unique_ptr<Config> GetConfig() const;

private:
  std::unique_ptr<Member> m_;
};

class GIT2PPP_API RepositoryInterface final: public Interface {
public:
  static const RepositoryInterface & Get();

private:
  RepositoryInterface(const Library & library);
  ~RepositoryInterface();
};

GIT2PPP_NAMESPACE_END

#endif // INCLUDE_GIT2PPP_REPOSITORY_HPP
