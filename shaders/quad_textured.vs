#version 460 core

layout(location = 0) in vec2 in_pos;
layout(location = 1) in vec2 in_tex_coord;

out vec2 tex_coord;

uniform mat4 scale;
uniform mat4 translate;

uniform vec2 top_left;
uniform vec2 bottom_right;

void main()
{
	gl_Position = translate * scale * vec4(in_pos.x, in_pos.y, 0, 1.0);
	vec2 temp_tex = in_tex_coord;
	temp_tex.x = clamp(temp_tex.x, top_left.x, bottom_right.x);
	temp_tex.y = clamp(temp_tex.y, top_left.y, bottom_right.y);
	tex_coord = temp_tex;
}