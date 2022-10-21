#include "imageviewer.h"

#include <QtWidgets>
#include <QFileDialog>
#include <QMessageBox>

ImageViewer::ImageViewer(QWidget *parent) :
    QMainWindow(parent)
{
    //initalize
    initMenu();
    initToolBar();
    initConnect();
    initWindow();
}

ImageViewer::~ImageViewer()
{

}

void ImageViewer::initWindow(){
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollAera = new QScrollArea;
    scrollAera->setBackgroundRole(QPalette::Dark);
    scrollAera->setWidget(imageLabel);
    setCentralWidget(scrollAera);

    setWindowTitle(tr("Image Viewer"));
    resize(500,400);
}

void ImageViewer::initMenu()
{
    //add three menus
    fileMenu = new QMenu(tr("&File"),this);
    viewMenu = new QMenu(tr("&View"),this);
    helpMenu = new QMenu(tr("&About"),this);

    //add actions and add it into corresponding menu
    openAct = new QAction(QIcon(":/image/file"),"&Open",this);
    openAct -> setShortcut(tr("ctrl+O"));
    printAct = new QAction(QIcon(":/image/print"),"&Print",this);
    printAct -> setShortcut(tr("ctrl+P"));
    printAct -> setEnabled(false);
    exitAct = new QAction(QIcon(":/image/exit"),"&Exit",this);
    exitAct -> setShortcut(tr("ctrl+Q"));
    fileMenu -> addAction(openAct);
    fileMenu -> addAction(printAct);
    fileMenu -> addSeparator();
    fileMenu -> addAction(exitAct);

    zoomInAct = new QAction(tr("Zoom &In"),this);
    zoomInAct -> setShortcut(tr("ctrl+="));
    zoomInAct -> setEnabled(false);
    zoomOutAct = new QAction(tr("Zoom &Out"),this);
    zoomOutAct -> setShortcut(tr("ctrl+-"));
    zoomOutAct -> setEnabled(false);
    normalSizeAct = new QAction(tr("&Normal Size"),this);
    normalSizeAct -> setShortcut(tr("ctrl+S"));
    normalSizeAct -> setEnabled(false);
    fitToWindowAct = new QAction(tr("&Fit to Window"),this);
    fitToWindowAct -> setShortcut(tr("ctrl+F"));
    fitToWindowAct -> setEnabled(false);
    viewMenu -> addAction(zoomInAct);
    viewMenu -> addAction(zoomOutAct);
    viewMenu -> addAction(normalSizeAct);
    viewMenu -> addSeparator();
    viewMenu -> addAction(fitToWindowAct);

    aboutAct = new QAction(tr("&About"),this);
    aboutQtAct = new QAction(tr("&About Qt"),this);
    helpMenu -> addAction(aboutAct);
    helpMenu -> addAction(aboutQtAct);

    //add menus to menubar
    menuBar() -> addMenu(fileMenu);
    menuBar() -> addMenu(viewMenu);
    menuBar() -> addMenu(helpMenu);
}

void ImageViewer::initToolBar()
{
    //add a toolbar and add its actions
     fileToolBar = new QToolBar(this);

     fileToolBar -> addAction(openAct);
     fileToolBar -> addAction(printAct);
     fileToolBar -> addAction(exitAct);

     addToolBar(Qt::TopToolBarArea,fileToolBar);
}

void ImageViewer::initConnect()
{   
    //singals and slots
    connect(openAct,SIGNAL(triggered()),this,SLOT(open()));
    connect(printAct,SIGNAL(triggered()),this,SLOT(print()));
    connect(exitAct,SIGNAL(triggered()),this,SLOT(close()));
    connect(zoomInAct,SIGNAL(triggered()),this,SLOT(zoomIn()));
    connect(zoomOutAct,SIGNAL(triggered()),this,SLOT(zoomOut()));
    connect(normalSizeAct,SIGNAL(triggered()),this,SLOT(normalSize()));
    connect(fitToWindowAct,SIGNAL(triggered()),this,SLOT(fitToWindow()));
    connect(aboutAct,SIGNAL(triggered()),this,SLOT(about()));
    connect(aboutQtAct,SIGNAL(triggered()),this,SLOT(aboutQt()));
}

//implement slot functions
void ImageViewer::updateActions()
{
    zoomInAct -> setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct -> setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct -> setEnabled(!fitToWindowAct->isChecked());
}

void ImageViewer::scaleImage(double factor)
{
    Q_ASSERT(imageLabel -> pixmap());
    scaleFactor *= factor;
    imageLabel -> resize(scaleFactor *imageLabel->pixmap()->size());

    adjustScrollBar(scrollAera -> horizontalScrollBar(),factor);
    adjustScrollBar(scrollAera -> verticalScrollBar(),factor);

    zoomInAct -> setEnabled(scaleFactor < 3.0);
    zoomOutAct -> setEnabled(scaleFactor > 0.333);
}

void ImageViewer::adjustScrollBar(QScrollBar *scrollBar,double factor)
{
    scrollBar -> setValue(int(factor * scrollBar->value()+((factor -1 ) * scrollBar->pageStep()/2)));
}

void ImageViewer::open()
{
    qDebug() << "open()";
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),QDir::currentPath());
    if(!fileName.isEmpty()){
        QImage image(fileName);
        if(image.isNull()){
            QMessageBox::information(this,tr("Image Viewer"),tr("Cannot load %1").arg(fileName));
            return;
        }
        imageLabel -> setPixmap(QPixmap::fromImage(image));
        scaleFactor = 1.0;

        printAct -> setEnabled(true);
        fitToWindowAct -> setEnabled(true);
        updateActions();

        if (!fitToWindowAct->isChecked())
            imageLabel->adjustSize();
    }
}

void ImageViewer::print()
{
    Q_ASSERT(imageLabel->pixmap());
    QPrintDialog dialog(&printer, this);
    if (dialog.exec()) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = imageLabel->pixmap()->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(imageLabel->pixmap()->rect());
        painter.drawPixmap(0, 0, *imageLabel->pixmap());
    }
}

void ImageViewer::zoomIn()
{
    scaleImage(1.25);
}

void ImageViewer::zoomOut()
{
    scaleImage(0.8);
}

void ImageViewer::normalSize()
{
    imageLabel -> adjustSize();
    scaleFactor = 1.0;
}

void ImageViewer::fitToWindow()
{
    bool fitToWindow = fitToWindowAct -> isChecked();
    scrollAera -> setWidgetResizable(fitToWindow);
    if (!fitToWindow) {
        normalSize();
    }
    updateActions();
}

void ImageViewer::about()
{
    QMessageBox::about(this, tr("About Image Viewer"),tr("<b>Image Viewer</b> example."));
}

void ImageViewer::aboutQt()
{
    QMessageBox::about(this,tr("About Qt version"),tr("Powered by Qt5.9.7"));
}
