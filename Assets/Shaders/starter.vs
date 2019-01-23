// Author: David Wong
// Email: david.wongcascante@digipen.edu
// Created: 27-Apr-2018
// Last Modified: 22-Jan-2019
// File name: starterVS.glsl

#version 430 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in mat4 modelTransform;
layout (location = 6) in float textureID;

out vec2 TexCoords;
out float TextureID;
uniform mat4 orthographic;

void main()
{
	TexCoords = texCoords;
	TextureID = textureID;
	gl_Position = orthographic * modelTransform * vec4(pos, 1.0);
}