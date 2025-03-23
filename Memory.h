#pragma once
#include <cstdint>
#include <mach/mach.h>
#include <string>
#include <vector>
#include <dlfcn.h>

//ADD IN YOUR OWN KERNEL STUFF, ReadProcessMemory will get you banned

namespace Memory
{
	inline uint64_t ModuleBaseAddress = 0;
	inline pid_t ProcessID = 0;
	inline mach_port_t Task = 0;
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