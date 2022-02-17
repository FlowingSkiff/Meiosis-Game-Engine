#shader vertex
#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texCoord;

uniform mat4 u_MVP;
out vec2 v_TexCoord;

void main()
{
    vec4 pos = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    gl_Position = u_MVP * pos;
    v_TexCoord = texCoord;
};

#shader fragment
#version 410 core

layout(location = 0) out vec4 FragColor;

in vec2 v_TexCoord;
uniform sampler2D u_Texture;

void main()
{
  vec4 texColor = texture(u_Texture, v_TexCoord);
  FragColor = texColor;
}