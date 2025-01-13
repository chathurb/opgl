#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

uniform float u_Time;

out vec2 v_TexCoord;

void main()
{
   float modTime = mod(u_Time, 60.0f);
   float theta = modTime / 60.0f * 2.0f * 3.14159f;

   gl_Position = position;
   gl_Position.x = position.x * cos(theta) + position.y * sin(theta);
   gl_Position.y = position.y * cos(theta) - position.x * sin(theta);
   v_TexCoord = texCoord;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
   vec4 texColor = texture(u_Texture, v_TexCoord);
   float gradient = gl_FragCoord.y / 480.0f;
   color = mix(u_Color, vec4(0.0f, 0.0f, 0.0f, 0.0f), gradient);
}