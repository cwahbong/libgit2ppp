#include "git2ppp/config.hpp"

#include "git2ppp/exception.hpp"
#include "git2ppp/library.hpp"

#include "config_impl.hpp"

#include <git2/buffer.h>
#include <git2/config.h>

GIT2PPP_NAMESPACE_BEGIN

Config::Config(ConfigImpl * pImpl):
  m_pImpl{pImpl}
{/* Empty. */}

Config::~Config()
{/* Empty. */}

void
Config::Set(const std::string & name, const std::string & value)
{
  m_pImpl->Set(name, value);
}

void
Config::SetBool(const std::string & name, bool value)
{
  m_pImpl->SetBool(name, value);
}

void
Config::SetInt32(const std::string & name, int32_t value)
{
  m_pImpl->SetInt32(name, value);
}

void
Config::SetInt64(const std::string & name, int64_t value)
{
  m_pImpl->SetInt64(name, value);
}

void
Config::SetMultiVar(const std::string & name, const std::string & old_value_regexp, const std::string & value)
{
  m_pImpl->SetMultiVar(name, old_value_regexp, value);
}

std::string
Config::Get(const std::string & name) const
{
  return m_pImpl->Get(name);
}

bool
Config::GetBool(const std::string & name) const
{
  return m_pImpl->GetBool(name);
}

int32_t
Config::GetInt32(const std::string & name) const
{
  return m_pImpl->GetInt32(name);
}

int64_t
Config::GetInt64(const std::string & name) const
{
  return m_pImpl->GetInt64(name);
}

void
Config::Delete(const std::string & name)
{
  m_pImpl->Delete(name);
}

void
Config::DeleteMultiVar(const std::string & name, const std::string & value_regexp)
{
  m_pImpl->DeleteMultiVar(name, value_regexp);
}

std::unique_ptr<Config>
Config::OpenLevel(int level) const
{
  return m_pImpl->OpenLevel(level);
}

std::unique_ptr<Config>
Config::Snapshot() const
{
  return m_pImpl->Snapshot();
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
  return std::unique_ptr<Config>{new Config{new ConfigImpl{pConfig}}};
}

std::unique_ptr<Config>
ConfigInterface::Open(const std::string & path) const
{
  git_config * pConfig = nullptr;
  ThrowOnError(git_config_open_ondisk(&pConfig, path.c_str()));
  return std::unique_ptr<Config>{new Config{new ConfigImpl{pConfig}}};
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
