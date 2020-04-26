#include "Sculptor.h"
#include <GL/glut.h>
#include <qpushbutton.h>
#include <QPainter>

Sculptor::Sculptor(QWidget *parent)
	: QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
	//showFullScreen();
	baseFormDim = 10.0f;
	formType = 0;
	transCamX = 0.0f;
	transCamY = 0.f;
	transCamZ = -(2.0*baseFormDim);
	camAngleX = 0.f;
	camAngleY = 0.f;
	camAngleZ = 0.f;
	cutterType = 0;
	cutterDim = baseFormDim / 10.f;
	cutterPosX = 0.f;
	cutterPosY = 0.f;
	cutterPosZ = 1.5*baseFormDim;
	cutterActivated = 0;
	dimX = 40;
	dimY = 40;
	dimZ = 40;
	voxelSize = baseFormDim / dimX;
	cutterSpeed = 0.1;
	cutterColor[0] = 1.0f; cutterColor[1] = 0.0f; cutterColor[2] = 0.0f;
	formColor[0] = 1.0f; formColor[1] = 1.0f; formColor[2] = 0;
	light[0] = 0.7f; light[1] = 0.7f; light[2] = 0.7f; light[3] = 1;
	minMCvalue = 0.f;
	timer = new QTimer(this);
	timerOn = false;
	connect(timer, SIGNAL(timeout()), this, SLOT(timerEvent()));
	incrCutter = new QPushButton("a", this);
	incrCutter->setGeometry(QRect(QPoint(50, 30), QSize(50, 50)));
	connect(incrCutter, SIGNAL(released()), this, SLOT(handleIncrCut()));
	decrCutter = new QPushButton("b", this);
	decrCutter->setGeometry(QRect(QPoint(50, 90), QSize(50, 50)));
	connect(decrCutter, SIGNAL(released()), this, SLOT(handleDecrCut()));
	incrSpeed = new QPushButton("c", this);
	incrSpeed->setGeometry(QRect(QPoint(50, 150), QSize(50, 50)));
	connect(incrSpeed, SIGNAL(released()), this, SLOT(handleIncrSpeed()));
	decrSpeed = new QPushButton("d", this);
	decrSpeed->setGeometry(QRect(QPoint(50, 210), QSize(50, 50)));
	connect(decrSpeed, SIGNAL(released()), this, SLOT(handleDecrSpeed()));
	changeCutter = new QPushButton("e", this);
	changeCutter->setGeometry(QRect(QPoint(50, 270), QSize(50, 50)));
	connect(changeCutter, SIGNAL(released()), this, SLOT(handleChanCut()));
	incrLight = new QPushButton("f", this);
	incrLight->setGeometry(QRect(QPoint(50, 330), QSize(50, 50)));
	connect(incrLight, SIGNAL(released()), this, SLOT(handleIncrLight()));
	decrLight = new QPushButton("g", this);
	decrLight->setGeometry(QRect(QPoint(50, 390), QSize(50, 50)));
	connect(decrLight, SIGNAL(released()), this, SLOT(handleDecrLight()));
	incrForm = new QPushButton("h", this);
	incrForm->setGeometry(QRect(QPoint(50, 450), QSize(50, 50)));
	connect(incrForm, SIGNAL(released()), this, SLOT(handleIncrForm()));
	decrForm = new QPushButton("i", this);
	decrForm->setGeometry(QRect(QPoint(50, 510), QSize(50, 50)));
	connect(decrForm, SIGNAL(released()), this, SLOT(handleDecrForm()));
	changeForm = new QPushButton("l", this);
	changeForm->setGeometry(QRect(QPoint(50, 570), QSize(50, 50)));
	connect(changeForm, SIGNAL(released()), this, SLOT(handleChanForm()));

	incrRedForm = new QPushButton("m", this);
	incrRedForm->setGeometry(QRect(QPoint(50, 640), QSize(25, 25)));
	connect(incrRedForm, SIGNAL(released()), this, SLOT(handleIncrRedForm()));
	decrRedForm = new QPushButton("n", this);
	decrRedForm->setGeometry(QRect(QPoint(90, 640), QSize(25, 25)));
	connect(decrRedForm, SIGNAL(released()), this, SLOT(handleDecrRedForm()));

	incrGreenForm = new QPushButton("o", this);
	incrGreenForm->setGeometry(QRect(QPoint(50, 700), QSize(25, 25)));
	connect(incrGreenForm, SIGNAL(released()), this, SLOT(handleIncrGreenForm()));
	decrGreenForm = new QPushButton("p", this);
	decrGreenForm->setGeometry(QRect(QPoint(90, 700), QSize(25, 25)));
	connect(decrGreenForm, SIGNAL(released()), this, SLOT(handleDecrGreenForm()));

	incrBlueForm = new QPushButton("q", this);
	incrBlueForm->setGeometry(QRect(QPoint(50, 760), QSize(25, 25)));
	connect(incrBlueForm, SIGNAL(released()), this, SLOT(handleIncrBlueForm()));
	decrBlueForm = new QPushButton("r", this);
	decrBlueForm->setGeometry(QRect(QPoint(90, 760), QSize(25, 25)));
	connect(decrBlueForm, SIGNAL(released()), this, SLOT(handleDecrBlueForm()));

	incrRedCutter = new QPushButton("s", this);
	incrRedCutter->setGeometry(QRect(QPoint(50, 820), QSize(25, 25)));
	connect(incrRedCutter, SIGNAL(released()), this, SLOT(handleIncrRedCutt()));
	decrRedCutter = new QPushButton("t", this);
	decrRedCutter->setGeometry(QRect(QPoint(90, 820), QSize(25, 25)));
	connect(decrRedCutter, SIGNAL(released()), this, SLOT(handleDecrRedCutt()));

	incrGreenCutter = new QPushButton("u", this);
	incrGreenCutter->setGeometry(QRect(QPoint(50, 880), QSize(25, 25)));
	connect(incrGreenCutter, SIGNAL(released()), this, SLOT(handleIncrGreenCutt()));
	decrGreenCutter = new QPushButton("v", this);
	decrGreenCutter->setGeometry(QRect(QPoint(90, 880), QSize(25, 25)));
	connect(decrGreenCutter, SIGNAL(released()), this, SLOT(handleDecrGreenCutt()));

	incrBlueCutter = new QPushButton("w", this);
	incrBlueCutter->setGeometry(QRect(QPoint(50, 940), QSize(25, 25)));
	connect(incrBlueCutter, SIGNAL(released()), this, SLOT(handleIncrBlueCutt()));
	decrBlueCutter = new QPushButton("z", this);
	decrBlueCutter->setGeometry(QRect(QPoint(90, 940), QSize(25, 25)));
	connect(decrBlueCutter, SIGNAL(released()), this, SLOT(handleDecrBlueCutt()));

	mcPoints = new mp4Vector[(dimX + 1)*(dimY + 1)*(dimZ + 1)];
	float halfDim = baseFormDim / 2.0f;
	for (int i = 0; i < dimX + 1; i++)
		for (int j = 0; j < dimY + 1; j++)
			for (int k = 0; k < dimZ + 1; k++)
			{
				mp4Vector vertex(-halfDim + (i*voxelSize), -halfDim + (j*voxelSize), -halfDim + (k*voxelSize), 0);
				if ((i == 0 || j == 0 || k == 0 || i == dimX || j == dimY || k == dimZ) && formType == 0)
					vertex.val = 1;
				else
					vertex.val = calcIsoValue(vertex);
				mcPoints[i*(dimY + 1)*(dimZ + 1) + j*(dimZ + 1) + k] = vertex;
			}
	mcTriangles = MarchingCubes(dimX, dimY, dimZ, minMCvalue, mcPoints, LinearInterp, numOfTriangles);
}

Sculptor::~Sculptor()
{}

void Sculptor::resetDraw()
{
	float halfDim = baseFormDim / 2.0f;
	for (int i = 0; i < dimX + 1; i++)
		for (int j = 0; j < dimY + 1; j++)
			for (int k = 0; k < dimZ + 1; k++)
			{
				mp4Vector vertex(-halfDim + (i*voxelSize), -halfDim + (j*voxelSize), -halfDim + (k*voxelSize), 0);
				if ((i == 0 || j == 0 || k == 0 || i == dimX || j == dimY || k == dimZ) && formType == 0)
					vertex.val = 1;
				else
					vertex.val = calcIsoValue(vertex);
				mcPoints[i*(dimY + 1)*(dimZ + 1) + j*(dimZ + 1) + k] = vertex;
			}
	free(mcTriangles);
	mcTriangles = MarchingCubes(dimX, dimY, dimZ, minMCvalue, mcPoints, LinearInterp, numOfTriangles);
	cutterPosX = 0.f;
	cutterPosY = 0.f;
	cutterPosZ = 1.5*baseFormDim;
	cutterActivated = 0;
	updateGL();
}
void Sculptor::initializeGL()
{
	setWindowTitle("3DSculpting");

	glClearColor(0.5, 0.5, 0.5, 1);
	glClearDepth(1.0f);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_LIGHTING);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	float difColor[] = { 0.5,0.5,0.5,1 };
	//float color[] = { 1,1,1,1 };
	float ambColor[] = { 0,0,0,1 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difColor);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, color);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambColor);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_LIGHT0);

}

void Sculptor::paintGL()
{
	/*
	painter=new QPainter(this);
	painter.begin(this);
	painter->beginNativePainting();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	*/

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(transCamX, transCamY, transCamZ);
	glRotatef(camAngleX, 1, 0, 0);
	glRotatef(camAngleY, 0, 1, 0);
	glRotatef(camAngleZ, 0, 0, 1);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < numOfTriangles; i++) {
		glNormal3f(mcTriangles[i].norm.x, mcTriangles[i].norm.y, mcTriangles[i].norm.z);
		for (int j = 0; j < 3; j++)
		{
			glColor3f(formColor[0], formColor[1], formColor[2]);
			//glColor3f(0.0f, 1.f, 0.0f);
			glVertex3f(mcTriangles[i].p[j].x, mcTriangles[i].p[j].y, mcTriangles[i].p[j].z);
		}

	}
	glEnd();
	if (!timerOn)
	{
		glBegin(GL_LINES);
		glColor3f(0, 0, 1);

		glVertex3f(0.0, 0.0, 0.0);		//x coordinate
		glVertex3f(50, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);		//y coordinate
		glVertex3f(0.0, 50, 0.0);
		glVertex3f(0.0, 0.0, 0.0);		//z coordinate
		glVertex3f(0.0, 0.0, 50);

		//glVertex3f(cutterPosX, cutterPosY, cutterPosZ);
		//QVector4D vec = { 0,0,10,1 };
		//vec = matrix*vec;
		//glVertex3f(vec.x(),vec.y(),vec.z());
		glEnd();

		glTranslatef(cutterPosX, cutterPosY, cutterPosZ);
		glColor3f(cutterColor[0], cutterColor[1], cutterColor[2]);
		if (cutterType == 0)
		{
			GLUquadricObj* sphereQuadric = gluNewQuadric();
			gluSphere(sphereQuadric, cutterDim / 2.0f, 360, 360);
		}
		else if (cutterType == 1)
		{
			glutSolidCube(cutterDim);
		}
	}
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();

	//Draw stringhe
	std::string string = "INCREASE CUTTER SIZE";
	glColor3f(0, 0, 0);
	glRasterPos2i(50, 565);
	for (int i = 0; i < string.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)string[i]);

	string = "DECREASE CUTTER SIZE";
	glRasterPos2i(50, 530);
	for (int i = 0; i < string.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)string[i]);

	string = "INCREASE CUTTER SPEED";
	glRasterPos2i(50, 492);
	for (int i = 0; i < string.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)string[i]);

	string = "DECREASE CUTTER SPEED";
	glRasterPos2i(50, 455);
	for (int i = 0; i < string.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)string[i]);

	string = "CHANGE CUTTER";
	glRasterPos2i(50, 420);
	for (int i = 0; i < string.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)string[i]);

	string = "INCREASE LIGHT";
	glRasterPos2i(50, 385);
	for (int i = 0; i < string.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)string[i]);

	string = "DECREASE LIGHT";
	glRasterPos2i(50, 350);
	for (int i = 0; i < string.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)string[i]);

	string = "INCREASE FORM";
	glRasterPos2i(50, 315);
	for (int i = 0; i < string.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)string[i]);

	string = "DECREASE FORM";
	glRasterPos2i(50, 278);
	for (int i = 0; i < string.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)string[i]);

	string = "CHANGE FORM";
	glRasterPos2i(50, 240);
	for (int i = 0; i < string.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)string[i]);

	string = "+ | - RED FORM";
	glRasterPos2i(50, 207);
	for (int i = 0; i < string.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)string[i]);

	string = "+ | - GREEN FORM";
	glRasterPos2i(50, 172);
	for (int i = 0; i < string.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)string[i]);

	string = "+ | - BLUE FORM";
	glRasterPos2i(50, 135);
	for (int i = 0; i < string.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)string[i]);

	string = "+ | - RED CUTTER";
	glRasterPos2i(50, 100);
	for (int i = 0; i < string.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)string[i]);

	string = "+ | - GREEN CUTTER";
	glRasterPos2i(50, 64);
	for (int i = 0; i < string.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)string[i]);

	string = "+ | - BLUE CUTTER";
	glRasterPos2i(50, 27);
	for (int i = 0; i < string.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)string[i]);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);

	glFlush();
	//painter->endNativePainting();
	//painter.fillRect(10, 10, 100, 100, QColor(100, 100, 100));
	//painter->end();

}

void Sculptor::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float ratio = (float)h / (float)w;
	glFrustum(-1, 1, -ratio, ratio, 1, 200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Sculptor::mouseMoveEvent(QMouseEvent *event)
{
	static int x = event->globalX();
	static int y = event->globalY();
	if (event->buttons() == Qt::LeftButton)
	{
		if (event->modifiers().testFlag(Qt::ShiftModifier))
		{
			camAngleZ += event->x() < x ? -2 : (event->x() == x ? 0 : 2);
			//camAngleX += event->y() < y ? -1 : (event->y() == y ? 0 : 2);
		}
		else
		{
			camAngleY += event->x() < x ? -2 : (event->x() == x ? 0 : 2);
			camAngleX += event->y() < y ? -2 : (event->y() == y ? 0 : 2);
		}
		x = event->x();
		y = event->y();
		updateGL();

	}
}

void Sculptor::keyPressEvent(QKeyEvent* event)
{
	if (event->modifiers().testFlag(Qt::ControlModifier))
	{
		switch (event->key())
		{
		case Qt::Key_A: transCamX += 0.5; updateGL(); break;
		case Qt::Key_D: transCamX -= 0.5; updateGL(); break;
		case Qt::Key_S: transCamY += 0.5; updateGL(); break;
		case Qt::Key_W: transCamY -= 0.5; updateGL(); break;
		}
	}
	else
	{
		switch (event->key())
		{
		case Qt::Key_M:
		{			
			if (timerOn)
			{
				timerOn = false;
				timer->stop();
			}
			else
			{
				timerOn = true;
				timer->start(10);
			}
			
		}break;
		case Qt::Key_R: transCamZ += 0.5; updateGL(); break;
		case Qt::Key_F: transCamZ -= 0.5; updateGL(); break;		
		case Qt::Key_CapsLock: cutterActivated = (cutterActivated == 0) ? 1 : 0; break;
		case Qt::Key_Q:
		{
			cutterPosZ += cutterSpeed;
			if (cutterInside() && cutterActivated)
				executeCut();
			updateGL();
		}
		break;
		case Qt::Key_E:
		{
			cutterPosZ -= cutterSpeed;
			if (cutterInside() && cutterActivated)
				executeCut();
			updateGL();
		}
		break;
		case Qt::Key_A:
		{
			cutterPosX -= cutterSpeed;
			if (cutterInside() && cutterActivated)
				executeCut();
			updateGL();
		}
		break;
		case Qt::Key_D:
		{
			cutterPosX += cutterSpeed;
			if (cutterInside() && cutterActivated)
				executeCut();
			updateGL();
		}
		break;
		case Qt::Key_W:
		{
			cutterPosY += cutterSpeed;
			if (cutterInside() && cutterActivated)
				executeCut();
			updateGL();
		}
		break;
		case Qt::Key_S:
		{
			cutterPosY -= cutterSpeed;
			if (cutterInside() && cutterActivated)
				executeCut();
			updateGL();
		}
		break;
		default: event->ignore(); break;
		}
	}
}

float Sculptor::calcIsoValue(mpVector point)
{
	if (formType == 0)
		return std::max(abs(point.x), std::max(abs(point.y), abs(point.z))) - (baseFormDim / 2.0f);
	else
	{
		float pointX = std::pow((point.x), 2);
		float pointY = std::pow((point.y), 2);
		float pointZ = std::pow((point.z), 2);
		float rad = baseFormDim / 2.0f;
		float dist = std::sqrt(pointX + pointY + pointZ);
		return dist - rad;
	}
}

float Sculptor::calcNewIsoValue(mpVector point, float formValue)
{
	float cutterValue;
	if (cutterType == 0)
	{
		float pointX = std::pow((point.x - cutterPosX), 2);
		float pointY = std::pow((point.y - cutterPosY), 2);
		float pointZ = std::pow((point.z - cutterPosZ), 2);
		float rad = cutterDim / 2.0f;
		float dist = std::sqrt(pointX + pointY + pointZ);
		cutterValue = dist - rad;
	}
	else if (cutterType == 1)
	{
		cutterValue = std::max(abs(point.x - cutterPosX), std::max(abs(point.y - cutterPosY), abs(point.z - cutterPosZ))) - (cutterDim / 2.0f);
	}
	if (cutterValue >= 0.f && formValue > 0.f)
		return formValue;
	if (cutterValue <= 0.f && formValue < 0.f)
		if (cutterValue == 0 && cutterType == 1)
			return voxelSize;
		else
			return -cutterValue;
	if (cutterValue >= 0.f && formValue <= 0.f)
	{
		if (abs(cutterValue)<abs(formValue))
			return -cutterValue;
		else
			return formValue;
	}
	if (cutterValue <= 0.f && formValue>0.f)
	{
		if (abs(cutterValue) < abs(formValue))
			return formValue;
		else
			return -cutterValue;
	}
}

void Sculptor::timerEvent()
{
	transCamX = 0;
	transCamY =0;
	transCamZ = -(3.0*baseFormDim);
	camAngleX = 0;
	camAngleZ = 0;

	camAngleY += 0.1;
	camAngleY = (camAngleY > 360.0) ? camAngleY - 360.0 : camAngleY;
	updateGL();
}
void Sculptor::handleIncrCut()
{
	cutterDim += 0.05;
	updateGL();
}
void Sculptor::handleDecrCut()
{
	cutterDim -= 0.05;
	updateGL();
}
void Sculptor::handleIncrSpeed()
{
	cutterSpeed += 0.01;
}
void Sculptor::handleDecrSpeed()
{
	if (cutterSpeed - 0.01 < 0)
		cutterSpeed = 0;
	else
		cutterSpeed -= 0.01;
}
void Sculptor::handleChanCut()
{
	cutterType = (cutterType == 0) ? 1 : 0;
	cutterActivated = 0;
	updateGL();
}
void Sculptor::handleIncrLight()
{
	if (light[0] < 1.0)
	{
		light[0] += 0.05;
		light[1] += 0.05;
		light[2] += 0.05;
	}
	updateGL();
}
void Sculptor::handleDecrLight()
{
	if (light[0] > 0.0)
	{
		light[0] -= 0.05;
		light[1] -= 0.05;
		light[2] -= 0.05;
	}
	updateGL();
}
void Sculptor::handleIncrForm()
{
	baseFormDim += 1.0;
	voxelSize = baseFormDim / dimX;
	resetDraw();
}
void Sculptor::handleDecrForm()
{
	baseFormDim = (baseFormDim - 1.0 < 1.0) ? 1.0 : baseFormDim - 1.0;
	voxelSize = baseFormDim / dimX;
	resetDraw();
}
void Sculptor::handleChanForm()
{
	formType = (formType == 0) ? 1 : 0;
	resetDraw();
}
void Sculptor::handleIncrRedForm()
{
	(formColor[0] + 0.1 > 1.0) ? formColor[0] = 1.0 : formColor[0] += 0.1;
	updateGL();
}
void Sculptor::handleDecrRedForm()
{
	(formColor[0] - 0.1 < 0) ? formColor[0] = 0 : formColor[0] -= 0.1;
	updateGL();
}
void Sculptor::handleIncrGreenForm()
{
	(formColor[1] + 0.1 > 1.0) ? formColor[1] = 1.0 : formColor[1] += 0.1;
	updateGL();
}
void Sculptor::handleDecrGreenForm()
{
	(formColor[1] - 0.1 < 0) ? formColor[1] = 0 : formColor[1] -= 0.1;
	updateGL();
}
void Sculptor::handleIncrBlueForm()
{
	(formColor[2] + 0.1 > 1.0) ? formColor[2] = 1.0 : formColor[2] += 0.1;
	updateGL();
}
void Sculptor::handleDecrBlueForm()
{
	(formColor[2] - 0.1 < 0) ? formColor[2] = 0 : formColor[2] -= 0.1;
	updateGL();
}
void Sculptor::handleIncrRedCutt()
{
	(cutterColor[0] + 0.1 > 1.0) ? cutterColor[0] = 1.0 : cutterColor[0] += 0.1;
	updateGL();
}
void Sculptor::handleDecrRedCutt()
{
	(cutterColor[0] - 0.1 < 0) ? cutterColor[0] = 0 : cutterColor[0] -= 0.1;
	updateGL();
}
void Sculptor::handleIncrGreenCutt()
{
	(cutterColor[1] + 0.1 > 1.0) ? cutterColor[1] = 1.0 : cutterColor[1] += 0.1;
	updateGL();
}
void Sculptor::handleDecrGreenCutt()
{
	(cutterColor[1] - 0.1 < 0) ? cutterColor[1] = 0 : cutterColor[1] -= 0.1;
	updateGL();
}
void Sculptor::handleIncrBlueCutt()
{
	(cutterColor[2] + 0.1 > 1.0) ? cutterColor[2] = 1.0 : cutterColor[2] += 0.1;
	updateGL();
}
void Sculptor::handleDecrBlueCutt()
{
	(cutterColor[2] - 0.1 < 0) ? cutterColor[2] = 0 : cutterColor[2] -= 0.1;
	updateGL();
}

void Sculptor::executeCut()
{
	float minX, minY, minZ, maxX, maxY, maxZ;
	minX = std::floor((cutterPosX - (cutterDim / 2.0f) + baseFormDim / 2.0f) / voxelSize);
	maxX = std::ceil((cutterPosX + (cutterDim / 2.0f) + baseFormDim / 2.0f) / voxelSize);
	minY = std::floor((cutterPosY - (cutterDim / 2.0f) + baseFormDim / 2.0f) / voxelSize);
	maxY = std::ceil((cutterPosY + (cutterDim / 2.0f) + baseFormDim / 2.0f) / voxelSize);
	minZ = std::floor((cutterPosZ - (cutterDim / 2.0f) + baseFormDim / 2.0f) / voxelSize);
	maxZ = std::ceil((cutterPosZ + (cutterDim / 2.0f) + baseFormDim / 2.0f) / voxelSize);
	minX = (minX< 0) ? 0 : minX;
	minY = (minY < 0) ? 0 : minY;
	minZ = (minZ < 0) ? 0 : minZ;
	maxX = (maxX > dimX) ? dimX : maxX;
	maxY = (maxY > dimY) ? dimY : maxY;
	maxZ = (maxZ > dimZ) ? dimZ : maxZ;
	for (int i = minX; i < maxX + 1; i++)
		for (int j = minY; j < maxY + 1; j++)
			for (int k = minZ; k < maxZ + 1; k++) {
				mp4Vector vert(-(baseFormDim / 2.0f) + i*voxelSize, -(baseFormDim / 2.0f) + j*voxelSize, -(baseFormDim / 2.0f) + k*voxelSize, 0);
				mcPoints[i*(dimY + 1)*(dimZ + 1) + j*(dimZ + 1) + k].val = calcNewIsoValue(vert, mcPoints[i*(dimY + 1)*(dimZ + 1) + j*(dimZ + 1) + k].val);
			}
	free(mcTriangles);
	mcTriangles = MarchingCubes(dimX, dimY, dimZ, minMCvalue, mcPoints, LinearInterp, numOfTriangles);
}
bool Sculptor::cutterInside()
{
	float halfDim = baseFormDim / 2.0;
	float cutterRad = cutterDim / 2.0;
	if (cutterPosX >= -halfDim - cutterRad && cutterPosX <= halfDim + cutterRad && cutterPosY >= -halfDim - cutterRad && cutterPosY <= halfDim + cutterRad && cutterPosZ >= -halfDim - cutterRad && cutterPosZ <= halfDim + cutterRad)
		return true;
	else
		return false;
}
