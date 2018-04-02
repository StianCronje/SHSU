#version 330 core

in vec2 position; 
//in: means that this is some input data
//vertexPosition_modelspace: could be anything else. 
//It will contain the position of the vertex for each run of the vertex shader.

uniform mat4 trans;
void main(){

	//gl_Position is one of the few built-in variables : you have to assign some value to it. 
	//Everything else is optional; we’ll see what “everything else” means later.

    gl_Position = trans*vec4(position,0.0,1.0);
    

}

