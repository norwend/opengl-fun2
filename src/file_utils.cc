#include <file_utils.hh>

std::string read_file(const std::string& file_name) {
    std::fstream file(file_name);
    if (!file.good()) {
	std::string err = "Failed opening file " + file_name;
	throw std::runtime_error(err);
	return "";
    }

    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}
