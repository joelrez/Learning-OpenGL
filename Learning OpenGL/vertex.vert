#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;

out vec3 vCol;
out vec2 TexCoord;

void main(){
	gl_Position = model*vec4(pos, 1.0f);
	vCol = col;
	TexCoord = aTexCoord;
}