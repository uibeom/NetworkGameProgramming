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

#define BUILDINGNUMBER 12        //����(�ǹ�)�� ����

//�ǹ��� ��ǥ�� ��Ÿ����
glm::vec3 buildingCoord[BUILDINGNUMBER];        //������ ��ǥ
glm::vec3 handrailCoord[BUILDINGNUMBER];        //������ ��ǥ

//���� ���� �Ѱ� 
glm::vec3 handrailCoord2[1];        //������ ��ǥ
glm::vec3 clear[1];

//���� �ǹ��� ���� 
#define BUILDINGNUMBER3 6        //����(�ǹ�)�� ����
glm::vec3 buildingCoord3[BUILDINGNUMBER3];        //������ ��ǥ
glm::vec3 handrailCoord3[BUILDINGNUMBER3];        //������ ��ǥ

float nangansize = 3.0f;

void InitMap() {
    //0�� �ǹ�
    buildingCoord[0] = glm::vec3(5.5f, 1.5f, 0.0);
  //  handrailCoord[0] = glm::vec3(2.5f, 1.5f, 0.0);
    

    //1�� �ǹ�
    buildingCoord[1] = glm::vec3(-25.5f, 1.5f, 0.0);
  //  handrailCoord[1] = glm::vec3(0.0f, 1.5f, 0.1);
    
    //2�� �ǹ�
    buildingCoord[2] = glm::vec3(5.5f, 1.5f, -100 );
   // handrailCoord[2] = glm::vec3(-3.5f, 1.5f, 0);
    //3�� �ǹ�
    buildingCoord[3] = glm::vec3(-25.5f, 1.5f, -100 );
   // handrailCoord[3] = glm::vec3(-3.5f, 1.5f, 0);
    
    //4�� �ǹ�
    buildingCoord[4] = glm::vec3(5.5f, 1.5f, -200);
//    handrailCoord[4] = glm::vec3(2.5f, 1.5f, -11.5 * 4);
    //5�� �ǹ�
    buildingCoord[5] = glm::vec3(-25.5f, 1.5f, -200);
  //  handrailCoord[5] = glm::vec3(-3.5f, 1.5f, -11.5 * 5);

    //6�� �ǹ�
    buildingCoord[6] = glm::vec3(5.5f, 1.5f, -300);
    //7�� �ǹ�
    buildingCoord[7] = glm::vec3(-25.5f, 1.5f, -300);
    //8�� �ǹ�
    buildingCoord[8] = glm::vec3(5.5f, 1.5f, -400);
    //9�� �ǹ�
    buildingCoord[9] = glm::vec3(-25.5f, 1.5f, -400);
    //10�� �ǹ�
    buildingCoord[10] = glm::vec3(5.5f, 1.5f, -500);
    //11�� �ǹ�
    buildingCoord[11] = glm::vec3(-25.5f, 1.5f, -500);



    /**
    //6�� �ǹ�
    buildingCoord[6] = glm::vec3(5.5f, 1.5f, -11.5 * 6);
    handrailCoord[6] = glm::vec3(2.5f, 1.5f, -11.5 * 6);  */

    /*
    //������ȯ ���� 1��
    handrailCoord2[0] = glm::vec3(4.5f, 1.5f, -11.5 * 6 - 5.5f);


    //8�� �ǹ�
    buildingCoord3[0] = glm::vec3(5.5f + 9.5, 1.5f, -11.5 * 6 - 2.5f);
    handrailCoord3[0] = glm::vec3(5.5f + 9.5, 1.5f, -11.5 * 6 - 5.5f);

    //9�� �ǹ�
    buildingCoord3[1] = glm::vec3(5.5f + 9.5 + 11.5, 1.5f, -11.5 * 6 - 2.5f - 11.0f);
    handrailCoord3[1] = glm::vec3(5.5f + 9.5 + 11.5, 1.5f, -11.5 * 6 - 5.5f - 5.0f);


    //10�� �ǹ�
    buildingCoord3[2] = glm::vec3(5.5f + 9.5 + 11.5 * 2, 1.5f, -11.5 * 6 - 2.5f - 11.0f);
    handrailCoord3[2] = glm::vec3(5.5f + 9.5 + 11.5 * 2, 1.5f, -11.5 * 6 - 5.5f - 5.0f);


    //11�� �ǹ�
    buildingCoord3[3] = glm::vec3(5.5f + 9.5 + 11.5 * 3, 1.5f, -11.5 * 6 - 2.5f);
    handrailCoord3[3] = glm::vec3(5.5f + 9.5 + 11.5 * 3, 1.5f, -11.5 * 6 - 5.5f);


    //12�� �ǹ�
    buildingCoord3[4] = glm::vec3(5.5f + 9.5 + 11.5 * 4, 1.5f, -11.5 * 6 - 2.5f - 11.0f);
    handrailCoord3[4] = glm::vec3(5.5f + 9.5 + 11.5 * 4, 1.5f, -11.5 * 6 - 5.5f - 5.0f);


    //13�� �ǹ�
    buildingCoord3[5] = glm::vec3(5.5f + 9.5 + 11.5 * 5, 1.5f, -11.5 * 6 - 2.5f);
    handrailCoord3[5] = glm::vec3(5.5f + 9.5 + 11.5 * 5, 1.5f, -11.5 * 6 - 5.5f);*/

    //Ŭ���� 
    clear[0] = glm::vec3(5.5f + 9.5 + 11.5 * 6, 1.5f, -11.5 * 6 - 7.0f);
}


void drawMap(GLuint program, int vertexCount, GLuint vao[], glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
    glm::mat4 transformMatrix(1.0f);      //���庯ȯ

    glm::mat4 basicChange(1.0f);         //�⺻�����
    glm::mat4 basicChange2(1.0f);         //�⺻�����

    glm::mat4 transMatrixj(1.0f);         //���j/J
    glm::mat4 rotateMatrixm(1.0f);         //���m/M
    glm::mat4 rotateMatrixt(1.0f);         //���t/T
    glm::mat4 scalehandfoot(1.0f);         //�հ� ���� ������ å��
    glm::mat4 transMatrixpoint(1.0f);      //������ �̵�


    //����
    glm::vec3 objColor(1.0f, 1.0f, 1.0f);
    //���ؽ� ����(������ ����)
    unsigned int transformLocation;
    unsigned int viewLocation;
    unsigned int projectionLocation;
    unsigned int objcolorLocation;


    glUseProgram(program);
    for (int i = 0; i < 2; i++) {
        //�ǹ���ü

        transformMatrix = glm::mat4(1.0f);   //�ʱ�ȭ
        basicChange = glm::mat4(1.0f);      //�ʱ�ȭ   
        basicChange = glm::translate(basicChange, glm::vec3(1.50f, -0.5f, -0.5f));  //�������� �̵�(������ü�� �߾��� ����)   Y -0.5
        transformMatrix = basicChange * transformMatrix;

        basicChange = glm::mat4(1.0f);      //�ʱ�ȭ
        basicChange = glm::scale(basicChange, glm::vec3(5.0f, 20.0f, 100.0f));      //������ ����
        transformMatrix = basicChange * transformMatrix;   //ũ��

        basicChange = glm::mat4(1.0f);
        basicChange = glm::translate(basicChange, glm::vec3(buildingCoord[i].x, buildingCoord[i].y, buildingCoord[i].z));     //�ǹ��� �־�� �ϴ� ��ġ�� �̵�
        transformMatrix = basicChange * transformMatrix;

        objColor = glm::vec3(0.7f, 0.5f, 0.0f);
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

       /*//����
        basicChange = glm::mat4(1.0f);      //�ʱ�ȭ   
        transformMatrix = glm::mat4(1.0f);   //�ʱ�ȭ
        basicChange = glm::translate(basicChange, glm::vec3(-0.5f, -0.5f, -0.5f));   //�������� �̵�(������ü�� �߾��� ����)
        transformMatrix = basicChange * transformMatrix;
        basicChange = glm::mat4(1.0f);      //�ʱ�ȭ
        basicChange = glm::scale(basicChange, glm::vec3(2.0f, 1.0f, nangansize));      //������ ����
        transformMatrix = basicChange * transformMatrix;   //ũ��
        basicChange = glm::mat4(1.0f);
        basicChange = glm::translate(basicChange, glm::vec3(handrailCoord[i].x, handrailCoord[i].y, handrailCoord[i].z));   //�ǹ��� �־�� �ϴ� ��ġ�� �̵�
        transformMatrix = basicChange * transformMatrix;

        objColor = glm::vec3(0.3f, 0.3f, 0.3f);
        transformLocation = glGetUniformLocation(program, "transform");
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
        viewLocation = glGetUniformLocation(program, "viewTransform");
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &viewMatrix[0][0]);
        projectionLocation = glGetUniformLocation(program, "projectionTransform");
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
        objcolorLocation = glGetUniformLocation(program, "objectColor");
        glUniform3f(objcolorLocation, objColor.x, objColor.y, objColor.z);
        glBindVertexArray(vao[1]);
        glDrawElements(GL_TRIANGLES, vertexCount * 3, GL_UNSIGNED_INT, 0);*/
    }

    for (int i = 2; i < 4; i++) {
        //�ǹ���ü

        transformMatrix = glm::mat4(1.0f);   //�ʱ�ȭ
        basicChange = glm::mat4(1.0f);      //�ʱ�ȭ   
        basicChange = glm::translate(basicChange, glm::vec3(1.50f, -0.5f, -0.5f));  //�������� �̵�(������ü�� �߾��� ����)   Y -0.5
        transformMatrix = basicChange * transformMatrix;

        basicChange = glm::mat4(1.0f);      //�ʱ�ȭ
        basicChange = glm::scale(basicChange, glm::vec3(5.0f, 20.0f, 100.0f));      //������ ����
        transformMatrix = basicChange * transformMatrix;   //ũ��

        basicChange = glm::mat4(1.0f);
        basicChange = glm::translate(basicChange, glm::vec3(buildingCoord[i].x, buildingCoord[i].y, buildingCoord[i].z));     //�ǹ��� �־�� �ϴ� ��ġ�� �̵�
        transformMatrix = basicChange * transformMatrix;

        objColor = glm::vec3(0.0f, 0.8f, 0.5f);
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
    for (int i =4; i < 6; i++) {
        //�ǹ���ü

        transformMatrix = glm::mat4(1.0f);   //�ʱ�ȭ
        basicChange = glm::mat4(1.0f);      //�ʱ�ȭ   
        basicChange = glm::translate(basicChange, glm::vec3(1.50f, -0.5f, -0.5f));  //�������� �̵�(������ü�� �߾��� ����)   Y -0.5
        transformMatrix = basicChange * transformMatrix;

        basicChange = glm::mat4(1.0f);      //�ʱ�ȭ
        basicChange = glm::scale(basicChange, glm::vec3(5.0f, 20.0f, 100.0f));      //������ ����
        transformMatrix = basicChange * transformMatrix;   //ũ��

        basicChange = glm::mat4(1.0f);
        basicChange = glm::translate(basicChange, glm::vec3(buildingCoord[i].x, buildingCoord[i].y, buildingCoord[i].z));     //�ǹ��� �־�� �ϴ� ��ġ�� �̵�
        transformMatrix = basicChange * transformMatrix;

        objColor = glm::vec3(0.0f, 0.0f, 0.5f);
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
    for (int i = 6; i < 8; i++) {
        //�ǹ���ü

        transformMatrix = glm::mat4(1.0f);   //�ʱ�ȭ
        basicChange = glm::mat4(1.0f);      //�ʱ�ȭ   
        basicChange = glm::translate(basicChange, glm::vec3(1.50f, -0.5f, -0.5f));  //�������� �̵�(������ü�� �߾��� ����)   Y -0.5
        transformMatrix = basicChange * transformMatrix;

        basicChange = glm::mat4(1.0f);      //�ʱ�ȭ
        basicChange = glm::scale(basicChange, glm::vec3(5.0f, 20.0f, 100.0f));      //������ ����
        transformMatrix = basicChange * transformMatrix;   //ũ��

        basicChange = glm::mat4(1.0f);
        basicChange = glm::translate(basicChange, glm::vec3(buildingCoord[i].x, buildingCoord[i].y, buildingCoord[i].z));     //�ǹ��� �־�� �ϴ� ��ġ�� �̵�
        transformMatrix = basicChange * transformMatrix;

        objColor = glm::vec3(0.7f, 0.5f, 0.0f);
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


    for (int i = 8; i < 10; i++) {
        //�ǹ���ü

        transformMatrix = glm::mat4(1.0f);   //�ʱ�ȭ
        basicChange = glm::mat4(1.0f);      //�ʱ�ȭ   
        basicChange = glm::translate(basicChange, glm::vec3(1.50f, -0.5f, -0.5f));  //�������� �̵�(������ü�� �߾��� ����)   Y -0.5
        transformMatrix = basicChange * transformMatrix;

        basicChange = glm::mat4(1.0f);      //�ʱ�ȭ
        basicChange = glm::scale(basicChange, glm::vec3(5.0f, 20.0f, 100.0f));      //������ ����
        transformMatrix = basicChange * transformMatrix;   //ũ��

        basicChange = glm::mat4(1.0f);
        basicChange = glm::translate(basicChange, glm::vec3(buildingCoord[i].x, buildingCoord[i].y, buildingCoord[i].z));     //�ǹ��� �־�� �ϴ� ��ġ�� �̵�
        transformMatrix = basicChange * transformMatrix;

        objColor = glm::vec3(0.0f, 0.8f, 0.5f);
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
    for (int i = 10; i < 12; i++) {
        //�ǹ���ü

        transformMatrix = glm::mat4(1.0f);   //�ʱ�ȭ
        basicChange = glm::mat4(1.0f);      //�ʱ�ȭ   
        basicChange = glm::translate(basicChange, glm::vec3(1.50f, -0.5f, -0.5f));  //�������� �̵�(������ü�� �߾��� ����)   Y -0.5
        transformMatrix = basicChange * transformMatrix;

        basicChange = glm::mat4(1.0f);      //�ʱ�ȭ
        basicChange = glm::scale(basicChange, glm::vec3(5.0f, 20.0f, 100.0f));      //������ ����
        transformMatrix = basicChange * transformMatrix;   //ũ��

        basicChange = glm::mat4(1.0f);
        basicChange = glm::translate(basicChange, glm::vec3(buildingCoord[i].x, buildingCoord[i].y, buildingCoord[i].z));     //�ǹ��� �־�� �ϴ� ��ġ�� �̵�
        transformMatrix = basicChange * transformMatrix;

        objColor = glm::vec3(0.0f, 0.0f, 0.5f);
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
  

    //Ŭ���� ���� 

    //�̰� �����ؾ��� 

    transformMatrix = glm::mat4(1.0f);   //�ʱ�ȭ
    basicChange = glm::mat4(1.0f);      //�ʱ�ȭ
    basicChange = glm::translate(basicChange, glm::vec3(-0.5f, -0.5f, -0.5f));  //�������� �̵�(������ü�� �߾��� ����)
    transformMatrix = basicChange * transformMatrix;

    basicChange = glm::mat4(1.0f);      //�ʱ�ȭ
    basicChange = glm::scale(basicChange, glm::vec3(10.0f, 1.0f, 5.0f));      //������ ����
    transformMatrix = basicChange * transformMatrix;   //ũ��

    basicChange = glm::mat4(1.0f);
    basicChange = glm::translate(basicChange, glm::vec3(clear[0].x, clear[0].y, clear[0].z));     //�ǹ��� �־�� �ϴ� ��ġ�� �̵�
    transformMatrix = basicChange * transformMatrix;

    objColor = glm::vec3(0.0f, 0.0f, 1.0f);
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
