#pragma once
#include <cstdint>
#include <mach/mach.h>
#include <string>
#include <vector>
#include <dlfcn.h>

bool IsValid(long addr) {
    return addr > 0x100000000 && addr < 0x3000000000;
}

bool IsValidAddress(long addr) {
    return addr > 0x100000000 && addr < 0x3000000000;
}

bool _read(long addr, void *buffer, int len)
{
    if (!IsValidAddress(addr)) return false;
    vm_size_t size = 0;
    kern_return_t error = vm_read_overwrite(mach_task_self(), (vm_address_t)addr, len, (vm_address_t)buffer, &size);
    if(error != KERN_SUCCESS || size != len)
    {
        return false;
    }
    return true;
}

bool _write(long addr, void *buffer, int len)
{
   if (!IsValidAddress(addr)) return false;
    kern_return_t error = vm_write(mach_task_self(), (vm_address_t)addr, (vm_offset_t)buffer, (mach_msg_type_number_t)len);
    if(error != KERN_SUCCESS)
    {
        return false;
    }
    return true;
}

namespace Memory
{
	inline uint64_t ModuleBaseAddress = (uint64_t)_dyld_get_image_header(0);
	inline pid_t ProcessID = 0;
	inline mach_port_t Task = m;
}

template <typename R> R Read(uint64_t address)
{
	R value = R();
	mach_vm_size_t size = sizeof(R);
	vm_read_overwrite(Memory::Task, address, size, (mach_vm_address_t)&value, &size);
	return value;
}

template<typename T>
std::string read_stringRPM(uint64_t address)
{
	char buffer[70];
	mach_vm_size_t size = sizeof(buffer);
	vm_read_overwrite(Memory::Task, address, size, (mach_vm_address_t)&buffer, &size);

	std::string nameString;
	for (int i = 0; i < 70; i += 2) {
		if (buffer[i] == 0)
			break;
		else
			nameString += buffer[i];
	};

	return nameString;
}

//need extra entitlements- TODO: refactor
uint64_t FindModuleBaseAddress(pid_t ProcessID, const char* modulename)
{
	const struct mach_header *mh = NULL;
	uint64_t baseAddress = 0;

	Dl_info info;
	if (dladdr((const void *)modulename, &info)) {
		mh = (const struct mach_header *)info.dli_fbase;
		baseAddress = reinterpret_cast<uint64_t>(mh);
	}

	return baseAddress;
}