#include "renderer.h"
#include "shader.h"
#include "data.h"
#include "memory.h"

#include <stdbool.h>
#include <stdio.h>

struct GLContext{
    GLuint programID;
    GLuint transformsSBOID;  

    struct Transform transforms[1000];
    unsigned int transformCount, shaderCount; 
    unsigned int shaders[100];
};

static struct GLContext glContext;

GLuint create_shader(int shaderType, const char* shaderPath, MemoryCluster* cluster){
    int fileSize = 0;
    char* headerSource = read_file("src/shader.h", &fileSize, cluster); 
    char* shaderSource = read_file(shaderPath, &fileSize, cluster);

    if(!shaderSource || !headerSource)
        printf("Failed creating shader: %s\n", shaderPath);

    const GLchar* programSource[] = {
        "#version 430 core\r\n",
        headerSource,
        shaderSource
    };

    GLuint shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID, ArraySize(programSource), programSource, 0);
    glCompileShader(shaderID);
    puts("passed");

    int success;
    char shaderLog[2048] = {};

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(shaderID, 2048, 0, shaderLog);
        printf("Failed linking shader: %s", shaderLog);
    }
    puts("passed");

    return shaderID;
}

bool init_gl(MemoryCluster* cluster){
    load_gl_functions();
    
    GLuint vertexShaderID = create_shader(GL_VERTEX_SHADER, "shaders/quad.vert", cluster);
    GLuint fragShaderID = create_shader(GL_FRAGMENT_SHADER, "shaders/quad.frag", cluster);

    if(!vertexShaderID || !fragShaderID){
        puts("failed to create shaders");
        return false;
    }

    unsigned int currentShader = glContext.shaders[glContext.shaderCount];
    glAttachShader(currentShader, vertexShaderID);
    glAttachShader(currentShader, fragShaderID);
    glLinkProgram(currentShader);

    int success;
    char infoLog[512];
    glGetProgramiv(currentShader, GL_LINK_STATUS, &success);

    if(!success){
        glGetProgramInfoLog(currentShader, 512, 0, infoLog);
        printf("Failed to link shader program! %s", infoLog);
        return false;
    }

    glDetachShader(currentShader, vertexShaderID);
    glDetachShader(currentShader, fragShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragShaderID);

    glContext.shaderCount++;


    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &glContext.transformsSBOID);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, glContext.transformsSBOID);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(struct Transform) * 1000, glContext.transforms, GL_DYNAMIC_DRAW);

    printf("past arrays and buffers creation");

    glEnable(GL_FRAMEBUFFER_SRGB);
    glDisable(0x809D);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_GREATER);

    glUseProgram(glContext.shaders[0]);

    printf("past program usage");
    return true;
}
