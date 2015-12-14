#version 120

uniform	mat4 projection;
uniform	mat4 view;
uniform	mat4 model;
uniform vec4 color;
uniform vec4 alpha;

uniform sampler2D fTexture0;

attribute vec4 vPosition;
attribute vec4 vColor;
attribute vec4 vNormal;
attribute vec2 vTexCoord;

varying vec4 fColor;
varying vec4 fNormal;
varying vec2 fUv;
varying vec4 fAlpha;

void main(void)
{
  if (color != vec4(1))
    fColor = (vColor + color + color) / 3;
  else
    fColor = vColor;
  fAlpha = alpha;
  fNormal = vNormal;
  fUv = vTexCoord;
  gl_Position = projection * view * model * vPosition;
}