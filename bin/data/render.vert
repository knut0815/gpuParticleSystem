#version 150

uniform mat4 modelViewProjectionMatrix;
uniform vec2 resolution;
uniform sampler2DRect currentPos;

in vec4 position;
in vec2 texcoord;

void main() {
    vec4 posFromTexture = texture(currentPos, texcoord);
    
    vec4 modifiedPos = posFromTexture;
    modifiedPos.x *= resolution.x;
    modifiedPos.y *= resolution.y;
    
    gl_Position = modelViewProjectionMatrix * modifiedPos;
}