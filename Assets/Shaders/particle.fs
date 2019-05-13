// Author: David Wong
// Email: david.wongcascante@digipen.edu
// Created: May 10 2019
// Last Modified: May 10 2019
// File name: particleFS.fs

#version 430 core

// In Variables
in vec2 TexCoords;
in vec4 color;
in flat uint TextureAtlas;

// Uniforms
uniform sampler2DArray diffuse;

// Out Variables
out vec4 outColor;

void main()
{
	outColor = mix(texture(diffuse, vec3(TexCoords, TextureAtlas)), color, 0.5);
	//outColor = color;
}