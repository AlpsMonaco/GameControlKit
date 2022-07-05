#ifndef KEYBOARDMONITORWIDGET_H
#define KEYBOARDMONITORWIDGET_H

#include <QWidget>
#include "widgetkeeper.h"

namespace Ui
{
    class KeyboardMonitorWidget;
}

class KeyboardMonitorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit KeyboardMonitorWidget(WidgetKeeper* widget_keeper,
                                   QWidget* parent = nullptr);
    ~KeyboardMonitorWidget();

signals:
    void AppendText(const QString& text);

private:
    Ui::KeyboardMonitorWidget* ui;
    WidgetKeeper::Widget<KeyboardMonitorWidget> widget_;
};

#endif // KEYBOARDMONITORWIDGET_H
