#include "keyboard.h"

using namespace controlkit;

KeyboardListener::Handler KeyboardListener::handler_        = nullptr;
KeyboardListener::HandlerMap KeyboardListener::handler_map_ = KeyboardListener::HandlerMap();
HHOOK KeyboardListener::hook_                               = NULL;

LRESULT CALLBACK KeyboardListener::KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT* ks = (KBDLLHOOKSTRUCT*)lParam;
    for (const auto& it : handler_map_)
    {
        if (!it.second(ks->vkCode, wParam))
        {
            return 1;
        }
    }
    return CallNextHookEx(NULL, code, wParam, lParam);
}

void KeyboardListener::Stop()
{
    if (hook_ != NULL)
        UnhookWindowsHookEx(hook_);
    hook_ = NULL;
}

void KeyboardListener::Start() { hook_ = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0); }
void KeyboardListener::RegisterHandler(HandlerId id, const Handler& handler) { handler_map_[id] = handler; }
void KeyboardListener::RemoveHandler(HandlerId id) { handler_map_.erase(id); }