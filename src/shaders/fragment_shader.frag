R"zzz(#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV2;

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform sampler2D texture_sampler;

void main(){

    // Output color = color of the texture at the specified UV
    // color = vec4(0,0,1,1);
	color = vec4(texture( texture_sampler, UV2 ).rgb, 1);
	color = color/256;
})zzz"