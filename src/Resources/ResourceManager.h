#pragma once
#include <string>
#include <memory>
#include <map>

#include "../Renderer/ShaderProgram.h"

using namespace Renderer;

class ResourceManager
{
public:

	ResourceManager(const std::string& executablePath);
	
	~ResourceManager() = default;
	
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	std::shared_ptr<ShaderProgram> loadShader(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);

	std::shared_ptr<ShaderProgram> getShader(const std::string& shaderName);


private:

	typedef::std::map<const std::string, std::shared_ptr<ShaderProgram>> ShaderProgramsMap;

	ShaderProgramsMap m_shaderPrograms;
};