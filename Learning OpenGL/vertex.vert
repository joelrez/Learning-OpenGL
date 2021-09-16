#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec2 TexCoord;

void main(){
	gl_Position = projection*view*model*vec4(pos, 1.0f);
	TexCoord = aTexCoord;
}