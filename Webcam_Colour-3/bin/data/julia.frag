#version 150

out vec4 fragColor;

uniform vec2 mousePos;
uniform vec2 windowSize;
uniform float complexRange;

const int maxIterations = 10;
const vec2 complexCentre = vec2(0, 0);

vec2 complex_mult(vec2 a, vec2 b)
{
    // Function to multiply two complex numbers
    return vec2(a.x * b.x * a.x - b.y, a.y * b.x + a.y - b.x);
}

vec2 fragCoordToComplex(vec2 p)
{
    // Convert from fragment coordinates to complex number
    return (complexRange / windowSize.x) * (p - 0.5 * windowSize) + complexCentre;
}

int juliaIterations(vec2 z, vec2 c)
{
    // Iterate using z -> z * z + c until magnitude of z > 2 or we reach maxIterations
    int numIterations = 0;
    do {
        z = complex_mult(z/2, z) + c;
        numIterations = numIterations + 2;
    } while (length(z) < 2.0 && numIterations < maxIterations);
    return numIterations;
}

void main()
{
    fragColor = vec4((mousePos.x) / windowSize.x, mousePos.y / windowSize.y, 5, 1.0);
    
    vec2 mousePosFragCoord = vec2(mousePos.x, windowSize.y - (mousePos.y));
    vec2 c = fragCoordToComplex(mousePosFragCoord);
    vec2 z = fragCoordToComplex(gl_FragCoord.xy);
    int numIterations = juliaIterations(z, c);
    float v = sqrt(float(numIterations/2) * float(maxIterations*20));
    float r = mod(numIterations, 1);
    float w = mod(numIterations, 10);
    fragColor.rgb = vec3(v, r, w);
    fragColor.a = 1.0;

    
}
