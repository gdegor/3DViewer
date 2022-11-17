#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

//uniform sampler2D texture;
uniform mediump vec4 color;

//varying vec2 v_texcoord;

void main()
{
//    color = vec4(1.0,0.0,0.0,1.0);
    gl_FragColor = color;
}

