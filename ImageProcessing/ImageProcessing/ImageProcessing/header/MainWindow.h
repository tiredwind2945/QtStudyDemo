#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma execution_character_set("utf-8")		// ���ı���
#include <QMainWindow>
#include <QtGui>
#include <QtWidgets>
#include "ui_ImageProcessing.h"

#include "opencv2/highgui/highgui.hpp"    
#include "opencv2/opencv.hpp"    
#include <opencv2/core/core.hpp>  

#include "header/CreateMenu.h"
#include "header/ImgChange.h"
#include "header/Geom.h"
#include "header/Gray.h"
#include "header/Enhance.h"
#include "header/Morp.h"
#include "header/PaintWidget.h"
#include "header/CustomWindow.h"

class Menu;
class CustomWindow;
class QTextEdit;
class QLabel;
class QScrollArea;

class ImageProcessing : public QMainWindow
{
	Q_OBJECT

public:
	explicit ImageProcessing(QWidget *parent = 0);
	~ImageProcessing();

	std::vector<std::vector<QImage>> imgVector;	// �洢ͼ���Vector����
	std::vector<QImage>::iterator iter;			// Vector������
	
	PaintWidget *imgLabel;						// ͼ����ʾ��
	PaintWidget *preLabel;						// Ԥ����ʾ��
	QToolBar *I_ColorBar;						// ��ͼ������
	QDockWidget *dock_Image,*dock_Tool, *dock_Output, *dock_Prop;		// ������
	QDockWidget *dock_Geom, *dock_Gray,	*dock_Enhance, *dock_Morp, *dock_Color;

	void ShowImage(QImage Img, bool isSave);	// ��ʾͼ��
	void PreviewImage(QImage Img);				// Ԥ��ͼ��
	void UpdateImgName(QString name);			// ����ͼ���ַ
	void UpdateProp(QImage src);				// ��������
	void output(QString information);			// ���
		
public slots:
	// edit
	void undo();								// ����
	void redo();								// ����
	void maxScreen();							// �����ʾ
	void fullScreen();							// ȫ����ʾ
	// Geom
	void changeImageSize();						// �ı�ͼ���С
	void defaultImageSize();					// ����ͼ���С
	void enlargeReduce();						// ͼ������
	void enlargeReduceOK();						// ȷ��
	void enlarge2();							// ����Ŵ�2��
	void reduce2();								// ������С2��
	void rotateImage();							// ͼ����ת
	void rotateImageOK();						// ȷ��
	void rotateImage_90();						// ͼ����ת90
	void rotateImage_180();						// ͼ����ת180
	void rotateImage_270();						// ͼ����ת270
	void flipImage_H();							// ˮƽ����
	void flipImage_V();							// ��ֱ����
	void LeanImage();							// ͼ����б
	void LeanImageOK();							// ͼ����б
	// Gray
	void binImage();							// ��ֵͼ��
	void binImageOK();							// ȷ��
	void grayImage();							// �Ҷ�ͼ��
	void reverseImage();						// ͼ��ת
	void linearImage();							// ���Ա任
	void linearImageOK();						// ȷ��
	void logImage();							// �����任
	void logImageOK();							// ȷ��
	void gammaImage();							// ٤��任
	void gammaImageOK();						// ȷ��
	void histeqImage();							// ֱ��ͼ���⻯
	// Enhance
	void normalizedImage();						// ���˲�
	void gaussianImage();						// ��˹�˲�
	void medianImage();							// ��ֵ�˲�
	void sobelImage();							// sobel��Ե���
	void laplacianImage();						// laplacian��Ե���
	void cannyImage();							// canny��Ե���
	void lineImage();							// line��Ե���
	void circleImage();							// circle��Ե���
	// Morp
	void erodeImage();							// ��ʴ
	void dilateImage();							// ����
	void openImage();							// ������
	void closeImage();							// ������
	void gradImage();							// ��̬ѧ�ݶ�
	void tophatImage();							// ��ñ����
	void blackhatImage();						// ��ñ����
	// Color
	void splitR();								// R����ͼ
	void splitG();								// G����ͼ
	void splitB();								// B����ͼ
	void splitH_HSV();							// H����ͼHSV
	void splitS_HSV();							// S����ͼHSV
	void splitV_HSV();							// V����ͼHSV
	void splitY_YUV();							// Y����ͼYUV
	void splitU_YUV();							// U����ͼYUV
	void splitV_YUV();							// V����ͼYUV
	void splitH_HLS();							// H����ͼHLS
	void splitL_HLS();							// L����ͼHLS
	void splitS_HLS();							// S����ͼHLS
	// ��ť��
	void toolButtonClicked(int id); 
	void preButtonClicked(int id);
	// ��ͼ������
	void penWidth();							// �����߿�
	void penColor();							// ��ʾ��ѡ��ɫ
	void whiteLayout();							// ��ɫ����
	void blackLayout();							// ��ɫ����
	void fullSize();							// ͼ����������
	void autoSize();							// ͼ������Ӧ���ڴ�С
	void changeSkin();							// �л�Ƥ��
	void option();								// ����
	// ���������Ƿ��
	void isDockImage();
	void isDockTool();
	void isDockOutput();
	void isDockProp();
	void isDockGeom();
	void isDockGray();
	void isDockEnhance();
	void isDockMorp();
	void isDockColor();
	
private:
	// Main
	Ui::ImageProcessingClass ui;
	ImgChange *imgChangeClass;					// ͼ��ı���
	Geom *geomClass;							// ���α任��
	Gray *grayClass;							// �Ҷȱ任��
	Enhance *enhanceClass;						// ͼ����ǿ��
	Morp *morpClass;							// ��̬ѧ��
	Menu *I_menubar;							// �˵���
	QTextEdit *menuEdit;						// �����˵�
	QTextEdit *outputEdit;						// �����
	QScrollArea* ImgscrollArea;					// ͼ�񴰿ڻ�����
	QWidget *widget_pre[7];						// Ԥ�����
	QString stylesheet;							// QSS��ʽ��
	bool isSkin;								// �Ƿ��л��ɺ�ɫƤ��
	
	// Geom
	QSpinBox *spinbox_size;						// ����΢����
	QSpinBox *spinbox_rotate;					// ��ת΢����
	QSpinBox *spinbox_leanX, *spinbox_leanY;	// ͼ���ƶ�����

	QLineEdit *line_L, *line_W;					// ���ó���
	QSpinBox *line_times;
	QSpinBox *line_degree;
	QSpinBox *line_leanX, *line_leanY;			// ��б�Ƕ�

	// Gray
	QSpinBox *spinbox_bin;
	QSpinBox *spinbox_alpha, *spinbox_beta;		// ͼ��Ҷȱ任
	QSpinBox *spinbox_gamma, *spinbox_c;		// ͼ��Ҷȱ任
	QSpinBox *line_bin;
	QSpinBox *line_alpha, *line_beta;
	QSpinBox *line_gamma, *line_c;

	// Enhance
	QSpinBox *spinbox_canny;					// canny΢����
	QSpinBox *spinbox_lineThreshold, *spinbox_minLineLength, *spinbox_maxLineGap;// Line
	QSpinBox *spinbox_minRadius, *spinbox_maxRadius;	// circle
	QComboBox *combo_smooth, *combo_sharpen;	// ����ѡ���

	// Morp
	QSpinBox *spinbox_erode, *spinbox_dilate;
	QSpinBox *spinbox_open, *spinbox_close;
	QSpinBox *spinbox_tophat, *spinbox_blackhat;
	QSpinBox *spinbox_hitmiss;
	QComboBox *combo_kernel, *combo_elem;

	// Help
	QRadioButton *whiteRadio, *blackRadio;

	// ���Դ���
	QLineEdit *line_img;
	QLineEdit *line_length;
	QLineEdit *line_width;
	QLineEdit *line_depth;
	QLineEdit *line_isGray;

	// Ԥ������
	CustomWindow *preWin;						// Ԥ������
	QButtonGroup *preButtonGroup;

 	// ������
	QButtonGroup *toolButtonGroup;
	int drawType;	
	
	// ��ͼ������
	QSpinBox *spinbox_penWidth;
	QFrame *frame_color;

	void init();								// ��ʼ��
	void Show();								// ����
	void CreateLayout();						// ��������
	void InitImage();							// ��ʼ��ͼ��
	void ColorToolBar();						// ���ƹ�����

	void WinMain();								// ���崰��
	void WinProp();								// ���Դ���
	void WinTool();								// ������
	void WinPreview();							// Ԥ������
	void WinGeom();								// ���α任����
	void WinGray();								// �Ҷȱ任����
	void WinEnhance();							// ͼ����ǿ����
	void WinMorp();								// ��̬ѧ������
	void WinColor();							// ��ɫģ�ʹ���
};

#endif // MAINWINDOW_H
