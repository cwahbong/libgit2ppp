#include "config.hpp"

#include "git2ppp/exception.hpp"
#include "git2ppp/library.hpp"

#include "memory.hpp"

#include <git2/buffer.h>
#include <git2/config.h>

GIT2PPP_NAMESPACE_BEGIN

Config::Config(std::unique_ptr<Member> && m):
  m_{std::move(m)}
{/* Empty. */}

Config::~Config()
{/* Empty. */}

void
Config::Set(const std::string & name, const std::string & value)
{
  ThrowOnError(git_config_set_string(m_->pConfig, name.c_str(), value.c_str()));
}

void
Config::SetBool(const std::string & name, bool value)
{
  ThrowOnError(git_config_set_bool(m_->pConfig, name.c_str(), value));
}

void
Config::SetInt32(const std::string & name, int32_t value)
{
  ThrowOnError(git_config_set_int32(m_->pConfig, name.c_str(), value));
}

void
Config::SetInt64(const std::string & name, int64_t value)
{
  ThrowOnError(git_config_set_int64(m_->pConfig, name.c_str(), value));
}

void
Config::SetMultiVar(const std::string & name, const std::string & old_value_regexp, const std::string & value)
{
  ThrowOnError(git_config_set_multivar(m_->pConfig, name.c_str(), old_value_regexp.c_str(), value.c_str()));
}

std::string
Config::Get(const std::string & name) const
{
  const char * value = nullptr;
  ThrowOnError(git_config_get_string(&value, m_->pConfig, name.c_str()));
  return std::string(value);
}

bool
Config::GetBool(const std::string & name) const
{
  int value = 0;
  ThrowOnError(git_config_get_bool(&value, m_->pConfig, name.c_str()));
  return value;
}

int32_t
Config::GetInt32(const std::string & name) const
{
  int32_t value = 0;
  ThrowOnError(git_config_get_int32(&value, m_->pConfig, name.c_str()));
  return value;
}

int64_t
Config::GetInt64(const std::string & name) const
{
  int64_t value = 0;
  ThrowOnError(git_config_get_int64(&value, m_->pConfig, name.c_str()));
  return value;
}

void
Config::Delete(const std::string & name)
{
  ThrowOnError(git_config_delete_entry(m_->pConfig, name.c_str()));
}

void
Config::DeleteMultiVar(const std::string & name, const std::string & value_regexp)
{
  ThrowOnError(git_config_delete_multivar(m_->pConfig, name.c_str(), value_regexp.c_str()));
}

std::unique_ptr<Config>
Config::OpenLevel(int level) const
{
  git_config * pConfig = nullptr;
  ThrowOnError(git_config_open_level(&pConfig, m_->pConfig, static_cast<git_config_level_t>(level)));
  return Wrap<Config, git_config>(pConfig);
}

std::unique_ptr<Config>
Config::Snapshot() const
{
  git_config * pSnapshot = nullptr;
  ThrowOnError(git_config_snapshot(&pSnapshot, m_->pConfig));
  return Wrap<Config, git_config>(pSnapshot);
}

ConfigInterface::ConfigInterface(const Library & library):
  Interface(library)
{/* Empty. */}

ConfigInterface::~ConfigInterface()
{/* Empty. */}

const ConfigInterface &
ConfigInterface::Get()
{
  thread_local const ConfigInterface interface(Library::Get());
  return interface;
}

std::unique_ptr<Config>
ConfigInterface::Open() const
{
  git_config * pConfig = nullptr;
  ThrowOnError(git_config_open_default(&pConfig));
  return Wrap<Config, git_config>(pConfig);
}

std::unique_ptr<Config>
ConfigInterface::Open(const std::string & path) const
{
  git_config * pConfig = nullptr;
  ThrowOnError(git_config_open_ondisk(&pConfig, path.c_str()));
  return Wrap<Config, git_config>(pConfig);
}

std::string
ConfigInterface::GlobalPath() const
{
  git_buf buf = GIT_BUF_INIT_CONST(nullptr, 0);
  ThrowOnError(git_config_find_global(&buf));
  const std::string path{buf.ptr, buf.size};
  git_buf_free(&buf);
  return path;
}

std::string
ConfigInterface::SystemPath() const
{
  git_buf buf = GIT_BUF_INIT_CONST(nullptr, 0);
  ThrowOnError(git_config_find_system(&buf));
  const std::string path{buf.ptr, buf.size};
  git_buf_free(&buf);
  return path;
}

std::string
ConfigInterface::XdgPath() const
{
  git_buf buf = GIT_BUF_INIT_CONST(nullptr, 0);
  ThrowOnError(git_config_find_xdg(&buf));
  const std::string path{buf.ptr, buf.size};
  git_buf_free(&buf);
  return path;
}

bool
ConfigInterface::ParseBool(const std::string & value) const
{
  int res = 0;
  ThrowOnError(git_config_parse_bool(&res, value.c_str()));
  return res;
}

int32_t
ConfigInterface::ParseInt32(const std::string & value) const
{
  int32_t res = 0;
  ThrowOnError(git_config_parse_int32(&res, value.c_str()));
  return res;
}

int64_t
ConfigInterface::ParseInt64(const std::string & value) const
{
  int64_t res = 0;
  ThrowOnError(git_config_parse_int64(&res, value.c_str()));
  return res;
}

GIT2PPP_NAMESPACE_END
