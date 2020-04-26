
#include "ui_Sculptor.h"
#include <QtWidgets>
#include <QGLWidget>
#include <QtGui>
#include "MarchingCubes.h"
#include <qpushbutton.h>

class Sculptor : public QGLWidget
{
	Q_OBJECT

public:
	Sculptor(QWidget *parent = NULL);
	~Sculptor();

private:
	//Ui::SculptorClass ui;
	float transCamX, transCamY, transCamZ;
	float camAngleX, camAngleY, camAngleZ;

	float minMCvalue;
	int dimX, dimY, dimZ;
	int formType;
	float baseFormDim;
	int cutterType;
	float cutterDim;
	float cutterPosX, cutterPosY, cutterPosZ;	
	float voxelSize;
	int cutterActivated;
	float cutterSpeed;
	float cutterColor[3];
	float formColor[3];
	float light[4];
	bool timerOn;
	QTimer* timer;
	QPushButton* incrCutter;
	QPushButton* decrCutter;
	QPushButton* incrSpeed;
	QPushButton* decrSpeed;
	QPushButton* changeCutter;
	QPushButton* incrLight;
	QPushButton* decrLight;
	QPushButton* incrForm;
	QPushButton* decrForm;
	QPushButton* changeForm;
	QPushButton* incrRedForm;
	QPushButton* decrRedForm;
	QPushButton* incrGreenForm;
	QPushButton* decrGreenForm;
	QPushButton* incrBlueForm;
	QPushButton* decrBlueForm;	
	QPushButton* incrRedCutter;
	QPushButton* decrRedCutter;
	QPushButton* incrGreenCutter;
	QPushButton* decrGreenCutter;
	QPushButton* incrBlueCutter;
	QPushButton* decrBlueCutter;
	
	QMatrix4x4 transfMatrix;
	mp4Vector* mcPoints;
	TRIANGLE* mcTriangles;
	int numOfTriangles;
	double *matrix;

	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
	void resetDraw();
	void mouseMoveEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent* event);
	//void timerEvent(QTimerEvent * event);
	float calcIsoValue(mpVector point);
	float calcNewIsoValue(mpVector point, float value);
	void executeCut();
	bool cutterInside();		
	private slots:
		void timerEvent();
		void handleIncrCut();
		void handleDecrCut();
		void handleIncrSpeed();
		void handleDecrSpeed();
		void handleChanCut();
		void handleIncrLight();
		void handleDecrLight();
		void handleIncrForm();
		void handleDecrForm();
		void handleChanForm();
		void handleIncrRedForm();
		void handleDecrRedForm();
		void handleIncrGreenForm();
		void handleDecrGreenForm();
		void handleIncrBlueForm();
		void handleDecrBlueForm();
		void handleIncrRedCutt();
		void handleDecrRedCutt();
		void handleIncrGreenCutt();
		void handleDecrGreenCutt();
		void handleIncrBlueCutt();
		void handleDecrBlueCutt();
};

