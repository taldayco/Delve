#pragma once

#include <GL/glew.h>
#include <string>

class GLSLProgram {
public:
  GLSLProgram();
  ~GLSLProgram();

  void compileShaders(const std::string &vertexShaderFilePath,
                      const std::string &fragmentShaderFilepath);
  void linkShaders();

  void addAttribute(const std::string &attributeName);

  GLint getUniformLocation(const std::string &uniformName);

  void use();
  void unUse();

private:
  void compileShaders(const std::string &filePath, GLuint id);

  int _numAttributes;

  GLuint _programID;
  GLuint _vertexShaderID;
  GLuint _fragmentShaderID;
};
