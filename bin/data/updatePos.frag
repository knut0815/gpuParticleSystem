#version 150

uniform sampler2DRect currentPos;
uniform sampler2DRect currentVel;

in vec2 texcoordVarying;
out vec4 outputColor;

float map(float value, float inputMin, float inputMax, float outputMin, float outputMax) {
    float outVal = ((value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin);
    if(outputMax < outputMin){
        if (outVal < outputMax) {
            outVal = outputMax;
        }
        else if (outVal > outputMin) {
            outVal = outputMin;
        }
    }
    else{
        if (outVal > outputMax) {
            outVal = outputMax;
        }
        else if (outVal < outputMin) {
            outVal = outputMin;
        }
    }
    return outVal;
}

void main() {
    //Get the position and velocity from the corresponding textures
    vec4 posFromTexture = texture(currentPos, texcoordVarying);
    vec4 velFromTexture = texture(currentVel, texcoordVarying);

    //Remap velocity from [0-1] to [-1,1]
    velFromTexture.x = map(velFromTexture.x, 0.0, 1.0, -1.0, 1.0);
    velFromTexture.y = map(velFromTexture.y, 0.0, 1.0, -1.0, 1.0);
    
    //Calculate the new position
    vec4 newPos = posFromTexture + (velFromTexture * 0.005);
    
    outputColor = vec4(newPos.x, newPos.y, 1.0, 1.0);
}