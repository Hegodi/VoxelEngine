#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>

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
"layout (location = 2) in vec2 aTexCoord;\n"
"uniform mat4 transform;\n"
"out vec3 FragPos;\n"
"out vec3 Normal;\n"
"out vec2 TexCoord;\n"
"void main()\n"
"{\n"
"   gl_Position = transform * vec4(aPos, 1.0);\n"
"   Normal = aNormal;\n"
"   FragPos = aPos;\n"
"   TexCoord = aTexCoord;\n" 
"}\0";


const char* default2 = "#version 330 core\n"
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
"uniform sampler2D ourTexture;\n"
"in vec3 FragPos;\n"
"in vec3 Normal;\n"
"in vec2 TexCoord;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   vec3 ambient = light.color * material.ambient;\n"
"   float diff = max(dot(Normal, light.direction), 0.0);\n"
"   vec3 diffuse = light.color * (diff * material.diffuse);\n"
"   // specular \n"
//"   vec3 viewDir = normalize(viewPos - FragPos); \n"
//"   vec3 reflectDir = reflect(-light.direction, Normal);\n"
//"   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);\n"
//"   vec3 specular = light.color * (spec * material.specular);\n"
//"   vec3 result = ambient + diffuse;\n"
//"   vec3 result = ambient + diffuse + specular;\n"
"   FragColor =  texture(ourTexture, TexCoord) * vec4(result, 1.0);\n"
"}\n\0";


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
"uniform sampler2D ourTexture;\n"
"in vec3 FragPos;\n"
"in vec3 Normal;\n"
"in vec2 TexCoord;\n"
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
"   vec3 result = ambient + diffuse;\n"
//"   vec3 result = ambient + diffuse + specular;\n"
"   FragColor =  texture(ourTexture, TexCoord) * vec4(result, 1.0);\n"
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
    glBindTexture(GL_TEXTURE_2D, m_textureId);
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

void CShader::SetTexture(std::string const& path)
{
    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "ERROR: Failed to load texture: " << path << std::endl;
    }
    stbi_image_free(data);
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

void Shaders::Compile()
{
    for (int i = 0; i < (int)EShaderType::COUNT; i++)
    {
        m_shaders[i] = new CShader((EShaderType)i);
    }
    m_compiled = true;
}

CShader* Shaders::GetShader(EShaderType type)
{
    if (!m_compiled)
    {
        std::cout << "ERROR: trying to use a shader which has not been compiled. \n"
                  << "Make sure you call Shaders::Compile() before\n";
        return nullptr;
    }

    return m_shaders[(int)type];
}


std::array<CShader*, (int)EShaderType::COUNT> Shaders::m_shaders;
bool Shaders::m_compiled = false;
