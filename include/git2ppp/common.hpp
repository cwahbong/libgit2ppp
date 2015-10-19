#ifndef INCLUDE_GIT2PPP_COMMON_HPP
#define INCLUDE_GIT2PPP_COMMON_HPP

#define GIT2PPP_NAMESPACE_BEGIN namespace git2ppp {
#define GIT2PPP_NAMESPACE_END }

#ifdef GIT2PPP_EXPORT
  #define GIT2PPP_API __attribute__ ((visibility ("default")))
  #define GIT2PPP_API_FWD
  #define GIT2PPP_INTERNAL_FWD
#else
  #define GIT2PPP_API
  #define GIT2PPP_API_FWD
  #define GIT2PPP_INTERNAL_FWD
#endif

#endif // INCLUDE_GIT2PPP_COMMON_HPP
