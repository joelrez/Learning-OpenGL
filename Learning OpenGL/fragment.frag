#version 330

in vec3 vCol;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;

void main(){
	FragColor = texture(ourTexture, TexCoord)*vec4(vCol,1.0f);
}