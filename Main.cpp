#include "Memory.h"
#include "Cheats.static 

void didFinishLaunching(CFNotificationCenterRef center, void *observer, CFStringRef name, const void *object, CFDictionaryRef info)
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
       main();
    });
}

__attribute__((constructor)) static void initialize()
{
    CFNotificationCenterAddObserver(CFNotificationCenterGetLocalCenter(), NULL, &didFinishLaunching, (CFStringRef)UIApplicationDidFinishLaunchingNotification, NULL, CFNotificationSuspensionBehaviorDrop);
}


int main()
{
	// ONCE AGAIN THIS IS WILL GET YOU BANNED ON BATTLEYE SERVERS, ADD IN YOUR OWN DRIVER TO RPM
	HWND window = FindWindowA(NULL, "ArkAscended");
	GetWindowThreadProcessId(window, &Memory::ProcessID);
	if (Memory::ProcessID == 0) return 0;

	Memory::ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, false, Memory::ProcessID);
	Memory::ModuleBaseAddress = FindModuleBaseAddress(Memory::ProcessID, "ArkAscended.exe");
	
	if (Memory::ModuleBaseAddress != 0)
		Cheats::Run();
	else
		return 0;
}