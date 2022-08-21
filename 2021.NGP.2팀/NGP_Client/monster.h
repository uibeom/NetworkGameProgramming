#pragma once
#include <iostream>
#include <cstdio>
#include <conio.h>
#include <gl/glew.h>
#include <gl/glut.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <ctime>
#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "sound.h"
#include "map.h"



/*
�������� ��ġ : narutoCoord(�ı�����.cpp drawScene���� ��� �ؼ� ������Ʈ)
*/



//���ΰ��̵�(x,y,z��)

float M_pointx = 2.25f;
float M_pointz = -10.0f;

glm::vec3 MonsterCoord(2.25f, 0.0f, 0.0f);

float M_setat = 0.0f;      //�̵��� �ٸ��� �����̴� �ִϸ��̼��� �ϱ����� ����
float M_setam = 180.0f;      //���� ȸ���� ����
float M_setaRighthand = 60.0f;
float M_setaLefthand = 60.0f;




void drawMonster(GLuint program, int vertexCount, GLuint vao[], GLuint vbo[], glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {

    //��� 
    glm::mat4 transformMatrix(1.0f);      //���庯ȯ
    glm::mat4 basicChange(1.0f);         //�⺻�����
    glm::mat4 basicChange2(1.0f);         //�⺻�����

    glm::mat4 rotateMatrixm(1.0f);         //���m/M
    glm::mat4 rotateMatrixt(1.0f);         //���t/T
    glm::mat4 scalehandfoot(5.0f);         //�հ� ���� ������ å��
    glm::mat4 transMatrixpoint(1.0f);      //������ �̵�
    glm::mat4 charTerrace(1.0f);
    charTerrace = glm::translate(charTerrace, glm::vec3(0.0f, 2.0f, 0.0f));

    //����
    glm::vec3 objColor(0.0f, 0.0f, 0.0f);
    //���ؽ� ����(������ ����)
    unsigned int transformLocation;
    unsigned int viewLocation;
    unsigned int projectionLocation;
    unsigned int objcolorLocation;

    //���
    scalehandfoot = glm::scale(basicChange, glm::vec3(0.5f, 2.5f, 0.5f));         //�հ����� ũ�� ���(�⺻���)
    transMatrixpoint = glm::translate(transMatrixpoint, glm::vec3(MonsterCoord.x, MonsterCoord.y, MonsterCoord.z));
    rotateMatrixm = glm::rotate(rotateMatrixm, glm::radians(M_setam), glm::vec3(0.0f, 1.0f, 0.0f));      //���� ȸ��



    glUseProgram(program);
    //�ٵ�
    //���庯ȯ �� �� ��� ����
    basicChange = glm::mat4(1.0f);      //�ʱ�ȭ   
    transformMatrix = glm::mat4(1.0f);   //�ʱ�ȭ
    basicChange = glm::translate(basicChange, glm::vec3(-0.5f, -0.5f, -0.5f));
    transformMatrix = basicChange * transformMatrix;
    basicChange = glm::mat4(1.0f);      //�ʱ�ȭ
    basicChange = glm::scale(basicChange, glm::vec3(5.0f, 4.0f, 2.5f));      //������ ����
    transformMatrix = basicChange * transformMatrix;


    basicChange = glm::mat4(1.0f);
    basicChange = glm::translate(basicChange, glm::vec3(0.0, 0.8f, 0.0));      //�ٴ��� �������� �̵�
    transformMatrix = basicChange * transformMatrix;
    transformMatrix = rotateMatrixm * transformMatrix;      //������ ȸ��
    transformMatrix = transMatrixpoint * transformMatrix;      //������ �̵�
    transformMatrix = charTerrace * transformMatrix;      //�������� �̵�

    objColor = glm::vec3(0.1f, 0.1f, 0.1f);

    transformLocation = glGetUniformLocation(program, "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
    viewLocation = glGetUniformLocation(program, "viewTransform");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &viewMatrix[0][0]);
    projectionLocation = glGetUniformLocation(program, "projectionTransform");
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
    objcolorLocation = glGetUniformLocation(program, "objectColor");
    glUniform3f(objcolorLocation, objColor.x, objColor.y, objColor.z);
    glBindVertexArray(vao[1]);
    glDrawElements(GL_TRIANGLES, vertexCount * 3, GL_UNSIGNED_INT, 0);


    //�Ӹ�
    //���庯ȯ �� �� ��� ����
    transformMatrix = glm::mat4(1.0f);
    basicChange = glm::mat4(1.0f);
    basicChange = glm::translate(basicChange, glm::vec3(-0.5f, -0.5f, -0.5f));      //�����̵�
    transformMatrix = basicChange * transformMatrix;
    basicChange = glm::mat4(1.0f);      //�ʱ�ȭ
    basicChange = glm::scale(basicChange, glm::vec3(3.5f, 1.8f, 3.5f));      //������ ����
    transformMatrix = basicChange * transformMatrix;
    basicChange = glm::mat4(1.0f);
    basicChange = glm::translate(basicChange, glm::vec3(0.0, 3.8f, 0.0));      //1���� �������� �̵�
    transformMatrix = basicChange * transformMatrix;
    transformMatrix = rotateMatrixm * transformMatrix;      //������ ȸ��
    transformMatrix = transMatrixpoint * transformMatrix;      //������ �̵�
    transformMatrix = charTerrace * transformMatrix;
    objColor = glm::vec3(0.0f, 0.0f, 0.0f);
    transformLocation = glGetUniformLocation(program, "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
    viewLocation = glGetUniformLocation(program, "viewTransform");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &viewMatrix[0][0]);
    projectionLocation = glGetUniformLocation(program, "projectionTransform");
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
    objcolorLocation = glGetUniformLocation(program, "objectColor");
    glUniform3f(objcolorLocation, objColor.x, objColor.y, objColor.z);
    glBindVertexArray(vao[1]);
    glDrawElements(GL_TRIANGLES, vertexCount * 3, GL_UNSIGNED_INT, 0);

    //��
    transformMatrix = glm::mat4(1.0f);
    basicChange = glm::mat4(1.0f);
    basicChange = glm::translate(basicChange, glm::vec3(-0.5f, -0.5f, -0.5f));
    transformMatrix = basicChange * transformMatrix;
    basicChange = glm::mat4(1.0f);      //�ʱ�ȭ
    basicChange = glm::scale(basicChange, glm::vec3(0.3f, 0.2f, 0.4f));      //������ ����
    transformMatrix = basicChange * transformMatrix;
    basicChange = glm::mat4(1.0f);
    basicChange = glm::translate(basicChange, glm::vec3(-0.3, 3.8f,-2.0));      //1���� �������� �̵�
    transformMatrix = basicChange * transformMatrix;
    transformMatrix = rotateMatrixm * transformMatrix;      //������ ȸ��
    transformMatrix = transMatrixpoint * transformMatrix;      //������ �̵�
    transformMatrix = charTerrace * transformMatrix;
    objColor = glm::vec3(1.0f, 0.0f, 0.0f);
    transformLocation = glGetUniformLocation(program, "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
    viewLocation = glGetUniformLocation(program, "viewTransform");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &viewMatrix[0][0]);
    projectionLocation = glGetUniformLocation(program, "projectionTransform");
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
    objcolorLocation = glGetUniformLocation(program, "objectColor");
    glUniform3f(objcolorLocation, objColor.x, objColor.y, objColor.z);
    glBindVertexArray(vao[1]);
    glDrawElements(GL_TRIANGLES, vertexCount * 3, GL_UNSIGNED_INT, 0);

    //������
    //���庯ȯ �� �� ��� ����
    transformMatrix = glm::mat4(1.0f);
    basicChange = glm::mat4(1.0f);
    basicChange = glm::translate(basicChange, glm::vec3(-0.5f, -0.5f, -0.5f));
    transformMatrix = basicChange * transformMatrix;
    basicChange = glm::mat4(1.0f);      //�ʱ�ȭ
    transformMatrix = scalehandfoot * transformMatrix;      //��ũ��
    basicChange = glm::mat4(1.0f);
    basicChange = glm::translate(basicChange, glm::vec3(0.0f, -0.25f, 0.0));      //ȸ���� �̵�
    transformMatrix = basicChange * transformMatrix;
    rotateMatrixt = glm::rotate(rotateMatrixt, glm::radians(M_setaRighthand), glm::vec3(1.0f, 0.0f, 0.0f));   //�̵��� ���� ������
    transformMatrix = rotateMatrixt * transformMatrix;
    basicChange = glm::mat4(1.0f);
    basicChange = glm::translate(basicChange, glm::vec3(-2.8f, 0.9f, 0.0));      //������ ��ġ�� �̵�
    transformMatrix = basicChange * transformMatrix;
    transformMatrix = rotateMatrixm * transformMatrix;         //������ ȸ��
    transformMatrix = transMatrixpoint * transformMatrix;      //������ �̵�
    transformMatrix = charTerrace * transformMatrix;
    objColor = glm::vec3(0.0f, 0.0f, 0.0f);
    transformLocation = glGetUniformLocation(program, "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
    viewLocation = glGetUniformLocation(program, "viewTransform");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &viewMatrix[0][0]);
    projectionLocation = glGetUniformLocation(program, "projectionTransform");
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
    objcolorLocation = glGetUniformLocation(program, "objectColor");
    glUniform3f(objcolorLocation, objColor.x, objColor.y, objColor.z);
    glBindVertexArray(vao[1]);
    glDrawElements(GL_TRIANGLES, vertexCount * 3, GL_UNSIGNED_INT, 0);

    //�����ʼ�
    //���庯ȯ �� �� ��� ����
    transformMatrix = glm::mat4(1.0f);
    basicChange = glm::mat4(1.0f);
    basicChange = glm::translate(basicChange, glm::vec3(-0.5f, -0.5f, -0.5f));
    transformMatrix = basicChange * transformMatrix;
    basicChange = glm::mat4(1.0f);      //�ʱ�ȭ
    transformMatrix = scalehandfoot * transformMatrix;      //��ũ��
    basicChange = glm::mat4(1.0f);
    basicChange = glm::translate(basicChange, glm::vec3(0.0f, -0.25f, 0.0));      //ȸ���� �̵�
    transformMatrix = basicChange * transformMatrix;
    rotateMatrixt = glm::mat4(1.0f);
    rotateMatrixt = glm::rotate(rotateMatrixt, glm::radians(M_setaLefthand), glm::vec3(1.0f, 0.0f, 0.0f));   //�̵��� ���� ������
    transformMatrix = rotateMatrixt * transformMatrix;
    basicChange = glm::mat4(1.0f);
    basicChange = glm::translate(basicChange, glm::vec3(2.7f, 0.9f, 0.0));      //������ ��ġ�� �̵�
    transformMatrix = basicChange * transformMatrix;
    transformMatrix = rotateMatrixm * transformMatrix;      //������ ȸ��
    transformMatrix = transMatrixpoint * transformMatrix;      //������ �̵�
    transformMatrix = charTerrace * transformMatrix;
    objColor = glm::vec3(0.0f, 0.0f, 0.0f);
    transformLocation = glGetUniformLocation(program, "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
    viewLocation = glGetUniformLocation(program, "viewTransform");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &viewMatrix[0][0]);
    projectionLocation = glGetUniformLocation(program, "projectionTransform");
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
    objcolorLocation = glGetUniformLocation(program, "objectColor");
    glUniform3f(objcolorLocation, objColor.x, objColor.y, objColor.z);
    glBindVertexArray(vao[1]);
    glDrawElements(GL_TRIANGLES, vertexCount * 3, GL_UNSIGNED_INT, 0);

    //���� ��
    //���庯ȯ �� �� ��� ����
    transformMatrix = glm::mat4(1.0f);
    basicChange = glm::mat4(1.0f);
    basicChange = glm::translate(basicChange, glm::vec3(-0.5f, -0.5f, -0.5f));
    transformMatrix = basicChange * transformMatrix;
    basicChange = glm::mat4(1.0f);      //�ʱ�ȭ
    transformMatrix = scalehandfoot * transformMatrix;      //ũ��
    basicChange = glm::mat4(1.0f);
    basicChange = glm::translate(basicChange, glm::vec3(0.0f, -0.25f, 0.0));      //ȸ���� �̵�
    transformMatrix = basicChange * transformMatrix;
    rotateMatrixt = glm::mat4(1.0f);
    rotateMatrixt = glm::rotate(rotateMatrixt, glm::radians(-M_setat), glm::vec3(1.0f, 0.0f, 0.0f));   //�̵��� ���� ������
    transformMatrix = rotateMatrixt * transformMatrix;
    basicChange = glm::mat4(1.0f);
    basicChange = glm::translate(basicChange, glm::vec3(-1.3f, -2.0f, 0.0));      //������ ��ġ�� �̵�
    transformMatrix = basicChange * transformMatrix;
    transformMatrix = rotateMatrixm * transformMatrix;      //������ ȸ��
    transformMatrix = transMatrixpoint * transformMatrix;      //������ �̵�
    transformMatrix = charTerrace * transformMatrix;
    objColor = glm::vec3(0.0f, 0.0f, 0.0f);
    transformLocation = glGetUniformLocation(program, "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
    viewLocation = glGetUniformLocation(program, "viewTransform");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &viewMatrix[0][0]);
    projectionLocation = glGetUniformLocation(program, "projectionTransform");
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
    objcolorLocation = glGetUniformLocation(program, "objectColor");
    glUniform3f(objcolorLocation, objColor.x, objColor.y, objColor.z);
    glBindVertexArray(vao[1]);
    glDrawElements(GL_TRIANGLES, vertexCount * 3, GL_UNSIGNED_INT, 0);

    //������ ��
    //���庯ȯ �� �� ��� ����
    transformMatrix = glm::mat4(1.0f);
    basicChange = glm::mat4(1.0f);
    basicChange = glm::translate(basicChange, glm::vec3(-0.5f, -0.5f, -0.5f));
    transformMatrix = basicChange * transformMatrix;
    basicChange = glm::mat4(1.0f);      //�ʱ�ȭ
    transformMatrix = scalehandfoot * transformMatrix;      //ũ��
    basicChange = glm::mat4(1.0f);
    basicChange = glm::translate(basicChange, glm::vec3(0.0f, -0.25f, 0.0));      //ȸ���� �̵�
    transformMatrix = basicChange * transformMatrix;
    rotateMatrixt = glm::mat4(1.0f);
     rotateMatrixt = glm::rotate(rotateMatrixt, glm::radians(M_setat), glm::vec3(1.0f, 0.0f, 0.0f));

    transformMatrix = rotateMatrixt * transformMatrix;
    basicChange = glm::mat4(1.0f);
    basicChange = glm::translate(basicChange, glm::vec3(0.8, -0.0f, 0.0));      //������ ��ġ�� �̵�
    transformMatrix = basicChange * transformMatrix;
    transformMatrix = rotateMatrixm * transformMatrix;      //������ ȸ��
    transformMatrix = transMatrixpoint * transformMatrix;      //������ �̵�
    objColor = glm::vec3(0.0f, 0.0f, 0.0f);
    transformLocation = glGetUniformLocation(program, "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
    viewLocation = glGetUniformLocation(program, "viewTransform");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &viewMatrix[0][0]);
    projectionLocation = glGetUniformLocation(program, "projectionTransform");
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
    objcolorLocation = glGetUniformLocation(program, "objectColor");
    glUniform3f(objcolorLocation, objColor.x, objColor.y, objColor.z);
    glBindVertexArray(vao[1]);
    glDrawElements(GL_TRIANGLES, vertexCount * 3, GL_UNSIGNED_INT, 0);


}



