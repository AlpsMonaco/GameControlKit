#include "keyboardmonitorwidget.h"
#include "ui_keyboardmonitorwidget.h"
#include <QScrollBar>
#include <QEvent>
#include <QKeyEvent>

using namespace controlkit;

KeyboardMonitorWidget::KeyboardMonitorWidget(QWidget* parent)
    : QWidget(parent),
      ui(new Ui::KeyboardMonitorWidget)
{
    ui->setupUi(this);
    ui->keyboard_monitor_text_->installEventFilter(this);
    ui->keyboard_monitor_text_->document()->setMaximumBlockCount(1000);
    setAttribute(Qt::WA_DeleteOnClose);
    connect(this, &KeyboardMonitorWidget::AppendText,
            this, &KeyboardMonitorWidget::OnAppendText);
    RegisterKeyboardEvent();
    setFocusPolicy(Qt::NoFocus);
}

KeyboardMonitorWidget::~KeyboardMonitorWidget()
{
    KeyboardListener::RemoveHandler(KeyboardHandlerEnum::kKeyboardMonitor);
    delete ui;
}

void KeyboardMonitorWidget::OnAppendText(const QString& string) { ui->keyboard_monitor_text_->append(string); }
void KeyboardMonitorWidget::RegisterKeyboardEvent()
{
    using KeyCode  = KeyboardListener::KeyCode;
    using KeyState = KeyboardListener::KeyState;
    KeyboardListener::RegisterHandler(KeyboardHandlerEnum::kKeyboardMonitor,
                                      [&](KeyCode key_code, KeyState key_state) -> bool
                                      {
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

bool KeyboardMonitorWidget::eventFilter(QObject* object, QEvent* event)
{
    qDebug() << event->type();
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* key_event = static_cast<QKeyEvent*>(event);
        qDebug() << key_event->key();
        return true;
    }
    return QWidget::eventFilter(object, event);
}
