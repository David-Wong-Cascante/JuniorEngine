// Author: David Wong
// Email: david.wongcascante@digipen.edu
// Created: 27-Apr-2018
// Last Modified: 14-Feb-2019
// File name: starterVS.glsl

#version 430 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in mat4 modelTransform;
// Texture coordinate modifications where (x,y) are translations and (z,w) are scale in x and y axes
layout (location = 6) in vec4 texCoordModif;
layout (location = 7) in float textureID;

out vec2 TexCoords;
out float TextureID;
uniform mat4 camera;

void main()
{
	TexCoords = texCoords;
	TexCoords.x *= texCoordModif.z;
	TexCoords.y *= texCoordModif.w;
	TexCoords += texCoordModif.xy;
	TextureID = textureID;
	gl_Position = camera * modelTransform * vec4(pos, 1.0);
}