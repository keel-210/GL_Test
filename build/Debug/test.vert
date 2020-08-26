#version 150 core
uniform vec2 size;
uniform float scale;
in vec4 position;
void main()
{
	gl_Position = vec4(position.xy*2.0*scale/size,position.zw);
}