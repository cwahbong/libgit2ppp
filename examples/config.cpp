#include <iostream>

#include <git2ppp/config.hpp>
#include <git2ppp/library.hpp>
#include <git2ppp/repository.hpp>


int main(int argc, char ** argv)
{
  if (argc != 2) {
    std::cerr << "Path invalid." << std::endl;
    return -1;
  }

  std::cout << argv[1] << std::endl;

  if (git2ppp::Library::Get().HasError()) {
    std::cerr << "Library initialize error." << std::endl;
    return -1;
  }

  const auto & ri = git2ppp::RepositoryInterface::Get();
  auto repository = ri.Open(argv[1]);
  if (repository.HasError()) {
    std::cerr << "Repository open error." << std::endl;
    return -1;
  }

  auto config = repository.GetConfig();
  if (config.HasError()) {
    std::cerr << "Config error." << std::endl;
    return -1;
  }
  config.ForEach(
    [](std::string && name, std::string && value) {
      std::cout << "name = " << name << ", value = " << value << "." << std::endl;
      return true;
    });
}
