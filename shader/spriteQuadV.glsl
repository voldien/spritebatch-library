ATTRIBUTE_IN(0) vec3 vertex;
ATTRIBUTE_IN(1) vec2 uv;
ATTRIBUTE_IN(2) vec4 color;
ATTRIBUTE_IN(3) int tex;

FLAT_OUT int ftexture;
SMOOTH_OUT vec4 fcolor;
SMOOTH_OUT vec2 fuv;

uniform mat3 gmat;

void main(void){
    /*  */
    vec3 screenCoord = vec3(vertex.xy, 1.0);
    gl_Position = vec4((gmat * screenCoord).xy, 1.0, 1.0);

    fuv = uv;
    fcolor = color;
    ftexture = tex;
}