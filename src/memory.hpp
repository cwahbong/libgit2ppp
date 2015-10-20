#ifndef INCLUDE_GIT2PPP_INTERNAL_MEMORY_HPP
#define INCLUDE_GIT2PPP_INTERNAL_MEMORY_HPP

#include <memory>

GIT2PPP_NAMESPACE_BEGIN

template <class WrapType, class RawType>
std::unique_ptr<WrapType>
Wrap(RawType * pRaw)
{
  using Member = typename WrapType::Member;
  Member member{pRaw};
  std::unique_ptr<Member> upMember{new Member{std::move(member)}};
  std::unique_ptr<WrapType> upWrap{new WrapType{std::move(upMember)}};
  return upWrap;
}

GIT2PPP_NAMESPACE_END

#endif // INCLUDE_GIT2PPP_INTERNAL_MEMORY_HPP
