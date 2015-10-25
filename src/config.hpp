#ifndef INCLUDE_GIT2PPP_INTERNAL_CONFIG_HPP
#define INCLUDE_GIT2PPP_INTERNAL_CONFIG_HPP

#include "git2ppp/config.hpp"

#include <git2/config.h>

GIT2PPP_NAMESPACE_BEGIN

struct Config::Member {
  git_config * pConfig;

  Member(git_config * config) noexcept:
    pConfig{config}
  {/* Empty. */}

  Member(Member && member) noexcept:
    pConfig{member.pConfig}
  {
    member.pConfig = nullptr;
  }

  ~Member() {
    git_config_free(pConfig);
  }
};

GIT2PPP_NAMESPACE_END

#endif // INCLUDE_GIT2PPP_INTERNAL_CONFIG_HPP
