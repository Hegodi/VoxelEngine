#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

// Shaders
// TODO: move it to separate files??
const char* unlit_vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aNormal;\n"
"uniform mat4 transform;\n"
"void main()\n"
"{\n"
"   gl_Position = transform * vec4(aPos, 1.0f);\n"
"}\0";


const char* unlit_fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

//////////////////////////////////////////////////////////////////

const char* default_vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aNormal;\n"
"uniform mat4 transform;\n"
"out vec3 FragPos;\n"
"out vec3 Normal;\n"
"void main()\n"
"{\n"
"   gl_Position = transform * vec4(aPos, 1.0);\n"
"   Normal = aNormal;\n"
"   FragPos = aPos;\n"
"}\0";


const char* default_fragmentShaderSource = "#version 330 core\n"
"struct Material {\n"
"    vec3 diffuse;\n"
"    vec3 specular;\n"
"    vec3 ambient;\n"
"    float shininess;\n"
"};\n"
"struct Light {\n"
"    vec3 color;\n"
"    vec3 direction;\n"
"};\n"
"uniform Material material;\n"
"uniform Light light;\n"
"uniform vec3 viewPos;\n"
"in vec3 FragPos;\n"
"in vec3 Normal;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   vec3 ambient = light.color * material.ambient;\n"
"   float diff = max(dot(Normal, light.direction), 0.0);\n"
"   vec3 diffuse = light.color * (diff * material.diffuse);\n"
"   // specular \n"
"   vec3 viewDir = normalize(viewPos - FragPos); \n"
"   vec3 reflectDir = reflect(-light.direction, Normal);\n"
"   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);\n"
"   vec3 specular = light.color * (spec * material.specular);\n"
"   vec3 result = ambient + diffuse + specular;\n"
"   FragColor = vec4(result, 1.0);\n"
"}\n\0";





CShader::CShader() : CShader(EShaderType::Unlit)
{
}

CShader::CShader(EShaderType type)
{
    unsigned int vertexShader = 0;
    unsigned int fragmentShader = 0;

    switch (type)
    {
    case EShaderType::Unlit:
        vertexShader = CompileShader(unlit_vertexShaderSource, GL_VERTEX_SHADER);
        fragmentShader = CompileShader(unlit_fragmentShaderSource, GL_FRAGMENT_SHADER);
        break;
    case EShaderType::Default:
        vertexShader = CompileShader(default_vertexShaderSource, GL_VERTEX_SHADER);
        fragmentShader = CompileShader(default_fragmentShaderSource, GL_FRAGMENT_SHADER);
        break;
    default:
        break;
    }

    m_type = type;

    LinkShaders(vertexShader, fragmentShader);
}

CShader::~CShader()
{
    glDeleteProgram(m_id);
}

void CShader::Use()
{
    glUseProgram(m_id);
}

void CShader::SetBoolean(std::string const& name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
}

void CShader::SetFloat(std::string const& name, float value) const
{
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void CShader::SetInteger(std::string const& name, int value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void CShader::SetMatrix4(std::string const& name, glm::mat4 const& value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void CShader::SetVec3(std::string const& name, glm::vec3 const& value) const
{
    glUniform3f(glGetUniformLocation(m_id, name.c_str()),value.x, value.y, value.z);
}

void CShader::SetVec4(std::string const& name, glm::vec4 const& value) const
{
    glUniform4f(glGetUniformLocation(m_id, name.c_str()),value.x, value.y, value.z, value.w);
}

const char* CShader::ReadShaderProgramFromFile(const char* path)
{
    std::string code;
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        file.open(path);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        code = stream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        return nullptr;
    }
    return code.c_str();
}

unsigned int CShader::CompileShader(const char* code, int type)
{
    int success;
    char infoLog[512];

    // vertex shader
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}

void CShader::LinkShaders(unsigned int vertexShader, unsigned int fragmentShader)
{
    int success;
    char infoLog[512];

    m_id = glCreateProgram();
    glAttachShader(m_id, vertexShader);
    glAttachShader(m_id, fragmentShader);
    glLinkProgram(m_id);
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}
