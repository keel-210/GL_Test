#version 150 core
uniform vec2 size;
uniform vec2 location;
uniform float scale;
in vec4 position;
void main()
{
	gl_Position = vec4(position.xy*2.0*scale/size,position.zw)
	+vec4(location,0.0,0.0);
}