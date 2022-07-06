#ifndef KEYBOARDMONITORWIDGET_H
#define KEYBOARDMONITORWIDGET_H

#include <QWidget>
#include "widgetsingleton.h"

namespace Ui
{
    class KeyboardMonitorWidget;
}

class KeyboardMonitorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit KeyboardMonitorWidget(QWidget* parent = nullptr);
    ~KeyboardMonitorWidget();

signals:
    void AppendText(const QString& text);

private:
    Ui::KeyboardMonitorWidget* ui;
    WidgetSingleton::Item<KeyboardMonitorWidget> item_;
};

#endif // KEYBOARDMONITORWIDGET_H
