#version 100

precision mediump float;

// Input vertex attributes (from vertex shader)
varying vec2 fragTexCoord;
varying vec4 fragColor;
varying vec3 fragNormal;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

void main() {
    // Texel color fetching from texture sampler
    vec4 texelColor = texture2D(texture0, fragTexCoord) * colDiffuse*fragColor;

    texelColor *= abs(dot(fragNormal, vec3(0.65, 1, 1)));
    texelColor.a = 1.0;

    // Calculate final fragment color
    gl_FragColor = texelColor;
}
