//-----------------------------------------------------------------------------
// basic.frag by _Edd.ie_
// Fragment shader
//-----------------------------------------------------------------------------
#version 460 core

in vec2 texCoord;       // Input from the basic.vert

uniform sampler2D Texture;  //2D texture

out vec4 fragColor;     // Four-element vector containing RGBA value

void main()
{
    fragColor = texture(Texture, texCoord);
}
