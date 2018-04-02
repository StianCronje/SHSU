#version 330 core

in vec3 vertexPosition_modelspace; 
//in: means that this is some input data
//vertexPosition_modelspace: could be anything else. 
//It will contain the position of the vertex for each run of the vertex shader.

void main(){

	//gl_Position is one of the few built-in variables : you have to assign some value to it. 
	//Everything else is optional; we’ll see what “everything else” means later.

    gl_Position.xyz = vertexPosition_modelspace;
    gl_Position.w = 1.0; //we will know the 4th coordinates in the next lab (math introduction)

}

