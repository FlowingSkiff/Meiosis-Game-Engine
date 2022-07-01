#shader-type VERTEX
#version 330 core
layout(location=0)in vec2 a_position;
layout(location=1)in vec3 a_color;
uniform mat4 u_transform;
uniform mat4 u_view_projection;

out vec3 v_position;
out vec4 v_color;
void main()
{
    v_position=vec3(a_position,1.);
    v_color=vec4(a_color,1.);
    gl_Position=u_view_projection*u_transform*vec4(a_position,0.,1.);
    // gl_Position = vec4(a_position, 0.0, 1.0);
}
#shader-type FRAGMENT
#version 330 core
layout(location=0)out vec4 color;
in vec3 v_position;
in vec4 v_color;

void main()
{
    color=v_color;
}