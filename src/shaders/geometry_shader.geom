R"zzz(#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec2[] UV;

out vec2 UV2;

void main()
{
	int n = 0;
	for (n = 0; n < gl_in.length(); n++) {
		UV2 = UV[n];
        gl_Position = gl_in[n].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
	
})zzz"