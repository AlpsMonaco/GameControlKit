#ifndef XINPUTLISTENER_H
#define XINPUTLISTENER_H

#include <Windows.h>
#include <XInput.h>
#include <functional>
#include <thread>

#pragma comment(lib, "Xinput.lib")

namespace controlkit
{
    class XInputListener
    {
    public:
        using XInputState   = XINPUT_STATE;
        using XInputIndex   = DWORD;
        using XInputGamepad = XINPUT_GAMEPAD;
        using Handler       = std::function<void(const XInputGamepad&)>;

        XInputListener(XInputIndex index, unsigned long long sample_ms = 10);
        void SetHandler(const Handler& handler);
        void Start();
        void Stop();
        void Wait();

    protected:
        unsigned long long sample_ms_;
        XInputIndex index_;
        bool is_stop_;
        XInputState state_;
        DWORD last_packet_number_;
        std::thread handler_thread_;
        Handler handler_;
    };
} // namespace controlkit

#endif // XINPUTLISTENER_H
