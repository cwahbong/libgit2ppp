#include "git2ppp/interface.hpp"

#include "git2ppp/library.hpp"

GIT2PPP_NAMESPACE_BEGIN

Interface::Interface(const Library & library) noexcept:
  _library(library)
{/* Empty. */}

Interface::~Interface()
{/* Empty. */}

GIT2PPP_NAMESPACE_END
