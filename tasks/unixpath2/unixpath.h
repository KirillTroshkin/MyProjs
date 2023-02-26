#pragma once

#include <string>
#include <string_view>
#include <vector>

class UnixPath {
public:
    explicit UnixPath(std::string_view initial_dir);

    void ChangeDirectory(std::string_view path);

    std::string GetAbsolutePath() const;
    std::string GetRelativePath() const;

private:
    std::vector<std::string_view> current_dir_;
    std::vector<std::string_view> start_path_;
    std::vector<std::string_view> Splitted(std::string_view s) const;
    std::string NormalizePath(std::vector<std::string_view> path) const;
};
