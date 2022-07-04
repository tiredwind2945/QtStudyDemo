#pragma execution_character_set("utf-8")		// ���ı���


//#include <QMainWindow>
//#include "ui_ImageProcessing.h"
#include <QtGui>
#include <QtWidgets>
#include <string>
#include <QMainWindow>

#include "opencv2/highgui/highgui.hpp"    
#include "opencv2/opencv.hpp"    
#include <opencv2/core/core.hpp>  

#include "header/MainWindow.h"
#include "header/CreateMenu.h"
#include "header/ImgChange.h" 
#include "header/CustomWindow.h"

using namespace cv;
using namespace std;

Menu::Menu(QWidget *parent, ImageProcessing *p)
	: QMenuBar(parent)
{
	I_MainWindow = (ImageProcessing*)p;
	
	I_ToolBar = new QToolBar ;
	I_ToolBar = I_MainWindow->addToolBar(tr("�ļ�������"));
	I_ToolBar->setMovable(false);
	
	Menu_File();
	Menu_Edit();
	Menu_View();
	Menu_Geom();
	Menu_Gray();
	Menu_Enhance();
	Menu_Morp();	
	Menu_Color();
	Menu_Help();
}

Menu::~Menu()
{
}

void Menu::Menu_File()
{
	QAction *Act_file_new = new QAction(QIcon("../Image/file/New.png"), tr("�½�"), this);
	Act_file_new->setShortcut(Qt::Key_Control & Qt::Key_N);
	//Act_file_new->setStatusTip(tr("�½�ͼ��"));
	connect(Act_file_new, SIGNAL(triggered()), this, SLOT(File_new()));

	QAction *Act_file_open = new QAction(QIcon("../Image/file/Open.png"), tr("��"), this);
	Act_file_open->setShortcuts(QKeySequence::Open);
	//Act_file_open->setStatusTip(tr("��ͼ��"));
	connect(Act_file_open, SIGNAL(triggered()), this, SLOT(File_open()));

	QAction *Act_file_save = new QAction(QIcon("../Image/file/Save.png"), tr("����"), this);
	Act_file_save->setShortcuts(QKeySequence::Save);
	//Act_file_save->setStatusTip(tr("����ͼ��"));
	connect(Act_file_save, SIGNAL(triggered()), this, SLOT(File_save()));

	QAction *Act_file_saveas = new QAction(QIcon("../Image/file/SaveAs.png"), tr("���Ϊ"), this);
	Act_file_saveas->setShortcuts(QKeySequence::SaveAs);
	//Act_file_saveas->setStatusTip(tr("ͼ�����Ϊ"));
	connect(Act_file_saveas, SIGNAL(triggered()), this, SLOT(File_saveas()));

	QAction *Act_file_close = new QAction(QIcon("../Image/file/Close.png"), tr("�ر�"), this);
	Act_file_close->setShortcuts(QKeySequence::Close);
	//Act_file_close->setStatusTip(tr("�ر����"));
	connect(Act_file_close, SIGNAL(triggered()), I_MainWindow, SLOT(close()));

	QMenu *file = addMenu(tr("�ļ�"));
	file->addAction(Act_file_new);
	file->addAction(Act_file_open);
	file->addAction(Act_file_save);
	file->addAction(Act_file_saveas);
	file->addSeparator();						//���һ���ָ���
	file->addAction(Act_file_close);

	I_ToolBar->addAction(Act_file_new);
	I_ToolBar->addAction(Act_file_open);
	I_ToolBar->addAction(Act_file_save);
}

void Menu::Menu_Edit()
{
	Act_edit_undo = new QAction(QIcon("../Image/edit/Edit_Cancel.png"), tr("����"), this);
	Act_edit_undo->setShortcuts(QKeySequence::Undo);
	connect(Act_edit_undo, SIGNAL(triggered()), I_MainWindow, SLOT(undo()));
	
	Act_edit_redo = new QAction(QIcon("../Image/edit/Edit_Resume.png"), tr("����"), this);
	Act_edit_redo->setShortcuts(QKeySequence::Redo);
	connect(Act_edit_redo, SIGNAL(triggered()), I_MainWindow, SLOT(redo()));

	QAction *Act_edit_full = new QAction(QIcon("../Image/edit/Edit_Full.png"), tr("ȫ����ʾ"), this);
	Act_edit_full->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
	connect(Act_edit_full, SIGNAL(triggered()), I_MainWindow, SLOT(fullScreen()));

	QAction *Act_edit_back = new QAction(QIcon("../Image/edit/Edit_Max.png"), tr("�˳�ȫ��"), this);
	Act_edit_back->setShortcut(QKeySequence(Qt::Key_Escape));
	connect(Act_edit_back, SIGNAL(triggered()), I_MainWindow, SLOT(maxScreen()));

	QMenu *edit = addMenu(tr("�༭"));
	edit->addAction(Act_edit_undo);
	edit->addAction(Act_edit_redo);
	edit->addAction(Act_edit_full);
	edit->addAction(Act_edit_back);

	I_ToolBar->addAction(Act_edit_undo);
	I_ToolBar->addAction(Act_edit_redo);
}

void Menu::Menu_View()
{
	Act_view_tool = new QAction(QIcon("../Image/view/Check.png"), tr("������"), this);
	connect(Act_view_tool, SIGNAL(triggered()), this, SLOT(View_tool()));
	Act_view_geom = new QAction(QIcon("../Image/view/Check.png"), tr("���α任"), this);
	connect(Act_view_geom, SIGNAL(triggered()), this, SLOT(View_geom()));
	Act_view_gray = new QAction(QIcon("../Image/view/Check.png"), tr("�Ҷȱ任"), this);
	connect(Act_view_gray, SIGNAL(triggered()), this, SLOT(View_gray()));
	Act_view_enhance = new QAction(QIcon("../Image/view/Check.png"), tr("ͼ����ǿ"), this);
	connect(Act_view_enhance, SIGNAL(triggered()), this, SLOT(View_enhance()));
	Act_view_morp = new QAction(QIcon("../Image/view/Check.png"), tr("��̬ѧ����"), this);
	connect(Act_view_morp, SIGNAL(triggered()), this, SLOT(View_morp()));
	Act_view_color = new QAction(QIcon("../Image/view/Check.png"), tr("��ɫģ��"), this);
	connect(Act_view_color, SIGNAL(triggered()), this, SLOT(View_color()));
	Act_view_image = new QAction(QIcon("../Image/view/Check.png"), tr("ͼ�񴰿�"), this);
	connect(Act_view_image, SIGNAL(triggered()), this, SLOT(View_image()));
	Act_view_output = new QAction(QIcon("../Image/view/Check.png"), tr("�������"), this);
	connect(Act_view_output, SIGNAL(triggered()), this, SLOT(View_output()));
	Act_view_prop = new QAction(QIcon("../Image/view/Check.png"), tr("���Դ���"), this);
	connect(Act_view_prop, SIGNAL(triggered()), this, SLOT(View_prop()));
	Act_edit_file = new QAction(QIcon("../Image/view/Check.png"), tr("�ļ�������"), this);
	connect(Act_edit_file, SIGNAL(triggered()), this, SLOT(View_fileBar()));
	Act_edit_paint = new QAction(QIcon("../Image/view/Check.png"), tr("��ͼ������"), this);
	connect(Act_edit_paint, SIGNAL(triggered()), this, SLOT(View_colorBar()));

	QMenu *view = addMenu(tr("��ͼ"));
	view->addAction(Act_view_tool);
	view->addAction(Act_view_geom);
	view->addAction(Act_view_gray);
	view->addAction(Act_view_enhance);
	view->addAction(Act_view_morp);
	view->addAction(Act_view_color);
	view->addAction(Act_view_output);
	view->addAction(Act_view_prop);
	view->addAction(Act_edit_file);
	view->addAction(Act_edit_paint);
}

void Menu::Menu_Geom()
{
	// �����˵�
	QAction *Act_geom_size = new QAction(QIcon("../Image/geom/Geom_Default.png"), tr("����Ӧ����"), this);
	connect(Act_geom_size, SIGNAL(triggered()), I_MainWindow, SLOT(autoSize()));
	QAction *Act_geom_enlarge = new QAction(QIcon("../Image/geom/Geom_Enlarge.png"), tr("�Ŵ�һ��"), this);
	connect(Act_geom_enlarge, SIGNAL(triggered()), I_MainWindow, SLOT(enlarge2()));
	QAction *Act_geom_reduce = new QAction(QIcon("../Image/geom/Geom_Reduce.png"), tr("��Сһ��"), this);
	connect(Act_geom_reduce, SIGNAL(triggered()), I_MainWindow, SLOT(reduce2()));

	menu_resize = new QMenu();
	menu_resize->setIcon(QIcon("../Image/geom/Geom_EnlargeReduce.png"));
	menu_resize->setTitle(tr("ͼ������"));
	menu_resize->addAction(Act_geom_size);
	menu_resize->addAction(Act_geom_enlarge);
	menu_resize->addAction(Act_geom_reduce);

	QAction *Act_geom_left = new QAction(QIcon("../Image/geom/Geom_RotateRight.png"), tr("˳ʱ����ת"), this);
	connect(Act_geom_left, SIGNAL(triggered()), I_MainWindow, SLOT(rotateImage_270()));
	QAction *Act_geom_right = new QAction(QIcon("../Image/geom/Geom_RotateLeft.png"), tr("��ʱ����ת"), this);
	connect(Act_geom_right, SIGNAL(triggered()), I_MainWindow, SLOT(rotateImage_90()));
	QAction *Act_geom_180 = new QAction(QIcon("../Image/geom/Geom_RotateCenter.png"), tr("������ת"), this);
	connect(Act_geom_180, SIGNAL(triggered()), I_MainWindow, SLOT(rotateImage_180()));

	menu_rotate = new QMenu();
	menu_rotate->setIcon(QIcon("../Image/geom/Geom_Rotate.png"));
	menu_rotate->setTitle(tr("ͼ����ת"));
	menu_rotate->addAction(Act_geom_left);
	menu_rotate->addAction(Act_geom_right);
	menu_rotate->addAction(Act_geom_180);

	QAction *Act_geom_H = new QAction(QIcon("../Image/geom/Geom_FlipX.png"), tr("ˮƽ��ת"), this);
	connect(Act_geom_H, SIGNAL(triggered()), I_MainWindow, SLOT(flipImage_H()));
	QAction *Act_geom_V = new QAction(QIcon("../Image/geom/Geom_FlipY.png"), tr("��ֱ��ת"), this);
	connect(Act_geom_V, SIGNAL(triggered()), I_MainWindow, SLOT(flipImage_V()));

	menu_flip = new QMenu();
	menu_flip->setIcon(QIcon("../Image/geom/Geom_Flip.png"));
	menu_flip->setTitle(tr("ͼ��ת"));
	menu_flip->addAction(Act_geom_H);
	menu_flip->addAction(Act_geom_V);
	
	QMenu *geom = addMenu(tr("���α任"));
	geom->addMenu(menu_resize);
	geom->addMenu(menu_rotate);
	geom->addMenu(menu_flip);
}

void Menu::Menu_Gray()		// �Ҷȱ任
{
	// �����˵�
	QAction *Act_gray_log = new QAction(QIcon("../Image/gray/Gray_Log.png"), tr("�����任"), this);
	connect(Act_gray_log, SIGNAL(triggered()), I_MainWindow, SLOT(logImageOK()));
	QAction *Act_gray_gamma = new QAction(QIcon("../Image/gray/Gray_Gamma.png"),tr("٤��任"), this);
	connect(Act_gray_gamma, SIGNAL(triggered()), I_MainWindow, SLOT(gammaImageOK()));
	QAction *Act_gray_histeq = new QAction(QIcon("../Image/gray/Gray_Histeq.png"), tr("ֱ��ͼ���⻯"), this);
	connect(Act_gray_histeq, SIGNAL(triggered()), I_MainWindow, SLOT(histeqImage()));

	menu_nolinear = new QMenu();
	menu_nolinear->addAction(Act_gray_log);
	menu_nolinear->addAction(Act_gray_gamma);
	menu_nolinear->addAction(Act_gray_histeq);
	
	// һ���˵�
	QAction *Act_gray_bin = new QAction(QIcon("../Image/gray/Gray_Bin.png"), tr("��ֵͼ"), this);
	connect(Act_gray_bin, SIGNAL(triggered()), I_MainWindow, SLOT(binImageOK()));
	QAction *Act_gray_gray = new QAction(QIcon("../Image/gray/Gray_Gray.png"), tr("�Ҷ�ͼ"), this);
	connect(Act_gray_gray, SIGNAL(triggered()), I_MainWindow, SLOT(grayImage()));
	QAction *Act_gray_reverse = new QAction(QIcon("../Image/gray/Gray_Reverse.png"), tr("��ת�任"), this);
	connect(Act_gray_reverse, SIGNAL(triggered()), I_MainWindow, SLOT(reverseImage()));
	QAction *Act_gray_linear = new QAction(QIcon("../Image/gray/Gray_Linear.png"), tr("���Ա任"), this);
	connect(Act_gray_linear, SIGNAL(triggered()), I_MainWindow, SLOT(linearImageOK()));
	QAction *Act_gray_nolinear = new QAction(QIcon("../Image/gray/Gray_Nolinear.png"), tr("�����Ա任"), this);
	Act_gray_nolinear->setMenu(menu_nolinear);
	
	QMenu *gray = addMenu(tr("�Ҷȱ任"));
	gray->addAction(Act_gray_bin);
	gray->addAction(Act_gray_gray);
	gray->addAction(Act_gray_reverse);
	gray->addAction(Act_gray_linear);
	gray->addAction(Act_gray_nolinear);
}

void Menu::Menu_Enhance()
{
	// �����˵�
	QAction *Act_enhance_circles = new QAction(tr("Բ���"), this);
	connect(Act_enhance_circles, SIGNAL(triggered()), I_MainWindow, SLOT(circleImage()));
	QAction *Act_enhance_lines = new QAction(tr("ֱ�߼��"), this);
	connect(Act_enhance_lines, SIGNAL(triggered()), I_MainWindow, SLOT(lineImage()));

	menu_detect = new QMenu();
	menu_detect->addAction(Act_enhance_circles);
	menu_detect->addAction(Act_enhance_lines);
	
	// �����˵�
	QAction *Act_enhance_normalize = new QAction(tr("���˲�"));
	connect(Act_enhance_normalize, SIGNAL(triggered()), I_MainWindow, SLOT(normalizedImage()));
	QAction *Act_enhance_gaussian = new QAction(tr("��˹�˲�"));
	connect(Act_enhance_gaussian, SIGNAL(triggered()), I_MainWindow, SLOT(gaussianImage()));
	QAction *Act_enhance_median = new QAction(tr("��ֵ�˲�"));
	connect(Act_enhance_median, SIGNAL(triggered()), I_MainWindow, SLOT(medianImage()));

	menu_smooth = new QMenu();
	menu_smooth->addAction(Act_enhance_normalize);
	menu_smooth->addAction(Act_enhance_gaussian);
	menu_smooth->addAction(Act_enhance_median);

	QAction *Act_enhance_sobel = new QAction(tr("Sobel����"));
	connect(Act_enhance_sobel, SIGNAL(triggered()), I_MainWindow, SLOT(sobelImage()));
	QAction *Act_enhance_laplacian = new QAction(tr("Laplacian����"));
	connect(Act_enhance_laplacian, SIGNAL(triggered()), I_MainWindow, SLOT(laplacianImage()));
	QAction *Act_enhance_canny = new QAction(tr("Canny����"));
	connect(Act_enhance_canny, SIGNAL(triggered()), I_MainWindow, SLOT(cannyImage()));
	QAction *Act_enhance_hough = new QAction(tr("Hough����"));
	Act_enhance_hough->setMenu(menu_detect);

	menu_sharpen = new QMenu();
	menu_sharpen->addAction(Act_enhance_sobel);
	menu_sharpen->addAction(Act_enhance_laplacian);
	menu_sharpen->addAction(Act_enhance_canny);
	menu_sharpen->addAction(Act_enhance_hough);
		
	// һ���˵�
	QAction *Act_enhance_smooth = new QAction(tr("ƽ��"), this);
	Act_enhance_smooth->setMenu(menu_smooth);
	QAction *Act_enhance_sharpen = new QAction(tr("��"), this);
	Act_enhance_sharpen->setMenu(menu_sharpen);

	QMenu *enhance = addMenu(tr("ͼ����ǿ"));
	enhance->addAction(Act_enhance_smooth);
	enhance->addAction(Act_enhance_sharpen);
}

void Menu::Menu_Morp()
{
	QAction *Act_morp_erode = new QAction(tr("��ʴ"), this);
	connect(Act_morp_erode, SIGNAL(triggered()), I_MainWindow, SLOT(erodeImage()));
	QAction *Act_morp_dilate = new QAction(tr("����"), this);
	connect(Act_morp_dilate, SIGNAL(triggered()), I_MainWindow, SLOT(dilateImage()));
	QAction *Act_morp_open = new QAction(tr("������"), this);
	connect(Act_morp_open, SIGNAL(triggered()), I_MainWindow, SLOT(openImage()));
	QAction *Act_morp_close = new QAction(tr("������"), this);
	connect(Act_morp_close, SIGNAL(triggered()), I_MainWindow, SLOT(closeImage()));
	QAction *Act_morp_tophat = new QAction(tr("��ñ����"), this);
	connect(Act_morp_tophat, SIGNAL(triggered()), I_MainWindow, SLOT(tophatImage()));
	QAction *Act_morp_blackhat = new QAction(tr("��ñ����"), this);
	connect(Act_morp_blackhat, SIGNAL(triggered()), I_MainWindow, SLOT(blackhatImage()));
	QAction *Act_morp_grad = new QAction(tr("��̬ѧ�ݶ�"), this);
	connect(Act_morp_grad, SIGNAL(triggered()), I_MainWindow, SLOT(gradImage()));

	QMenu *morp = addMenu(tr("��̬ѧ����"));
	morp->addAction(Act_morp_erode);
	morp->addAction(Act_morp_dilate);
	morp->addAction(Act_morp_open);
	morp->addAction(Act_morp_close);
	morp->addAction(Act_morp_tophat);
	morp->addAction(Act_morp_blackhat);
	morp->addAction(Act_morp_grad);
}

void  Menu::Menu_Color()
{
	QAction *Act_RGB_R = new QAction(tr("R����ͼ"), this);
	connect(Act_RGB_R, SIGNAL(triggered()), I_MainWindow, SLOT(splitR()));
	QAction *Act_RGB_G = new QAction(tr("G����ͼ"), this);
	connect(Act_RGB_G, SIGNAL(triggered()), I_MainWindow, SLOT(splitG()));
	QAction *Act_RGB_B = new QAction(tr("B����ͼ"), this);
	connect(Act_RGB_B, SIGNAL(triggered()), I_MainWindow, SLOT(splitB()));
	
	menu_RGB = new QMenu();
	menu_RGB->addAction(Act_RGB_R);
	menu_RGB->addAction(Act_RGB_G);
	menu_RGB->addAction(Act_RGB_B);
	QAction *Act_color_RGB = new QAction(tr("RGBģ��"), this);
	Act_color_RGB->setMenu(menu_RGB);
	
	QAction *Act_HSV_H = new QAction(tr("H����ͼ"), this);
	connect(Act_HSV_H, SIGNAL(triggered()), I_MainWindow, SLOT(splitH_HSV()));
	QAction *Act_HSV_S = new QAction(tr("S����ͼ"), this);
	connect(Act_HSV_S, SIGNAL(triggered()), I_MainWindow, SLOT(splitS_HSV()));
	QAction *Act_HSV_V = new QAction(tr("V����ͼ"), this);
	connect(Act_HSV_V, SIGNAL(triggered()), I_MainWindow, SLOT(splitV_HSV()));

	menu_HSV = new QMenu();
	menu_HSV->addAction(Act_HSV_H);
	menu_HSV->addAction(Act_HSV_S);
	menu_HSV->addAction(Act_HSV_V);
	QAction *Act_color_HSV = new QAction(tr("HSVģ��"), this);
	Act_color_HSV->setMenu(menu_HSV);
	
	QAction *Act_YUV_Y = new QAction(tr("Y����ͼ"), this);
	connect(Act_YUV_Y, SIGNAL(triggered()), I_MainWindow, SLOT(splitY_YUV()));
	QAction *Act_YUV_U = new QAction(tr("U����ͼ"), this);
	connect(Act_YUV_U, SIGNAL(triggered()), I_MainWindow, SLOT(splitU_YUV()));
	QAction *Act_YUV_V = new QAction(tr("V����ͼ"), this);
	connect(Act_YUV_V, SIGNAL(triggered()), I_MainWindow, SLOT(splitV_YUV()));
	
	menu_YUV = new QMenu();
	menu_YUV->addAction(Act_YUV_Y);
	menu_YUV->addAction(Act_YUV_U);
	menu_YUV->addAction(Act_YUV_V);
	QAction *Act_color_YUV = new QAction(tr("YUVģ��"), this);
	Act_color_YUV->setMenu(menu_YUV);

	QAction *Act_HLS_H = new QAction(tr("H����ͼ"), this);
	connect(Act_HLS_H, SIGNAL(triggered()), I_MainWindow, SLOT(splitH_HLS()));
	QAction *Act_HLS_L = new QAction(tr("L����ͼ"), this);
	connect(Act_HLS_L, SIGNAL(triggered()), I_MainWindow, SLOT(splitL_HLS()));
	QAction *Act_HLS_S = new QAction(tr("S����ͼ"), this);
	connect(Act_HLS_S, SIGNAL(triggered()), I_MainWindow, SLOT(splitS_HLS()));

	menu_HLS = new QMenu();
	menu_HLS->addAction(Act_HLS_H);
	menu_HLS->addAction(Act_HLS_L);
	menu_HLS->addAction(Act_HLS_S);
	QAction *Act_color_HLS = new QAction(tr("HLSģ��"), this);
	Act_color_HLS->setMenu(menu_HLS);

	QMenu *color = addMenu(tr("��ɫģ��"));
	color->addAction(Act_color_RGB);
	color->addAction(Act_color_HSV);
	color->addAction(Act_color_YUV);
	color->addAction(Act_color_HLS);
}

void Menu::Menu_Help()
{
	QAction *Act_help_info = new QAction(QIcon("../Image/help/Help_Info.png"), tr("����"), this);
	connect(Act_help_info, SIGNAL(triggered()), this, SLOT(Help_info()));

	Act_help_option = new QAction(QIcon("../Image/edit/Edit_Option.png"), tr("����"), this);
	connect(Act_help_option, SIGNAL(triggered()), I_MainWindow, SLOT(option()));
	
	QMenu *help = addMenu(tr("����"));
	help->addAction(Act_help_info);
	help->addAction(Act_help_option);
}

// -------------------�ļ�-------------------------------------------

void Menu::File_new()		// �½��ļ�
{
	// ��������ʾ
	QImage image = QImage(500, 500, QImage::Format_RGB32);
	image.fill(qRgb(255, 255, 255));
	I_MainWindow->ShowImage(image,true);
	I_MainWindow->output("�½�ͼ��: ��500����500");
	I_MainWindow->UpdateImgName("��ͼ��");
	currentPath = "";
}

void Menu::File_open()		// ���ļ�
{
	QString path = QFileDialog::getOpenFileName(this, tr("ѡ��ͼ��"), ".", tr("Images(*.jpg *.png *.bmp)"));
	if (!path.isEmpty())
	{
		QImage* img = new QImage();
		if (!(img->load(path)))
		{
			QMessageBox::information(this, tr("����"), tr("��ͼ��ʧ�ܣ�"));
			delete img;
			return;
		}
		I_MainWindow->ShowImage(*img, true);
		I_MainWindow->output("��ͼ��: "+ path );
		I_MainWindow->UpdateImgName(path);
		currentPath = path;
	}
}

void Menu::File_save()			// �����ļ�
{
	ImgChange *imgchange = new ImgChange();

	if (currentPath.isEmpty())
	{
		QString path = QFileDialog::getSaveFileName(this, tr("����ͼ��"), ".", tr("Images(*.jpg *.png *.bmp)"));
		{
			if (!path.isEmpty())
			{
				QImage img = I_MainWindow->imgLabel->getImage();
				img.save(path);
				I_MainWindow->output("ͼ�񱣴�: " + path);
				I_MainWindow->UpdateImgName(path);
				currentPath = path;
				I_MainWindow->ShowImage(img, true);
			}
		}
	}
	else
	{
		QImage img = I_MainWindow->imgLabel->getImage();
		img.save(currentPath);
		I_MainWindow->output("����ͼ��ͼ���ѱ���");
		I_MainWindow->ShowImage(img, true);
	}
}

void Menu::File_saveas()			// ���Ϊ�ļ�
{
	QString path = QFileDialog::getSaveFileName(this, tr("ͼ�����Ϊ"), ".", tr("Images(*.jpg *.png *.bmp)"));
	if (!path.isEmpty())
	{
		ImgChange *imgchange = new ImgChange();
		QImage img = I_MainWindow->imgLabel->getImage();
		img.save(path);
		I_MainWindow->output("ͼ�����Ϊ: " + path );
		I_MainWindow->UpdateImgName(path);
		I_MainWindow->ShowImage(img, true);
	}
}

// -------------------��ͼ-------------------------------------------

void Menu::View_output()
{
	if (I_MainWindow->dock_Output->isHidden() == true)
	{
		I_MainWindow->dock_Output->show();
		I_MainWindow->output("������ʾ���������");
	}
	else
	{
		I_MainWindow->dock_Output->hide();
		I_MainWindow->output("���ڹرգ��������");
	}
}

void Menu::View_tool()
{
	if (I_MainWindow->dock_Tool->isHidden() == true)
	{
	I_MainWindow->dock_Tool->show();
	I_MainWindow->output("������ʾ������������");
	}
	else
	{
		I_MainWindow->dock_Tool->hide();
		I_MainWindow->output("���ڹرգ�����������");
	}
}

void Menu::View_geom()
{
	if (I_MainWindow->dock_Geom->isHidden() == true)
	{
		I_MainWindow->dock_Geom->show();
		I_MainWindow->output("������ʾ�����α任����");
	}
	else
	{
		I_MainWindow->dock_Geom->hide();
		I_MainWindow->output("���ڹرգ����α任����");
	}
}

void Menu::View_gray()
{
	if (I_MainWindow->dock_Gray->isHidden() == true)
	{
		I_MainWindow->dock_Gray->show();
		I_MainWindow->output("������ʾ���Ҷȱ任����");
	}
	else
	{
		I_MainWindow->dock_Gray->hide();
		I_MainWindow->output("���ڹرգ��Ҷȱ任����");
	}
}

void Menu::View_enhance()
{
	if (I_MainWindow->dock_Enhance->isHidden() == true)
	{
		I_MainWindow->dock_Enhance->show();
		I_MainWindow->output("������ʾ��ͼ����ǿ����");
	}
	else
	{
		I_MainWindow->dock_Enhance->hide();
		I_MainWindow->output("���ڹرգ�ͼ����ǿ����");
	}
}

void Menu::View_morp()
{
	if (I_MainWindow->dock_Morp->isHidden() == true)
	{
		I_MainWindow->dock_Morp->show();
		I_MainWindow->output("������ʾ����̬ѧ����");
	}
	else
	{
		I_MainWindow->dock_Morp->hide();
		I_MainWindow->output("���ڹرգ���̬ѧ����");
	}
}

void Menu::View_color()
{
	if (I_MainWindow->dock_Color->isHidden() == true)
	{
		I_MainWindow->dock_Color->show();
		I_MainWindow->output("������ʾ����ɫģ�ʹ���");
	}
	else
	{
		I_MainWindow->dock_Color->hide();
		I_MainWindow->output("���ڹرգ���ɫģ�ʹ���");
	}
}

void Menu::View_image()
{
	if (I_MainWindow->dock_Image->isHidden() == true)
	{
		I_MainWindow->dock_Image->show();
		I_MainWindow->output("������ʾ��ͼ�񴰿�");
	}
	else
	{
		I_MainWindow->dock_Image->hide();
		I_MainWindow->output("���ڹرգ�ͼ�񴰿�");
	}
}

void Menu::View_prop()
{
	if (I_MainWindow->dock_Prop->isHidden() == true)
	{
		I_MainWindow->dock_Prop->show();
		I_MainWindow->output("������ʾ�����Դ���");
	}
	else
	{
		I_MainWindow->dock_Prop->hide();
		I_MainWindow->output("���ڹرգ����Դ���");
	}
}

void Menu::View_fileBar()
{
	if (I_ToolBar->isHidden() == true)
	{
		I_ToolBar->show();
		Act_edit_file->setIcon(QIcon("../Image/view/Check.png"));
		I_MainWindow->output("��ʾ���ļ�������");
	}
	else
	{
		I_ToolBar->hide();
		Act_edit_file->setIcon(QIcon(""));
		I_MainWindow->output("���أ��ļ�������");
	}
}

void Menu::View_colorBar()
{
	if (I_MainWindow->I_ColorBar->isHidden() == true)
	{
		I_MainWindow->I_ColorBar->show();
		Act_edit_paint->setIcon(QIcon("../Image/view/Check.png"));
		I_MainWindow->output("��ʾ����ͼ������");
	}
	else
	{
		I_MainWindow->I_ColorBar->hide();
		Act_edit_paint->setIcon(QIcon(""));
		I_MainWindow->output("���أ���ͼ������");
	}
}

// -------------------����-------------------------------------------

void Menu::Help_info()
{
	helpWin = new CustomWindow();
	helpWin->resize(600, 400);

	QLabel *label_about = new QLabel(helpWin);
	label_about->setText(tr("ͼ�����Ա���� 1.0 ��"));
	QLabel *label_right = new QLabel(helpWin);
	label_right->setText(tr("Copyright (C) 2018  ���� ATR"));
	QLabel *label_author = new QLabel(helpWin);
	label_author->setText(tr("���ߣ��ʼ�	  http://blog.csdn.net/u013165921"));
	QPushButton *button_ok = new QPushButton(helpWin);
	button_ok->setText(tr("ȷ��"));
	connect(button_ok, SIGNAL(clicked()), helpWin, SLOT(close()));

	label_about->move(100, 100);
	label_right->move(100, 180);
	label_author->move(100, 260);
	button_ok->move(400, 180);

	helpWin->exec();
}


void Menu::setMenuQSS(bool flag)		// ���ö����˵�QSS
{
	setSubMenu(menu_resize,flag);
	setSubMenu(menu_rotate, flag);
	setSubMenu(menu_flip, flag);
	setSubMenu(menu_nolinear, flag);
	setSubMenu(menu_detect, flag);
	setSubMenu(menu_smooth, flag);
	setSubMenu(menu_sharpen, flag);
	setSubMenu(menu_RGB, flag);
	setSubMenu(menu_HSV, flag);
	setSubMenu(menu_YUV, flag);
	setSubMenu(menu_HLS, flag);
}

void Menu::setSubMenu(QMenu *menu, bool flag)		// ����qss
{
	if (flag == true)
		menu->setStyleSheet("background-color: rgba(74, 79, 81, 1); color: rgb(187, 187, 187);selection-background-color:#4b6eaf; ");
	else
		menu->setStyleSheet(0);
}