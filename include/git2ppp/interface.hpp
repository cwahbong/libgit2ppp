#ifndef INCLUDE_GIT2PPP_INTERFACE_HPP
#define INCLUDE_GIT2PPP_INTERFACE_HPP

#include "common.hpp"

GIT2PPP_NAMESPACE_BEGIN

class GIT2PPP_API_FWD Library;

class GIT2PPP_API Interface {
protected:
  Interface(const Library & library) noexcept;
  ~Interface();

private:
  const Library & _library;
};

GIT2PPP_NAMESPACE_END

#endif // INCLUDE_GIT2PPP_INTERFACE_HPP
