#ifndef INCLUDE_GIT2PPP_CONFIG_HPP
#define INCLUDE_GIT2PPP_CONFIG_HPP

#include "common.hpp"

#include "error.hpp"
#include "interface.hpp"

#include <string>
#include <memory>

GIT2PPP_NAMESPACE_BEGIN

class GIT2PPP_API Config final {
public:
  struct GIT2PPP_INTERNAL_FWD Member;

  using EntryCallbackType = std::function<bool (std::string &&, std::string &&)>;

  Config(std::unique_ptr<Member> && m) noexcept;
  Config(const Config &) = delete;
  Config(Config &&) noexcept;
  ~Config();

  Config & operator=(const Config &) = delete;
  Config & operator=(Config &&) noexcept;

  Returned<void> Set(const std::string & name, const std::string & value) noexcept;
  Returned<void> SetBool(const std::string & name, bool value) noexcept;
  Returned<void> SetInt32(const std::string & name, int32_t value) noexcept;
  Returned<void> SetInt64(const std::string & name, int64_t value) noexcept;
  Returned<void> SetMultiVar(const std::string & name, const std::string & old_value_regexp, const std::string & value) noexcept;

  Returned<std::string> Get(const std::string & name) const noexcept;
  Returned<bool> GetBool(const std::string & name) const noexcept;
  Returned<int32_t> GetInt32(const std::string & name) const noexcept;
  Returned<int64_t> GetInt64(const std::string & name) const noexcept;
  Returned<void> GetMultiVarForEach(const std::string & name, const std::string & regexp, EntryCallbackType callback) const noexcept;

  Returned<void> Delete(const std::string & name) noexcept;
  Returned<void> DeleteMultiVar(const std::string & name, const std::string & value_regexp) noexcept;

  Returned<void> ForEach(EntryCallbackType callback) noexcept;
  Returned<void> ForEachMatch(const std::string & regexp, EntryCallbackType callback) noexcept;

  Returned<Config> OpenLevel(int level) const noexcept;
  Returned<Config> OpenGlobal() const noexcept;
  Returned<Config> Snapshot() const noexcept;

private:
  std::unique_ptr<Member> m_;
};

class GIT2PPP_API ConfigInterface final: public Interface {
public:
  static const ConfigInterface & Get() noexcept;

  Returned<Config> Create() const noexcept;
  Returned<Config> OpenDefault() const noexcept;
  Returned<Config> Open(const std::string & path) const noexcept;

  Returned<std::string> GlobalPath() const noexcept;
  Returned<std::string> SystemPath() const noexcept;
  Returned<std::string> XdgPath() const noexcept;

  Returned<bool> ParseBool(const std::string & value) const noexcept;
  Returned<int32_t> ParseInt32(const std::string & value) const noexcept;
  Returned<int64_t> ParseInt64(const std::string & value) const noexcept;

private:
  ConfigInterface(const Library & library) noexcept;
  ~ConfigInterface();
};

GIT2PPP_NAMESPACE_END

#endif // INCLUDE_GIT2PPP_CONFIG_HPP
