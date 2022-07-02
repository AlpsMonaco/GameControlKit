#include "virtualcontroller.h"

using namespace controlkit;

VirtualController::VirtualController() : client_(nullptr),
                                         target_(nullptr)
{
}

VirtualController::~VirtualController()
{
    if (target_ != nullptr)
        vigem_target_free(target_);
}

bool VirtualController::Connect()
{
    client_ = VirtualControllerAllocator::Get().GetClient();
    if (client_ == nullptr)
        return false;
    if (target_ == nullptr)
    {
        target_ = vigem_target_x360_alloc();
        if (target_ == nullptr)
            return false;
    }
    VIGEM_ERROR vigem_error = vigem_target_add(client_, target_);
    if (!VIGEM_SUCCESS(vigem_error))
        return false;
    return true;
}

void VirtualController::Disconnect()
{
    if (target_ != nullptr)
        vigem_target_remove(client_, target_);
}

VirtualControllerAllocator& VirtualControllerAllocator::Get()
{
    static VirtualControllerAllocator allocator;
    return allocator;
}

VirtualControllerAllocator::VirtualControllerAllocator() : client_(nullptr)
{
    PVIGEM_CLIENT client = vigem_alloc();
    if (client != nullptr)
    {
        const auto retval = vigem_connect(client);
        if (VIGEM_SUCCESS(retval))
            client_ = client;
    }
}

VirtualControllerAllocator::~VirtualControllerAllocator()
{
    if (client_ != nullptr)
    {
        vigem_disconnect(client_);
        vigem_free(client_);
    }
}

PVIGEM_CLIENT VirtualControllerAllocator::GetClient() { return client_; }

bool VirtualControllerAllocator::Reallocate()
{
    PVIGEM_CLIENT client = vigem_alloc();
    if (client == nullptr)
        return false;
    const auto retval = vigem_connect(client);
    if (!VIGEM_SUCCESS(retval))
        return false;
    client_ = client;
    return true;
}
