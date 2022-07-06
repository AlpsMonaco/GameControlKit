#include "virtualcontroller.h"
#include "logs.h"

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
    {
        Logs::Error("no vigem client exists.");
        return false;
    }
    if (target_ == nullptr)
    {
        target_ = vigem_target_x360_alloc();
        if (target_ == nullptr)
        {
            Logs::Error("allocate xbox360 virtual controller failed");
            return false;
        }
    }
    VIGEM_ERROR vigem_error = vigem_target_add(client_, target_);
    if (!VIGEM_SUCCESS(vigem_error))
    {
        Logs::Error("bind virtual controller to vigem client error:" + std::to_string(vigem_error));
        return false;
    }
    return true;
}

void VirtualController::Disconnect()
{
    if (target_ != nullptr)
        vigem_target_remove(client_, target_);
}

VirtualControllerAllocator &VirtualControllerAllocator::Get()
{
    static VirtualControllerAllocator allocator;
    return allocator;
}

PVIGEM_CLIENT GetVigemClient()
{
    PVIGEM_CLIENT client = vigem_alloc();
    if (client == nullptr)
    {
        Logs::Error("allocate vigem failed.");
        return nullptr;
    }
    const auto retval = vigem_connect(client);
    if (!VIGEM_SUCCESS(retval))
    {
        Logs::Error("connect to vigem error:" + std::to_string(retval));
        return nullptr;
    }
    return client;
}

VirtualControllerAllocator::~VirtualControllerAllocator()
{
    if (client_ != nullptr)
    {
        vigem_disconnect(client_);
        vigem_free(client_);
    }
}

bool VirtualControllerAllocator::Reallocate()
{
    client_ = GetVigemClient();
    return client_ != nullptr;
}

PVIGEM_CLIENT VirtualControllerAllocator::GetClient() { return client_; }
VirtualControllerAllocator::VirtualControllerAllocator() : client_(nullptr) { client_ = GetVigemClient(); }
