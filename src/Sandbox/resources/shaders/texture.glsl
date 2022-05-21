#shader-type VERTEX
#version 450 core
layout(location=0)in vec2 a_position;
layout(location=1)in uint a_texture_id;
layout(location=2)in vec2 a_texture_coord;

uniform mat4 u_transform;
uniform mat4 u_view_projection;

layout(location=0)out vec2 v_texture_coord;
layout(location=1)out flat uint v_texture_id;

void main()
{
	gl_Position=u_view_projection*u_transform*vec4(a_position,0.,1.);
	v_texture_coord=a_texture_coord;
	v_texture_id=a_texture_id;
}

#shader-type FRAGMENT
#version 450 core
layout(location=0)out vec4 f_color;

layout(location=0)in vec2 v_texture_coord;
layout(location=1)in flat uint v_texture_id;
layout(binding=0)uniform sampler2D u_texture[32];

void main()
{
	// f_color=vec4(texture(u_texture[0],v_texture_coord).r,texture(u_texture[1],v_texture_coord).r,texture(u_texture[2],v_texture_coord).r,1.);
	vec4 color=texture(u_texture[0],v_texture_coord);
	f_color=color;
}