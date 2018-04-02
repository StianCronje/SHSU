#version 330 core

uniform vec3 framecolor;

// Ouput data
out vec4 color;

void main()
{
	// we set the color of each fragment to red.
	color = vec4(framecolor,1.0);

}
