#line 1
FRAGLOCATION(0, vec4, fragColor);

FLAT_IN int ftexture;
SMOOTH_IN vec4 fcolor;
SMOOTH_IN vec2 fuv;

/*  Sprite textures.    */
#ifdef gl_MaxTextureImageUnits
uniform sampler2D textures[gl_MaxTextureImageUnits];
#else
uniform sampler2D textures[16];
#endif


vec4 gettextfrag(const in int index, const in vec2 uv){
    #if __VERSION__ < 410
    switch(index) {
        case 0:
        return texture(textures[0], uv);
        case 1:
        return texture(textures[1], uv);
        case 2:
        return texture(textures[2], uv);
        case 3:
        return texture(textures[3], uv);
        case 4:
        return texture(textures[4], uv);
        case 5:
        return texture(textures[5], uv);
        case 6:
        return texture(textures[6], uv);
        case 7:
        return texture(textures[7], uv);
        case 8:
        return texture(textures[8], uv);
        case 9:
        return texture(textures[9], uv);
        case 10:
        return texture(textures[10], uv);
        case 11:
        return texture(textures[11], uv);
        case 12:
        return texture(textures[12], uv);
        case 13:
        return texture(textures[13], uv);
        case 14:
        return texture(textures[14], uv);
        case 15:
        return texture(textures[15], uv);
        #ifdef gl_MaxTextureImageUnits
        #if gl_MaxTextureImageUnits > 16
        case 16:
        return texture(textures[16], uv);
        case 17:
        return texture(textures[17], uv);
        case 18:
        return texture(textures[18], uv);
        case 19:
        return texture(textures[19], uv);
        case 20:
        return texture(textures[20], uv);
        case 21:
        return texture(textures[21], uv);
        case 22:
        return texture(textures[22], uv);
        case 23:
        return texture(textures[23], uv);
        case 24:
        return texture(textures[24], uv);
        case 25:
        return texture(textures[25], uv);
        case 26:
        return texture(textures[26], uv);
        case 27:
        return texture(textures[27], uv);
        case 28:
        return texture(textures[28], uv);
        case 29:
        return texture(textures[29], uv);
        case 30:
        return texture(textures[30], uv);/*
		case 31:
		    return texture(textures[31], uv);
		case 32:
		    return texture(textures[32], uv);
		case 33:
		    return texture(textures[33], uv);*/
        #endif
        #endif
        default:
        return vec4(0.0);
    }
        #else
    return texture2D(textures[index], uv);
    #endif
}

void main(void){
    vec4 finalColor = gettextfrag(ftexture, fuv) * fcolor;
    fragColor = finalColor;
}