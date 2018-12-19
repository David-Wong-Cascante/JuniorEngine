// Author: David Wong
// Email: david.wongcascante@digipen.edu
// Created: 27-Apr-2018
// Last Modified: Jun-13-2018
// File name: starterFS.glsl

#version 330 core
out vec4 color;

in vec2 TexCoords;

uniform sampler2D diffuse;

void main()
{
	color = texture(diffuse, TexCoords);
	//vec4(0.2, 0.8, 0.2, 1.0);
}