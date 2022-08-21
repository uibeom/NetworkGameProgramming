#version 330
//--- ex_Color: ���ؽ� ���̴����� �Է¹޴� ���� ��
//--- gl_FragColor: ����� ������ ������ ���� ���α׷����� ���� ��.

in vec3 ex_Color; //--- ���ؽ� ���̴����Լ� ���� ����
in vec2 TexCoord;
in vec3 Normal; //--- ��ְ��� �����׸�Ʈ ���̴��� ������.

out vec4 gl_FragColor; //--- ���� ���

uniform vec3 objectColor;		//�÷����� �־����� �ʾ����� ������� �ʱ�ȭ
uniform sampler2D texture1;

void main(void)
{
	if(objectColor.x==-1.0f){
	gl_FragColor = texture(texture1,TexCoord);
	//l_FragColor.a=1.0f;
	}
	else{
	vec3 result=objectColor;
	gl_FragColor = vec4(result,1.0);
	}
}