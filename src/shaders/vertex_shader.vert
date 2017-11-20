R"zzz(#version 330 core

// Input vertex data, different for all executions of this shader.
in vec4 vertex_position;
in vec2 vertex_uv;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

void main(){

    // Output position of the vertex, in clip space : MVP * position
    gl_Position =  vertex_position;

    // UV of the vertex. No special space for this one.
    UV = vertex_uv;
})zzz"