// Author: David Wong
// Email: david.wongcascante@digipen.edu
// Created: 10 May 2019
// Last Modified: 14 May 2019
// File name: particleFS.fs

#version 430 core

// In Variables
in vec2 TexCoords;
in vec4 color;
in flat int TextureAtlas;

// Uniforms
uniform sampler2DArray diffuse;

// Out Variables
out vec4 outColor;

void main()
{
	outColor = mix(texture(diffuse, vec3(TexCoords, TextureAtlas)), color, 0.5);
	//outColor = color;
}