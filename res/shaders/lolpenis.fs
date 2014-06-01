#version 330
#define stupdierest 3

uniform vec2 other_vec;
uniform vec2 it_works;
uniform
vec4 blah ;
//uniform vec5 falseo;


void main()
{
	gl_FragColor = vec4((vec3(other_vec, 0.5f)) + vec3(it_works, 0.4f) , 0.23f);
}
