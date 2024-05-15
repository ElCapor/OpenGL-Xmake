#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP
#include <filesystem>
#include "FilesystemUtils.hpp"
namespace fs = std::filesystem;
class ResourceManager
{
public:
    ResourceManager() : m_ResourcesPath(fsutils::executableDirectory().concat("\\resources")) {}
    fs::path ResourcesPath() {return m_ResourcesPath;}
    fs::path DataPath() {return ResourcesPath().concat("\\data");}
    fs::path ShadersPath() {return ResourcesPath().concat("\\shaders");}

private:
    fs::path m_ResourcesPath;
};

#endif /* RESOURCEMANAGER_HPP */
