#version 330 core

uniform vec3 framecolor;

// Ouput data
out vec3 color;

void main()
{
	// we set the color of each fragment to red.
	color = framecolor;

}
