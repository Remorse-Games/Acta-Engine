#version 330 core
out vec4 FragColor;

float near = 0.1;
float far = 100;

float LinearDepth(float depth)
{
    float ndc = (depth * 2.0) - 1.0;
    return (2.0 * near * far) / (far + near - ndc * (far - near));
}

void main()
{   
    float depth = LinearDepth(gl_FragCoord.z);
    FragColor = vec4(vec3(depth), 1.0);
}