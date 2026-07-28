#include "Memory.hpp"
#include <Globals.hpp>
#include <winternl.h>

namespace Core {

	uintptr_t MemoryClass::PatternScan(std::vector<uint8_t> Pattern, int InstructionLength)
	{
		uintptr_t Address = FindSignature(Pattern);

		if (InstructionLength != 0)
		{
			Address = ResolveRelativeAddress(Address, InstructionLength);
		}

		return Address;
	}

	uintptr_t MemoryClass::FindSignature(std::vector<uint8_t> Signature, uintptr_t ModuleBase, uintptr_t ModuleBaseSize)
	{
		const size_t blockSize = (4096 * 4);
		std::unique_ptr<uint8_t[]> data = std::make_unique<uint8_t[]>(blockSize);

		DWORD oldProtect;
		size_t signatureSize = Signature.size();

		uintptr_t ModulBase;
		uintptr_t ModulBaseSize;

		if (ModuleBase != 0 && ModuleBaseSize != 0) {
			ModulBase = ModuleBase;
			ModulBaseSize = ModuleBaseSize;
		}
		else {
			ModulBase = ModBase;
			ModulBaseSize = ModBaseSize;
		}

		for (uintptr_t address = ModulBase; address < ModulBase + ModulBaseSize; address += blockSize)
		{
			if (!VirtualProtectEx(ProcHandle, (LPVOID)address, blockSize, PAGE_EXECUTE_READWRITE, &oldProtect)) { continue; }

			SIZE_T bytesRead;
			if (!ReadProcessMemory(ProcHandle, (void*)address, data.get(), blockSize, &bytesRead)) {
				VirtualProtectEx(ProcHandle, (LPVOID)address, blockSize, oldProtect, NULL);
				continue;
			}

			VirtualProtectEx(ProcHandle, (LPVOID)address, blockSize, oldProtect, NULL);

			for (uintptr_t i = 0; i < bytesRead; i++)
			{
				for (uintptr_t j = 0; j < signatureSize; j++)
				{
					if (Signature[j] == 0x00)
						continue;

					if (data[i + j] != Signature[j])
						break;

					if (j == signatureSize - 1)
						return (address + i);
				}
			}
		}

		return 0x0;
	}

	uintptr_t MemoryClass::FindSignatureBypass(std::vector<uint8_t> Signature, uintptr_t ModuleBase, uintptr_t ModuleBaseSize)
	{
		const size_t blockSize = (4096 * 4);
		std::unique_ptr<uint8_t[]> data = std::make_unique<uint8_t[]>(blockSize);

		DWORD oldProtect;
		size_t signatureSize = Signature.size();

		uintptr_t ModulBase;
		uintptr_t ModulBaseSize;

		if (ModuleBase != 0 && ModuleBaseSize != 0) {
			ModulBase = ModuleBase;
			ModulBaseSize = ModuleBaseSize;
		}
		else {
			ModulBase = ModBase;
			ModulBaseSize = ModBaseSize;
		}

		for (uintptr_t address = ModulBase; address < ModulBase + ModulBaseSize; address += blockSize)
		{
			//if (!VirtualProtectEx(ProcHandle, (LPVOID)address, blockSize, PAGE_EXECUTE_READWRITE, &oldProtect)) { continue; }

			SIZE_T bytesRead;
			if (!ReadProcessMemory(ProcHandle, (void*)address, data.get(), blockSize, &bytesRead)) {
				//VirtualProtectEx(ProcHandle, (LPVOID)address, blockSize, oldProtect, NULL);
				continue;
			}

			//VirtualProtectEx(ProcHandle, (LPVOID)address, blockSize, oldProtect, NULL);

			for (uintptr_t i = 0; i < bytesRead; i++)
			{
				for (uintptr_t j = 0; j < signatureSize; j++)
				{
					if (Signature[j] == 0x00)
						continue;

					if (data[i + j] != Signature[j])
						break;

					if (j == signatureSize - 1)
						return (address + i);
				}
			}
		}

		return 0x0;
	}

	uintptr_t MemoryClass::FindSignatureStr(std::string Pattern, uintptr_t ModuleBase, uintptr_t ModuleBaseSize) {
		std::vector<uint8_t> signature = Pattern2Vector(Pattern);
		if (ModuleBase != 0 && ModuleBaseSize != 0) {
			return FindSignature(signature, ModuleBase, ModuleBaseSize);
		}
		else {
			return FindSignature(signature); // Find Sig in module from open proc.
		}
	}

	std::vector<uint8_t> MemoryClass::ReadBytes(uintptr_t Addr, size_t Size) {
		std::vector<uint8_t> bytes(Size);
		size_t bytesRead = 0;
		ZwReadVirtualMemory(ProcHandle, (LPCVOID)Addr, bytes.data(), Size, &bytesRead);
		bytes.resize(bytesRead);
		return bytes;
	}

	BOOL MemoryClass::WriteBytes(uintptr_t Addr, std::vector<uint8_t> Bytes) {
		NTSTATUS status = ZwWriteVirtualMemory(ProcHandle, (LPVOID)Addr, Bytes.data(), Bytes.size(), NULL);
		return NT_SUCCESS(status);
	}

	BOOL MemoryClass::PatchFunc(uintptr_t Addr, int NopCount)
	{
		if (!NopCount) return false;

		std::vector<uint8_t> PatchTable = { };
		for (int i = 0; i < NopCount; i++)
		{
			PatchTable.push_back({ 0x90 });
		}

		return WriteBytes(Addr, PatchTable);
	}


	BOOL MemoryClass::GetMaxPrivileges(HANDLE hProc) {
		HANDLE h_Token;
		DWORD dw_TokenLength;
		if (OpenProcessToken(hProc, TOKEN_READ | TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &h_Token))
		{
			TOKEN_PRIVILEGES* privilages = new TOKEN_PRIVILEGES[100];
			if (GetTokenInformation(h_Token, TokenPrivileges, privilages, sizeof(TOKEN_PRIVILEGES) * 100, &dw_TokenLength))
			{
				for (int i = 0; i < privilages->PrivilegeCount; i++)
				{
					privilages->Privileges[i].Attributes = SE_PRIVILEGE_ENABLED;
				}
				if (AdjustTokenPrivileges(h_Token, false, privilages, sizeof(TOKEN_PRIVILEGES) * 100, NULL, NULL))
				{
					delete[] privilages;
					return true;
				}
			}
			delete[] privilages;
		}

		return false;
	}

	std::string MemoryClass::ReadString(uintptr_t Addr) {
		char buffer[256] = {};
		SIZE_T bytesRead = 0;
		NTSTATUS status = ZwReadVirtualMemory(ProcHandle, (LPCVOID)Addr, buffer, sizeof(buffer) - 1, &bytesRead);
		if (!NT_SUCCESS(status))
			return {};
		buffer[bytesRead] = '\0';
		return std::string(buffer);
	}

	std::string MemoryClass::ReadStdString(uintptr_t Addr) {
		struct StdStringData {
			union {
				char Buf[16];
				char* Ptr;
			};
			size_t Size;
			size_t Capacity;
		};
		StdStringData data = {};
		SIZE_T bytesRead = 0;
		NTSTATUS status = ZwReadVirtualMemory(ProcHandle, (LPCVOID)Addr, &data, sizeof(data), &bytesRead);
		if (!NT_SUCCESS(status))
			return {};
		if (data.Size > 256)
			return {};
		const size_t SsoFlag = 0x8000000000000000;
		if (data.Capacity & SsoFlag) {
			size_t len = min(data.Size, (size_t)15);
			return std::string(data.Buf, data.Buf + len);
		}
		else {
			if (!data.Ptr)
				return {};
			std::string result;
			result.resize(data.Size);
			if (data.Size > 0) {
				ZwReadVirtualMemory(ProcHandle, (LPCVOID)data.Ptr, &result[0], data.Size, NULL);
			}
			return result;
		}
	}

	DWORD MemoryClass::GetPidByName(const char* ProcName) {
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hSnapshot == INVALID_HANDLE_VALUE) {
			return 0;
		}

		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);

		if (!Process32First(hSnapshot, &pe32)) {
			CloseHandle(hSnapshot);
			return 0;
		}

		DWORD pid = 0;
		do {
			if (_stricmp(pe32.szExeFile, ProcName) == 0) {
				pid = pe32.th32ProcessID;
				break;
			}
		} while (Process32Next(hSnapshot, &pe32));

		CloseHandle(hSnapshot);
		return pid;
	}

	std::string MemoryClass::GetNameByPid(DWORD Pid) {
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, Pid);
		if (!hProcess) { return ""; }

		char processName[MAX_PATH];
		if (!GetModuleFileNameEx(hProcess, NULL, processName, MAX_PATH)) { return ""; }

		CloseHandle(hProcess);

		std::string fullPath(processName);
		size_t pos = fullPath.find_last_of(xorstr("\\/"));
		if (pos != std::string::npos) {
			return fullPath.substr(pos + 1);
		}
		else {
			return fullPath;
		}
	}

	uintptr_t MemoryClass::GetModuleBaseAddr(DWORD ProcId, const char* ModuleName, uintptr_t* ModSize) {
		HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcId);

		if (hSnapShot == INVALID_HANDLE_VALUE) { return 0; }

		uintptr_t baseAddr = 0;
		uintptr_t modSize = 0;

		MODULEENTRY32 ModuleEntry;
		ModuleEntry.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(hSnapShot, &ModuleEntry)) {
			do {
				if (strcmp(ModuleEntry.szModule, ModuleName) == 0) {
					baseAddr = (uintptr_t)ModuleEntry.modBaseAddr;
					modSize = (uintptr_t)ModuleEntry.modBaseSize;
					break;
				}
			} while (Module32Next(hSnapShot, &ModuleEntry));
		}
		CloseHandle(hSnapShot);

		if (ModSize) *ModSize = modSize;
		return baseAddr;
	}

	uint64_t MemoryClass::GetModuleBaseByName(DWORD Pid, std::wstring ModuleName) {
		HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, Pid);
		if (hSnapShot == INVALID_HANDLE_VALUE) return 0;
		uint64_t baseAddr = 0;
		int nameLen = WideCharToMultiByte(CP_UTF8, 0, ModuleName.c_str(), -1, NULL, 0, NULL, NULL);
		std::string modNameA(nameLen, 0);
		WideCharToMultiByte(CP_UTF8, 0, ModuleName.c_str(), -1, &modNameA[0], nameLen, NULL, NULL);
		MODULEENTRY32 ModuleEntry;
		ModuleEntry.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(hSnapShot, &ModuleEntry)) {
			do {
				if (modNameA == ModuleEntry.szModule) {
					baseAddr = (uintptr_t)ModuleEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnapShot, &ModuleEntry));
		}
		CloseHandle(hSnapShot);
		return baseAddr;
	}

	uint64_t MemoryClass::GetModuleBaseSizeByName(DWORD Pid, std::wstring ModuleName) {
		HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, Pid);
		if (hSnapShot == INVALID_HANDLE_VALUE) return 0;
		uint64_t modSize = 0;
		int nameLen = WideCharToMultiByte(CP_UTF8, 0, ModuleName.c_str(), -1, NULL, 0, NULL, NULL);
		std::string modNameA(nameLen, 0);
		WideCharToMultiByte(CP_UTF8, 0, ModuleName.c_str(), -1, &modNameA[0], nameLen, NULL, NULL);
		MODULEENTRY32 ModuleEntry;
		ModuleEntry.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(hSnapShot, &ModuleEntry)) {
			do {
				if (modNameA == ModuleEntry.szModule) {
					modSize = (uintptr_t)ModuleEntry.modBaseSize;
					break;
				}
			} while (Module32Next(hSnapShot, &ModuleEntry));
		}
		CloseHandle(hSnapShot);
		return modSize;
	}

	BOOL MemoryClass::OpenProcByPid() {
		if (g_Variables.ProcIdFiveM == 0) { return false; }

		ProcHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, g_Variables.ProcIdFiveM);
		std::cout << "Process Handle: " << ProcHandle << std::endl;
		if (!ProcHandle) { return false; };

		std::string procNameStr(Mem.ProcName.begin(), Mem.ProcName.end()); 
		Mem.ModBase = Mem.GetModuleBaseAddr(g_Variables.ProcIdFiveM, procNameStr.c_str(), &ModBaseSize);


		return true;
	}

}