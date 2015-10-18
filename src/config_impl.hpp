#include "git2ppp/config.hpp"

#include <git2/config.h>

GIT2PPP_NAMESPACE_BEGIN

class ConfigImpl final {
public:
  ConfigImpl(git_config *);
  ~ConfigImpl();
  // TODO not assignable

  void Set(const std::string & name, const std::string & value);
  void SetBool(const std::string & name, bool value);
  void SetInt32(const std::string & name, int32_t value);
  void SetInt64(const std::string & name, int64_t value);
  void SetMultiVar(const std::string & name, const std::string & old_value_regexp, const std::string & value);

  std::string Get(const std::string & name) const;
  bool GetBool(const std::string & name) const;
  int32_t GetInt32(const std::string & name) const;
  int64_t GetInt64(const std::string & name) const;

  void Delete(const std::string & name);
  void DeleteMultiVar(const std::string & name, const std::string & value_regexp);

  std::unique_ptr<Config> OpenLevel(int level) const;
  std::unique_ptr<Config> Snapshot() const;

private:
  git_config * const m_pConfig;
};

// TODO exception safe
std::unique_ptr<Config> MakeConfig(git_config * pConfig);

GIT2PPP_NAMESPACE_END
