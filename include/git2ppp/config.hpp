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

  Git2Error Set(const std::string & name, const std::string & value) noexcept;
  Git2Error SetBool(const std::string & name, bool value) noexcept;
  Git2Error SetInt32(const std::string & name, int32_t value) noexcept;
  Git2Error SetInt64(const std::string & name, int64_t value) noexcept;
  Git2Error SetMultiVar(const std::string & name, const std::string & old_value_regexp, const std::string & value) noexcept;

  std::pair<Git2Error, std::string> Get(const std::string & name) const noexcept;
  std::pair<Git2Error, bool> GetBool(const std::string & name) const noexcept;
  std::pair<Git2Error, int32_t> GetInt32(const std::string & name) const noexcept;
  std::pair<Git2Error, int64_t> GetInt64(const std::string & name) const noexcept;
  Git2Error GetMultiVarForEach(const std::string & name, const std::string & regexp, EntryCallbackType callback) const noexcept;

  Git2Error Delete(const std::string & name) noexcept;
  Git2Error DeleteMultiVar(const std::string & name, const std::string & value_regexp) noexcept;

  Git2Error ForEach(EntryCallbackType callback) noexcept;
  Git2Error ForEachMatch(const std::string & regexp, EntryCallbackType callback) noexcept;

  std::pair<Git2Error, Config> OpenLevel(int level) const noexcept;
  std::pair<Git2Error, Config> OpenGlobal() const noexcept;
  std::pair<Git2Error, Config> Snapshot() const noexcept;

private:
  std::unique_ptr<Member> m_;
};

class GIT2PPP_API ConfigInterface final: public Interface {
public:
  static const ConfigInterface & Get() noexcept;

  std::pair<Git2Error, Config> Create() const noexcept;
  std::pair<Git2Error, Config> OpenDefault() const noexcept;
  std::pair<Git2Error, Config> Open(const std::string & path) const noexcept;

  std::pair<Git2Error, std::string> GlobalPath() const noexcept;
  std::pair<Git2Error, std::string> SystemPath() const noexcept;
  std::pair<Git2Error, std::string> XdgPath() const noexcept;

  std::pair<Git2Error, bool> ParseBool(const std::string & value) const noexcept;
  std::pair<Git2Error, int32_t> ParseInt32(const std::string & value) const noexcept;
  std::pair<Git2Error, int64_t> ParseInt64(const std::string & value) const noexcept;

private:
  ConfigInterface(const Library & library) noexcept;
  ~ConfigInterface();
};

GIT2PPP_NAMESPACE_END

#endif // INCLUDE_GIT2PPP_CONFIG_HPP
