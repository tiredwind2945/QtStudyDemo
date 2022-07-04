#pragma execution_character_set("utf-8")		
#include <QtGui>
#include <QtWidgets>
#include <QMainWindow>
#include <QSpinBox>

#include "opencv2/highgui/highgui.hpp"    
#include "opencv2/opencv.hpp"    
#include <opencv2/core/core.hpp>  

#include "header/MainWindow.h"
#include "header/CreateMenu.h"
#include "header/ImgChange.h"
#include "header/Geom.h"
#include "header/Gray.h"
#include "header/Enhance.h"
#include "header/Morp.h"
using namespace cv;
using namespace std;

ImageProcessing::ImageProcessing(QWidget *parent) :
	QMainWindow(parent)
{
	ui.setupUi(this);
	init();
	Show(); 
}

ImageProcessing::~ImageProcessing()
{
}

// ��ʼ��
void ImageProcessing::init()
{
	imgVector.resize(2);

	// ���ͼ��
	setWindowIcon(QIcon("../Image/icon/ImageProcessing.png"));

	// ��ĳ�ʼ��
	imgChangeClass = new ImgChange;
	geomClass = new Geom;
	grayClass = new Gray; 
	enhanceClass = new Enhance;  
	morpClass = new Morp;

	// ������ڱ༭��
	outputEdit = new QTextEdit();
	outputEdit->textCursor().movePosition(QTextCursor::End);		// ��ֱ�������Զ����ٵ���ײ�
	outputEdit->setWordWrapMode(QTextOption::NoWrap);				// ˮƽ������
	outputEdit->setReadOnly(true);

	// ������
	drawType = 0;

	// ������� 
	isSkin = false;
	whiteRadio = new QRadioButton();// ��ѡ��
	blackRadio = new QRadioButton();

	QFile file("../qss/black.qss");
	file.open(QFile::ReadOnly);
	QTextStream filetext(&file);
	stylesheet = filetext.readAll();
	file.close();
}

// ��ʾ����
void ImageProcessing::Show()
{
	// �����С
	setWindowTitle("ͼ�����Ա���� by �ʼ�");
	resize(QApplication::desktop()->width()*0.9, QApplication::desktop()->height()*0.9);
	move(QApplication::desktop()->width()*0.05, QApplication::desktop()->height()*0.01);

	// �˵���
	I_menubar = new Menu(this, this);
	this->setMenuBar(I_menubar);

	// ����
	CreateLayout();

	// ͼ�񴰿�
	InitImage();	

	// ��ɫ����
	//this->setStyleSheet(stylesheet);
	//preWin->setStyleSheet(stylesheet);
	//I_menubar->setMenuQSS(true);
	//blackRadio->setChecked(true);
	//isSkin = true;
}

// -------------------------------------�ָ���---------------------------------------------------------------------

// ��������
void ImageProcessing::CreateLayout()
{
	QWidget* p = takeCentralWidget();	//ɾ�����봰��
	if (p)
		delete p;
	setDockNestingEnabled(true);		//����Ƕ��dock

	WinMain();		// ���崰��
	WinTool();		// ������
	WinPreview();	// Ԥ������
	WinGeom();		// ���α任����
	WinGray();		// �Ҷȱ任����
	WinEnhance();	// ͼ����ǿ����
	WinMorp();		// ��̬ѧ������
	WinColor();		// ��ɫģ�ʹ���
	WinProp();		// ���Դ���	
	ColorToolBar();	// ��ͼ������
		
	// ���ڴ�С
	dock_Tool->setFixedWidth(100);
	dock_Geom->setFixedWidth(450);
	dock_Gray->setFixedWidth(450);
	dock_Enhance->setFixedWidth(450);
	dock_Morp->setFixedWidth(450);
	dock_Color->setFixedWidth(450);
	dock_Prop->setMaximumHeight(240);
	
	// ����
	setCentralWidget(dock_Image);
	addDockWidget(Qt::LeftDockWidgetArea, dock_Tool);
	addDockWidget(Qt::BottomDockWidgetArea, dock_Output);
	addDockWidget(Qt::RightDockWidgetArea, dock_Geom);
	addDockWidget(Qt::RightDockWidgetArea, dock_Gray);
	addDockWidget(Qt::RightDockWidgetArea, dock_Enhance);
	addDockWidget(Qt::RightDockWidgetArea, dock_Morp);
	addDockWidget(Qt::RightDockWidgetArea, dock_Color);
	addDockWidget(Qt::RightDockWidgetArea, dock_Prop);

	splitDockWidget(dock_Tool, dock_Image, Qt::Horizontal);		// ˮƽ��ֱ
//	splitDockWidget(dock_Image, dock_Output, Qt::Vertical);
	splitDockWidget(dock_Geom, dock_Prop, Qt::Vertical);
	splitDockWidget(dock_Gray, dock_Prop, Qt::Vertical);
	splitDockWidget(dock_Enhance, dock_Prop, Qt::Vertical);
	splitDockWidget(dock_Morp, dock_Prop, Qt::Vertical);
	splitDockWidget(dock_Color, dock_Prop, Qt::Vertical);
	
	splitDockWidget(dock_Geom, dock_Output, Qt::Vertical);
	splitDockWidget(dock_Gray, dock_Output, Qt::Vertical);
	splitDockWidget(dock_Enhance, dock_Output, Qt::Vertical);
	splitDockWidget(dock_Morp, dock_Output, Qt::Vertical);
	splitDockWidget(dock_Color, dock_Output, Qt::Vertical);

	tabifyDockWidget(dock_Geom, dock_Gray);		// �ϲ�
	tabifyDockWidget(dock_Gray, dock_Enhance);
	tabifyDockWidget(dock_Enhance, dock_Morp);
	tabifyDockWidget(dock_Morp, dock_Color);
	tabifyDockWidget(dock_Output, dock_Prop);
	dock_Geom->raise();
	dock_Output->raise();	
	
	connect(dock_Image, SIGNAL(visibilityChanged(bool)), this, SLOT(isDockImage()));
	connect(dock_Tool, SIGNAL(visibilityChanged(bool)), this, SLOT(isDockTool()));
	connect(dock_Output, SIGNAL(visibilityChanged(bool)), this, SLOT(isDockOutput()));
	connect(dock_Prop, SIGNAL(visibilityChanged(bool)), this, SLOT(isDockProp()));
	connect(dock_Geom, SIGNAL(visibilityChanged(bool)), this, SLOT(isDockGeom()));
	connect(dock_Gray, SIGNAL(visibilityChanged(bool)), this, SLOT(isDockGray()));
	connect(dock_Enhance, SIGNAL(visibilityChanged(bool)), this, SLOT(isDockEnhance()));
	connect(dock_Morp, SIGNAL(visibilityChanged(bool)), this, SLOT(isDockMorp()));
	connect(dock_Color, SIGNAL(visibilityChanged(bool)), this, SLOT(isDockColor()));
}

// ��ʼ��ͼ��
void ImageProcessing::InitImage()
{
	imgLabel = new PaintWidget(dock_Image);
	imgLabel->setScaledContents(true);

	// ��ʼͼ��
	//QString filename = "../test/test.jpg";
	//QImage *testimg = new QImage();
	//if (!(testimg->load(filename)))
	//{
	//	QMessageBox::information(this, tr("��ͼ��ʧ��"), tr("��ͼ��ʧ��!"));
	//	delete testimg;
	//	return;
	//}

	QImage image = QImage(500, 500, QImage::Format_RGB32);
	image.fill(qRgb(255, 255, 255));
	imgLabel->setPenWidth(2);
	imgLabel->setPenColor(Qt::black);
	imgLabel->setImage(image);
	imgLabel->setPixmap(QPixmap::fromImage(image));
	imgVector[0].push_back(image);
	UpdateProp(image);
	UpdateImgName("ͼ��");


	iter = imgVector[0].end() - 1;						// ���һ��Ԫ�ض�Ӧ�ĵ�����ָ��
	I_menubar->Act_edit_undo->setEnabled(false);		// ��������
	I_menubar->Act_edit_redo->setEnabled(false);		// ����������

	// ���ӹ�����
	ImgscrollArea = new QScrollArea();
	ImgscrollArea->setBackgroundRole(QPalette::Dark);
	ImgscrollArea->setAlignment(Qt::AlignCenter);
	ImgscrollArea->setWidget(imgLabel);
	dock_Image->setWidget(ImgscrollArea);
}

// ��ʾͼ��
void ImageProcessing::ShowImage(QImage Img, bool isSave)
{
	imgLabel->setImage(Img);
	imgLabel->setPixmap(QPixmap::fromImage(Img));
	imgLabel->resize(Img.width(), Img.height());
	UpdateProp(Img);
	if (isSave == true)
	{		
		if (iter != (imgVector[0].end() - 1))
		{
			imgVector[0].erase(++iter, imgVector[0].end());
		}
		
		imgVector[0].push_back(Img);
		iter = imgVector[0].end() - 1;
		I_menubar->Act_edit_undo->setEnabled(true);
		I_menubar->Act_edit_redo->setEnabled(false);	
	}
}

// Ԥ��ͼ��
void ImageProcessing::PreviewImage(QImage Img)			
{
	preLabel->setImage(Img);
	preLabel->setPixmap(QPixmap::fromImage(Img));
	preLabel->resize(Img.width(), Img.height());
}

// ���
void ImageProcessing::output(QString information)			
{
	outputEdit->append(information);
}

// --------------------------------------��������-----------------------------------------------------------------

// ���崰��
void ImageProcessing::WinMain()						
{
	dock_Image = new QDockWidget(this);				//	ͼ��
	dock_Image->setWindowTitle(QString("ͼ��"));
	dock_Image->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
	
	dock_Output = new QDockWidget(tr("�������"), this);				// �������
	dock_Output->setFeatures(QDockWidget::AllDockWidgetFeatures);
	dock_Output->setWidget(outputEdit);
}

// Ԥ������
void ImageProcessing::WinPreview()
{
	preWin = new CustomWindow;
	preWin->resize(700, 820);

	preButtonGroup = new QButtonGroup();
	connect(preButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(preButtonClicked(int)));

	// ������
	preLabel = new PaintWidget(preWin);
	preLabel->setScaledContents(true);

	QScrollArea* scrollArea = new QScrollArea(preWin);// ���ӹ�����
	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setAlignment(Qt::AlignCenter);
	scrollArea->setWidget(preLabel);
	scrollArea->resize(600, 600);

	QImage image = QImage(550, 550, QImage::Format_RGB32);
	image.fill(qRgb(255, 255, 255));
	preLabel->setImage(image);
	preLabel->setPixmap(QPixmap::fromImage(image));
	preLabel->resize(image.width(), image.height());
	
	QPushButton *button_cancel = new QPushButton(tr("�˳�Ԥ��/Esc"), preWin);
	connect(button_cancel, SIGNAL(clicked()), preWin, SLOT(close()));

	scrollArea->move(50, 50);
	button_cancel->move(500, 770);
	button_cancel->resize(120, 30);

	// ����Ԥ��
	QLabel *label_size = new QLabel(tr("���ű���:"));
	spinbox_size = new QSpinBox(preWin);
	spinbox_size->setAlignment(Qt::AlignCenter);
	spinbox_size->setRange(-40, 40);
	spinbox_size->setValue(0);

	QSlider *slider_size = new QSlider(Qt::Horizontal, preWin);	 
	slider_size->setRange(-40, 40);
	slider_size->setValue(0);
	
	connect(spinbox_size, SIGNAL(valueChanged(int)), slider_size, SLOT(setValue(int)));
	connect(slider_size, SIGNAL(valueChanged(int)), spinbox_size, SLOT(setValue(int)));
	connect(spinbox_size, SIGNAL(valueChanged(int)), this, SLOT(enlargeReduce()));

	QHBoxLayout *sizeLayout = new QHBoxLayout();
	sizeLayout->addWidget(label_size);
	sizeLayout->setStretchFactor(label_size, 1);
	sizeLayout->addWidget(slider_size);
	sizeLayout->setStretchFactor(slider_size, 5);
	sizeLayout->addWidget(spinbox_size);
	sizeLayout->setStretchFactor(spinbox_size, 2);

	widget_pre[0] = new QWidget(preWin);
	widget_pre[0]->setLayout(sizeLayout);
	widget_pre[0]->move(50, 660);
	widget_pre[0]->resize(600, 100);
	
	// ��תԤ��
	QLabel *label_rotate = new QLabel(tr("��ת�Ƕ�:"));
	spinbox_rotate = new QSpinBox;
	spinbox_rotate->setAlignment(Qt::AlignCenter);
	spinbox_rotate->setRange(-360, 360);
	spinbox_rotate->setValue(0);

	QSlider *slider_rotate = new QSlider(Qt::Horizontal);	 
	slider_rotate->setRange(-360, 360);
	slider_rotate->setValue(0);

	connect(spinbox_rotate, SIGNAL(valueChanged(int)), slider_rotate, SLOT(setValue(int)));
	connect(slider_rotate, SIGNAL(valueChanged(int)), spinbox_rotate, SLOT(setValue(int)));
	connect(spinbox_rotate, SIGNAL(valueChanged(int)), this, SLOT(rotateImage()));

	QHBoxLayout *rotateLayout = new QHBoxLayout();
	rotateLayout->addWidget(label_rotate);
	rotateLayout->setStretchFactor(label_rotate, 1);
	rotateLayout->addWidget(slider_rotate);
	rotateLayout->setStretchFactor(slider_rotate, 5);
	rotateLayout->addWidget(spinbox_rotate);
	rotateLayout->setStretchFactor(spinbox_rotate, 2);

	widget_pre[1] = new QWidget(preWin);
	widget_pre[1]->setLayout(rotateLayout);
	widget_pre[1]->move(50, 660);
	widget_pre[1]->resize(600, 100);

	// ��бԤ��
	QLabel *label_leanX = new QLabel(tr("ˮƽ�Ƕ�:"));
	spinbox_leanX = new QSpinBox();
	spinbox_leanX->setAlignment(Qt::AlignCenter);
	spinbox_leanX->setRange(0, 89);
	spinbox_leanX->setValue(0);
	QSlider *slider_leanX = new QSlider(Qt::Horizontal);
	slider_leanX->setRange(0, 89);
	slider_leanX->setValue(0);

	QLabel *label_leanY = new QLabel(tr("��ֱ�Ƕ�:"));
	spinbox_leanY = new QSpinBox();
	spinbox_leanY->setAlignment(Qt::AlignCenter);
	spinbox_leanY->setRange(0, 89);
	spinbox_leanY->setValue(0);
	QSlider *slider_leanY = new QSlider(Qt::Horizontal);
	slider_leanY->setRange(0, 89);
	slider_leanY->setValue(0);

	connect(spinbox_leanX, SIGNAL(valueChanged(int)), slider_leanX, SLOT(setValue(int)));
	connect(slider_leanX, SIGNAL(valueChanged(int)), spinbox_leanX, SLOT(setValue(int)));
	connect(spinbox_leanY, SIGNAL(valueChanged(int)), slider_leanY, SLOT(setValue(int)));
	connect(slider_leanY, SIGNAL(valueChanged(int)), spinbox_leanY, SLOT(setValue(int)));
	connect(spinbox_leanX, SIGNAL(valueChanged(int)), this, SLOT(LeanImage()));
	connect(spinbox_leanY, SIGNAL(valueChanged(int)), this, SLOT(LeanImage()));

	QHBoxLayout *leanXLayout = new QHBoxLayout();
	leanXLayout->addWidget(label_leanX);
	leanXLayout->setStretchFactor(label_leanX, 1);
	leanXLayout->addWidget(slider_leanX);
	leanXLayout->setStretchFactor(slider_leanX, 5);
	leanXLayout->addWidget(spinbox_leanX);
	leanXLayout->setStretchFactor(spinbox_leanX, 2);
	QWidget *leanXwidget = new QWidget();
	leanXwidget->setLayout(leanXLayout);
	QHBoxLayout *leanYLayout = new QHBoxLayout();
	leanYLayout->addWidget(label_leanY);
	leanYLayout->setStretchFactor(label_leanY, 1);
	leanYLayout->addWidget(slider_leanY);
	leanYLayout->setStretchFactor(slider_leanY, 5);
	leanYLayout->addWidget(spinbox_leanY);
	leanYLayout->setStretchFactor(spinbox_leanY, 2);
	QWidget *leanYwidget = new QWidget();
	leanYwidget->setLayout(leanYLayout);
	QVBoxLayout *leanLayout = new QVBoxLayout();
	leanLayout->addWidget(leanXwidget);
	leanLayout->addWidget(leanYwidget);

	widget_pre[2] = new QWidget(preWin);
	widget_pre[2]->setLayout(leanLayout);
	widget_pre[2]->move(50, 650);
	widget_pre[2]->resize(600, 120);

	// ��ֵ��Ԥ��
	QLabel *label_bin = new QLabel(tr("��ֵ����ֵ:"));
	spinbox_bin = new QSpinBox;
	spinbox_bin->setAlignment(Qt::AlignCenter);
	spinbox_bin->setRange(0, 255);
	spinbox_bin->setValue(100);
	QSlider *slider_bin = new QSlider(Qt::Horizontal); 
	slider_bin->setRange(0, 255);
	slider_bin->setValue(100);

	connect(spinbox_bin, SIGNAL(valueChanged(int)), slider_bin, SLOT(setValue(int)));
	connect(slider_bin, SIGNAL(valueChanged(int)), spinbox_bin, SLOT(setValue(int)));
	connect(spinbox_bin, SIGNAL(valueChanged(int)), this, SLOT(binImage()));

	QHBoxLayout *binLayout = new QHBoxLayout();
	binLayout->addWidget(label_bin);
	binLayout->setStretchFactor(label_bin, 1);
	binLayout->addWidget(slider_bin);
	binLayout->setStretchFactor(slider_bin, 5);
	binLayout->addWidget(spinbox_bin);
	binLayout->setStretchFactor(spinbox_bin, 2);

	widget_pre[3] = new QWidget(preWin);
	widget_pre[3]->setLayout(binLayout);
	widget_pre[3]->move(50, 660);
	widget_pre[3]->resize(600, 100);

	// ���Ա任
	QLabel *label_alpha = new QLabel(tr("Alpha:"));
	spinbox_alpha = new QSpinBox;
	spinbox_alpha->setAlignment(Qt::AlignCenter);
	spinbox_alpha->setRange(0, 500);
	spinbox_alpha->setValue(100);
	QSlider *slider_alpha = new QSlider(Qt::Horizontal);	 
	slider_alpha->setRange(0, 500);
	slider_alpha->setValue(100);

	QLabel *label_beta = new QLabel(tr("Beta:"));
	spinbox_beta = new QSpinBox;
	spinbox_beta->setAlignment(Qt::AlignCenter);
	spinbox_beta->setRange(0, 200);
	spinbox_beta->setValue(100);
	QSlider *slider_beta = new QSlider(Qt::Horizontal);		 
	slider_beta->setRange(0, 200);
	slider_beta->setValue(100);

	connect(spinbox_alpha, SIGNAL(valueChanged(int)), slider_alpha, SLOT(setValue(int)));
	connect(slider_alpha, SIGNAL(valueChanged(int)), spinbox_alpha, SLOT(setValue(int)));
	connect(spinbox_beta, SIGNAL(valueChanged(int)), slider_beta, SLOT(setValue(int)));
	connect(slider_beta, SIGNAL(valueChanged(int)), spinbox_beta, SLOT(setValue(int)));
	connect(spinbox_alpha, SIGNAL(valueChanged(int)), this, SLOT(linearImage()));
	connect(spinbox_beta, SIGNAL(valueChanged(int)), this, SLOT(linearImage()));

	QHBoxLayout *alphaLayout = new QHBoxLayout();
	alphaLayout->addWidget(label_alpha);
	alphaLayout->setStretchFactor(label_alpha, 1);
	alphaLayout->addWidget(slider_alpha);
	alphaLayout->setStretchFactor(slider_alpha, 5);
	alphaLayout->addWidget(spinbox_alpha);
	alphaLayout->setStretchFactor(spinbox_alpha, 2);
	QWidget *alphawidget = new QWidget();
	alphawidget->setLayout(alphaLayout);
	QHBoxLayout *betaLayout = new QHBoxLayout();
	betaLayout->addWidget(label_beta);
	betaLayout->setStretchFactor(label_beta, 1);
	betaLayout->addWidget(slider_beta);
	betaLayout->setStretchFactor(slider_beta, 5);
	betaLayout->addWidget(spinbox_beta);
	betaLayout->setStretchFactor(spinbox_beta, 2);
	QWidget *betawidget = new QWidget();
	betawidget->setLayout(betaLayout);
	QVBoxLayout *linearLayout = new QVBoxLayout();
	linearLayout->addWidget(alphawidget);
	linearLayout->addWidget(betawidget);

	widget_pre[4] = new QWidget(preWin);
	widget_pre[4]->setLayout(linearLayout);
	widget_pre[4]->move(50, 650);
	widget_pre[4]->resize(600, 120);

	// ٤��任
	QLabel *label_gamma = new QLabel(tr("Gamma:"));
	spinbox_gamma = new QSpinBox;
	spinbox_gamma->setRange(0, 200);
	spinbox_gamma->setValue(100);
	QSlider *slider_gamma = new QSlider(Qt::Horizontal);		 
	slider_gamma->setRange(0, 200);
	slider_gamma->setValue(100);

	connect(spinbox_gamma, SIGNAL(valueChanged(int)), slider_gamma, SLOT(setValue(int)));
	connect(slider_gamma, SIGNAL(valueChanged(int)), spinbox_gamma, SLOT(setValue(int)));
	connect(spinbox_gamma, SIGNAL(valueChanged(int)), this, SLOT(gammaImage()));

	QHBoxLayout *gammaLayout = new QHBoxLayout();
	gammaLayout->addWidget(label_gamma);
	gammaLayout->setStretchFactor(label_gamma, 1);
	gammaLayout->addWidget(slider_gamma);
	gammaLayout->setStretchFactor(slider_gamma, 5);
	gammaLayout->addWidget(spinbox_gamma);
	gammaLayout->setStretchFactor(spinbox_gamma, 2);

	widget_pre[5] = new QWidget(preWin);
	widget_pre[5]->setLayout(gammaLayout);
	widget_pre[5]->move(50, 660);
	widget_pre[5]->resize(600, 100);

	// �����任
	QLabel *label_c = new QLabel(tr("C:"));
	spinbox_c = new QSpinBox;
	spinbox_c->setAlignment(Qt::AlignCenter);
	spinbox_c->setRange(0, 200);
	spinbox_c->setValue(100);
	QSlider *slider_c = new QSlider(Qt::Horizontal);		 
	slider_c->setRange(0, 200);
	slider_c->setValue(100);

	connect(spinbox_c, SIGNAL(valueChanged(int)), slider_c, SLOT(setValue(int)));
	connect(slider_c, SIGNAL(valueChanged(int)), spinbox_c, SLOT(setValue(int)));
	connect(spinbox_c, SIGNAL(valueChanged(int)), this, SLOT(logImage()));

	QHBoxLayout *logLayout = new QHBoxLayout();
	logLayout->addWidget(label_c);
	logLayout->setStretchFactor(label_c, 1);
	logLayout->addWidget(slider_c);
	logLayout->setStretchFactor(slider_c, 5);
	logLayout->addWidget(spinbox_c);
	logLayout->setStretchFactor(spinbox_c, 2);

	widget_pre[6] = new QWidget(preWin);
	widget_pre[6]->setLayout(logLayout);
	widget_pre[6]->move(50, 660);
	widget_pre[6]->resize(600, 100);
}

// ������
void ImageProcessing::WinTool()
{
	dock_Tool = new QDockWidget(tr("������"), this);				// ������
	dock_Tool->setFeatures(QDockWidget::DockWidgetClosable);

	QPushButton *button_pen = new QPushButton(QIcon("../Image/toolbox/Painbrush.png"), tr(""), this);
	button_pen->setFixedSize(35, 35);
	button_pen->setToolTip(tr("�ֱ�"));
	button_pen->setObjectName("customButton");
	QPushButton *button_line = new QPushButton(QIcon("../Image/toolbox/Line.png"), tr(""), this);
	button_line->setFixedSize(35, 35);
	button_line->setToolTip(tr("����"));
	button_line->setObjectName("customButton");
	QPushButton *button_circle = new QPushButton(QIcon("../Image/toolbox/Circle.png"), tr(""), this);
	button_circle->setFixedSize(35, 35);
	button_circle->setToolTip(tr("Բ��"));
	button_circle->setObjectName("customButton");
	QPushButton *button_ellipse = new QPushButton(QIcon("../Image/toolbox/Elipse.png"), tr(""), this);
	button_ellipse->setFixedSize(35, 35);
	button_ellipse->setToolTip(tr("��Բ"));
	button_ellipse->setObjectName("customButton");
	QPushButton *button_triangle = new QPushButton(QIcon("../Image/toolbox/Triangle.png"), tr(""), this);
	button_triangle->setFixedSize(35, 35);
	button_triangle->setToolTip(tr("������"));
	button_triangle->setObjectName("customButton");
	QPushButton *button_rhombus = new QPushButton(QIcon("../Image/toolbox/Rhombus.png"), tr(""), this);
	button_rhombus->setFixedSize(35, 35);
	button_rhombus->setToolTip(tr("����"));
	button_rhombus->setObjectName("customButton");
	QPushButton *button_rect = new QPushButton(QIcon("../Image/toolbox/Rectangle.png"), tr(""),this);
	button_rect->setFixedSize(35, 35);
	button_rect->setToolTip(tr("������"));
	button_rect->setObjectName("customButton");
	QPushButton *button_square = new QPushButton(QIcon("../Image/toolbox/Square.png"), tr(""), this);
	button_square->setFixedSize(35, 35);
	button_square-> setToolTip(tr("������"));
	button_square->setObjectName("customButton");
	QPushButton *button_hexagon = new QPushButton(QIcon("../Image/toolbox/Hexagon.png"), tr(""), this);
	button_hexagon->setFixedSize(35, 35);
	button_hexagon->setToolTip(tr("������"));
	button_hexagon->setObjectName("customButton");
	
	toolButtonGroup = new QButtonGroup();
	connect(toolButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(toolButtonClicked(int)));
	toolButtonGroup->addButton(button_pen,1);
	toolButtonGroup->addButton(button_line,2);
	toolButtonGroup->addButton(button_ellipse,3);
	toolButtonGroup->addButton(button_circle,4);
	toolButtonGroup->addButton(button_triangle,5);
	toolButtonGroup->addButton(button_rhombus,6);
	toolButtonGroup->addButton(button_rect,7);
	toolButtonGroup->addButton(button_square,8);
	toolButtonGroup->addButton(button_hexagon,9);

	QGridLayout *toolLayout = new QGridLayout();
	toolLayout->setAlignment(Qt::AlignTop);
	toolLayout->addWidget(button_pen, 0, 0);
	toolLayout->addWidget(button_line, 0, 1);
	toolLayout->addWidget(button_ellipse, 1, 1);
	toolLayout->addWidget(button_circle, 1, 0);
	toolLayout->addWidget(button_triangle, 2, 0);
	toolLayout->addWidget(button_rhombus, 2, 1);
	toolLayout->addWidget(button_rect, 3, 0);
	toolLayout->addWidget(button_square, 3, 1);
	toolLayout->addWidget(button_hexagon, 4, 0);
	
	QWidget *toolWidget = new QWidget(dock_Tool);
	toolWidget->setLayout(toolLayout);
	dock_Tool->setWidget(toolWidget);
}

// ��ͼ������
void ImageProcessing::ColorToolBar()
{
	I_ColorBar = new QToolBar();
	I_ColorBar = addToolBar(tr("���ʹ�����"));
	I_ColorBar->setMovable(true);

	QLabel *label_penWidth = new QLabel(tr("�߿�"));
	spinbox_penWidth = new QSpinBox;
	spinbox_penWidth->setRange(1, 50);
	spinbox_penWidth->setValue(2);
	
	QPushButton *button_color = new QPushButton(tr("������ɫ"));

	frame_color = new QFrame;	
	frame_color->setObjectName("customFrame");
	frame_color->setFrameShape(QFrame::Box);
	frame_color->setPalette(QPalette(Qt::black)); 
	frame_color->setAutoFillBackground(true);
	frame_color->setFixedSize(25, 25);
	frame_color->setStyleSheet("QFrame{background-color: rgba(" + QString::number(0) + "," + QString::number(0) + "," + QString::number(0) + ",1);border:none}");

	QPushButton *button_full = new QPushButton(tr("��������"));
	QPushButton *button_auto = new QPushButton(tr("����Ӧ����"));
	QPushButton *button_skin = new QPushButton(tr("һ������")); 

	connect(spinbox_penWidth, SIGNAL(valueChanged(int)), this, SLOT(penWidth()));
	connect(button_color, SIGNAL(clicked()), this, SLOT(penColor()));
	connect(button_full, SIGNAL(clicked()), this, SLOT(fullSize()));
	connect(button_auto, SIGNAL(clicked()), this, SLOT(autoSize()));
	connect(button_skin, SIGNAL(clicked()), this, SLOT(changeSkin()));

	QHBoxLayout *colorLayout = new QHBoxLayout();
	colorLayout->setAlignment(Qt::AlignLeft);

	colorLayout->addWidget(label_penWidth);
	colorLayout->addWidget(spinbox_penWidth);
	colorLayout->addWidget(button_color); 
	colorLayout->addWidget(frame_color);
	colorLayout->addWidget(button_full);
	colorLayout->addWidget(button_auto);
	colorLayout->addWidget(button_skin);

	QWidget *colorWidget = new QWidget();
	colorWidget->setLayout(colorLayout);
	I_ColorBar->addWidget(colorWidget);
}

// ���Դ���
void ImageProcessing::WinProp()
{
	dock_Prop = new QDockWidget(tr("����"), this);				// ���Դ���
	dock_Prop->setFeatures(QDockWidget::AllDockWidgetFeatures);

	line_img = new QLineEdit();
	line_length = new QLineEdit();
	line_width = new QLineEdit();
	line_depth = new QLineEdit();
	line_isGray = new QLineEdit();

	line_img->setReadOnly(true);
	line_length->setReadOnly(true);
	line_width->setReadOnly(true);
	line_depth->setReadOnly(true);
	line_isGray->setReadOnly(true);

	QFormLayout *propLayout = new QFormLayout();
	propLayout->addRow(tr("ͼ��"), line_img);
	propLayout->addRow(tr("����"), line_length);
	propLayout->addRow(tr("���"), line_width);
	propLayout->addRow(tr("���"), line_depth);
	propLayout->addRow(tr("�Ƿ�Ҷ�"), line_isGray);
	propLayout->setSpacing(20);
	propLayout->setMargin(20);

	QWidget *propWidget = new QWidget(dock_Prop);
	propWidget->setLayout(propLayout);
	dock_Prop->setWidget(propWidget);
}

// ����ͼ���ַ
void ImageProcessing::UpdateImgName(QString name)			
{
	line_img->setText(name);
}

// �������Դ�������
void ImageProcessing::UpdateProp(QImage Img)
{
	line_length->setText(QString::number(Img.width()));
	line_width->setText(QString::number(Img.height())); 
	line_depth->setText(QString::number(Img.depth()));
	if (Img.depth() == 8 || Img.depth() == 1)
		line_isGray->setText("��");
	else
		line_isGray->setText("��");
}

// ���α任����
void ImageProcessing::WinGeom()										
{
	dock_Geom = new QDockWidget(tr("���α任"), this);				// ���α任
	dock_Geom->setFeatures(QDockWidget::AllDockWidgetFeatures);

	
	// ͼ���С
	QLabel *null = new QLabel(tr("	"));
	QLabel *label_area = new QLabel(tr("ͼ���С"));
	QLabel *labelL = new QLabel(tr("ͼ�񳤶�:"));
	QLabel *labelW = new QLabel(tr("ͼ����:"));
	QPushButton *buttonDefault = new QPushButton(tr("Ĭ��"));
	QPushButton *buttonOK = new QPushButton(tr("ȷ��"));
	line_L = new QLineEdit("512");
	line_L->setValidator(new QIntValidator(1, 10000));		// ֻ����������
	line_L->setAlignment(Qt::AlignCenter);
	line_L->setStyleSheet("min-width: 50px;");
	line_W = new QLineEdit("512");
	line_W->setValidator(new QIntValidator(1, 10000)); 
	line_W->setAlignment(Qt::AlignCenter);
//	connect(buttonDefault, SIGNAL(clicked()), this, SLOT(defaultImageSize()));
	connect(buttonDefault, SIGNAL(clicked()), this, SLOT(autoSize()));
	connect(buttonOK, SIGNAL(clicked()), this, SLOT(changeImageSize()));

	// ͼ������
	QLabel *label_size = new QLabel(tr("ͼ������"));
	QLabel *label_times = new QLabel(tr("���ű���:"));
	QPushButton *button_size = new QPushButton(tr("ȷ��"));
	QPushButton *buttonPre_size = new QPushButton(tr("Ԥ��"));
	//line_times = new QLineEdit("0");
	//line_times->setValidator(new QIntValidator(-10, 10));		// ֻ����������
	//line_times->setAlignment(Qt::AlignCenter);
	line_times = new QSpinBox();
	line_times->setAlignment(Qt::AlignCenter);
	line_times->setRange(-10, 10);
	line_times->setValue(0);
	connect(button_size, SIGNAL(clicked()), this, SLOT(enlargeReduceOK()));
	
	// ͼ����ת
	QLabel *label_rotate = new QLabel(tr("ͼ����ת"));
	QLabel *label_degree = new QLabel(tr("��ת�Ƕ�:"));
	QPushButton *button_rotate = new QPushButton(tr("ȷ��"));
	QPushButton *buttonPre_rotate = new QPushButton(tr("Ԥ��"));
	QPushButton *button_left = new QPushButton(tr("˳ʱ��90"));
	QPushButton *button_right = new QPushButton(tr("��ʱ��90"));
	QPushButton *button_180 = new QPushButton(tr("��ת180"));
	//line_degree = new QLineEdit("0");
	//line_degree->setValidator(new QIntValidator(-360, 360));		// ֻ����������
	//line_degree->setAlignment(Qt::AlignCenter);
	line_degree = new QSpinBox();
	line_degree->setAlignment(Qt::AlignCenter);
	line_degree->setRange(-360, 360);
	line_degree->setValue(0);
	connect(button_rotate, SIGNAL(clicked()), this, SLOT(rotateImageOK()));
	connect(button_left, SIGNAL(clicked()), this, SLOT(rotateImage_270()));
	connect(button_right, SIGNAL(clicked()), this, SLOT(rotateImage_90()));
	connect(button_180, SIGNAL(clicked()), this, SLOT(rotateImage_180()));
		
	// ͼ����б
	QLabel *label_lean = new QLabel(tr("ͼ����б"));
	QLabel *label_leanX = new QLabel(tr("ˮƽ�Ƕ�:"));
	QLabel *label_leanY = new QLabel(tr("��ֱ�Ƕ�:"));
	QPushButton *button_lean = new QPushButton(tr("ȷ��"));
	QPushButton *buttonPre_lean = new QPushButton(tr("Ԥ��"));
	//line_leanX = new QLineEdit("0");
	//line_leanX->setValidator(new QIntValidator(0, 89));		 
	//line_leanX->setAlignment(Qt::AlignCenter);
	//line_leanY = new QLineEdit("0");
	//line_leanY->setValidator(new QIntValidator(0, 89));	 
	//line_leanY->setAlignment(Qt::AlignCenter);
	line_leanX = new QSpinBox();
	line_leanX->setAlignment(Qt::AlignCenter);
	line_leanX->setRange(0, 89);
	line_leanX->setValue(0);
	line_leanY = new QSpinBox();
	line_leanY->setAlignment(Qt::AlignCenter);
	line_leanY->setRange(0, 89);
	line_leanY->setValue(0);
	connect(button_lean, SIGNAL(clicked()), this, SLOT(LeanImageOK())); 

	// ͼ��ת
	QLabel *label_reverse = new QLabel(tr("ͼ��ת"));
	QLabel *label_H = new QLabel(tr("ˮƽ��ת:"));
	QLabel *label_V = new QLabel(tr("��ֱ��ת:"));
	QPushButton *button_H = new QPushButton(tr("ˮƽ��ת"));
	QPushButton *button_V = new QPushButton(tr("��ֱ��ת"));
	connect(button_H, SIGNAL(clicked()), this, SLOT(flipImage_H()));
	connect(button_V, SIGNAL(clicked()), this, SLOT(flipImage_V()));

	// Ԥ����ť��
	preButtonGroup->addButton(buttonPre_size, 0);
	preButtonGroup->addButton(buttonPre_rotate, 1);
	preButtonGroup->addButton(buttonPre_lean, 2);
	
	// ��դ����
	QGridLayout *geomLayout = new QGridLayout();
	geomLayout->setAlignment(Qt::AlignTop);
	geomLayout->setMargin(30);

	geomLayout->addWidget(label_area, 0, 0, 1, 1);// ͼ���С
	geomLayout->addWidget(labelL, 1, 1, 1, 1);
	geomLayout->addWidget(line_L, 1, 2, 1, 1);
	geomLayout->addWidget(labelW, 2, 1, 1, 1); 
	geomLayout->addWidget(line_W, 2, 2, 1, 1);
	geomLayout->addWidget(buttonOK, 1, 3, 1, 1);
	geomLayout->addWidget(buttonDefault, 1, 4, 1, 1);

	geomLayout->addWidget(null, 10, 0, 1, 1);// ͼ������
	geomLayout->addWidget(label_size, 11, 0, 1, 1);
	geomLayout->addWidget(label_times, 12, 1, 1, 1);
	geomLayout->addWidget(line_times, 12, 2, 1, 1);
	geomLayout->addWidget(button_size, 12, 3, 1, 1);
	geomLayout->addWidget(buttonPre_size, 12, 4, 1, 1);
	geomLayout->addWidget(null, 14, 0, 1, 1); 

	geomLayout->addWidget(null, 20, 0, 1, 1);// ͼ����ת
	geomLayout->addWidget(label_rotate, 21, 0, 1, 1);
	geomLayout->addWidget(label_degree, 22, 1, 1, 1);
	geomLayout->addWidget(line_degree, 22, 2, 1, 1);
	geomLayout->addWidget(button_rotate, 22, 3, 1, 1);
	geomLayout->addWidget(buttonPre_rotate, 22, 4, 1, 1);
	geomLayout->addWidget(button_180, 23, 2, 1, 1);
	geomLayout->addWidget(button_left, 23, 3, 1, 1);
	geomLayout->addWidget(button_right, 23, 4, 1, 1);
	
	geomLayout->addWidget(null, 30, 0, 1, 1);// ͼ����б
	geomLayout->addWidget(label_lean, 31, 0, 1, 1);
	geomLayout->addWidget(label_leanX, 32, 1, 1, 1);
	geomLayout->addWidget(line_leanX, 32, 2, 1, 1);
	geomLayout->addWidget(label_leanY, 33, 1, 1, 1);
	geomLayout->addWidget(line_leanY, 33, 2, 1, 1);
	geomLayout->addWidget(button_lean, 32, 3, 1, 1);
	geomLayout->addWidget(buttonPre_lean, 32, 4, 1, 1);

	geomLayout->addWidget(null, 40, 0, 1, 1);// ͼ��ת
	geomLayout->addWidget(label_reverse, 41, 0, 1, 1);
//	geomLayout->addWidget(label_H, 42, 1, 1, 1);
	geomLayout->addWidget(button_H, 42, 1, 1, 2);
//	geomLayout->addWidget(label_V, 43, 1, 1, 1);
	geomLayout->addWidget(button_V, 42, 3, 1, 2);

	QWidget *geomWidget = new QWidget(dock_Geom);
	geomWidget->setFixedWidth(420);
	geomWidget->setLayout(geomLayout);
	dock_Geom->setWidget(geomWidget);

	QScrollArea *scrollArea = new QScrollArea(dock_Geom);
	scrollArea->setAlignment(Qt::AlignLeft);
	scrollArea->setWidget(geomWidget);
	dock_Geom->setWidget(scrollArea);


}

// �Ҷȱ任����
void ImageProcessing::WinGray()		
{
	dock_Gray = new QDockWidget(tr("�Ҷȱ任"), this);
	dock_Gray->setFeatures(QDockWidget::AllDockWidgetFeatures);
	
	QLabel *label_linear = new QLabel(tr("���Ա任"));
	QLabel *label_alpha = new QLabel(tr("Alpha:"));
	QLabel *label_beta = new QLabel(tr(" Beta:"));
	QPushButton *button_linear = new QPushButton(tr("ȷ��"));
	QPushButton *buttonPre_linear = new QPushButton(tr("Ԥ��"));
	//line_alpha = new QLineEdit("100");
	//line_alpha->setValidator(new QIntValidator(0, 500));		 
	//line_alpha->setAlignment(Qt::AlignCenter);
	//line_beta = new QLineEdit("100");
	//line_beta->setValidator(new QIntValidator(0, 200));		 
	//line_beta->setAlignment(Qt::AlignCenter);
	line_alpha = new QSpinBox();
	line_alpha->setAlignment(Qt::AlignCenter);
	line_alpha->setRange(0, 500);
	line_alpha->setValue(100);
	line_beta = new QSpinBox();
	line_beta->setAlignment(Qt::AlignCenter);
	line_beta->setRange(0, 200);
	line_beta->setValue(100);

	QLabel *label_log = new QLabel(tr("�����任"));
	QLabel *label_c = new QLabel(tr("  Log:"));
	QPushButton *button_log = new QPushButton(tr("ȷ��"));
	QPushButton *buttonPre_log = new QPushButton(tr("Ԥ��"));
	//line_c = new QLineEdit("100");
	//line_c->setValidator(new QIntValidator(0, 200));
	//line_c->setAlignment(Qt::AlignCenter);
	line_c = new QSpinBox();
	line_c->setAlignment(Qt::AlignCenter);
	line_c->setRange(0, 200);
	line_c->setValue(100);

	QLabel *label_gamma = new QLabel(tr("٤��任"));
	QLabel *label_gam = new QLabel(tr("Gamma:"));
	QPushButton *button_gamma = new QPushButton(tr("ȷ��"));
	QPushButton *buttonPre_gamma = new QPushButton(tr("Ԥ��"));
	//line_gamma = new QLineEdit("100");
	//line_gamma->setValidator(new QIntValidator(0, 200));
	//line_gamma->setAlignment(Qt::AlignCenter);
	line_gamma = new QSpinBox();
	line_gamma->setAlignment(Qt::AlignCenter);
	line_gamma->setRange(0, 200);
	line_gamma->setValue(100);

	// ��ֵͼ��
	QLabel *null = new QLabel(tr("	"));
	QLabel *label_bin = new QLabel(tr("��ֵͼ��"));
	QLabel *label_threshold = new QLabel(tr(" ��ֵ:"));
	QPushButton *button_bin = new QPushButton(tr("ȷ��"));
	QPushButton *buttonPre_bin = new QPushButton(tr("Ԥ��"));
	//line_bin = new QLineEdit("100");
	//line_bin->setValidator(new QIntValidator(0, 255));
	//line_bin->setAlignment(Qt::AlignCenter);
	line_bin = new QSpinBox();
	line_bin->setAlignment(Qt::AlignCenter);
	line_bin->setRange(0, 255);
	line_bin->setValue(100);

	QLabel *label_graylevel = new QLabel(tr("�Ҷ�ͼ��"));
	QPushButton *button_graylevel = new QPushButton(tr("�Ҷ�ͼ��"));

	QLabel *label_reverse = new QLabel(tr("��ת�任"));
	QPushButton *button_reverse = new QPushButton(tr("ͼ��ת"));

	QLabel *label_histeq = new QLabel();
	label_histeq->setText(tr("ֱ��ͼ"));
	QPushButton *button_histeq = new QPushButton();
	button_histeq->setText(tr("�Ҷ�ֱ��ͼ���⻯"));

	preButtonGroup->addButton(buttonPre_bin, 3);
	preButtonGroup->addButton(buttonPre_linear, 4);
	preButtonGroup->addButton(buttonPre_gamma, 5);
	preButtonGroup->addButton(buttonPre_log, 6);

	connect(button_bin, SIGNAL(clicked()), this, SLOT(binImageOK()));
	connect(button_graylevel, SIGNAL(clicked()), this, SLOT(grayImage()));
	connect(button_reverse, SIGNAL(clicked()), this, SLOT(reverseImage()));
	connect(button_linear, SIGNAL(clicked()), this, SLOT(linearImageOK()));
	connect(button_gamma, SIGNAL(clicked()), this, SLOT(gammaImageOK()));
	connect(button_log, SIGNAL(clicked()), this, SLOT(logImageOK()));
	connect(button_histeq, SIGNAL(clicked()), this, SLOT(histeqImage()));

	// ��դ����
	QGridLayout *grayLayout = new QGridLayout();
	grayLayout->setAlignment(Qt::AlignTop);
	grayLayout->setMargin(30);

	grayLayout->addWidget(label_linear, 16, 0, 1, 1);
	grayLayout->addWidget(label_alpha, 17, 1, 1, 1);
	grayLayout->addWidget(line_alpha, 17, 2, 1, 1);
	grayLayout->addWidget(label_beta, 18, 1, 1, 1);
	grayLayout->addWidget(line_beta, 18, 2, 1, 1);
	grayLayout->addWidget(button_linear, 17, 3, 1, 1);
	grayLayout->addWidget(buttonPre_linear, 17, 4, 1, 1);

	grayLayout->addWidget(null, 20, 0, 1, 1);
	grayLayout->addWidget(label_log, 21, 0, 1, 1);
	grayLayout->addWidget(label_c, 22, 1, 1, 1);
	grayLayout->addWidget(line_c, 22, 2, 1, 1);
	grayLayout->addWidget(button_log, 22, 3, 1, 1);
	grayLayout->addWidget(buttonPre_log, 22, 4, 1, 1);

	grayLayout->addWidget(null, 25, 0, 1, 1);
	grayLayout->addWidget(label_gamma, 26, 0, 1, 1);
	grayLayout->addWidget(label_gam, 27, 1, 1, 1);
	grayLayout->addWidget(line_gamma, 27, 2, 1, 1);
	grayLayout->addWidget(button_gamma, 27, 3, 1, 1);
	grayLayout->addWidget(buttonPre_gamma, 27, 4, 1, 1);

	grayLayout->addWidget(null, 30, 0, 1, 1);
	grayLayout->addWidget(label_bin, 31, 0, 1, 1);
	grayLayout->addWidget(label_threshold, 32, 1, 1, 1);
	grayLayout->addWidget(line_bin, 32, 2, 1, 1);
	grayLayout->addWidget(button_bin, 32, 3, 1, 1);
	grayLayout->addWidget(buttonPre_bin, 32, 4, 1, 1);

	grayLayout->addWidget(null, 35, 0, 1, 1);
	grayLayout->addWidget(label_graylevel, 36, 0, 1, 1);
	grayLayout->addWidget(button_graylevel, 37, 1, 1, 4);

	grayLayout->addWidget(null, 40, 0, 1, 1);
	grayLayout->addWidget(label_reverse, 41, 0, 1, 1);
	grayLayout->addWidget(button_reverse, 42, 1, 1, 4);

	grayLayout->addWidget(null, 45, 0, 1, 1);
	grayLayout->addWidget(label_histeq, 46, 0, 1, 1);
	grayLayout->addWidget(button_histeq, 47, 1, 1, 4);
	
	QWidget *grayWidget = new QWidget(dock_Gray);
	grayWidget->setFixedWidth(420);
	grayWidget->setLayout(grayLayout);
	dock_Gray->setWidget(grayWidget);
	
	QScrollArea *scrollArea = new QScrollArea(dock_Gray);
	scrollArea->setAlignment(Qt::AlignLeft);
	scrollArea->setWidget(grayWidget);
	dock_Gray->setWidget(scrollArea);
}

// ͼ����ǿ����
void ImageProcessing::WinEnhance()
{
	dock_Enhance = new QDockWidget(tr("ͼ����ǿ"), this);
	dock_Enhance->setFeatures(QDockWidget::AllDockWidgetFeatures);

	QLabel *null = new QLabel(tr("	"));
	QLabel *label_smooth = new QLabel(tr("ͼ��ƽ��"));
	QLabel *label_coreSmooth = new QLabel(tr("ģ���С"));
	QPushButton *button_Normalized = new QPushButton(tr("���˲�"));
	QPushButton *button_Gaussian = new QPushButton(tr("��˹�˲�"));
	QPushButton *button_Median = new QPushButton(tr("��ֵ�˲�"));
	combo_smooth = new QComboBox();
	combo_smooth->addItem(tr("3��3")); combo_smooth->addItem(tr("5��5"));	
	combo_smooth->addItem(tr("7��7")); combo_smooth->addItem(tr("9��9"));
	combo_smooth->addItem(tr("11��11")); combo_smooth->addItem(tr("13��13"));
	combo_smooth->addItem(tr("15��15")); combo_smooth->addItem(tr("17��17"));
	combo_smooth->addItem(tr("19��19")); combo_smooth->addItem(tr("21��21"));

	connect(button_Normalized, SIGNAL(clicked()), this, SLOT(normalizedImage()));
	connect(button_Gaussian, SIGNAL(clicked()), this, SLOT(gaussianImage()));
	connect(button_Median, SIGNAL(clicked()), this, SLOT(medianImage()));
	connect(combo_smooth, SIGNAL(currentIndexChanged(int)), this, SLOT(kernelSmoothChange()));

	QLabel *label_sharpen = new QLabel(tr("ͼ����"));
	QLabel *label_coreSharpen = new QLabel(tr("ģ���С"));
	QPushButton *button_sobel = new QPushButton(tr("Sobel��Ե���"));
	QPushButton *button_laplacian = new QPushButton(tr("Laplacian���"));
	QPushButton *button_canny = new QPushButton(tr("Canny��Ե���"));
	QPushButton *button_line = new QPushButton(tr("Hough�߼��"));
	QPushButton *button_circle = new QPushButton(tr("HoughԲ���"));
	combo_sharpen = new QComboBox();
	combo_sharpen->addItem(tr("3��3")); combo_sharpen->addItem(tr("5��5"));
	combo_sharpen->addItem(tr("7��7")); combo_sharpen->addItem(tr("9��9"));
	combo_sharpen->addItem(tr("11��11")); combo_sharpen->addItem(tr("13��13"));
	combo_sharpen->addItem(tr("15��15")); combo_sharpen->addItem(tr("17��17"));
	combo_sharpen->addItem(tr("19��19")); combo_sharpen->addItem(tr("21��21"));
	
	QLabel *label_canny = new QLabel(tr("Canny��ֵ"));
	spinbox_canny = new QSpinBox;							// ΢����
	spinbox_canny->setRange(0, 100);
	spinbox_canny->setValue(20);

	QSlider *slider_canny = new QSlider(Qt::Horizontal);		// ������
	slider_canny->setRange(0, 100);
	slider_canny->setValue(20);
	
	connect(button_sobel, SIGNAL(clicked()), this, SLOT(sobelImage()));
	connect(button_laplacian, SIGNAL(clicked()), this, SLOT(laplacianImage()));
	connect(button_canny, SIGNAL(clicked()), this, SLOT(cannyImage()));
	connect(button_line, SIGNAL(clicked()), this, SLOT(lineImage()));
	connect(button_circle, SIGNAL(clicked()), this, SLOT(circleImage()));
	connect(combo_sharpen, SIGNAL(currentIndexChanged(int)), this, SLOT(kernelSharpenChange()));
		
	connect(spinbox_canny, SIGNAL(valueChanged(int)), slider_canny, SLOT(setValue(int)));
	connect(slider_canny, SIGNAL(valueChanged(int)), spinbox_canny, SLOT(setValue(int)));
	connect(spinbox_canny, SIGNAL(valueChanged(int)), this, SLOT(cannyValueChange()));

	QLabel *label_lineThreshold = new QLabel(tr("�߼����ֵ"));
	spinbox_lineThreshold = new QSpinBox;						// HoughLine
	spinbox_lineThreshold->setRange(0, 500);
	spinbox_lineThreshold->setValue(50); 
	QSlider *slider_lineThreshold = new QSlider(Qt::Horizontal);
	slider_lineThreshold->setRange(0, 500);
	slider_lineThreshold->setValue(50);
	connect(spinbox_lineThreshold, SIGNAL(valueChanged(int)), slider_lineThreshold, SLOT(setValue(int)));
	connect(slider_lineThreshold, SIGNAL(valueChanged(int)), spinbox_lineThreshold, SLOT(setValue(int)));

	QLabel *label_minLineLength = new QLabel(tr("�߶���С����"));
	spinbox_minLineLength = new QSpinBox;
	spinbox_minLineLength->setRange(0, 500);
	spinbox_minLineLength->setValue(50);
	QSlider *slider_minLineLength = new QSlider(Qt::Horizontal);
	slider_minLineLength->setRange(0, 500);
	slider_minLineLength->setValue(50);
	connect(spinbox_minLineLength, SIGNAL(valueChanged(int)), slider_minLineLength, SLOT(setValue(int)));
	connect(slider_minLineLength, SIGNAL(valueChanged(int)), spinbox_minLineLength, SLOT(setValue(int)));

	QLabel *label_maxLineGap = new QLabel(tr("���������"));
	spinbox_maxLineGap = new QSpinBox;							
	spinbox_maxLineGap->setRange(0, 500);
	spinbox_maxLineGap->setValue(10);
	QSlider *slider_maxLineGap = new QSlider(Qt::Horizontal);
	slider_maxLineGap->setRange(0, 500);
	slider_maxLineGap->setValue(50);
	connect(spinbox_maxLineGap, SIGNAL(valueChanged(int)), slider_maxLineGap, SLOT(setValue(int)));
	connect(slider_maxLineGap, SIGNAL(valueChanged(int)), spinbox_maxLineGap, SLOT(setValue(int)));

	QLabel *label_minRadius = new QLabel(tr("��С�뾶"));
	spinbox_minRadius = new QSpinBox;
	spinbox_minRadius->setRange(0, 1000);
	spinbox_minRadius->setValue(1);
	QSlider *slider_minRadius = new QSlider(Qt::Horizontal);
	slider_minRadius->setRange(0, 1000);
	slider_minRadius->setValue(1);
	connect(spinbox_minRadius, SIGNAL(valueChanged(int)), slider_minRadius, SLOT(setValue(int)));
	connect(slider_minRadius, SIGNAL(valueChanged(int)), spinbox_minRadius, SLOT(setValue(int)));

	QLabel *label_maxRadius = new QLabel(tr("���뾶"));
	spinbox_maxRadius = new QSpinBox;
	spinbox_maxRadius->setRange(0, 1000);
	spinbox_maxRadius->setValue(100);
	QSlider *slider_maxRadius = new QSlider(Qt::Horizontal);
	slider_maxRadius->setRange(0, 1000);
	slider_maxRadius->setValue(100);
	connect(spinbox_maxRadius, SIGNAL(valueChanged(int)), slider_maxRadius, SLOT(setValue(int)));
	connect(slider_maxRadius, SIGNAL(valueChanged(int)), spinbox_maxRadius, SLOT(setValue(int)));

	// ��դ����
	QGridLayout *enhanceLayout = new QGridLayout();
	enhanceLayout->setAlignment(Qt::AlignTop);
	enhanceLayout->setMargin(30);

	enhanceLayout->addWidget(label_smooth, 0, 0, 1, 1);
	enhanceLayout->addWidget(label_coreSmooth, 1, 1, 1, 1);
	enhanceLayout->addWidget(combo_smooth, 1, 2, 1, 1);
	enhanceLayout->addWidget(button_Normalized, 2, 2, 1, 1);
	enhanceLayout->addWidget(button_Gaussian, 3, 2, 1, 1);
	enhanceLayout->addWidget(button_Median, 4, 2, 1, 1);
	
	enhanceLayout->addWidget(label_sharpen, 5, 0, 1, 1);
	enhanceLayout->addWidget(label_coreSharpen, 6, 1, 1, 1);
	enhanceLayout->addWidget(combo_sharpen, 6, 2, 1, 1);
	enhanceLayout->addWidget(button_sobel, 7, 2, 1, 1);
	enhanceLayout->addWidget(button_laplacian, 8, 2, 1, 1);
	enhanceLayout->addWidget(button_canny, 9, 2, 1, 1);
	
	enhanceLayout->addWidget(label_canny, 10, 1, 1, 1);
	enhanceLayout->addWidget(slider_canny, 10, 2, 1, 1);
	enhanceLayout->addWidget(spinbox_canny, 10, 3, 1, 1);

	enhanceLayout->addWidget(button_line, 11, 2, 1, 1);
	enhanceLayout->addWidget(label_lineThreshold, 12, 1, 1, 1);
	enhanceLayout->addWidget(slider_lineThreshold, 12, 2, 1, 1);
	enhanceLayout->addWidget(spinbox_lineThreshold, 12, 3, 1, 1);

	enhanceLayout->addWidget(label_minLineLength, 13, 1, 1, 1);
	enhanceLayout->addWidget(slider_minLineLength, 13, 2, 1, 1);
	enhanceLayout->addWidget(spinbox_minLineLength, 13, 3, 1, 1);

	enhanceLayout->addWidget(label_maxLineGap, 14, 1, 1, 1);
	enhanceLayout->addWidget(slider_maxLineGap, 14, 2, 1, 1);
	enhanceLayout->addWidget(spinbox_maxLineGap, 14, 3, 1, 1);

	enhanceLayout->addWidget(button_circle, 15, 2, 1, 1);
	enhanceLayout->addWidget(label_minRadius, 16, 1, 1, 1);
	enhanceLayout->addWidget(slider_minRadius, 16, 2, 1, 1);
	enhanceLayout->addWidget(spinbox_minRadius, 16, 3, 1, 1);

	enhanceLayout->addWidget(label_maxRadius, 17, 1, 1, 1);
	enhanceLayout->addWidget(slider_maxRadius, 17, 2, 1, 1);
	enhanceLayout->addWidget(spinbox_maxRadius, 17, 3, 1, 1);

	QWidget *enhanceWidget = new QWidget(dock_Enhance);
	enhanceWidget->setFixedWidth(420);
	enhanceWidget->setLayout(enhanceLayout);
	dock_Enhance->setWidget(enhanceWidget);

	QScrollArea *scrollArea = new QScrollArea(dock_Enhance);
	scrollArea->setAlignment(Qt::AlignLeft);
	scrollArea->setWidget(enhanceWidget);
	dock_Enhance->setWidget(scrollArea);
}

// ��̬ѧ������
void ImageProcessing::WinMorp()
{
	dock_Morp = new QDockWidget(tr("��̬ѧ����"), this);
	dock_Morp->setFeatures(QDockWidget::AllDockWidgetFeatures);

	QLabel *label_kernel = new QLabel();
	label_kernel->setText(tr("ģ���С"));
	combo_kernel = new QComboBox();
	combo_kernel->addItem(tr("3��3")); combo_kernel->addItem(tr("5��5"));
	combo_kernel->addItem(tr("7��7")); combo_kernel->addItem(tr("9��9"));
	combo_kernel->addItem(tr("11��11")); combo_kernel->addItem(tr("13��13"));
	combo_kernel->addItem(tr("15��15")); combo_kernel->addItem(tr("17��17"));
	combo_kernel->addItem(tr("19��19")); combo_kernel->addItem(tr("21��21"));

	QLabel *label_elem = new QLabel();
	label_elem->setText(tr("�ṹԪ��"));
	combo_elem = new QComboBox();
	combo_elem->addItem(tr("����"));
	combo_elem->addItem(tr("ʮ����"));
	combo_elem->addItem(tr("��Բ��"));

	QLabel *label_erode = new QLabel();
	label_erode->setText(tr("��ʴ"));
	QLabel *label_erodeCount = new QLabel();
	label_erodeCount->setText(tr("��"));
	spinbox_erode = new QSpinBox;							
	spinbox_erode->setRange(1, 50);
	spinbox_erode->setValue(1);
	QPushButton *button_erode = new QPushButton();			// ȷ����ť
	button_erode->setText(tr("��ʴ"));

	QLabel *label_dilate = new QLabel();
	label_dilate->setText(tr("����"));
	QLabel *label_dilateCount = new QLabel();
	label_dilateCount->setText(tr("��"));
	spinbox_dilate = new QSpinBox;
	spinbox_dilate->setRange(1, 50);
	spinbox_dilate->setValue(1);
	QPushButton *button_dilate = new QPushButton();			// ȷ����ť
	button_dilate->setText(tr("����"));

	QLabel *label_open = new QLabel();
	label_open->setText(tr("������"));
	QLabel *label_openCount = new QLabel();
	label_openCount->setText(tr("��"));
	spinbox_open = new QSpinBox;
	spinbox_open->setRange(1, 50);
	spinbox_open->setValue(1);
	QPushButton *button_open = new QPushButton();			// ȷ����ť
	button_open->setText(tr("������"));

	QLabel *label_close = new QLabel();
	label_close->setText(tr("������"));
	QLabel *label_closeCount = new QLabel();
	label_closeCount->setText(tr("��"));
	spinbox_close = new QSpinBox;
	spinbox_close->setRange(1, 50);
	spinbox_close->setValue(1);
	QPushButton *button_close = new QPushButton();			// ȷ����ť
	button_close->setText(tr("������"));

	QLabel *label_grad = new QLabel();
	label_grad->setText(tr("��̬ѧ�ݶ�"));
	QPushButton *button_grad = new QPushButton();			// ȷ����ť
	button_grad->setText(tr("��̬ѧ�ݶ�"));

	QLabel *label_tophat = new QLabel();
	label_tophat->setText(tr("��ñ����"));
	QPushButton *button_tophat = new QPushButton();			// ȷ����ť
	button_tophat->setText(tr("��ñ����"));

	QLabel *label_blackhat = new QLabel();
	label_blackhat->setText(tr("��ñ����"));
	QPushButton *button_blackhat = new QPushButton();			// ȷ����ť
	button_blackhat->setText(tr("��ñ����"));
	
	connect(button_erode, SIGNAL(clicked()), this, SLOT(erodeImage()));
	connect(button_dilate, SIGNAL(clicked()), this, SLOT(dilateImage()));
	connect(button_open, SIGNAL(clicked()), this, SLOT(openImage()));
	connect(button_close, SIGNAL(clicked()), this, SLOT(closeImage()));
	connect(button_grad, SIGNAL(clicked()), this, SLOT(gradImage()));
	connect(button_tophat, SIGNAL(clicked()), this, SLOT(tophatImage()));
	connect(button_blackhat, SIGNAL(clicked()), this, SLOT(blackhatImage()));

	QGridLayout *morpLayout = new QGridLayout();
	morpLayout->setAlignment(Qt::AlignTop);
	morpLayout->setMargin(30);

	morpLayout->addWidget(label_kernel, 0, 1, 1, 1);
	morpLayout->addWidget(combo_kernel, 0, 2, 1, 1);
	morpLayout->addWidget(label_elem, 1, 1, 1, 1);
	morpLayout->addWidget(combo_elem, 1, 2, 1, 1);

	morpLayout->addWidget(label_erode, 2, 0, 1, 1);
	morpLayout->addWidget(button_erode, 3, 1, 1, 1);
	morpLayout->addWidget(spinbox_erode, 3, 2, 1, 1);
	morpLayout->addWidget(label_erodeCount, 3, 3, 1, 1);

	morpLayout->addWidget(label_dilate, 4, 0, 1, 1);
	morpLayout->addWidget(button_dilate, 5, 1, 1, 1);
	morpLayout->addWidget(spinbox_dilate, 5, 2, 1, 1);
	morpLayout->addWidget(label_dilateCount, 5, 3, 1, 1);

	morpLayout->addWidget(label_open, 6, 0, 1, 1);
	morpLayout->addWidget(button_open, 7, 1, 1, 1);
	morpLayout->addWidget(spinbox_open, 7, 2, 1, 1);
	morpLayout->addWidget(label_openCount, 7, 3, 1, 1);

	morpLayout->addWidget(label_close, 8, 0, 1, 1);
	morpLayout->addWidget(button_close, 9, 1, 1, 1);
	morpLayout->addWidget(spinbox_close, 9, 2, 1, 1);
	morpLayout->addWidget(label_closeCount, 9, 3, 1, 1);

	morpLayout->addWidget(label_tophat, 10, 0, 1, 1);
	morpLayout->addWidget(button_tophat, 11, 1, 1, 1);
	morpLayout->addWidget(label_blackhat, 12, 0, 1, 1);
	morpLayout->addWidget(button_blackhat, 13, 1, 1, 1);
	morpLayout->addWidget(label_grad, 14, 0, 1, 1);
	morpLayout->addWidget(button_grad, 15, 1, 1, 1);

	QWidget *morpWidget = new QWidget(dock_Morp);
	morpWidget->setFixedWidth(420);
	morpWidget->setLayout(morpLayout);
	dock_Morp->setWidget(morpWidget);
	
	QScrollArea *scrollArea = new QScrollArea(dock_Morp);
	scrollArea->setAlignment(Qt::AlignLeft);
	scrollArea->setWidget(morpWidget);
	dock_Morp->setWidget(scrollArea);
}

// ��ɫģ�ʹ���
void ImageProcessing::WinColor()
{
	dock_Color = new QDockWidget(tr("��ɫģ��"), this);
	dock_Color->setFeatures(QDockWidget::AllDockWidgetFeatures);
	
	QLabel *null = new QLabel(tr("	"));
	QLabel *label_RGB = new QLabel(tr("RGBģ��"));
	QPushButton *button_R = new QPushButton(tr("R����ͼ"));
	QPushButton *button_G = new QPushButton(tr("G����ͼ"));
	QPushButton *button_B = new QPushButton(tr("B����ͼ"));

	connect(button_R, SIGNAL(clicked()), this, SLOT(splitR()));
	connect(button_G, SIGNAL(clicked()), this, SLOT(splitG()));
	connect(button_B, SIGNAL(clicked()), this, SLOT(splitB()));
	
	QLabel *label_HSV = new QLabel(tr("HSVģ��"));
	QPushButton *button1_H = new QPushButton(tr("H����ͼ"));
	QPushButton *button1_S = new QPushButton(tr("S����ͼ"));
	QPushButton *button1_V = new QPushButton(tr("V����ͼ"));

	connect(button1_H, SIGNAL(clicked()), this, SLOT(splitH_HSV()));
	connect(button1_S, SIGNAL(clicked()), this, SLOT(splitS_HSV()));
	connect(button1_V, SIGNAL(clicked()), this, SLOT(splitV_HSV()));

	QLabel *label_YUV = new QLabel(tr("YUVģ��"));
	QPushButton *button2_Y = new QPushButton(tr("Y����ͼ"));
	QPushButton *button2_U = new QPushButton(tr("U����ͼ"));
	QPushButton *button2_V = new QPushButton(tr("V����ͼ"));

	connect(button2_Y, SIGNAL(clicked()), this, SLOT(splitY_YUV()));
	connect(button2_U, SIGNAL(clicked()), this, SLOT(splitU_YUV()));
	connect(button2_V, SIGNAL(clicked()), this, SLOT(splitV_YUV()));

	QLabel *label_HLS = new QLabel(tr("HLSģ��"));
	QPushButton *button3_H = new QPushButton(tr("H����ͼ"));
	QPushButton *button3_L = new QPushButton(tr("L����ͼ"));
	QPushButton *button3_S = new QPushButton(tr("S����ͼ"));

	connect(button3_H, SIGNAL(clicked()), this, SLOT(splitH_HLS()));
	connect(button3_L, SIGNAL(clicked()), this, SLOT(splitL_HLS()));
	connect(button3_S, SIGNAL(clicked()), this, SLOT(splitS_HLS()));	
		
	QGridLayout *colorLayout = new QGridLayout();
	colorLayout->setAlignment(Qt::AlignTop);
	colorLayout->setMargin(30);

	colorLayout->addWidget(label_RGB, 0, 0, 1, 1);
	colorLayout->addWidget(button_R, 1, 1, 1, 1);
	colorLayout->addWidget(button_G, 1, 2, 1, 1);
	colorLayout->addWidget(button_B, 1, 3, 1, 1);

	colorLayout->addWidget(null, 5, 0, 1, 1);
	colorLayout->addWidget(label_HSV, 6, 0, 1, 1);
	colorLayout->addWidget(button1_H, 7, 1, 1, 1);
	colorLayout->addWidget(button1_S, 7, 2, 1, 1);
	colorLayout->addWidget(button1_V, 7, 3, 1, 1);

	colorLayout->addWidget(null, 10, 0, 1, 1);
	colorLayout->addWidget(label_YUV, 11, 0, 1, 1);
	colorLayout->addWidget(button2_Y, 12, 1, 1, 1);
	colorLayout->addWidget(button2_U, 12, 2, 1, 1);
	colorLayout->addWidget(button2_V, 12, 3, 1, 1);

	colorLayout->addWidget(null, 15, 0, 1, 1);
	colorLayout->addWidget(label_HLS, 16, 0, 1, 1);
	colorLayout->addWidget(button3_H, 17, 1, 1, 1);
	colorLayout->addWidget(button3_L, 17, 2, 1, 1);
	colorLayout->addWidget(button3_S, 17, 3, 1, 1);

	QWidget *colorWidget = new QWidget(dock_Color);
	colorWidget->setFixedWidth(420);
	colorWidget->setLayout(colorLayout);
	dock_Color->setWidget(colorWidget);

	QScrollArea *scrollArea = new QScrollArea(dock_Color);
	scrollArea->setAlignment(Qt::AlignLeft);
	scrollArea->setWidget(colorWidget);
	dock_Color->setWidget(scrollArea);
}

// ------------------------------------------�����ۺ���--------------------------------------------------------

// ����
void ImageProcessing::undo()
{
	if (iter != imgVector[0].begin())			// ǰ�滹�ж���
	{		
		iter--;
		ShowImage(*iter, false);
		output("ϵͳ��ʾ������");
		I_menubar->Act_edit_redo->setEnabled(true);

		if (iter == imgVector[0].begin())		// �ж��Լ����Ƿ�Ϊ��ʼͼ��
		{
			I_menubar->Act_edit_undo->setEnabled(false);
		}
	}
}

// ����															
void ImageProcessing::redo()
{
	if (iter != (imgVector[0].end() - 1))		// ���滹�ж���
	{
		iter++;
		ShowImage(*iter, false);
		output("ϵͳ��ʾ������");
		I_menubar->Act_edit_undo->setEnabled(true);

		if (iter == (imgVector[0].end() - 1))
		{
			I_menubar->Act_edit_redo->setEnabled(false);
		}
	}
}

// �˳�ȫ��
void ImageProcessing::maxScreen()
{
	showMaximized();
}

// ȫ����ʾ
void ImageProcessing::fullScreen()
{
	showFullScreen();
}

// ����
void ImageProcessing::option()
{
	QDialog *optionWin = new QDialog();
	optionWin->setWindowTitle(tr("����"));
	optionWin->setWindowIcon(QIcon("../Image/edit/Edit_Option.png"));
	optionWin->resize(600, 400);

	QTabWidget *tabWidget = new QTabWidget(optionWin);
	QWidget *optionWidget = new QWidget(optionWin);
	tabWidget->addTab(optionWidget, "ѡ����ʽ");
	QWidget *otherWidget = new QWidget(optionWin);
	tabWidget->addTab(otherWidget, "��������");
	
	// ������ʽ(ͼƬ)
	QLabel *label_white = new QLabel();
	QImage *img_white = new QImage();
	img_white->load("../Image/edit/img_white.png");
	label_white->setPixmap(QPixmap::fromImage(*img_white));
	label_white->resize(label_white->width(), label_white->height());

	QLabel *label_black = new QLabel();
	QImage *img_black = new QImage();
	img_black->load("../Image/edit/img_black.png");
	label_black->setPixmap(QPixmap::fromImage(*img_black));
	label_black->resize(img_black->width(), img_black->height());
		
	// ������ʽ(��ѡ��)
	whiteRadio->setText(tr("�����ɫ"));
	blackRadio->setText(tr("���ź�ɫ"));
	QButtonGroup *radioGroup = new QButtonGroup();
	radioGroup->setExclusive(true);
	radioGroup->addButton(whiteRadio);
	radioGroup->addButton(blackRadio);
	connect(whiteRadio, SIGNAL(clicked()), this, SLOT(whiteLayout()));
	connect(blackRadio, SIGNAL(clicked()), this, SLOT(blackLayout()));

	if (blackRadio->isChecked() == true)		// ��Գ�ʼ���ް�ť��������
		blackRadio->setChecked(true);
	else
		whiteRadio->setChecked(true);

	// ������ʽ�����֣�
	QVBoxLayout *whiteLayout = new QVBoxLayout;
	whiteLayout->setAlignment(Qt::AlignCenter);
	whiteLayout->addWidget(label_white);
	whiteLayout->addWidget(whiteRadio);
	QWidget *whiteWidget = new QWidget();
	whiteWidget->setLayout(whiteLayout);

	QVBoxLayout *blackLayout = new QVBoxLayout();
	blackLayout->setAlignment(Qt::AlignCenter);
	blackLayout->addWidget(label_black);
	blackLayout->addWidget(blackRadio);
	QWidget *blackWidget = new QWidget();
	blackWidget->setLayout(blackLayout);

	QHBoxLayout *optionLayout = new QHBoxLayout();
	optionLayout->setAlignment(Qt::AlignCenter);
	optionLayout->addWidget(whiteWidget);
	optionLayout->addWidget(blackWidget);
	optionWidget->setLayout(optionLayout);

	// ����
	QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok	| QDialogButtonBox::Cancel);
	buttonBox->button(QDialogButtonBox::Ok)->setText(tr("ȷ��"));
	buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("ȡ��"));
	connect(buttonBox, SIGNAL(accepted()), optionWin, SLOT(close()));
	connect(buttonBox, SIGNAL(rejected()), optionWin, SLOT(close()));

	QVBoxLayout *QssLayout = new QVBoxLayout;
	QssLayout->addWidget(tabWidget);
	QssLayout->addWidget(buttonBox);
	optionWin->setLayout(QssLayout);

	optionWin->exec();
}

// ��ɫ����
void ImageProcessing::whiteLayout()
{
	this->setStyleSheet(0);
	preWin->setStyleSheet(0);
	I_menubar->setMenuQSS(false);
	isSkin = false;
}

// ��ɫ����
void ImageProcessing::blackLayout()
{
	this->setStyleSheet(stylesheet);
	preWin->setStyleSheet(stylesheet);
	I_menubar->setMenuQSS(true);
	isSkin = true;
}

// �л�Ƥ��
void ImageProcessing::changeSkin()
{
	if (isSkin == false)
	{
		this->setStyleSheet(stylesheet);
		preWin->setStyleSheet(stylesheet);
		I_menubar->setMenuQSS(true);
		blackRadio->setChecked(true);
		isSkin = true;
	}
	else
	{
		this->setStyleSheet(0);
		preWin->setStyleSheet(0);
		I_menubar->setMenuQSS(false);
		whiteRadio->setChecked(true);
		isSkin = false;
	}
}

// ͼ����������
void ImageProcessing::fullSize()
{
	QImage Img = imgLabel->getImage().scaled(ImgscrollArea->width() - 2, ImgscrollArea->height() - 2, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	ShowImage(Img, true);
	output("ͼ���С��ͼ����������");
}

// ͼ������Ӧ���ڴ�С
void ImageProcessing::autoSize()
{
	QImage Img;
	double ImgRatio = 1.0 * imgLabel->getImage().width() / imgLabel->getImage().height();
	double WinRatio = 1.0 * (ImgscrollArea->width() - 2) / (ImgscrollArea->height() - 2);
	if (ImgRatio > WinRatio)
	{
		Img = imgLabel->getImage().scaled((ImgscrollArea->width() - 2), (ImgscrollArea->width() - 2) / ImgRatio, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	}
	else
	{
		Img = imgLabel->getImage().scaled((ImgscrollArea->height() - 2) * ImgRatio, (ImgscrollArea->height() - 2), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	}
	//QImage Img = imgLabel->getImage().scaled(ImgscrollArea->width() - 2, ImgscrollArea->height() - 2, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	ShowImage(Img, true);
	output("ͼ���С������Ӧ���ڴ�С");
}

// �ı��С
void ImageProcessing::changeImageSize()				
{
	QImage Img = geomClass->Resize(imgLabel->getImage(), line_L->text().toInt(), line_W->text().toInt());
	ShowImage(Img,true);	// ͼ�񱣴�
	output("����ı䣺�� " + QString::number(Img.width()) + "	�� " + QString::number(Img.height()));
}

// Ĭ�ϴ�С
void ImageProcessing::defaultImageSize()
{
	QImage Img = geomClass->Resize(imgLabel->getImage(), 512, 512);
	ShowImage(Img, true);	// ͼ�񱣴�
	output("����ı䣺�� " + QString::number(Img.width()) + "	�� " + QString::number(Img.height()));
}

// ȷ������
void ImageProcessing::enlargeReduceOK()
{
	QImage Img = geomClass->Enlarge_Reduce(imgLabel->getImage(), line_times->text().toInt());
	ShowImage(Img, true);	// ͼ�񱣴�
	output("ͼ�����ţ��� " + QString::number(Img.width()) + "	�� " + QString::number(Img.height()));
}

// ͼ��Ŵ�2��
void ImageProcessing::enlarge2()
{
	QImage Img = geomClass->Enlarge_Reduce(imgLabel->getImage(), 1);
	ShowImage(Img, true);	// ͼ�񱣴�			
	output("ͼ��Ŵ󣺳� " + QString::number(Img.width()) + "	�� " + QString::number(Img.height()));
}

// ͼ����С2��
void ImageProcessing::reduce2()
{
	QImage Img = geomClass->Enlarge_Reduce(imgLabel->getImage(), -1);
	ShowImage(Img, true);	// ͼ�񱣴�				
	output("ͼ����С���� " + QString::number(Img.width()) + "	�� " + QString::number(Img.height()));
}

// ȷ����ת
void ImageProcessing::rotateImageOK()
{
	QImage Img;
	if(line_degree->text().toInt() == 90 || line_degree->text().toInt() == -270)
		Img = geomClass->Rotate_fixed(imgLabel->getImage(), 90);
	else if (line_degree->text().toInt() == 180 || line_degree->text().toInt() == -180)
		Img = geomClass->Rotate_fixed(imgLabel->getImage(), 180);
	else if (line_degree->text().toInt() == 270 || line_degree->text().toInt() == -90)
		Img = geomClass->Rotate_fixed(imgLabel->getImage(), 270);
	else 
		Img = geomClass->Rotate(imgLabel->getImage(), 0 - line_degree->text().toInt());

	ShowImage(Img, true);	// ͼ�񱣴�	
	output("ͼ����ת����ת�Ƕ� " + QString::number(line_degree->text().toInt()));
}

// ͼ����ת90
void ImageProcessing::rotateImage_90()				
{
	QImage Img = geomClass->Rotate_fixed(imgLabel->getImage(), 90);
	ShowImage(Img, true);	// ͼ�񱣴�	
	output("ͼ����ת��˳ʱ����ת90��");
}

// ͼ����ת180
void ImageProcessing::rotateImage_180()				
{
	QImage Img = geomClass->Rotate_fixed(imgLabel->getImage(), 180);
	ShowImage(Img, true);	// ͼ�񱣴�	
	spinbox_rotate->setValue(0);
	output("ͼ����ת��������ת180��");
}

// ͼ����ת270
void ImageProcessing::rotateImage_270()			
{
	QImage Img = geomClass->Rotate_fixed(imgLabel->getImage(), 270);
	ShowImage(Img, true);	// ͼ�񱣴�	
	spinbox_rotate->setValue(0);
	output("ͼ����ת����ʱ����ת90��");
}

// ˮƽ����
void ImageProcessing::flipImage_H()		
{
	QImage Img = geomClass->Flip(imgLabel->getImage(), 1);
	ShowImage(Img, true);	// ͼ�񱣴�	
	output("ͼ��ת��ˮƽ��ת");
}

// ��ֱ����
void ImageProcessing::flipImage_V()		
{
	QImage Img = geomClass->Flip(imgLabel->getImage(), 0);
	ShowImage(Img, true);	// ͼ�񱣴�	
	output("ͼ��ת����ֱ��ת");
}

// ͼ����б
void ImageProcessing::LeanImageOK()
{
	QImage Img = geomClass->Lean(imgLabel->getImage(), line_leanX->text().toInt(), line_leanY->text().toInt());
	ShowImage(Img,true);
	output("ͼ����б��ˮƽ " + line_leanX->text() + "	��ֱ " + line_leanY->text());
}

// ȷ�϶�ֵͼ��
void ImageProcessing::binImageOK()							
{
	QImage Img = grayClass->Bin(imgLabel->getImage(), line_bin->text().toInt());
	ShowImage(Img, true);	// ͼ�񱣴�
	output("�Ҷȱ任��ͼ���ֵ��");
}

// �Ҷ�ͼ��
void ImageProcessing::grayImage()							
{
	QImage Img = grayClass->Graylevel(imgLabel->getImage());
	ShowImage(Img, true);	// ͼ�񱣴�
	output("�Ҷȱ任���Ҷ�ͼ��");
}

// ͼ��ת
void ImageProcessing::reverseImage()
{
	QImage Img = grayClass->Reverse(imgLabel->getImage());
	ShowImage(Img, true);	// ͼ�񱣴�
	output("ͼ��ת");
}

// ȷ�����Ա任
void ImageProcessing::linearImageOK()
{
	QImage Img = grayClass->Linear(imgLabel->getImage(), line_alpha->text().toInt(), line_beta->text().toInt());
	ShowImage(Img, true);	// ͼ�񱣴�
	output("�Ҷȱ任�����Ա任");
}

// ȷ�϶����任
void ImageProcessing::logImageOK()
{
	QImage Img = grayClass->Log(imgLabel->getImage(), line_c->text().toInt());
	ShowImage(Img, true);	// ͼ�񱣴�
	output("�Ҷȱ任�������任");
}

// ȷ��٤��任
void ImageProcessing::gammaImageOK()
{
	QImage Img = grayClass->Gamma(imgLabel->getImage(), line_gamma->text().toInt());
	ShowImage(Img, true);	// ͼ�񱣴�
	output("�Ҷȱ任��٤��任");
}

// ֱ��ͼ���⻯
void ImageProcessing::histeqImage()
{
	QImage Img = grayClass->Histeq(imgLabel->getImage());
	ShowImage(Img, true);	// ͼ�񱣴�
	output("�Ҷȱ任��ֱ��ͼ���⻯");
}

// ���˲�
void ImageProcessing::normalizedImage()
{
	QImage Img = enhanceClass->Normalized(imgLabel->getImage(), 2 * (combo_smooth->currentIndex()) + 3);
	ShowImage(Img, true);	// ͼ�񱣴�
	output("ͼ��ƽ�������˲�");
}

// ��˹�˲�
void ImageProcessing::gaussianImage()
{
	QImage Img = enhanceClass->Gaussian(imgLabel->getImage(), 2 * (combo_smooth->currentIndex()) + 3);
	ShowImage(Img, true);	// ͼ�񱣴�
	output("ͼ��ƽ������˹�˲�");
}

// ��ֵ�˲�
void ImageProcessing::medianImage()
{
	QImage Img = enhanceClass->Median(imgLabel->getImage(), 2 * (combo_smooth->currentIndex()) + 3);
	ShowImage(Img, true);	// ͼ�񱣴�
	output("ͼ��ƽ������ֵ�˲�");
}

// sobel��Ե���
void ImageProcessing::sobelImage()
{
	QImage Img = enhanceClass->Sobel(imgLabel->getImage(), 2 * (combo_sharpen->currentIndex()) + 3);
	ShowImage(Img, true);	// ͼ�񱣴�
	output("ͼ���񻯣�Sobel��Ե���");
}

// laplacian��Ե���
void ImageProcessing::laplacianImage()
{
	QImage Img = enhanceClass->Laplacian(imgLabel->getImage(), 2 * (combo_sharpen->currentIndex()) + 3);
	ShowImage(Img, true);	// ͼ�񱣴�
	output("ͼ���񻯣�Laplacian��Ե���");
}

// canny��Ե���
void ImageProcessing::cannyImage()
{
	QImage Img = enhanceClass->Canny(imgLabel->getImage(), 2 * (combo_sharpen->currentIndex()) + 3, spinbox_canny->text().toInt());
	ShowImage(Img, true);	// ͼ�񱣴�
	output("ͼ���񻯣�Canny��Ե���");
}

// line���
void ImageProcessing::lineImage()
{
	QImage Img = enhanceClass->HoughLine(imgLabel->getImage(), spinbox_lineThreshold->text().toInt(), spinbox_minLineLength->text().toInt(), spinbox_maxLineGap->text().toInt());
	ShowImage(Img, true);	// ͼ�񱣴�
	output("ͼ���񻯣�Hough�߼��");
}

// circle���
void ImageProcessing::circleImage()
{
	if (spinbox_minRadius->text().toInt() > spinbox_maxRadius->text().toInt())
	{
		QMessageBox::information(this, tr("�������"), tr("���뾶Ӧ���ڵ�����С�뾶!"));
	}
	else
	{
		QImage Img = enhanceClass->HoughCircle(imgLabel->getImage(), spinbox_minRadius->text().toInt(), spinbox_maxRadius->text().toInt());
		ShowImage(Img, true);	// ͼ�񱣴�
		output("ͼ���񻯣�HoughԲ���");
	}
}

// ��ʴ
void ImageProcessing::erodeImage()							
{
	QImage Img = morpClass->Erode(imgLabel->getImage(), combo_elem->currentIndex(), combo_kernel->currentIndex(),spinbox_erode->text().toInt());
	ShowImage(Img, true);	// ͼ�񱣴�
	output("��̬ѧ����ʴ");
}

// ����
void ImageProcessing::dilateImage()							
{
	QImage Img = morpClass->Dilate(imgLabel->getImage(), combo_elem->currentIndex(), combo_kernel->currentIndex(), spinbox_dilate->text().toInt());
	ShowImage(Img, true);	// ͼ�񱣴�
	output("��̬ѧ������");
}

// ������
void ImageProcessing::openImage()							
{
	QImage Img = morpClass->Open(imgLabel->getImage(), combo_elem->currentIndex(), combo_kernel->currentIndex(), spinbox_open->text().toInt());
	ShowImage(Img, true);	// ͼ�񱣴�
	output("��̬ѧ��������");
}

// ������
void ImageProcessing::closeImage()							
{
	QImage Img = morpClass->Close(imgLabel->getImage(), combo_elem->currentIndex(), combo_kernel->currentIndex(), spinbox_close->text().toInt());
	ShowImage(Img, true);	// ͼ�񱣴�
	output("��̬ѧ��������");
}

// ��̬ѧ�ݶ�
void ImageProcessing::gradImage()							
{
	QImage Img = morpClass->Grad(imgLabel->getImage(), combo_elem->currentIndex(), combo_kernel->currentIndex());
	ShowImage(Img, true);	// ͼ�񱣴�
	output("��̬ѧ����̬ѧ�ݶ�");
}

// ��ñ����
void ImageProcessing::tophatImage()							
{
	QImage Img = morpClass->Tophat(imgLabel->getImage(), combo_elem->currentIndex(), combo_kernel->currentIndex());
	ShowImage(Img, true);	// ͼ�񱣴�
	output("��̬ѧ����ñ����");
}

// ��ñ����
void ImageProcessing::blackhatImage()						
{
	QImage Img = morpClass->Blackhat(imgLabel->getImage(), combo_elem->currentIndex(), combo_kernel->currentIndex());
	ShowImage(Img, true);	// ͼ�񱣴�
	output("��̬ѧ����ñ����");
}

// R����ͼ
void ImageProcessing::splitR()								
{
	QImage Img = imgChangeClass->splitBGR(imgLabel->getImage(), 2);
//	QImage Img = imgChangeClass->splitColor(imgLabel->getImage(), "RGB", 0);
	ShowImage(Img, true);	
	output("��ɫģ�ͣ�RGBģ�͡���R����ͼ");
}

// G����ͼ
void ImageProcessing::splitG()								
{
	QImage Img = imgChangeClass->splitBGR(imgLabel->getImage(), 1);
//	QImage Img = imgChangeClass->splitColor(imgLabel->getImage(), "RGB", 1);
	ShowImage(Img, true);
	output("��ɫģ�ͣ�RGBģ�͡���G����ͼ");
}

// B����ͼ
void ImageProcessing::splitB()								
{
	QImage Img = imgChangeClass->splitBGR(imgLabel->getImage(), 0);
//	QImage Img = imgChangeClass->splitColor(imgLabel->getImage(), "RGB", 2);
	ShowImage(Img, true);
	output("��ɫģ�ͣ�RGBģ�͡���B����ͼ");
}

// H����ͼHSV
void ImageProcessing::splitH_HSV()							
{
	if (imgLabel->getImage().depth() != 8)
	{
		QImage Img = imgChangeClass->splitColor(imgLabel->getImage(), "HSV", 0);
		ShowImage(Img, true);
		output("��ɫģ�ͣ�HSVģ�͡���H����ͼ");
	}
	else
	{
		QMessageBox message(QMessageBox::Information, tr("��ʾ"), tr("��ͼ��Ϊ�Ҷ�ͼ��"));
		message.exec();
	}
}

// S����ͼHSV
void ImageProcessing::splitS_HSV()							
{
	if (imgLabel->getImage().depth() != 8)
	{
		QImage Img = imgChangeClass->splitColor(imgLabel->getImage(), "HSV", 1);
		ShowImage(Img, true);
		output("��ɫģ�ͣ�HSVģ�͡���S����ͼ");
	}
	else
	{
		QMessageBox message(QMessageBox::Information, tr("��ʾ"), tr("��ͼ��Ϊ�Ҷ�ͼ��"));
		message.exec();
	}
}

// V����ͼHSV
void ImageProcessing::splitV_HSV()							
{
	if (imgLabel->getImage().depth() != 8)
	{
		QImage Img = imgChangeClass->splitColor(imgLabel->getImage(), "HSV", 2);
		ShowImage(Img, true);
		output("��ɫģ�ͣ�HSVģ�͡���V����ͼ");
	}
	else
	{
		QMessageBox message(QMessageBox::Information, tr("��ʾ"), tr("��ͼ��Ϊ�Ҷ�ͼ��"));
		message.exec();
	}
}

// Y����ͼYUV
void ImageProcessing::splitY_YUV()
{
	if (imgLabel->getImage().depth() != 8)
	{
		QImage Img = imgChangeClass->splitColor(imgLabel->getImage(), "YUV", 0);
		ShowImage(Img, true);
		output("��ɫģ�ͣ�YUVģ�͡���Y����ͼ");
	}
	else
	{
		QMessageBox message(QMessageBox::Information, tr("��ʾ"), tr("��ͼ��Ϊ�Ҷ�ͼ��"));
		message.exec();
	}
}

// U����ͼYUV
void ImageProcessing::splitU_YUV()							
{
	if (imgLabel->getImage().depth() != 8)
	{
		QImage Img = imgChangeClass->splitColor(imgLabel->getImage(), "YUV", 1);
		ShowImage(Img, true);
		output("��ɫģ�ͣ�YUVģ�͡���U����ͼ");
	}
	else
	{
		QMessageBox message(QMessageBox::Information, tr("��ʾ"), tr("��ͼ��Ϊ�Ҷ�ͼ��"));
		message.exec();
	}
}

// V����ͼYUV
void ImageProcessing::splitV_YUV()							
{
	if (imgLabel->getImage().depth() != 8)
	{
		QImage Img = imgChangeClass->splitColor(imgLabel->getImage(), "YUV", 2);
		ShowImage(Img, true);
		output("��ɫģ�ͣ�YUVģ�͡���V����ͼ");
	}
	else
	{
		QMessageBox message(QMessageBox::Information, tr("��ʾ"), tr("��ͼ��Ϊ�Ҷ�ͼ��"));
		message.exec();
	}
}

// H����ͼHLS
void ImageProcessing::splitH_HLS()							
{
	if (imgLabel->getImage().depth() != 8)
	{
		QImage Img = imgChangeClass->splitColor(imgLabel->getImage(), "HLS", 0);
		ShowImage(Img, true);
		output("��ɫģ�ͣ�HLSģ�͡���H����ͼ");
	}
	else
	{
		QMessageBox message(QMessageBox::Information, tr("��ʾ"), tr("��ͼ��Ϊ�Ҷ�ͼ��"));
		message.exec();
	}
}

// L����ͼHLS
void ImageProcessing::splitL_HLS()							
{
	if (imgLabel->getImage().depth() != 8)
	{
		QImage Img = imgChangeClass->splitColor(imgLabel->getImage(), "HLS", 1);
		ShowImage(Img, true);
		output("��ɫģ�ͣ�HLSģ�͡���L����ͼ");
	}
	else
	{
		QMessageBox message(QMessageBox::Information, tr("��ʾ"), tr("��ͼ��Ϊ�Ҷ�ͼ��"));
		message.exec();
	}
}

// S����ͼHLS
void ImageProcessing::splitS_HLS()							
{
	if (imgLabel->getImage().depth() != 8)
	{
		QImage Img = imgChangeClass->splitColor(imgLabel->getImage(), "HLS", 2);
		ShowImage(Img, true);
		output("��ɫģ�ͣ�HLSģ�͡���S����ͼ");
	}
	else
	{
		QMessageBox message(QMessageBox::Information, tr("��ʾ"), tr("��ͼ��Ϊ�Ҷ�ͼ��"));
		message.exec();
	}
}

 // ��ͼ�ۺ���ButtonGroup
void ImageProcessing::toolButtonClicked(int id)
{
	QList<QAbstractButton *> buttons = toolButtonGroup->buttons();
	foreach(QAbstractButton *button, buttons)
	{
		if (toolButtonGroup->button(id) != button) 
		{
			button->setChecked(false);
			button->setStyleSheet("{background-color: transparent}");	// ͸��
		}
		else if (drawType == id)
		{
			drawType = 0;
			button->setStyleSheet("{background-color: transparent}");	// ͸��
		}
		else
		{
			drawType = id;
			button->setStyleSheet("background-color: rgb(76,235,255)");// ����ɫ
		}
	}

	switch (drawType)
	{
	case 0:
		imgLabel->setShape(PaintWidget::Null); 
		ShowImage(imgLabel->getImage(),true);
		output("����ͼ�Σ��˳�����ģʽ"); break;
	case 1:								// �׸�ͼ�갴ť
		imgLabel->setShape(PaintWidget::Pen);
		output("����ͼ�Σ��ֱ�"); break;
	case 2:
		imgLabel->setShape(PaintWidget::Line);
		output("����ͼ�Σ�����"); break;
	case 3:
		imgLabel->setShape(PaintWidget::Ellipse);
		output("����ͼ�Σ���Բ��"); break;
	case 4:
		imgLabel->setShape(PaintWidget::Circle);
		output("����ͼ�Σ�Բ��"); break;
	case 5:
		imgLabel->setShape(PaintWidget::Triangle);
		output("����ͼ�Σ�������"); break;
	case 6:
		imgLabel->setShape(PaintWidget::Rhombus);
		output("����ͼ�Σ�����"); break;
	case 7:
		imgLabel->setShape(PaintWidget::Rect);
		output("����ͼ�Σ�������"); break;
	case 8:
		imgLabel->setShape(PaintWidget::Square);
		output("����ͼ�Σ�������"); break;
	case 9:
		imgLabel->setShape(PaintWidget::Hexagon);
		output("����ͼ�Σ�������"); break;
	default:
		break;
	}
}

// Ԥ�����ڲۺ���
void ImageProcessing::preButtonClicked(int id)
{
	// ���¸�ֵ
	preLabel->setImage(imgLabel->getImage());
	spinbox_size->setValue(line_times->text().toInt());
	spinbox_rotate->setValue(line_degree->text().toInt());
	spinbox_leanX->setValue(line_leanX->text().toInt());
	spinbox_leanY->setValue(line_leanY->text().toInt());
	spinbox_bin->setValue(line_bin->text().toInt());
	spinbox_alpha->setValue(line_alpha->text().toInt());
	spinbox_beta->setValue(line_beta->text().toInt());
	spinbox_c->setValue(line_c->text().toInt());
	spinbox_gamma->setValue(line_gamma->text().toInt());
	
	for (int i = 0; i < 7; i++)
	{
		if (i != id)
			widget_pre[i]->hide();
		else
			widget_pre[i]->show();
	}
	preWin->exec();
}

// ���û����߿�
void ImageProcessing::penWidth()						
{
	imgLabel->setPenWidth(spinbox_penWidth->text().toInt());
	output("�����߿�");

}

// ���û�����ɫ
void ImageProcessing::penColor()
{
	QColor c = QColorDialog::getColor(Qt::blue);
	if (c.isValid())
	{
		frame_color->setPalette(QPalette(c));
		imgLabel->setPenColor(c);
		frame_color->setStyleSheet("QFrame{background-color: rgba(" + QString::number(c.red()) + "," + QString::number(c.green()) + "," + QString::number(c.blue()) + ",1);border:none}");
	}
}

// ���������Ƿ��
void ImageProcessing::isDockImage()
{
	if (dock_Image->isHidden() == true)
		I_menubar->Act_view_image->setIcon(QIcon(""));
	else
		I_menubar->Act_view_image->setIcon(QIcon("../Image/view/Check.png"));
}

void ImageProcessing::isDockTool()
{
	if (dock_Tool->isHidden() == true)
		I_menubar->Act_view_tool->setIcon(QIcon(""));
	else
		I_menubar->Act_view_tool->setIcon(QIcon("../Image/view/Check.png"));
}

void ImageProcessing::isDockOutput()
{
	if (dock_Output->isHidden() == true)
		I_menubar->Act_view_output->setIcon(QIcon(""));
	else
		I_menubar->Act_view_output->setIcon(QIcon("../Image/view/Check.png"));
}

void ImageProcessing::isDockProp()
{
	if (dock_Prop->isHidden() == true)
		I_menubar->Act_view_prop->setIcon(QIcon(""));
	else
		I_menubar->Act_view_prop->setIcon(QIcon("../Image/view/Check.png"));
}

void ImageProcessing::isDockGeom()
{
	if (dock_Geom->isHidden() == true)
		I_menubar->Act_view_geom->setIcon(QIcon(""));
	else
		I_menubar->Act_view_geom->setIcon(QIcon("../Image/view/Check.png"));
}

void ImageProcessing::isDockGray()
{
	if (dock_Gray->isHidden() == true)
		I_menubar->Act_view_gray->setIcon(QIcon(""));
	else
		I_menubar->Act_view_gray->setIcon(QIcon("../Image/view/Check.png"));
}

void ImageProcessing::isDockEnhance()
{
	if (dock_Enhance->isHidden() == true)
		I_menubar->Act_view_enhance->setIcon(QIcon(""));
	else
		I_menubar->Act_view_enhance->setIcon(QIcon("../Image/view/Check.png"));
}

void ImageProcessing::isDockMorp()
{
	if (dock_Morp->isHidden() == true)
		I_menubar->Act_view_morp->setIcon(QIcon(""));
	else
		I_menubar->Act_view_morp->setIcon(QIcon("../Image/view/Check.png"));
}

void ImageProcessing::isDockColor()
{
	if (dock_Color->isHidden() == true)
		I_menubar->Act_view_color->setIcon(QIcon(""));
	else
		I_menubar->Act_view_color->setIcon(QIcon("../Image/view/Check.png"));
}

// ----------------------------------------------------------------------Ԥ�����ڲۺ���-------------------------------------------------------------------------------------

// ͼ�����ţ�Ԥ����
void ImageProcessing::enlargeReduce()
{
	QImage Img = geomClass->Enlarge_Reduce(imgLabel->getImage(), spinbox_size->text().toInt());
	PreviewImage(Img);	
}

// ͼ����ת��Ԥ����
void ImageProcessing::rotateImage()
{
	QImage Img = geomClass->Rotate(imgLabel->getImage(), 0 - spinbox_rotate->text().toInt());
	PreviewImage(Img);
}

// ͼ����б��Ԥ����
void ImageProcessing::LeanImage()
{
	QImage Img = geomClass->Lean(imgLabel->getImage(), spinbox_leanX->text().toInt(), spinbox_leanY->text().toInt());
	PreviewImage(Img);
}

// ��ֵͼ��Ԥ����
void ImageProcessing::binImage()
{
	QImage Img = grayClass->Bin(imgLabel->getImage(), spinbox_bin->text().toInt());
	PreviewImage(Img);
}

// ���Ա任��Ԥ����
void ImageProcessing::linearImage()
{
	QImage Img = grayClass->Linear(imgLabel->getImage(), spinbox_alpha->text().toInt(), spinbox_beta->text().toInt());
	PreviewImage(Img);
}

// �����任��Ԥ����
void ImageProcessing::logImage()
{
	QImage Img = grayClass->Log(imgLabel->getImage(), spinbox_c->text().toInt());
	PreviewImage(Img);
}

// ٤��任��Ԥ����
void ImageProcessing::gammaImage()
{
	QImage Img = grayClass->Gamma(imgLabel->getImage(), spinbox_gamma->text().toInt());
	PreviewImage(Img);
}