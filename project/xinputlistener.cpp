#include "xinputlistener.h"

using namespace controlkit;

XInputListener::XInputListener(XInputIndex index, unsigned long long sample_ms)
    : sample_ms_(sample_ms),
      index_(index),
      is_stop_(false),
      state_({0, {0, 0, 0, 0, 0, 0, 0}}),
      last_packet_number_(DWORD(~0)),
      handler_thread_(),
      handler_(nullptr)
{
}

void XInputListener::Start()
{
    handler_thread_ = std::thread(
        [&]() -> void
        {
            for (;;)
            {
                if (is_stop_)
                {
                    is_stop_ = false;
                    break;
                }
                if (XInputGetState(index_, &state_) == ERROR_SUCCESS)
                {
                    if (last_packet_number_ != state_.dwPacketNumber)
                    {
                        last_packet_number_ = state_.dwPacketNumber;
                        handler_(state_.Gamepad);
                    }
                }
                std::this_thread::sleep_for(std::chrono::seconds(sample_ms_));
            }
        });
}

void XInputListener::Stop() { is_stop_ = true; }
void XInputListener::Wait() { handler_thread_.join(); }
void XInputListener::SetHandler(const Handler& handler) { handler_ = handler; }
