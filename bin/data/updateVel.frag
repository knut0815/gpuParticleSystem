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
    vec4 posFromTexture = texture(currentPos, texcoordVarying);
    vec4 velFromTexture = texture(currentVel, texcoordVarying);
    
    vec4 newPos = posFromTexture + (velFromTexture * 0.005);
    
    //Keep the particle within the bounds of the window
//    if ( newPos.x < 0.0)
//        velFromTexture.x = map(-1.0 * currentVelX, -1.0, 1.0, 0.0, 1.0); //0.5 * abs(velFromTexture.x);
//    if ( newPos.x > 1.0)
//        velFromTexture.x = map(-1.0 * velFromTexture.x, -1.0, 1.0, 0.0, 1.0);//-0.5 * abs(velFromTexture.x);
//    if (newPos.y < 0.0)
//        velFromTexture.y = map(-1.0 * velFromTexture.y, -1.0, 1.0, 0.0, 1.0);//0.5 * abs(velFromTexture.y);
//    if ( newPos.y > 1.0)
//        velFromTexture.y = map(-1.0 * velFromTexture.y, -1.0, 1.0, 0.0, 1.0);//-0.5 * abs(velFromTexture.y);
    
    outputColor = vec4(velFromTexture.x, velFromTexture.y, 0.0, 1.0);
}