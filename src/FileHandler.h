#pragma once
#include <filesystem>
#include <string>


// returns true if file found at path
namespace FileHandler {

bool CheckPath(const std::string &_path) {
  std::filesystem::path path(_path);
  // Check if the path exists and is a regular file (not a directory)
  if (_path.find(':') == std::string::npos) {
    return false;
  }
  if (exists(path) && std::filesystem::is_regular_file(path)) {
    return true;
  }
  return false;
}
} 
