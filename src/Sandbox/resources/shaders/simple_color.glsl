#shader-type VERTEX
#version 450 core
layout(location=0)in vec2 a_position;

uniform mat4 u_transform;
uniform mat4 u_view_projection;
uniform vec3 u_color;

out vec3 v_color;

void main()
{
	gl_Position=u_view_projection*u_transform*vec4(a_position,0.,1.);
	v_color=u_color;
}

#shader-type FRAGMENT
#version 450 core
layout(location=0)out vec4 f_color;

in vec3 v_color;

void main()
{
	f_color=vec4(v_color,1.);
}