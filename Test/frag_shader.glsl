#version 410 core
uniform vec4 ourColor;
out vec4 frag_colour;
void main() {
    frag_colour = ourColor;
}
