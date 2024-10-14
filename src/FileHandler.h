#pragma once
#include <filesystem>
#include <fstream>
#include <string>

struct FileStreamSuccess
{
  std::ifstream file;
  bool success = false;
};
namespace FileHandler {

bool CheckPath(const std::string &_path) {
  std::filesystem::path path(_path);
  // Check if the path exists and is a regular file (not a directory)
  if (_path.find('/') == std::string::npos) {
    return false;
  }
  if (exists(path) && std::filesystem::is_regular_file(path)) {
    return true;
  }
  return false;
}
//Returns opened file at path
  std::ifstream GetFile(const std::string& _path)
{
  std::ifstream l_fs;
  l_fs.open(_path);
  return l_fs;
}
  
} 
