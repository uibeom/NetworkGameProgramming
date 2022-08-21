#pragma once

//�� ��� 
#include <stdio.h>
#include <string.h>
#include <math.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>

typedef enum {
    MODE_BITMAP,
    MODE_STROKE
} mode_type;

static mode_type mode;
static int font_index;
int g_time;

void
print_bitmap_string(void* font, const char* s)
{
    if (s && strlen(s)) {
        while (*s) {
            glutBitmapCharacter(font, *s);
            s++;
        }
    }
}


void
print_stroke_string(void* font, const char* s)
{
    if (s && strlen(s)) {
        while (*s) {
            glutStrokeCharacter(font, *s);
            s++;
        }
    }
}
void
my_init()
{
    mode = MODE_BITMAP;
    font_index = 0;
}
void
my_reshape(int w, int h)
{
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

}

void
my_handle_key(GLubyte key, GLint x, GLint y)
{
    switch (key) {

    case 27:    /* Esc - Quits the program. */
        printf("done.\n");
        exit(1);
        break;

    case ' ':    /* Space - toggles mode.     */
        mode = (mode == MODE_BITMAP) ? MODE_STROKE : MODE_BITMAP;
        font_index = 0;
        glutPostRedisplay();
        break;

    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
        if (mode == MODE_BITMAP || key == '1' || key == '2') {
            font_index = key - '1';
        }
        glutPostRedisplay();
        break;

    default:
        break;
    }
}
void
draw_stuff()
{
    char string[8][256];
    unsigned int i, j;
    unsigned int count;
    void* bitmap_fonts[7] = {
       GLUT_BITMAP_9_BY_15,
       GLUT_BITMAP_8_BY_13,
       GLUT_BITMAP_TIMES_ROMAN_10,
       GLUT_BITMAP_TIMES_ROMAN_24,
       GLUT_BITMAP_HELVETICA_10,
       GLUT_BITMAP_HELVETICA_12,
       GLUT_BITMAP_HELVETICA_18
    };

    const char* bitmap_font_names[7] = {
       "GLUT_BITMAP_9_BY_15",
       "GLUT_BITMAP_8_BY_13",
       "GLUT_BITMAP_TIMES_ROMAN_10",
       "GLUT_BITMAP_TIMES_ROMAN_24",
       "GLUT_BITMAP_HELVETICA_10",
       "GLUT_BITMAP_HELVETICA_12",
       "GLUT_BITMAP_HELVETICA_18"
    };

    void* stroke_fonts[2] = {
       GLUT_STROKE_ROMAN,
       GLUT_STROKE_MONO_ROMAN
    };

    const char* stroke_font_names[2] = {
       "GLUT_STROKE_ROMAN",
       "GLUT_STROKE_MONO_ROMAN"
    };

    GLfloat x, y, ystep, yild, stroke_scale;

    /* Set up some strings with the characters to draw. */          //���⼭ ���ϴ� �� �ֱ� 
    count = 0;
    std::string test = to_string(g_time);
    char const* time_text = test.c_str();

    for (i = 0; i < test.length(); ++i)
        string[0][i] = time_text[i];
    string[0][test.length()] = '\0';



    /* Draw the strings, according to the current mode and font. */
    glColor4f(1.0, 1.0, 0.0, 0.0);
    x = -20.0;
    y = 250.0;
    ystep = 100.0;
    yild = 20.0;
    if (mode == MODE_BITMAP) {
        glRasterPos2f(-150, y + 1.25 * yild);
        /*print_bitmap_string(
            bitmap_fonts[font_index], bitmap_font_names[font_index]);*/
        for (j = 0; j < 1; j++) {
            glRasterPos2f(x, y);
            print_bitmap_string(bitmap_fonts[font_index], string[j]);
            y -= yild;
        }
    }
    else {
        stroke_scale = 0.1f;
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix(); {
        
            glTranslatef(x, y + 1.25 * yild, 0.0);
            glScalef(stroke_scale, stroke_scale, stroke_scale);
            print_stroke_string(
                stroke_fonts[font_index], stroke_font_names[font_index]);
        } glPopMatrix();
        glPushMatrix(); {
            glTranslatef(x, y, 0.0);
            for (j = 0; j < 4; j++) {
                glPushMatrix(); {
                    glScalef(stroke_scale, stroke_scale, stroke_scale);
                    print_stroke_string(stroke_fonts[font_index], string[j]);
                } glPopMatrix();
                glTranslatef(0.0, -yild, 0.0);
            }
            glTranslatef(0.0, -ystep, 0.0);
        } glPopMatrix();
    }
}
