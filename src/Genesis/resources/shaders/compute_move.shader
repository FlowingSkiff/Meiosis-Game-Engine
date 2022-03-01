#version 430 core
#extension GL_ARB_compute_shader: enable
#extension GL_ARB_shader_storage_buffer_object: enable


layout(std140, binding=4) buffer Pos
{
    vec4 Positions[];
};

layout(std140, binding=5) buffer Vel
{
    vec4 Velocities[];
};
layout(std140, binding=6) buffer Col
{
    vec4 Colors[];
};

layout(local_size_x = 128, local_size_y = 1, local_size_z = 1) in;

void main()
{
    const vec3 gravity = vec3(0., -9.8, 0.);
    const float delta_time = 0.1;

    uint gid = gl_GlobalInvocationID.x;

    vec3 p = Positions[gid].xyz;
    vec3 v = Velocities[gid].xyz;

    vec3 pp = p + v * delta_time + 0.5 * delta_time * delta_time * gravity;
    vec3 vp = v + gravity * delta_time;

    Positions[gid].xyz = pp;
    Velocities[gid].xyz = vp;
}