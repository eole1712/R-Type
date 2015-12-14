#version 120

uniform	mat4 projection;
uniform	mat4 view;
uniform	mat4 model;

uniform sampler2D fTexture0;

varying vec4 fColor;
varying vec4 fAlpha;
varying vec4 fNormal;
varying vec2 fUv;

void main(void)
{
  if (fAlpha != vec4(0))
    gl_FragColor = fAlpha;
  else
    gl_FragColor = texture2D(fTexture0, fUv) * fColor;
}
