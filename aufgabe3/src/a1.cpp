#include <stdio.h>
#include <GL/freeglut.h>


static void draw() {
	glClearColor(0, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}

static void resize(int width, int height) {
	glViewport(0, 0, width, height);
}

static void keyboard(unsigned char key, int x, int y) {
	if (key == 'q') glutLeaveMainLoop();
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(640, 480);
	glutCreateWindow("cpp4cg3-Window");

	glutDisplayFunc(draw);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutMainLoop();
	return 0;
}
