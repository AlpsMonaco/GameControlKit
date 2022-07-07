#ifndef __VIRTUALCONTROLLER_H
#define __VIRTUALCONTROLLER_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <ViGEm/Client.h>
#pragma comment(lib, "setupapi.lib")

namespace controlkit
{
    class VirtualControllerAllocator
    {
    public:
        ~VirtualControllerAllocator();

        bool Reallocate();
        PVIGEM_CLIENT GetClient();

        static VirtualControllerAllocator& Get();

    protected:
        VirtualControllerAllocator();
        PVIGEM_CLIENT client_;
    };

    class VirtualController
    {
    public:
        VirtualController();
        ~VirtualController();

        bool Connect();
        void Disconnect();

    protected:
        PVIGEM_CLIENT client_;
        PVIGEM_TARGET target_;
    };
} // namespace controlkit

#endif // __VIRTUALCONTROLLER_H
