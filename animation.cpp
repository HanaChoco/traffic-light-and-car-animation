// 2023年2月作成
// version 1.0.0



#include <GL/glut.h>

// 左クリック、右クリック
int L_Button, R_Button;

// 点光源
GLfloat light0pos[] = { 20.0, 40.0, 20.0, 1.0 };
GLfloat light1pos[] = { 0.0, 30.0, 40.0, 1.0 };

GLfloat sun[] = { 1.0, 1.0, 0.8, 1.0 };

// クルマの移動量
double move_car = -10.0;

int count = 0;

// 信号機のスイッチ
bool signal_switch = false;

GLfloat carbody_def1[] = { 1.0, 0.5, 0.5, 1.0 };
GLfloat carbody_def2[] = { 0.5, 1.0, 0.5, 1.0 };
GLfloat carbody_def3[] = { 0.5, 0.5, 1.0, 1.0 };

GLfloat signal_off[] = {0.2, 0.2, 0.2, 1.0};

// Tの中心を回転軸とする回転角
double theta_T = 0.0;

void idle(void)
{
	glutPostRedisplay();
}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(4, 5, 6, 0, 0, 0, 0, 1, 0);

	/* 光源の位置設定 */
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
	glLightfv(GL_LIGHT1, GL_POSITION, light1pos);

	// 左クリックが押された時
	if (L_Button == 1) {

		// クルマの移動
		// 横断歩道側の信号が青のとき
		// 車側は赤信号
		if (signal_switch == false) {
			// 停止線の手前まで徐々に進む
			if (move_car>=-5 && 0 >= move_car) {
				move_car += 0.005;
			}
			else if ( move_car < -5 || (move_car > 5 && move_car < 40)) {
				// 停止線を越えているので進む
				move_car += 0.01;

			} else if(move_car > 40){
				move_car = -25.0;
				// 車体色変更フラグの更新
				count++;
				if (count > 2)count = 0;
			}

		// 横断歩道側の信号が赤のとき
		// 車側は青信号
		} else if (signal_switch == true) {
			// 進む
			if (move_car < 40) {
				move_car += 0.01;
			}
			else {
				move_car = -25.0;
				// 車体色変更フラグの更新
				count++;
				if (count > 2)count = 0;
			}
		}

	}

	// 地面
	glPushMatrix();
	glTranslated(0.0, -10.0, 0.0);
	glScaled(20.0, 1.0, 20.0);
	GLfloat road_def[] = { 0.5, 0.5, 0.5, 1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, road_def);
	glutSolidCube(2.0);
	glPopMatrix();

	// 信号
	// 柱
	glPushMatrix();
	GLfloat pillar_def[] = { 0.5, 0.5, 0.5, 1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, pillar_def);
	glTranslated(7.0, 0.0, 0.0);

	glPushMatrix();
	glScaled(1.0, 10.0, 1.0);
	glutSolidCube(2.0);
	glPopMatrix();

	// ライト部分
	glPushMatrix();
	glTranslated(3.0, 6.0, 0.0);
	glScaled(3.0, 4.0, 1.0);
	glutSolidCube(2.0);
	glPopMatrix();

	// ライト
	//赤
	switch (signal_switch) {
	case true:
		glMaterialfv(GL_FRONT, GL_DIFFUSE, carbody_def1);
		break;
	case false:
		glMaterialfv(GL_FRONT, GL_DIFFUSE, signal_off);
		break;
	default:
		glMaterialfv(GL_FRONT, GL_DIFFUSE, signal_off);
	}
	glPushMatrix();
	glTranslated(3.0, 7.5, 0.2);
	glScaled(1.6, 1.2, 1.0);
	glutSolidCube(2.0);
	glPopMatrix();

	// 青
	switch (signal_switch) {
	case true:
		glMaterialfv(GL_FRONT, GL_DIFFUSE, signal_off);
		break;
	case false:
		glMaterialfv(GL_FRONT, GL_DIFFUSE, carbody_def2);
		break;
	default:
		glMaterialfv(GL_FRONT, GL_DIFFUSE, signal_off);
	}
	glPushMatrix();
	glTranslated(3.0, 4.0, 0.2);
	glScaled(1.6, 1.2, 1.0);
	glutSolidCube(2.0);
	glPopMatrix();
	glPopMatrix();

	// 車線
	glPushMatrix();
	GLfloat roadline_def[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, roadline_def);
	glScaled(20.0, 1.0, 1.0);

	//車線1
	glPushMatrix();
	glTranslated(0.0, -9.9, 15.0);
	glutSolidCube(2.0);
	glPopMatrix();
	// 車線2
	glPushMatrix();
	glTranslated(0.0, -9.9, 3.0);
	glutSolidCube(2.0);
	glPopMatrix();
	glPopMatrix();

	// 車道の停止線
	glPushMatrix();
	glTranslated(5.0, -9.9, 8.0);
	glScaled(1.0, 1.0, 4.0);
	glutSolidCube(2.0);
	glPopMatrix();

	// 横断歩道
	glPushMatrix();
	glTranslated(13.0, -9.9, 5.5);
	glScaled(3.0, 1.0, 0.7);

	glPushMatrix();
	glutSolidCube(2.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 0.0, 5.0);
	glutSolidCube(2.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 0.0, 10.0);
	glutSolidCube(2.0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	// クルマのオブジェクトの移動
	glTranslated(move_car, 0.0, 9.0);

	// 車体の色の変更
	switch (count) {
	case 0:
		glMaterialfv(GL_FRONT, GL_DIFFUSE, carbody_def1);
		break;
	case 1:
		glMaterialfv(GL_FRONT, GL_DIFFUSE, carbody_def2);
		break;
	case 2:
		glMaterialfv(GL_FRONT, GL_DIFFUSE, carbody_def3);
		break;
	default:
		glMaterialfv(GL_FRONT, GL_DIFFUSE, carbody_def1);
	}

	// 車体
	glPushMatrix();
	glTranslated(0.0, -4.0, 0.0);
	glScaled(6.0, 2.5, 4.0);
	glutSolidCube(2.0);
	glPopMatrix();

	glPushMatrix();
	glScaled(3.0, 3.0, 4.0);
	glutSolidCube(2.0);
	glPopMatrix();

	// タイヤ
	GLfloat tires_def[] = { 0.3, 0.3, 0.3, 1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, tires_def);
	// 前輪
	glPushMatrix();
	glTranslated(3.0, -7.5, 4.0);
	glScaled(1.0, 1.0, 0.5);
	glutSolidSphere(2.0, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslated(3.0, -7.5, -4.0);
	glScaled(1.0, 1.0, 0.5);
	glutSolidSphere(2.0, 10, 10);
	glPopMatrix();
	// 後輪
	glPushMatrix();
	glTranslated(-3.0, -7.5, 4.0);
	glScaled(1.0, 1.0, 0.5);
	glutSolidSphere(2.0, 10, 10);
	glPopMatrix();

	// ライト
	GLfloat carlight_def[] = { 1.0, 1.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, carlight_def);

	glPushMatrix();
	glTranslated(5.75, -2.25, 3.25);
	glScaled(0.5, 1.0, 1.0);
	glutSolidCube(2.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(5.75, -2.25, -3.25);
	glScaled(0.5, 1.0, 1.0);
	glutSolidCube(2.0);
	glPopMatrix();

	glPopMatrix();

	// 建物
	glPushMatrix();
	glTranslated(-5.0, 0.0, -10.0);
	// 屋根
	GLfloat roof_def[] = { 0.7, 0.7, 0.7, 1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, roof_def);
	glPushMatrix();
	glTranslated(0.0, 8.0, 0.0);
	glScaled(12.5, 3.0, 8.0);
	glutSolidCube(2);
	glPopMatrix();
	// 本体
	GLfloat building_def[] = { 0.8, 0.8, 0.8, 1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, building_def);
	glPushMatrix();
	glScaled(12.0, 10.0, 6.0);
	glutSolidCube(2);
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-30, 30, -30, 30, -40.0, 40.0);

	glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			L_Button = 1;
		}
		else {
			L_Button = 0;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {
			R_Button = 1;
		}
		else {
			R_Button = 0;
		}
		break;
	default:
		break;
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		signal_switch = !signal_switch;
	}

	if ((L_Button == 0) && (R_Button == 0)) glutIdleFunc(0);
	else glutIdleFunc(idle);
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	//glEnable(GL_LIGHT2);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, sun);
	glLightfv(GL_LIGHT1, GL_SPECULAR, sun);

}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	init();
	glutMainLoop();
	return 0;
}