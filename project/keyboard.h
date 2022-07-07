#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Windows.h>
#pragma comment(lib, "User32.Lib")

#include <functional>
#include <map>
#include "keyboard_handler_enum.h"

namespace controlkit
{
    class KeyboardListener
    {
    public:
        using KeyCode    = DWORD;
        using KeyState   = WPARAM;
        using Handler    = std::function<bool(KeyCode, KeyState)>;
        using HandlerId  = KeyboardHandlerEnum;
        using HandlerMap = std::map<HandlerId, Handler>;

        static constexpr KeyState KeyPressed  = 256;
        static constexpr KeyState KeyReleased = 257;

        static void Start();
        static void Stop();
        static LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam);
        static void ResetHandlerList();
        static void RegisterHandler(HandlerId id, const Handler& handler);
        static void RemoveHandler(HandlerId);

    private:
        static Handler handler_;
        static HHOOK hook_;
        static HandlerMap handler_map_;
    };
} // namespace controlkit

#endif // KEYBOARD_H
