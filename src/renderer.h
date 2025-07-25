#pragma once

#include <GL/gl.h>
#include "shader.h"
#include "platform.h"

#include <stdio.h>

static PFNGLATTACHSHADERPROC glAttachShader_ptr;
static PFNGLLINKPROGRAMPROC glLinkProgram_ptr;
static PFNGLGETPROGRAMIVPROC glGetProgramiv_ptr;
static PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog_ptr;
static PFNGLDETACHSHADERPROC glDetachShader_ptr;
static PFNGLDELETESHADERPROC glDeleteShader_ptr;
static PFNGLUSEPROGRAMPROC glUseProgram_ptr;

static PFNGLCREATESHADERPROC glCreateShader_ptr;
static PFNGLSHADERSOURCEPROC glShaderSource_ptr;
static PFNGLCOMPILESHADERPROC glCompileShader_ptr;
static PFNGLGETSHADERIVPROC glGetShaderiv_ptr;
static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog_ptr;

static PFNGLGENVERTEXARRAYSPROC glGenVertexArrays_ptr;
static PFNGLBINDVERTEXARRAYPROC glBindVertexArray_ptr;
static PFNGLGENBUFFERSPROC glGenBuffers_ptr;
static PFNGLBINDBUFFERBASEPROC glBindBufferBase_ptr;
static PFNGLBUFFERDATAPROC glBufferData_ptr;

void load_gl_functions(){
    glAttachShader_ptr = (PFNGLATTACHSHADERPROC)load_gl_function("glAttachShader");
    glLinkProgram_ptr = (PFNGLLINKPROGRAMPROC)load_gl_function("glLinkProgram");
    glGetProgramiv_ptr = (PFNGLGETPROGRAMIVPROC)load_gl_function("glGetProgamiv");
    glGetProgramInfoLog_ptr = (PFNGLGETPROGRAMINFOLOGPROC)load_gl_function("glGetProgramInfoLog");
    glDetachShader_ptr = (PFNGLDETACHSHADERPROC)load_gl_function("glDetachShader");
    glDeleteShader_ptr = (PFNGLDELETESHADERPROC)load_gl_function("glDeleteShader");
    glUseProgram_ptr = (PFNGLUSEPROGRAMPROC)load_gl_function("glUseProgram");

    glCreateShader_ptr = (PFNGLCREATESHADERPROC)load_gl_function("glCreateShader");
    glShaderSource_ptr = (PFNGLSHADERSOURCEPROC)load_gl_function("glShaderSource");
    glCompileShader_ptr = (PFNGLCOMPILESHADERPROC)load_gl_function("glCompileShader");
    glGetShaderiv_ptr = (PFNGLGETSHADERIVPROC)load_gl_function("glGetShaderiv");
    glGetShaderInfoLog_ptr = (PFNGLGETSHADERINFOLOGPROC)load_gl_function("glGetShaderInfoLog");

    glGenVertexArrays_ptr = (PFNGLGENVERTEXARRAYSPROC)load_gl_function("glGenVertexArrays");
    glBindVertexArray_ptr = (PFNGLBINDVERTEXARRAYPROC)load_gl_function("glBindVertexArray");
    glGenBuffers_ptr = (PFNGLGENBUFFERSPROC)load_gl_function("glGenBuffers");
    glBindBufferBase_ptr = (PFNGLBINDBUFFERBASEPROC)load_gl_function("glBindBufferBase");
    glBufferData_ptr = (PFNGLBUFFERDATAPROC)load_gl_function("glBufferData");
}

GLAPI void APIENTRY glAttachShader(GLuint program, GLuint shader){
    return glAttachShader_ptr(program, shader);
}

GLAPI void APIENTRY glLinkProgram(GLuint program){
    return glLinkProgram_ptr(program);
}

GLAPI void APIENTRY glGetProgramiv(GLuint program, GLenum pname, GLint *params){
    return glGetProgramiv(program, pname, params);
}

GLAPI void APIENTRY glGetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei *length, GLchar *infoLog){
    return glGetProgramInfoLog_ptr(program, maxLength, length, infoLog);
}

GLAPI void APIENTRY glDetachShader(GLuint program, GLuint shader){
    return glDetachShader_ptr(program, shader);
}

GLAPI void APIENTRY glDeleteShader(GLuint shader){
    return glDeleteShader_ptr(shader);
}

GLAPI void APIENTRY glGenVertexArrays(GLsizei n, GLuint *arrays){
    return glGenVertexArrays_ptr(n, arrays);
}

GLAPI void APIENTRY glBindVertexArray(GLuint array){
    return glBindVertexArray_ptr(array);
}

GLAPI void APIENTRY glGenBuffers(GLsizei n, GLuint *buffers){
    return glGenBuffers_ptr(n, buffers);
}

GLAPI void APIENTRY glBindBufferBase(GLenum target, GLuint index, GLuint buffer){
    return glBindBufferBase_ptr(target, index, buffer);
}

GLAPI void APIENTRY glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage){
    return glBufferData_ptr(target, size, data, usage);
}

GLAPI void APIENTRY glUseProgram(GLuint program){
    return glUseProgram_ptr(program);
}

GLAPI GLuint APIENTRY glCreateShader(GLenum shaderType){
    return glCreateShader_ptr(shaderType);
}

GLAPI void APIENTRY glShaderSource(GLuint shader, GLsizei count, const GLchar** strings, const GLint *length){
    return glShaderSource_ptr(shader, count, strings, length);
}

GLAPI void APIENTRY glCompileShader(GLuint shader){
    return glCompileShader_ptr(shader);
}

GLAPI void APIENTRY glGetShaderiv(GLuint shader, GLenum pname, GLint* params){
    return glGetShaderiv_ptr(shader, pname, params);
}

GLAPI void APIENTRY glGetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei* size, GLchar* infoLog){
    return glGetShaderInfoLog_ptr(shader, maxLength, size, infoLog);
}
