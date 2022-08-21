#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "freeglut.lib")

#define STB_IMAGE_IMPLEMENTATION
#include "ReadObj.h"
#include "Map.h"
#include "Naruto.h"
#include "stb_image.h"
#include "sound.h"
#include "monster.h"
#include "object1.h"
#include "object2.h"
#include "behind.h"
#include  <string.h>
#include "text.h"
#include "network.h"
#include "goalline.h"

//#include "..\NGP\NGP\protocol.h"
using namespace std;

GLchar* vertexsource, * fragmentsource; // �ҽ��ڵ� ���� ����
GLuint vertexshader, fragmentshader; // ���̴� ��ü
GLuint s_program[6];      //��� ���̴� ���α׷�      //0 : �ٴ�, 1 : ĳ����, 2: �ǹ�, 3: ���

//�Լ��� ����
GLvoid reshape(int w, int h);
GLvoid drawScene();         //�׷��ִ� �Լ�
void make_vertexShader();      //���ؽ� ���̴� ����
void make_fragmentShader();      //�����׸�Ʈ ���̴� ����
void InitBuffer();      //���� ����� �Լ�
void InitShader();      //���α׷� ����� �Լ�
void InitTexture();     //�ؽ��� �Լ�
char* filetobuf(char* file);   //���̴��� ����ϱ� ���� ������ �������� �Լ�
GLvoid TimerFunction(int value);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid KeyboardUp(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);

void restart();
Network net;

//�ؽ�ó
unsigned int texture1, texture2, texture3, texture4, texture5, texture6, texture7, texture8, texture9;

//������ ����
//��ü����
GLuint vao[5];      //0 �ٴ�, 1: ������ü, 2: ���̾�, 3 : �ٴ�, 4: ���۹�ư
GLuint vbo[3];
GLuint ebo;

//ReadObj����
//�簢�� read
float* vPosData;
float* vNormalData;
float* vTextureCoordinateData;
int* indexData;
int vertexCount;
int indexCount;
//�� read
float* vPosDatas;
float* vNormalDatas;
float* vTextureCoordinateDatas;
int* indexDatas;
int vertexCounts;
int indexCounts;

//��� ����

bool boolt = false;      // �÷��̾� �ٸ� ȸ��
bool M_boolt = false; // ���� �ٸ� ȸ�� 

float setac = 0.0f;   //ī�޶� ����
float setay = 0.0f;      //ī�޶� ����
float transz = 0.0f;       //ī�޶� ���̵�

float setatspeed = 3.0f;        //�ٸ� ȸ���ӵ�

float mouseX;
float mouseY;
//float yy = 5.0f;

//��ֹ� ��ġ ���� ���� 
int num = 0;
int num2 = 0;
bool left_Object = false;
bool right_Object = false;
bool mid_Object = false;
bool set_Object1 = false;
bool set_Object2 = false;

// Ű �Է� ���� 
bool key_w_state = false;
bool key_s_state = false;
bool key_a_state = false;
bool key_d_state = false;

bool boolw2 = false;  //�밢�� �̵��� �ӵ� ���̱� ���� 
//Ÿ�̸� 1
unsigned int timer2 = 1000;
//�ٴ��� ���� ��ǥ
GLfloat floorShape[6][3] = {
   {-1.0f,0.0f,-1.0f},
   {-1.0f,0.0f,1.0f},
   {1.0f,0.0f,-1.0f},
   {1.0f,0.0f,-1.0f},
   {-1.0f,0.0f,1.0f},
   {1.0f,0.0f,1.0f}
};
GLfloat floorColor[6][3] = {
   {0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},
   {0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},
   {0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f}
};

float backGround[] = {
    -1.0,1.0,0.0, 0.0f,1.0f,0.0f,  0.0,1.0,//6
    -1.0,-1.0,0.0, 0.0f,0.0f,0.5f, 0.0,0.0,//8
     1.0,1.0,0.0, 0.5f,0.0f,0.5f,  1.0,1.0,//5

     1.0,1.0,0.0, 0.5f,0.0f,0.5f,  1.0,1.0,//5
     -1.0,-1.0,0.0, 0.0f,0.0f,0.5f, 0.0,0.0,//8
      1.0,-1.0,0.0, 0.5f,0.0f,0.0f,  1.0,0.0//7
};
float startbutton[] = {
     -0.3,0.1,0.0, 0.0f,1.0f,0.0f,  0.0,1.0,//6
    -0.3,-0.1,0.0, 0.0f,0.0f,0.5f, 0.0,0.0,//8
     0.3,0.1,0.0, 0.5f,0.0f,0.5f,  1.0,1.0,//5

     0.3,0.1,0.0, 0.5f,0.0f,0.5f,  1.0,1.0,//5
     -0.3,-0.1,0.0, 0.0f,0.0f,0.5f, 0.0,0.0,//8
      0.3,-0.1,0.0, 0.5f,0.0f,0.0f,  1.0,0.0//7
};

void COLL_CHECK(glm::vec3 user, glm::vec3 obj)
{
   
   if ((user.z -0.5 > obj.z - 1 && user.z + 0.5 < obj.z +1) && (user.x  - 0.5> obj.x - 2 && user.x +0.5 < obj.x + 2))
    {
       net.gameover = true;

    }
}

bool state = true;
void GameEnd()
{
    if (net.getMyId() < 3) {
        CLIENT_DATA client_data;
        client_data.id = net.getMyId();
        client_data.type = LOGOUT;
        send(net.getSock(), (char*)&client_data, sizeof(client_data), 0);
    }
    
}

//�Լ��� �ۼ��� ����
void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{
    //sound2();
    //--- ������ �����ϱ�
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("NGP2021");
    //--- GLEW �ʱ�ȭ�ϱ�
    glewExperimental = GL_TRUE;      //openGL extention ������ ������ �� �ֵ��� ����
    if (glewInit() != GLEW_OK) {            //glew �ʱ�ȭ
        std::cerr << "Unable to initialize GLEW" << std::endl;         //�ʱ�ȭ �Ҽ� ������ ���� ���
        exit(EXIT_FAILURE);
    }
    else
        std::cout << "GLEW LInitialized\n";

    net.network();

    ReadObj("cube.obj", vPosData, vNormalData, vTextureCoordinateData, indexData, vertexCount, indexCount, false);
    ReadObj("sphere.obj", vPosDatas, vNormalDatas, vTextureCoordinateDatas, indexDatas, vertexCounts, indexCounts, true);
    my_init();
    InitMap();
    InitBuffer();
    InitShader();
    InitTexture();


    net.objects[0].z = 0;
    net.objects[1].z = 0;
    net.objects[2].z = -999;
    net.objects[3].z = -999;
    net.objects[4].z = -999;
    net.objects[5].z = -999;


    glutReshapeFunc(reshape);
    net.m_time_start = clock();
    glutKeyboardFunc(Keyboard);
    glutKeyboardUpFunc(KeyboardUp);

    glutMouseFunc(Mouse);

    glutTimerFunc(timer2, TimerFunction, 0);

    glutCloseFunc(GameEnd);
    atexit(GameEnd);

    glutDisplayFunc(drawScene);
    glutMainLoop();
}

int time_start = -100;
int time_end;

GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
    net.m_time_end = clock();
    auto delay = net.m_time_end - net.m_time_start;
    while (delay < 15) {
        delay = 15;
        Sleep(delay); 
    }

    g_time = net.game_time;
    if (net.gameclear || net.gameover) {
        key_w_state = false;
        key_s_state = false;
        key_a_state = false;
        key_d_state = false;
    }

    if (key_w_state || key_s_state || key_a_state || key_d_state) {
        net.CS_MOVE();
    }

    //--- ����� ���� ����
    glClearColor(1.0, 1.0, 1.0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //��� 
    glm::mat4 transformMatrix(1.0f);      //���庯ȯ
    glm::mat4 viewMatrix(1.0f);            //�亯ȯ
    glm::mat4 projectionMatrix(1.0f);      //������ȯ
    glm::mat4 basicChange(1.0f);         //�⺻�����
    glm::mat4 basicChange2(1.0f);         //�⺻�����

    glm::mat4 transMatrixj(1.0f);         //���j/J
    glm::mat4 rotateMatrixm(1.0f);         //���m/M
    glm::mat4 rotateMatrixt(1.0f);         //���t/T
    glm::mat4 scalehandfoot(1.0f);         //�հ� ���� ������ å��
    glm::mat4 transMatrixpoint(1.0f);      //������ �̵�

    glm::mat4 charTerrace(1.0f);
    charTerrace = glm::translate(charTerrace, glm::vec3(0.0f, 2.0f, 0.0f));

    //����
    glm::vec3 objColor(1.0f, 1.0f, 1.0f);
    //���ؽ� ����(������ ����)
    unsigned int transformLocation;
    unsigned int viewLocation;
    unsigned int projectionLocation;
    unsigned int objcolorLocation;

    if (!net.gameover && !gamestart && !net.gameclear) {
        glDisable(GL_DEPTH_TEST);
        //���-------------------------------
        glUseProgram(s_program[3]);
        viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        transformMatrix = glm::mat4(1.0f);  //��ũ��?
        transformLocation = glGetUniformLocation(s_program[3], "transform");
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
        viewLocation = glGetUniformLocation(s_program[3], "viewTransform");
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &viewMatrix[0][0]);
        projectionMatrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
        projectionLocation = glGetUniformLocation(s_program[3], "projectionTransform");
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
        objColor = glm::vec3(-1.0f, 1.0f, 1.0f);
        objcolorLocation = glGetUniformLocation(s_program[3], "objectColor");
        glUniform3f(objcolorLocation, objColor.x, objColor.y, objColor.z);

        glBindVertexArray(vao[3]);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        //--------------------------------------
        //��
        //ī�޶��̵��߰� 
        glm::vec3 cameraPos(1.0f);
        cameraPos = glm::vec3((10.0f + narutoCoord[net.getMyId()].z) * sin(glm::radians(setac)), 8.0f, (11.0f + narutoCoord[net.getMyId()].z + 3.0f) * cos(glm::radians(setac)));

        glm::vec4 ang(0.0f, 0.0f, 0.0f, 0.0f);
        ang.x = ang.x - ((10.0f + transz) * sin(glm::radians(setac)));
        ang.z = ang.z - ((10.0f + transz) * cos(glm::radians(setac)));

        glm::mat4 ang2(1.0f);
        ang2 = glm::rotate(ang2, glm::radians(setay), glm::vec3(0.0f, 1.0f, 0.0f));
        ang = ang2 * ang;

        ang.x = ang.x + ((10.0f + transz) * sin(glm::radians(setac)));
        ang.z = ang.z + ((10.0f + transz) * cos(glm::radians(setac)));

        glm::vec3 cameraDirection(1.0f);
        cameraDirection = glm::vec3(ang.x, 3.0f, ang.z + narutoCoord[net.getMyId()].z - 0.2f);
        
        glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

        viewMatrix = glm::lookAt(cameraPos , cameraDirection, cameraUp);
        

        //����
        projectionMatrix = glm::perspective(glm::radians(45.0f), (float)600.0f / (float)600.0f, 0.1f, 50.0f);

        // ������Ʈ ��ǥ
        //��� //�׸� ��ġ ��� ���� 
        
        for (const auto& client : net.clients) {
            if (client.alive) {
                narutoCoord[client.id] = glm::vec3(client.x, client.y , client.z);        //ĳ������ ��ġ
            }
        }

        for (const auto& object : net.objects) {
            switch (object.objectType)
            {
            case BOSS:
                MonsterCoord = glm::vec3(object.x, object.y, object.z);
                break;
            case TRACKER:
                BehindCoord = glm::vec3(object.x, object.y, object.z);
                break;
            case BALL:
                Object2Coord = glm::vec3(object.x, object.y, object.z);
                break;
            case BULLDOZER:
                Object1Coord = glm::vec3(object.x, object.y, object.z);
                break;
            default:
                break;
            }
        }
    
        scalehandfoot = glm::scale(basicChange, glm::vec3(0.1f, 0.5f, 0.1f));         //�հ����� ũ�� ���(�⺻���)
        rotateMatrixm = glm::rotate(rotateMatrixm, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));      //���� ȸ��

        glDepthFunc(GL_LESS);
        glEnable(GL_DEPTH_TEST);
        //�ٴ�
        glUseProgram(s_program[0]);
        //���庯ȯ �� �� ��� ����
        transformMatrix = glm::mat4(1.0f);
        basicChange = glm::mat4(1.0f);
        basicChange = glm::scale(basicChange, glm::vec3(10.0f, 0.0f, 1000.0f));      //������ ����  1000�� �� 1��36�� 
        basicChange2 = glm::mat4(1.0f);
        basicChange2 = glm::translate(basicChange2, glm::vec3(0.0f, -2.0f, 0.0f));
        transformMatrix = basicChange2 * basicChange * transformMatrix;

        objColor = glm::vec3(0.7f, 0.7f, 1.0f);

        transformLocation = glGetUniformLocation(s_program[0], "transform");
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
        viewLocation = glGetUniformLocation(s_program[0], "viewTransform");
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &viewMatrix[0][0]);
        projectionLocation = glGetUniformLocation(s_program[0], "projectionTransform");
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
        objcolorLocation = glGetUniformLocation(s_program[0], "objectColor");
        glUniform3f(objcolorLocation, objColor.x, objColor.y, objColor.z);
        glBindVertexArray(vao[0]);
        glDrawArrays(GL_TRIANGLES, 0, 6);


        //�ٵ�
        for (const auto& client : net.clients) {
            if (client.alive) {
                drawNaruto(net, s_program[1], vertexCount, vao, vbo, viewMatrix, projectionMatrix, client.id);
            }
        }

        for (const auto& object : net.objects) {
            switch (object.objectType)
            {
            case BOSS:
                drawMonster(s_program[1], vertexCount, vao, vbo, viewMatrix, projectionMatrix);
                break;
            case TRACKER:
                drawBehind(s_program[1], vertexCount, vao, vbo, viewMatrix, projectionMatrix);
                break;
            case BALL:
                drawObject2(s_program[1], vertexCount, vao, vbo, viewMatrix, projectionMatrix);
                break;
            case BULLDOZER:
                drawObject1(s_program[1], vertexCount, vao, vbo, viewMatrix, projectionMatrix);
                break;
            default:
                break;
            }
        }

        //�ǹ��׸���
        drawMap(s_program[2], vertexCount, vao, viewMatrix, projectionMatrix);
        drawGoalLine(s_program[1], vertexCount, vao, vbo, viewMatrix, projectionMatrix);
    }

    if (gamestart) {
        //startbutton
        glUseProgram(s_program[4]);
        viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        transformMatrix = glm::mat4(1.0f);
        transformLocation = glGetUniformLocation(s_program[4], "transform");
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
        viewLocation = glGetUniformLocation(s_program[4], "viewTransform");
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &viewMatrix[0][0]);
        projectionMatrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
        projectionLocation = glGetUniformLocation(s_program[4], "projectionTransform");
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
        objColor = glm::vec3(-1.0f, 1.0f, 1.0f);
        objcolorLocation = glGetUniformLocation(s_program[4], "objectColor");
        glUniform3f(objcolorLocation, objColor.x, objColor.y, objColor.z);

        glBindVertexArray(vao[4]);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture4);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    if (net.gameover) {//gameover�϶� ����
        glUseProgram(s_program[3]);
        viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        transformMatrix = glm::mat4(1.0f);
        transformLocation = glGetUniformLocation(s_program[3], "transform");
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
        viewLocation = glGetUniformLocation(s_program[3], "viewTransform");
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &viewMatrix[0][0]);
        projectionMatrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
        projectionLocation = glGetUniformLocation(s_program[3], "projectionTransform");
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
        objColor = glm::vec3(-1.0f, 1.0f, 1.0f);
        objcolorLocation = glGetUniformLocation(s_program[3], "objectColor");
        glUniform3f(objcolorLocation, objColor.x, objColor.y, objColor.z);

        glBindVertexArray(vao[3]);
        glActiveTexture(GL_TEXTURE0);
        
        glBindTexture(GL_TEXTURE_2D, texture2);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    if (net.gameclear) {
        glUseProgram(s_program[3]);
        viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        transformMatrix = glm::mat4(1.0f);
        transformLocation = glGetUniformLocation(s_program[3], "transform");
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
        viewLocation = glGetUniformLocation(s_program[3], "viewTransform");
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &viewMatrix[0][0]);
        projectionMatrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
        projectionLocation = glGetUniformLocation(s_program[3], "projectionTransform");
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
        objColor = glm::vec3(-1.0f, 1.0f, 1.0f);
        objcolorLocation = glGetUniformLocation(s_program[3], "objectColor");
        glUniform3f(objcolorLocation, objColor.x, objColor.y, objColor.z);

        glBindVertexArray(vao[3]);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture5);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    if(net.getStart())
        draw_stuff();  //�ؽ�Ʈ

    glutSwapBuffers(); // ȭ�鿡 ����ϱ�
    glutPostRedisplay();

    net.m_time_start = clock();
}

GLvoid reshape(int w, int h) {
    GLdouble size;
    GLdouble aspect;

    /* Use the whole window. */
    glViewport(0, 0, w, h);

    /* We are going to do some 2-D orthographic drawing. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    size = (GLdouble)((w >= h) ? w : h) / 2.0;
    if (w <= h) {
        aspect = (GLdouble)h / (GLdouble)w;
        glOrtho(-size, size, -size * aspect, size * aspect, -100000.0, 100000.0);
    }
    else {
        aspect = (GLdouble)w / (GLdouble)h;
        glOrtho(-size * aspect, size * aspect, -size, size, -100000.0, 100000.0);
    }

    /* Make the world and window coordinates coincide so that 1.0 in */
    /* model space equals one pixel in window space.                 */
    glScaled(aspect, aspect, 1.0);

    /* Now determine where to draw things. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
   // glViewport(0, 0, w, h);
}

char* filetobuf(const char* file) {
    FILE* fptr;
    long length;
    char* buf;
    fopen_s(&fptr, file, "rb"); // Open file for reading
    if (!fptr) // Return NULL on failure
        return NULL;
    fseek(fptr, 0, SEEK_END); // Seek to the end of the file
    length = ftell(fptr); // Find out how many bytes into the file we are
    buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator
    fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file
    fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer
    fclose(fptr); // Close the file
    buf[length] = 0; // Null terminator
    return buf; // Return the buffer
}

void make_vertexShader() {
    vertexsource = filetobuf("vertex.glsl");
    //--- ���ؽ� ���̴� ��ü �����
    vertexshader = glCreateShader(GL_VERTEX_SHADER);
    //--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
    glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0);
    //--- ���ؽ� ���̴� �������ϱ�
    glCompileShader(vertexshader);
    //--- �������� ����� ���� ���� ���: ���� üũ
    GLint result;
    GLchar errorLog[512];
    glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(vertexshader, 512, NULL, errorLog);
        cerr << "ERROR: vertex shader ������ ����\n" << errorLog << endl;
        //return false;
        //return;
        exit(0);
    }
}

void make_fragmentShader()
{
    fragmentsource = filetobuf("fragment.glsl");
    //--- �����׸�Ʈ ���̴� ��ü �����
    fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    //--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
    glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, 0);
    //--- �����׸�Ʈ ���̴� ������
    glCompileShader(fragmentshader);
    //--- �������� ����� ���� ���� ���: ������make_fragmentShader ���� üũ
    GLint result;
    GLchar errorLog[512];
    glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(fragmentshader, 512, NULL, errorLog);
        cerr << "ERROR: fragment shader ������ ����\n" << errorLog << endl;
        //return false;
        //return;
        exit(0);
    }
}

void InitBuffer()
{
    glGenVertexArrays(5, vao); //--- VAO �� �����ϰ� �Ҵ��ϱ�

    //�ٴ�
    glBindVertexArray(vao[0]); //--- VAO�� ���ε��ϱ�
    glGenBuffers(3, vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floorShape), floorShape, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floorColor), floorColor, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    //������ü
    glBindVertexArray(vao[1]); //--- VAO�� ���ε��ϱ�
    glGenBuffers(3, vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float) * 3, vPosData, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float) * 3, vNormalData, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(int), indexData, GL_STATIC_DRAW);




    //���
    glBindVertexArray(vao[3]); //--- VAO�� ���ε��ϱ�
    glGenBuffers(3, vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(backGround), backGround, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //--- ��ġ �Ӽ�
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); //--- �븻�� �Ӽ�
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); //--- �ؽ�ó ��ǥ �Ӽ�
    glEnableVertexAttribArray(2);

    //���
    glBindVertexArray(vao[4]); //--- VAO�� ���ε��ϱ�
    glGenBuffers(3, vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(startbutton), startbutton, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //--- ��ġ �Ӽ�
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); //--- �븻�� �Ӽ�
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); //--- �ؽ�ó ��ǥ �Ӽ�
    glEnableVertexAttribArray(2);
}

void InitShader()
{
    make_vertexShader();
    make_fragmentShader();
    //-- shader Program
    for (int i = 0; i < 6; i++) {
        s_program[i] = glCreateProgram();
        glAttachShader(s_program[i], vertexshader);
        glAttachShader(s_program[i], fragmentshader);
        glLinkProgram(s_program[i]);
        //checkCompileErrors(s_program, "PROGRAM");
        //--- ���̴� �����ϱ�
        glDeleteShader(vertexshader);
        glDeleteShader(fragmentshader);
        //--- Shader Program ����ϱ�
        glUseProgram(s_program[i]);
    }
}

void InitTexture() {

    int width, height, nrChannels;
    unsigned char* data;
    int tLocation;
    //--- texture 1
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("sky.png", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glUseProgram(s_program[3]);
    tLocation = glGetUniformLocation(s_program[3], "texture"); //--- outTexture ������ ���÷��� ��ġ�� ������
    glUniform1i(tLocation, 6);
    stbi_image_free(data);

    //--- texture 2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("samurai_gameover.png", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glUseProgram(s_program[3]);
    tLocation = glGetUniformLocation(s_program[3], "texture"); //--- outTexture ������ ���÷��� ��ġ�� ������
    glUniform1i(tLocation, 6);
    stbi_image_free(data);

    //--- texture 3
    glGenTextures(1, &texture3);
    glBindTexture(GL_TEXTURE_2D, texture3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("background.png", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glUseProgram(s_program[3]);
    tLocation = glGetUniformLocation(s_program[3], "texture"); //--- outTexture ������ ���÷��� ��ġ�� ������
    glUniform1i(tLocation, 6);
    stbi_image_free(data);

    //--- texture 4
    glGenTextures(1, &texture4);
    glBindTexture(GL_TEXTURE_2D, texture4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("start2.jpg", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glUseProgram(s_program[4]);
    tLocation = glGetUniformLocation(s_program[4], "texture"); //--- outTexture ������ ���÷��� ��ġ�� ������
    glUniform1i(tLocation, 6);
    stbi_image_free(data);

    //--- texture 5
    glGenTextures(1, &texture5);
    glBindTexture(GL_TEXTURE_2D, texture5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("Ŭ����.png", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glUseProgram(s_program[3]);
    tLocation = glGetUniformLocation(s_program[3], "texture"); //--- outTexture ������ ���÷��� ��ġ�� ������
    glUniform1i(tLocation, 6);
    stbi_image_free(data);

    //--- texture 6
    glGenTextures(1, &texture6);
    glBindTexture(GL_TEXTURE_2D, texture6);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("next.jpg", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glUseProgram(s_program[4]);
    tLocation = glGetUniformLocation(s_program[4], "texture"); //--- outTexture ������ ���÷��� ��ġ�� ������
    glUniform1i(tLocation, 6);
    stbi_image_free(data);


    //--- texture 7
    glGenTextures(1, &texture7);
    glBindTexture(GL_TEXTURE_2D, texture7);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("1st.png", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glUseProgram(s_program[3]);
    tLocation = glGetUniformLocation(s_program[3], "texture"); //--- outTexture ������ ���÷��� ��ġ�� ������
    glUniform1i(tLocation, 6);
    stbi_image_free(data);
}

void Mouse(int button, int state, int x, int y)
{
    mouseX = (float)(x - (float)600 / 2.0) * (float)(1.0 / (float)(600 / 2.0));
    mouseY = -(float)(y - (float)600 / 2.0) * (float)(1.0 / (float)(600 / 2.0));

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (!net.getStart()) {
            if (mouseX > -0.3 && mouseX < 0.3 && mouseY>-0.1 && mouseY < 0.1) {
                gamestart = false;
                net.gameover = false;
                net.gameclear = false;
                net.CS_START();
            }
        }
    }
}

GLvoid TimerFunction(int value) {
    if (net.getStart()) {
        if (M_boolt) {  //�ٸ� ȸ�� 
            M_setat += setatspeed;
            if (M_setat >= 60.0f) {
                M_setat = 60.0f;
                M_boolt = false;
            }
        }
        else {
            M_setat -= setatspeed;
            if (M_setat <= -60.0f) {
                M_setat = -60.0f;
                M_boolt = true;
            }
        }

       if (boolt) {
           setat += setatspeed;
           if (setat >= 60.0f) {
               setat = 60.0f;
               boolt = false;
           }
       }
       else {
           setat -= setatspeed;
           if (setat <= -60.0f) {
               setat = -60.0f;
               boolt = true;
           }
       }
    }
    glutTimerFunc(1, TimerFunction, value); // Ÿ�̸��Լ� �� ����
}

GLvoid Keyboard(unsigned char key, int x, int y) {
    if (net.getStart()) {
        if (key == 'w')
            key_w_state = true;
        if (key == 's')
            key_s_state = true;
        if (key == 'a')
            key_a_state = true;
        if (key == 'd')
            key_d_state = true;
    }

    if (net.restart == true && key == 'r') {
        gamestart = true;
        net.restart = false;
    }
}

GLvoid KeyboardUp(unsigned char key, int x, int y) {
    if (net.getStart()) {
        if (key == 'w')
            key_w_state = false;
        if (key == 's')
            key_s_state = false;
        if (key == 'a')
            key_a_state = false;
        if (key == 'd')
            key_d_state = false;
    }
}