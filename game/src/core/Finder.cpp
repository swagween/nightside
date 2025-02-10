#include "nightside/core/Finder.hpp"
#include <iostream>

namespace nightside {

nightside::Finder::Finder() { m_resources = find_directory(fs::current_path(), "resources"); }

fs::path Finder::find_directory(fs::path const& exe, std::string const& target) {
	auto execpy = fs::path{exe};
	auto check = [target](fs::path const& prefix) {
		auto path = prefix / target;
		if (fs::is_directory(path)) { return path; }
		return fs::path{};
	};
	while (!execpy.empty()) {
		if (auto ret = check(execpy); !ret.empty()) { return ret; }
		auto parent = execpy.parent_path();
		if (execpy == parent) { break; }
		execpy = std::move(parent);
	}
	return {};
}

} // namespace nightside