#version 330 core

uniform sampler2D texture;
uniform vec2 resolution;
uniform float thickness; // Thickness of the diagonal band

void main() {
    vec2 uv = gl_FragCoord.xy / resolution;
    vec4 color = texture2D(texture, uv);

    if (gl_FragCoord.y < -thickness || gl_FragCoord.y > thickness) {
        color.a = 0.0;  // Hide pixels outside the band
    }

    gl_FragColor = color;
}
