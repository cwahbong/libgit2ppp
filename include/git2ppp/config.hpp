#ifndef INCLUDE_GIT2PPP_CONFIG_HPP
#define INCLUDE_GIT2PPP_CONFIG_HPP

#include "common.hpp"

#include "error_store.hpp"
#include "interface.hpp"

#include <string>
#include <memory>

GIT2PPP_NAMESPACE_BEGIN

class GIT2PPP_API Config final: public ErrorStore {
public:
  struct GIT2PPP_INTERNAL_FWD Member;

  using EntryCallbackType = std::function<bool (std::string &&, std::string &&)>;

  Config(std::unique_ptr<Member> && m) noexcept;
  Config(const ErrorType & error) noexcept;
  Config(const Config &) = delete;
  Config(Config &&) noexcept;
  ~Config();

  Config & operator=(const Config &) = delete;
  Config & operator=(Config &&) noexcept;

  void Set(const std::string & name, const std::string & value) noexcept;
  void SetBool(const std::string & name, bool value) noexcept;
  void SetInt32(const std::string & name, int32_t value) noexcept;
  void SetInt64(const std::string & name, int64_t value) noexcept;
  void SetMultiVar(const std::string & name, const std::string & old_value_regexp, const std::string & value) noexcept;

  std::string Get(const std::string & name) const noexcept;
  bool GetBool(const std::string & name) const noexcept;
  int32_t GetInt32(const std::string & name) const noexcept;
  int64_t GetInt64(const std::string & name) const noexcept;
  void GetMultiVarForEach(const std::string & name, const std::string & regexp, EntryCallbackType callback) const noexcept;

  void Delete(const std::string & name) noexcept;
  void DeleteMultiVar(const std::string & name, const std::string & value_regexp) noexcept;

  void ForEach(EntryCallbackType callback) noexcept;
  void ForEachMatch(const std::string & regexp, EntryCallbackType callback) noexcept;

  Config OpenLevel(int level) const noexcept;
  Config OpenGlobal() const noexcept;
  Config Snapshot() const noexcept;

private:
  std::unique_ptr<Member> m_;
};

class GIT2PPP_API ConfigInterface final: public Interface {
public:
  static const ConfigInterface & Get() noexcept;

  Config Create() const noexcept;
  Config OpenDefault() const noexcept;
  Config Open(const std::string & path) const noexcept;

  std::string GlobalPath() const noexcept;
  std::string SystemPath() const noexcept;
  std::string XdgPath() const noexcept;

  bool ParseBool(const std::string & value) const noexcept;
  int32_t ParseInt32(const std::string & value) const noexcept;
  int64_t ParseInt64(const std::string & value) const noexcept;

private:
  ConfigInterface(const Library & library) noexcept;
  ~ConfigInterface();
};

GIT2PPP_NAMESPACE_END

#endif // INCLUDE_GIT2PPP_CONFIG_HPP
