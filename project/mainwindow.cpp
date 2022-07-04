#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutwindow.h"
#include <QTableWidget>
#include <QScrollBar>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->action_about_, &QAction::triggered, this, &MainWindow::OpenAboutWindow);
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
