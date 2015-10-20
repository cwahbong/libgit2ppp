#ifndef INCLUDE_GIT2PPP_CONFIG_HPP
#define INCLUDE_GIT2PPP_CONFIG_HPP

#include "common.hpp"
#include "interface.hpp"

#include <string>
#include <memory>

GIT2PPP_NAMESPACE_BEGIN

class GIT2PPP_API Config final {
public:
  struct GIT2PPP_INTERNAL_FWD Member;

  Config(std::unique_ptr<Member> && m);
  ~Config();

  void Set(const std::string & name, const std::string & value);
  void SetBool(const std::string & name, bool value);
  void SetInt32(const std::string & name, int32_t value);
  void SetInt64(const std::string & name, int64_t value);
  void SetMultiVar(const std::string & name, const std::string & old_value_regexp, const std::string & value);

  std::string Get(const std::string & name) const;
  bool GetBool(const std::string & name) const;
  int32_t GetInt32(const std::string & name) const;
  int64_t GetInt64(const std::string & name) const;
  // GetMultiVar: maybe by iterator?

  void Delete(const std::string & name);
  void DeleteMultiVar(const std::string & name, const std::string & value_regexp);

  std::unique_ptr<Config> OpenLevel(int level) const;
  std::unique_ptr<Config> Snapshot() const;

private:
  std::unique_ptr<Member> m_;
};

class GIT2PPP_API ConfigInterface final: public Interface {
public:
  static const ConfigInterface & Get();

  std::unique_ptr<Config> Create() const;
  std::unique_ptr<Config> Open() const;
  std::unique_ptr<Config> Open(const std::string & path) const;

  std::string GlobalPath() const;
  std::string SystemPath() const;
  std::string XdgPath() const;

  bool ParseBool(const std::string & value) const;
  int32_t ParseInt32(const std::string & value) const;
  int64_t ParseInt64(const std::string & value) const;

private:
  ConfigInterface(const Library & library);
  ~ConfigInterface();
};

GIT2PPP_NAMESPACE_END

#endif // INCLUDE_GIT2PPP_CONFIG_HPP
