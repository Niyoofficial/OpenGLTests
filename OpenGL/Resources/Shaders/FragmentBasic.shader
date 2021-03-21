#version 330
layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform bool u_IsTexture;
uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    if (u_IsTexture)
    {
        color = texColor;
    }
    else
    {
        color = u_Color;
    }
}