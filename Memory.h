#pragma once

#include <cstdint>
#include <string>
#include <mach/mach.h>
#include "MemX/MemX.h"

namespace Memory {
    inline mach_port_t Task = mach_task_self();

    inline uintptr_t GetImageBase(const std::string& name) {
        return MemX::GetImageBase(name);
    }

    template<typename T>
    inline T Read(uintptr_t address) {
        return MemX::Read<T>(address);
    }

    template<typename T>
    inline void Write(uintptr_t address, const T& value) {
        MemX::Write<T>(address, value);
    }

    inline std::string ReadString(void* address, size_t max_len = 70) {
        return MemX::ReadString(address, max_len);
    }
}
