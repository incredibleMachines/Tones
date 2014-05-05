uniform sampler2DRect tex;
uniform float beat;
uniform float time;

void main(){
    vec2 st= gl_TexCoord[0].st;
    vec4 color= texture2DRect(tex, st);

   float beat = beat * 0.03;

  color.r += sin(time*0.02) * 0.1 + beat;
  color.g += cos(time*0.0) * 0.1 + beat;
  color.b += cos(time*0.02) * 0.2 + beat;

        
    // gl_FragColor = vec4(color.rgb, 1.0);
//        gl_FragColor = vec4(0,0,0,0);
        gl_FragColor = vec4(color.r - 0.3,color.g - 0.45,color.b - 0.2, 1.0);
//    gl_FragColor = vec4(color.r,color.g,color.b, 1.0);

}