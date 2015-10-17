#ifndef INCLUDE_GIT2PPP_INTERFACE_HPP
#define INCLUDE_GIT2PPP_INTERFACE_HPP

#include "common.hpp"

GIT2PPP_NAMESPACE_BEGIN

class Library;

class Interface {
protected:
  Interface(const Library & library);
  ~Interface();

private:
  const Library & _library;
};

GIT2PPP_NAMESPACE_END

#endif // INCLUDE_GIT2PPP_INTERFACE_HPP
