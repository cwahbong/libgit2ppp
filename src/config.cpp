#include "config.hpp"

#include "git2ppp/library.hpp"

#include "memory.hpp"

#include <git2/buffer.h>
#include <git2/config.h>
#include <git2/errors.h>

GIT2PPP_NAMESPACE_BEGIN

namespace {

int
EntryFunctionCallback(const git_config_entry * pEntry, void * pPayload)
{
  auto * pRealCallback = reinterpret_cast<Config::EntryCallbackType *>(pPayload);
  if (!(*pRealCallback)(pEntry->name, pEntry->value)) {
    return GIT_EUSER;
  }
  return 0;
}

} // namespace

Config::Config(std::unique_ptr<Member> && m) noexcept:
  m_{std::move(m)}
{/* Empty. */}

Config::Config(Config &&) noexcept = default;

Config::~Config() = default;

Config &
Config::operator=(Config && rhs) noexcept
{
  if (this != &rhs) {
    this->m_ = std::move(rhs.m_);
  }
  return *this;
}

Git2Error
Config::Set(const std::string & name, const std::string & value) noexcept
{
  return git_config_set_string(m_->pConfig, name.c_str(), value.c_str());
}

Git2Error
Config::SetBool(const std::string & name, bool value) noexcept
{
  return git_config_set_bool(m_->pConfig, name.c_str(), value);
}

Git2Error
Config::SetInt32(const std::string & name, int32_t value) noexcept
{
  return git_config_set_int32(m_->pConfig, name.c_str(), value);
}

Git2Error
Config::SetInt64(const std::string & name, int64_t value) noexcept
{
  return git_config_set_int64(m_->pConfig, name.c_str(), value);
}

Git2Error
Config::SetMultiVar(const std::string & name, const std::string & old_value_regexp, const std::string & value) noexcept
{
  return git_config_set_multivar(m_->pConfig, name.c_str(), old_value_regexp.c_str(), value.c_str());
}

std::pair<Git2Error, std::string>
Config::Get(const std::string & name) const noexcept
{
  const char * value = nullptr;
  const Git2Error ret = git_config_get_string(&value, m_->pConfig, name.c_str());
  if (ret < 0) {
    return std::make_pair(ret, "");
  }
  return std::make_pair(ret, std::string(value));
}

std::pair<Git2Error, bool>
Config::GetBool(const std::string & name) const noexcept
{
  int value = 0;
  const Git2Error ret = git_config_get_bool(&value, m_->pConfig, name.c_str());
  return std::make_pair(ret, value);
}

std::pair<Git2Error, int32_t>
Config::GetInt32(const std::string & name) const noexcept
{
  int32_t value = 0;
  const Git2Error ret = git_config_get_int32(&value, m_->pConfig, name.c_str());
  return std::make_pair(ret, value);
}

std::pair<Git2Error, int64_t>
Config::GetInt64(const std::string & name) const noexcept
{
  int64_t value = 0;
  const Git2Error ret = git_config_get_int64(&value, m_->pConfig, name.c_str());
  return std::make_pair(ret, value);
}

Git2Error
Config::GetMultiVarForEach(const std::string & name, const std::string & regexp, EntryCallbackType callback) const noexcept
{
  return git_config_get_multivar_foreach(m_->pConfig, name.c_str(), regexp.c_str(), EntryFunctionCallback, static_cast<void *>(&callback));
}

Git2Error
Config::Delete(const std::string & name) noexcept
{
  return git_config_delete_entry(m_->pConfig, name.c_str());
}

Git2Error
Config::DeleteMultiVar(const std::string & name, const std::string & value_regexp) noexcept
{
  return git_config_delete_multivar(m_->pConfig, name.c_str(), value_regexp.c_str());
}


Git2Error
Config::ForEach(std::function<bool(std::string &&, std::string &&)> callback) noexcept
{
  return git_config_foreach(m_->pConfig, EntryFunctionCallback, static_cast<void *>(&callback));
}

Git2Error
Config::ForEachMatch(const std::string & regexp, EntryCallbackType callback) noexcept
{
  return git_config_foreach_match(m_->pConfig, regexp.c_str(), EntryFunctionCallback, static_cast<void *>(&callback));
}

std::pair<Git2Error, Config>
Config::OpenLevel(int level) const noexcept
{
  git_config * pConfig = nullptr;
  const int ret = git_config_open_level(&pConfig, m_->pConfig, static_cast<git_config_level_t>(level));
  return std::make_pair(ret, Wrap<Config, git_config>(pConfig));
}

std::pair<Git2Error, Config>
Config::OpenGlobal() const noexcept
{
  git_config * pConfig = nullptr;
  const int ret = git_config_open_global(&pConfig, m_->pConfig);
  return std::make_pair(ret, Wrap<Config, git_config>(pConfig));
}

std::pair<Git2Error, Config>
Config::Snapshot() const noexcept
{
  git_config * pSnapshot = nullptr;
  const int ret = git_config_snapshot(&pSnapshot, m_->pConfig);
  return std::make_pair(ret, Wrap<Config, git_config>(pSnapshot));
}

ConfigInterface::ConfigInterface(const Library & library) noexcept:
  Interface(library)
{/* Empty. */}

ConfigInterface::~ConfigInterface()
{/* Empty. */}

const ConfigInterface &
ConfigInterface::Get() noexcept
{
  thread_local const ConfigInterface interface(Library::Get());
  return interface;
}

std::pair<Git2Error, Config>
ConfigInterface::OpenDefault() const noexcept
{
  git_config * pConfig = nullptr;
  const int ret = git_config_open_default(&pConfig);
  return std::make_pair(ret, Wrap<Config, git_config>(pConfig));
}

std::pair<Git2Error, Config>
ConfigInterface::Open(const std::string & path) const noexcept
{
  git_config * pConfig = nullptr;
  const int ret = git_config_open_ondisk(&pConfig, path.c_str());
  return std::make_pair(ret, Wrap<Config, git_config>(pConfig));
}

std::pair<Git2Error, std::string>
ConfigInterface::GlobalPath() const noexcept
{
  git_buf buf = GIT_BUF_INIT_CONST(nullptr, 0);
  const int ret = git_config_find_global(&buf);
  const std::string path{buf.ptr, buf.size};
  git_buf_free(&buf);
  return std::make_pair(ret, path);
}

std::pair<Git2Error, std::string>
ConfigInterface::SystemPath() const noexcept
{
  git_buf buf = GIT_BUF_INIT_CONST(nullptr, 0);
  const int ret = git_config_find_system(&buf);
  const std::string path{buf.ptr, buf.size};
  git_buf_free(&buf);
  return std::make_pair(ret, path);
}

std::pair<Git2Error, std::string>
ConfigInterface::XdgPath() const noexcept
{
  git_buf buf = GIT_BUF_INIT_CONST(nullptr, 0);
  const int ret = git_config_find_xdg(&buf);
  const std::string path{buf.ptr, buf.size};
  git_buf_free(&buf);
  return std::make_pair(ret, path);
}

std::pair<Git2Error, bool>
ConfigInterface::ParseBool(const std::string & value) const noexcept
{
  int res = 0;
  const int ret = git_config_parse_bool(&res, value.c_str());
  return std::make_pair(ret, res);
}

std::pair<Git2Error, int32_t>
ConfigInterface::ParseInt32(const std::string & value) const noexcept
{
  int32_t res = 0;
  const int ret = git_config_parse_int32(&res, value.c_str());
  return std::make_pair(ret, res);
}

std::pair<Git2Error, int64_t>
ConfigInterface::ParseInt64(const std::string & value) const noexcept
{
  int64_t res = 0;
  const int ret = git_config_parse_int64(&res, value.c_str());
  return std::make_pair(ret, res);
}

GIT2PPP_NAMESPACE_END
