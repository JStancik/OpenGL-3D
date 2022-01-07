#version 330 core

out vec4 color;

in vec2 UV;

uniform sampler2D TexSampler;

void main(){
	color = texture(TexSampler, UV);
}