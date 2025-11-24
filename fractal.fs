#version 330

uniform vec2 resolution;
uniform vec2 c;
uniform vec2 offset;
uniform float zoom;

out vec4 finalColor;

#define MAX_ITERATIONS 300
#define ESCAPE_RADIUS_SQ 16.0

vec3 hsv2rgb(vec3 c) {
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main() {
    vec2 uv = gl_FragCoord.xy / resolution;
    
    float aspect = resolution.x / resolution.y;
    vec2 z = (uv - 0.5) * vec2(aspect, 1.0) * (3.0 / zoom) + offset;
    
    int iter = 0;
    float min_dist_sq = 1000.0;
    
    for (int i = 0; i < MAX_ITERATIONS; i++) {
        float mag_sq = dot(z, z);
        if (mag_sq > ESCAPE_RADIUS_SQ) break;
        
        min_dist_sq = min(min_dist_sq, mag_sq);
        
        float temp_x = z.x * z.x - z.y * z.y + c.x;
        z.y = 2.0 * z.x * z.y + c.y;
        z.x = temp_x;
        
        iter++;
    }
    
    vec3 color = vec3(0.0);
    
    if (iter == MAX_ITERATIONS) {
        float t = sqrt(min_dist_sq);
        float hue = 0.1 + t * 0.5; 
        color = hsv2rgb(vec3(hue, 0.8, clamp(t * 2.5, 0.0, 1.0)));
    } else {
        float log_zn = log(dot(z, z)) / 2.0;
        float nu = log(log_zn / log(2.0)) / log(2.0);
        float smooth_val = float(iter) + 1.0 - nu;
        
        float hue = 0.5 + smooth_val * 0.015;
        color = hsv2rgb(vec3(hue, 0.7, 0.9));
    }
    
    finalColor = vec4(color, 1.0);
}

