#version 330

in vec2 fragTexCoord;
in vec4 fragColor;
out vec4 finalColor;

uniform sampler2D texture0;
uniform vec2 resolution;
uniform vec2 dir;
uniform float radius;

void main() {
    vec4 sum = vec4(0.0);
    vec2 tc = fragTexCoord;
    
    // Calcul de l'écart (blur offset)
    vec2 blur = vec2(radius) / resolution; 

    // Poids gaussiens (9-tap)
    sum += texture(texture0, tc - 4.0 * blur * dir) * 0.0162162162;
    sum += texture(texture0, tc - 3.0 * blur * dir) * 0.0540540541;
    sum += texture(texture0, tc - 2.0 * blur * dir) * 0.1216216216;
    sum += texture(texture0, tc - 1.0 * blur * dir) * 0.1945945946;
    sum += texture(texture0, tc) * 0.2270270270;
    sum += texture(texture0, tc + 1.0 * blur * dir) * 0.1945945946;
    sum += texture(texture0, tc + 2.0 * blur * dir) * 0.1216216216;
    sum += texture(texture0, tc + 3.0 * blur * dir) * 0.0540540541;
    sum += texture(texture0, tc + 4.0 * blur * dir) * 0.0162162162;

    finalColor = sum * fragColor;
}