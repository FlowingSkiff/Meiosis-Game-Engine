#include "ComputeShader.hpp"
#include <sstream>
#include <fstream>
#include "Core/Log/Log.hpp"
static constexpr int32_t work_group_size = 128;

void ComputeShader::run()
{
    int compute_start_index = 4;
    for (auto& v : m_compute_objects)
    {
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, compute_start_index++, v->renderer_id);
    }

    // glUseProgram(m_program);

    glDispatchCompute((m_count > work_group_size) ? m_count / work_group_size : 1, 1, 1);

    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

ComputeShader::ComputeShader(const std::string& file_path)
{
    compileShader(file_path);
}

void ComputeShader::compileShader(const std::string& file_path)
{
    std::ifstream file(file_path);
    if (file)
    {
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        m_source = buffer.str();
    }
    else
    {
        ENGINE_WARN("Compiling shader failed, could not open file.");
    }
}