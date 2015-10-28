#include "error_store.hpp"

GIT2PPP_NAMESPACE_BEGIN

namespace {

const ErrorStore::ErrorType success{0, 0, ""};

} // namespace

ErrorStore::ErrorStore() noexcept:
  ErrorStore(success)
{/* Empty. */}

ErrorStore::ErrorStore(const ErrorType & error) noexcept:
  m_{new(std::nothrow) Member{error}}
{/* Empty. */}

ErrorStore::ErrorStore(std::unique_ptr<Member> && m) noexcept:
  m_{std::move(m)}
{/* Empty. */}

ErrorStore::ErrorStore(ErrorStore && rhs) noexcept:
  m_{std::move(rhs.m_)}
{/* Empty. */}

ErrorStore &
ErrorStore::operator=(ErrorStore && rhs) noexcept
{
  if (this != &rhs) {
    m_ = std::move(rhs.m_);
  }
  return *this;
}

ErrorStore::~ErrorStore()
{/* Empty. */}

bool
ErrorStore::HasError() const noexcept
{
  return std::get<0>(m_->error) != 0;
}

ErrorStore::ErrorType
ErrorStore::GetError() const noexcept
{
  return m_->error;
}

void
ErrorStore::SetError(const ErrorType & error) const noexcept
{
  m_->error = error;
}

void
ErrorStore::SetSuccess() const noexcept
{
  m_->error = success;
}

GIT2PPP_NAMESPACE_END
