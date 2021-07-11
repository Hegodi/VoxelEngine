#pragma once
#include <string>
#include <array>
#include "glm/glm.hpp"

enum class EShaderType
{
	Unlit,
    Default,
	COUNT
};

class CShader 
{
public:
	CShader();
	CShader(EShaderType type);
	~CShader();
	void Use();
	void SetBoolean(std::string const& name, bool value) const;
	void SetFloat(std::string const& name, float value) const;
	void SetInteger(std::string const& name, int value) const;
	void SetMatrix4(std::string const& name, glm::mat4 const& value) const;
	void SetVec3(std::string const& name, glm::vec3 const& value) const;
	void SetVec4(std::string const& name, glm::vec4 const& value) const;
	void SetTexture(std::string const& path);
	EShaderType GetType() const { return m_type; }

private:
	const char* ReadShaderProgramFromFile(const char* path);
	unsigned int CompileShader(const char* code, int type);
	void LinkShaders(unsigned int vertex, unsigned int fragment);

private:
	EShaderType m_type;
	unsigned int m_id = 0;
	unsigned int m_textureId = 0;
};


class Shaders
{
public:
	static void Compile();
	static CShader* GetShader(EShaderType type);

private:
	static std::array<CShader*, (int)EShaderType::COUNT> m_shaders;
	static bool m_compiled;
};
