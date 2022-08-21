#version 330

layout (location=0) in vec3 in_Position;		//��ġ �Ӽ�
layout (location=1) in vec3 in_Color;		//���� �Ӽ�
layout (location=2) in vec2 in_texture;		//�ؽ�ó ��ǥ

out vec3 ex_Color;
out vec2 TexCoord;
out vec3 Normal; //--- ��ְ��� �����׸�Ʈ ���̴��� ������.

//layout (location = 0) in vec3 vPos;


uniform mat4 transform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;

void main(){
	gl_Position = projectionTransform * viewTransform * transform * vec4(in_Position.x,in_Position.y,in_Position.z,1.0);
	ex_Color = in_Color;
	TexCoord=in_texture;	//�ؽ�ó���� �����׸�Ʈ ���̴��� ������
};