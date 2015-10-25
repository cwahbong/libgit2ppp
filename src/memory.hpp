#ifndef INCLUDE_GIT2PPP_INTERNAL_MEMORY_HPP
#define INCLUDE_GIT2PPP_INTERNAL_MEMORY_HPP

#include <memory>

GIT2PPP_NAMESPACE_BEGIN

template <class WrapType, class RawType>
WrapType
Wrap(RawType * pRaw)
{
  using Member = typename WrapType::Member;
  Member member{pRaw};
  std::unique_ptr<Member> upMember{new Member{std::move(member)}};
  return WrapType{std::move(upMember)};
}

GIT2PPP_NAMESPACE_END

#endif // INCLUDE_GIT2PPP_INTERNAL_MEMORY_HPP
