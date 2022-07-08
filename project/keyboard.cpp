#include "keyboard.h"

using namespace controlkit;

namespace controlkit::__deprecated
{
    HHOOK KeyboardListener::hook_                               = NULL;
    KeyboardListener::Handler KeyboardListener::handler_        = nullptr;
    KeyboardListener::HandlerMap KeyboardListener::handler_map_ = KeyboardListener::HandlerMap();

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

} // namespace controlkit::__deprecated

/* v2 implementation */

KeyboardListener& KeyboardListener::Instance()
{
    static KeyboardListener instance;
    return instance;
}
KeyboardListener::KeyboardListener() : impl_() {}
KeyboardListener::~KeyboardListener() {}

KeyboardListener::Impl::Impl() : hook_(NULL)
{
}

KeyboardListener::Impl::~Impl() { Stop(); }
void KeyboardListener::Impl::Start() { hook_ = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0); }
void KeyboardListener::Impl::Stop()
{
    if (hook_ != NULL)
        UnhookWindowsHookEx(hook_);
    hook_ = NULL;
}
void KeyboardListener::Impl::RegisterHandler(HandlerId id, const Handler& handler) { handler_map_[id] = handler; }
void KeyboardListener::Impl::RemoveHandler(HandlerId id) { handler_map_.erase(id); }
KeyboardListener::Impl::HandlerMap KeyboardListener::Impl::handler_map_ = KeyboardListener::Impl::HandlerMap();
LRESULT CALLBACK KeyboardListener::Impl::KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT* ks = (KBDLLHOOKSTRUCT*)lParam;
    for (const auto& it : handler_map_)
    {
        if (!it.second(ks->vkCode, wParam))
            return 1;
    }
    return CallNextHookEx(NULL, code, wParam, lParam);
}