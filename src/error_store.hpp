#ifndef INCLUDE_GIT2PPP_INTERNAL_ERROR_STORE_HPP
#define INCLUDE_GIT2PPP_INTERNAL_ERROR_STORE_HPP

#include "git2ppp/error_store.hpp"

#include <git2/errors.h>

GIT2PPP_NAMESPACE_BEGIN

struct ErrorStore::Member {
  ErrorType error;
};

GIT2PPP_NAMESPACE_END

#define RETURN_STORE_ON_ERROR(Class, ret) do { \
  if (ret < 0) { \
    const git_error * error = giterr_last(); \
    return Class{ErrorStore::ErrorType{ret, error->klass, error->message}}; \
  } \
} while(0)

#define RETURN_VALUE_ON_ERROR(Type, ret) do { \
  if (ret < 0) { \
    const git_error * error = giterr_last(); \
    SetError(ErrorStore::ErrorType{ret, error->klass, error->message}); \
    return Type{}; \
  } \
} while(0)

#define RETURN_ON_ERROR(ret) do { \
  if (ret < 0) { \
    const git_error * error = giterr_last(); \
    SetError(ErrorStore::ErrorType{ret, error->klass, error->message}); \
    return; \
  } \
} while(0)

#define SET_ON_ERROR(ret) do { \
  if (ret < 0) { \
    const git_error * error = giterr_last(); \
    SetError(ErrorStore::ErrorType{ret, error->klass, error->message}); \
  } \
} while(0)\

#endif // INCLUDE_GIT2PPP_INTERNAL_ERROR_STORE_HPP
