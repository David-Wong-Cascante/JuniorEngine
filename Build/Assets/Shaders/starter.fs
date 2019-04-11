// Author: David Wong
// Email: david.wongcascante@digipen.edu
// Created: 27-Apr-2018
// Last Modified: Jan-22-2019
// File name: starterFS.glsl

#version 430 core
out vec4 color;

in vec2 TexCoords;
in float TextureID;

uniform sampler2DArray diffuse;

void main()
{
	color = texture(diffuse, vec3(TexCoords, TextureID));
}