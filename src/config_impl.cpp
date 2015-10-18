#include "config_impl.hpp"

#include "git2ppp/exception.hpp"

GIT2PPP_NAMESPACE_BEGIN

ConfigImpl::ConfigImpl(git_config * pConfig):
  m_pConfig{pConfig}
{/* Empty. */}

ConfigImpl::~ConfigImpl()
{
  git_config_free(m_pConfig);
}

void
ConfigImpl::Set(const std::string & name, const std::string & value)
{
  ThrowOnError(git_config_set_string(m_pConfig, name.c_str(), value.c_str()));
}

void
ConfigImpl::SetBool(const std::string & name, bool value)
{
  ThrowOnError(git_config_set_bool(m_pConfig, name.c_str(), value));
}

void
ConfigImpl::SetInt32(const std::string & name, int32_t value)
{
  ThrowOnError(git_config_set_int32(m_pConfig, name.c_str(), value));
}

void
ConfigImpl::SetInt64(const std::string & name, int64_t value)
{
  ThrowOnError(git_config_set_int64(m_pConfig, name.c_str(), value));
}

void
ConfigImpl::SetMultiVar(const std::string & name, const std::string & old_value_regexp, const std::string & value)
{
  ThrowOnError(git_config_set_multivar(m_pConfig, name.c_str(), old_value_regexp.c_str(), value.c_str()));
}

std::string
ConfigImpl::Get(const std::string & name) const
{
  const char * value = nullptr;
  ThrowOnError(git_config_get_string(&value, m_pConfig, name.c_str()));
  return std::string(value);
}

bool
ConfigImpl::GetBool(const std::string & name) const
{
  int value = 0;
  ThrowOnError(git_config_get_bool(&value, m_pConfig, name.c_str()));
  return value;
}

int32_t
ConfigImpl::GetInt32(const std::string & name) const
{
  int32_t value = 0;
  ThrowOnError(git_config_get_int32(&value, m_pConfig, name.c_str()));
  return value;
}

int64_t
ConfigImpl::GetInt64(const std::string & name) const
{
  int64_t value = 0;
  ThrowOnError(git_config_get_int64(&value, m_pConfig, name.c_str()));
  return value;
}

void
ConfigImpl::Delete(const std::string & name)
{
  ThrowOnError(git_config_delete_entry(m_pConfig, name.c_str()));
}

void
ConfigImpl::DeleteMultiVar(const std::string & name, const std::string & value_regexp)
{
  ThrowOnError(git_config_delete_multivar(m_pConfig, name.c_str(), value_regexp.c_str()));
}

std::unique_ptr<Config>
ConfigImpl::OpenLevel(int level) const
{
  git_config * pConfig = nullptr;
  ThrowOnError(git_config_open_level(&pConfig, m_pConfig, static_cast<git_config_level_t>(level)));
  return MakeConfig(pConfig);
}

std::unique_ptr<Config>
ConfigImpl::Snapshot() const
{
  git_config * pSnapshot = nullptr;
  ThrowOnError(git_config_snapshot(&pSnapshot, m_pConfig));
  return MakeConfig(pSnapshot);
}

std::unique_ptr<Config>
MakeConfig(git_config * pConfig)
{
  std::unique_ptr<ConfigImpl> upConfigImpl{new ConfigImpl{pConfig}};
  std::unique_ptr<Config> upConfig{new Config{upConfigImpl.get()}};
  upConfigImpl.release();
  return upConfig;
}

GIT2PPP_NAMESPACE_END
