#pragma once

#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
    std::string VertexSource, FragmentSource;
};

class shader
{
private:
    unsigned int m_renderedID;
    std::string m_filepath;
    std::unordered_map<std::string, int> m_uniformLocationCache;

public:
    shader(const std::string& filepath);
    ~shader();

    void Bind() const;
    void Unbind() const;

    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
    unsigned int GetUniformLocation(const std::string& name);
    ShaderProgramSource shader::ParseShader(const std::string& filepath);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    unsigned int CompileShader(unsigned int type, const std::string& source);
};