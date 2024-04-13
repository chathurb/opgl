#include "shader.h"

#include "utils.h"

#include <iostream>
#include <fstream>
#include <sstream>

shader::shader(const std::string& filepath)
    : m_filepath(filepath), m_renderedID(0)
{
    ShaderProgramSource source = ParseShader(filepath);
    m_renderedID = CreateShader(source.VertexSource, source.FragmentSource);
}

shader::~shader()
{
    GLCall(glDeleteProgram(m_renderedID));
}

void shader::Bind() const
{
    GLCall(glUseProgram(m_renderedID));
}

void shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void shader::SetUniform1i(const std::string& name, int i)
{
    GLCall(glUniform1i(GetUniformLocation(name), i));
}

void shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

unsigned int shader::GetUniformLocation(const std::string& name)
{
    if(m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];
    
    GLCall(int location = glGetUniformLocation(m_renderedID, name.c_str()));
    if(location == -1)
        std::cout << "Error : uniform '" << name <<"' does not exist" << std::endl;
    else
        m_uniformLocationCache[name] = location;
    
    return location;
}

ShaderProgramSource shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while(getline(stream, line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if(result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));

        std::cout << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
            << "shader compile failure";
        std::cout << message << std::endl;

        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}
