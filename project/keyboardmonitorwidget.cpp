#include "keyboardmonitorwidget.h"
#include "ui_keyboardmonitorwidget.h"

KeyboardMonitorWidget::KeyboardMonitorWidget(WidgetKeeper* widget_keeper,
                                             QWidget* parent)
    : QWidget(parent),
      ui(new Ui::KeyboardMonitorWidget),
      widget_(widget_keeper)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    connect(this, &KeyboardMonitorWidget::AppendText,
            ui->keyboard_monitor_text_, &QPlainTextEdit::appendPlainText);
}

KeyboardMonitorWidget::~KeyboardMonitorWidget()
{
    delete ui;
}