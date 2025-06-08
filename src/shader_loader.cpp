#include "shader_loader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <glad/glad.h>  // Use GLAD instead of GLEW

#if defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

// Helper to get directory where executable lives
std::string getExecutableDir() {
#if defined(__APPLE__)
    char path[1024];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) == 0) {
        auto execPath = std::filesystem::path(path).parent_path();
        auto resourcesPath = execPath / ".." / "Resources";
        return std::filesystem::canonical(resourcesPath).string();
    }
#endif
    return ".";  // fallback for other platforms
}

// Load shader source code from file, including fallback for macOS app bundle
std::string loadShaderSource(const std::string& filename) {
    std::string shaderPath = "shaders/" + filename;
    std::ifstream shaderFile(shaderPath);

    std::cout << "Trying to load shader from: " << shaderPath << std::endl;

    if (!shaderFile.is_open()) {
        shaderPath = "bin/shaders/" + filename;
        std::cout << "Fallback: trying to load shader from: " << shaderPath << std::endl;
        shaderFile.open(shaderPath);
    }

#if defined(__APPLE__)
    if (!shaderFile.is_open()) {
        std::string bundlePath = getExecutableDir() + "/shaders/" + filename;
        std::cout << "macOS .app fallback: trying to load shader from: " << bundlePath << std::endl;
        shaderFile.open(bundlePath);
        shaderPath = bundlePath;
    }
#endif

    if (!shaderFile.is_open()) {
        std::cerr << "Error: Could not open shader file at: " << shaderPath << std::endl;
        return "";
    }

    std::cout << "Shader loaded successfully from: " << shaderPath << std::endl;

    std::stringstream buffer;
    buffer << shaderFile.rdbuf();
    return buffer.str();
}

// Compile shader
GLuint compileShader(GLenum shaderType, const std::string& source) {
    GLuint shader = glCreateShader(shaderType);
    const char* shaderSource = source.c_str();
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        char* log = new char[logLength];
        glGetShaderInfoLog(shader, logLength, nullptr, log);
        std::cerr << "Error compiling shader: " << log << std::endl;
        delete[] log;
    }

    return shader;
}

// Link shader program from vertex and fragment shaders
GLuint createShaderProgramFromFile(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    std::string vertexShaderSource = loadShaderSource(vertexShaderPath);
    std::string fragmentShaderSource = loadShaderSource(fragmentShaderPath);

    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        GLint logLength;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);
        char* log = new char[logLength];
        glGetProgramInfoLog(shaderProgram, logLength, nullptr, log);
        std::cerr << "Error linking shader program: " << log << std::endl;
        delete[] log;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}


