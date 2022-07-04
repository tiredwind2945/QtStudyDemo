#ifndef CREATEMENU_H
#define CREATEMENU_H

#include <QtGui>
#include <QtWidgets>
#include <QMenuBar>
#include <QMainWindow>

#include "opencv2/highgui/highgui.hpp"    
#include "opencv2/opencv.hpp"    
#include <opencv2/core/core.hpp> 

#include "header/MainWindow.h"
#include "header/CustomWindow.h"
class ImageProcessing;

using namespace cv;


class Menu : public QMenuBar
{
	Q_OBJECT

public:
	Menu(QWidget *parent, ImageProcessing *p);
	~Menu();

	CustomWindow *helpWin;
	QAction *Act_view_tool, *Act_view_image,*Act_view_geom, *Act_view_gray, *Act_view_enhance, *Act_view_morp,
		*Act_view_color, *Act_view_output, *Act_view_prop, *Act_edit_file, *Act_edit_paint;
	QAction *Act_edit_undo, *Act_edit_redo, *Act_help_option;
	void setMenuQSS(bool);		// ���ö����˵���QSS

private slots :
	// ����Ŀ¼
	void File_new();		// �½�
	void File_open();		// ��
	void File_save();		// ����
	void File_saveas();		// ���Ϊ

	void View_output();
	void View_tool();
	void View_geom();
	void View_gray();
	void View_enhance();
	void View_morp();
	void View_color();
	void View_image();
	void View_prop();	
	void View_fileBar();
	void View_colorBar();
	void Help_info();		

private:
	ImageProcessing *I_MainWindow;
	QToolBar *I_ToolBar;
	QString currentPath;	// ��ǰͼ��·��
	void setSubMenu(QMenu *menu, bool flag);		// ����qss

	void Menu_File();		// �ļ��˵�
	void Menu_Edit();		// �༭�˵�
	void Menu_View();		// ��ͼ�˵�
	void Menu_Geom();		// ���α任
	void Menu_Gray();		// �Ҷȱ任
	void Menu_Enhance();	// ͼ����ǿ
	void Menu_Morp();		// ��̬ѧ
	void Menu_Color();		// ��ɫģ��
	void Menu_Help();		// �����˵�

	// �����˵�
	QMenu *menu_resize, *menu_rotate, *menu_flip, *menu_nolinear, *menu_detect, *menu_smooth, *menu_sharpen;
	QMenu *menu_RGB, *menu_HSV, *menu_YUV, *menu_HLS;
};

#endif
