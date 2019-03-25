#pragma once

#include "globals.hpp"
#include "Graphics.hpp"

class SevenSegment {
  public:
    SevenSegment(vec3 pos, GLfloat stroke, GLfloat side, GLuint dig);
    void draw();
    static const GLuint MINUS = 10, BLANK = 11;
    GLuint symbol;
    
  private:
    Rectangle segments[7];
    static const std::vector<int> litSegments[12];
};

class NumericDisplay {
  public:
    NumericDisplay(vec3 pos, GLuint digitCount, GLfloat stroke, GLfloat side, GLint value);
    bool setValue(GLint value);
    void draw();
    GLfloat width, height;

  private:
    std::vector<SevenSegment> digitDisplays;
};
