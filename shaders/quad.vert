layout (location = 0) out vec2 texCoord;
layout (location = 1) out flat int renderFlags;

layout (std430, binding = 0) buffer TransformSBO{
    Transform transforms[];
};

void main(){
    texCoord = vec2(0, 0);
    gl_Position = vec4(0);
}
