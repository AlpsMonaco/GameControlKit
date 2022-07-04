#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget* parent) : QWidget(parent),
                                            ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

AboutWindow::~AboutWindow()
{
    qDebug() << "destruct";
    delete ui;
}
