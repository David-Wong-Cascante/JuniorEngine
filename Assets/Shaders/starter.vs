// Author: David Wong
// Email: david.wongcascante@digipen.edu
// Created: 27-Apr-2018
// Last Modified: 2-Nov-2018
// File name: starterVS.glsl

#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in mat4 modelTransform;

out vec2 TexCoords;

uniform mat4 orthographic;

void main()
{
	TexCoords = texCoords;
	gl_Position = orthographic * modelTransform * vec4(pos, 1.0);
	//gl_Position = vec4(pos, 1.0);
	
	//gl_Position = modelTransform * vec4(pos, 1.0);
}