#include "keyboardmonitorwidget.h"
#include "ui_keyboardmonitorwidget.h"
#include <QScrollBar>

using namespace controlkit;

KeyboardMonitorWidget::KeyboardMonitorWidget(QWidget* parent)
    : QWidget(parent),
      ui(new Ui::KeyboardMonitorWidget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    connect(this, &KeyboardMonitorWidget::AppendText,
            ui->keyboard_monitor_text_, &QPlainTextEdit::appendPlainText);
    RegisterKeyboardEvent();
    setFocusPolicy(Qt::NoFocus);
}

KeyboardMonitorWidget::~KeyboardMonitorWidget()
{
    KeyboardListener::RemoveHandler(KeyboardHandlerEnum::kKeyboardMonitor);
    delete ui;
}

void KeyboardMonitorWidget::RegisterKeyboardEvent()
{
    using KeyCode  = KeyboardListener::KeyCode;
    using KeyState = KeyboardListener::KeyState;
    KeyboardListener::RegisterHandler(KeyboardHandlerEnum::kKeyboardMonitor,
                                      [&](KeyCode key_code, KeyState key_state) -> bool
                                      {
                                          ui->keyboard_monitor_text_->
                                          verticalScrollBar()->
                                          setValue(
                                            ui->keyboard_monitor_text_->verticalScrollBar()->maximum());
                                          static QString string;
                                          const static QString pressed_string  = "按下";
                                          const static QString released_string = "放开";

                                          string = "键值:" + QString::number(key_code);
                                          string += ", 状态：" +
                                                    ((key_state == KeyboardListener::KeyPressed) ? pressed_string : released_string);
                                          emit AppendText(string);
                                          return true;
                                      });
}
