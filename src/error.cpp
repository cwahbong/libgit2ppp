#include "error.hpp"

GIT2PPP_NAMESPACE_BEGIN

Error::Error(std::unique_ptr<Member> && m) noexcept:
  m_(std::move(m))
{/* Empty. */}

bool
Error::Empty() const noexcept
{
  return m_ == nullptr || m_->pError == nullptr;
}

int
Error::Class() const noexcept
{
  return m_->pError->klass;
}

std::string
Error::Message() const noexcept
{
  return m_->pError->message;
}

Error
ErrorInterface::Last() const noexcept
{
  const git_error * error = giterr_last();
  return Error(std::unique_ptr<Error::Member>(new(std::nothrow) Error::Member{error}));
}

void
ErrorInterface::Clear() const noexcept
{
  giterr_clear();
}

ErrorInterface::ErrorInterface(const Library & library) noexcept:
  Interface(library)
{/* Empty. */}

ErrorInterface::~ErrorInterface() = default;

GIT2PPP_NAMESPACE_END
