#version 120

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

uniform mat4 transform;

varying vec2 texCoord0;
varying vec3 normal0;

void main()
{
	texCoord0 = texCoord;
	normal0 = (transform * vec4(normal, 0)).xyz;
	gl_Position = transform * vec4(position, 1.0);
}