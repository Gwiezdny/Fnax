uniform sampler2D texture;
uniform vec2 resolution;
//uniform float curvature;

float map(float value, float min1, float max1, float min2, float max2) {
  return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

void main()
{
    vec2 uv = gl_TexCoord[0].xy / resolution;
    
    //orginalnie a = -+0.6 / power = 1
    float dist = pow(distance(gl_TexCoord[0].x, resolution.x / 2.0) / resolution.x, 2);
    
    uv.y = map(uv.y, 0, 1, 0.8 * dist, -0.8 * dist + 1);
    //uv.y = uv.y / 2 + 0.5;

    gl_FragColor = texture2D(texture, uv );
}