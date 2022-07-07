#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "keyboardmonitorwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void OpenAboutWindow();
    void dropEvent(QDropEvent* event) override;
    void dragEnterEvent(QDragEnterEvent* event) override;
    void OpenFileDialog();
    void OpenKeyboardMonitor();
    void OpenControllerMonitor();

private:
    Ui::MainWindow* ui;

    void InitKeyboardEvent();
};
#endif // MAINWINDOW_H
