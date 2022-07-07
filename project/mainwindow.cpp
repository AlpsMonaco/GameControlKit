#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutwindow.h"
#include "widgetsingleton.h"
#include "keyboard.h"
#include <thread>
#include <sstream>
#include <QTableWidget>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QFileDialog>
#include <QSettings>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->action_about_,
            &QAction::triggered,
            this,
            &MainWindow::OpenAboutWindow);
    connect(ui->action_open_,
            &QAction::triggered,
            this,
            &MainWindow::OpenFileDialog);
    connect(ui->button_keyboard_value_,
            &QPushButton::pressed,
            this,
            &MainWindow::OpenKeyboardMonitor);
    connect(ui->button_open_,
            &QPushButton::pressed,
            this,
            &MainWindow::OpenFileDialog);
    connect(ui->button_controller_value_,
            &QPushButton::pressed,
            this,
            &MainWindow::OpenControllerMonitor);
    InitKeyboardEvent();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OpenAboutWindow()
{
    qDebug() << "triggered";
    AboutWindow* about_window = new AboutWindow();
    about_window->show();
    qDebug() << "end";
}

void MainWindow::dropEvent(QDropEvent* event)
{
    const QMimeData* mimeData = event->mimeData(); // 获取MIME数据
    if (mimeData->hasUrls())
    {
        QList<QUrl> urlList = mimeData->urls(); // 获取URL列表
        for (auto& v : urlList)
        {
            qDebug() << v.toLocalFile();
        }
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
    else
        event->ignore();
}

void MainWindow::OpenFileDialog()
{
    const QString& fileName = QFileDialog::getOpenFileName(this,
                                                           tr("选择文件"),
                                                           ".",
                                                           tr("所有文件(*.*)"));
    qDebug() << "filename : " << fileName;
}

void MainWindow::OpenKeyboardMonitor()
{
    auto widget = WidgetSingleton::GetWidget<KeyboardMonitorWidget>();
    widget->showNormal();
    widget->activateWindow();
}

void MainWindow::OpenControllerMonitor()
{
    std::stringstream ss;
    ss << "current thread:" << std::this_thread::get_id();
    std::string s = ss.str();
    qDebug() << s.c_str();
}

void MainWindow::InitKeyboardEvent() { controlkit::KeyboardListener::Start(); }
