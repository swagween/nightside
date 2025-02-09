
#pragma once

#include <filesystem>

namespace nightside {

namespace fs = std::filesystem;

class Finder {
  public:
	Finder();
	fs::path find_directory(fs::path const& exe, std::string const& target);
	[[nodiscard]] auto get_resource_path() const -> fs::path { return m_resources; };

  private:
	fs::path m_resources{};
};

} // namespace nightside