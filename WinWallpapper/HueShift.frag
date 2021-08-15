uniform sampler2D texture;
uniform float shift;

/*
https://gist.github.com/mairod/a75e7b44f68110e1576d77419d608786

thank you viruseg good hueShift function :)

*/
vec3 hueShift(vec3 color, float hue) {
    const vec3 k = vec3(0.57735, 0.57735, 0.57735);
    float cosAngle = cos(hue);
    return vec3(color * cosAngle + cross(k, color) * sin(hue) + k * dot(k, color) * (1.0 - cosAngle));
}

void main()
{
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    gl_FragColor = vec4(hueShift(pixel, shift), 1.0f);
}