// Author: David Wong
// Email: david.wongcascante@digipen.edu
// Created: 27-Apr-2018
// Last Modified: Jun-13-2018
// File name: starterFS.glsl

#version 430 core
out vec4 color;

in vec2 TexCoords;

uniform sampler2DArray diffuse;

void main()
{
	int layer = 0;
	color = texture(diffuse, vec3(TexCoords, layer));
}