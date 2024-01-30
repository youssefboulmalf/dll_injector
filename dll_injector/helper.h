#include "mainForm.h"
#include <Windows.h>
#include <Tlhelp32.h>
#include <vcclr.h>
#include <msclr\marshal_cppstd.h>
#include <stdio.h>

using namespace System;
using namespace System::Collections::Generic;
using namespace msclr::interop;

array<String^>^ EnumProcs()
{
    List<String^>^ processNames = gcnew List<String^>();
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshot != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };
        if (Process32First(snapshot, &pe32))
        {
            do
            {
                String^ processName = marshal_as<String^>(pe32.szExeFile);
                processNames->Add(processName);
            } while (Process32Next(snapshot, &pe32));
        }
        CloseHandle(snapshot);
    }


    processNames->Sort();

    array<String^>^ processArray = processNames->ToArray();
    return processArray;
}


DWORD EnumProcsByName(String^ procName)
{
    List<String^>^ processNames = gcnew List<String^>();
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshot != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };
        if (Process32First(snapshot, &pe32))
        {
            do
            {
                String^ processName = marshal_as<String^>(pe32.szExeFile);
                if (processName == procName) {
                    return pe32.th32ProcessID;
                }
            } while (Process32Next(snapshot, &pe32));
        }
        CloseHandle(snapshot);
    }
    return 0;
}



int injectDll(System::String^ dllString, System::Object^ procNameObject){
    DWORD  dwPID = 0;
    DWORD  dwOldProt = 0;
    PVOID  rBuffer = NULL;
    HANDLE hProcess = NULL;
    HANDLE hThread = NULL;
    HMODULE hKernel32 = NULL;
    LPTHREAD_START_ROUTINE startThis = NULL;
    wchar_t dllPath[MAX_PATH] = {0};
    
    String ^ procName = procNameObject->ToString();

    dwPID = EnumProcsByName(procName);



    if (dllString != nullptr && dllPath != nullptr && MAX_PATH > 0)
    {

        pin_ptr<const wchar_t> pinnedString = PtrToStringChars(dllString);

        wcsncpy_s(dllPath, MAX_PATH, pinnedString, _TRUNCATE);
    }
    
    
    SIZE_T dllPathSize = sizeof(dllPath);





    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
    if (hProcess == NULL) {
	    return EXIT_FAILURE;
    }


    rBuffer = VirtualAllocEx(hProcess, NULL, dllPathSize, (MEM_RESERVE | MEM_COMMIT), PAGE_READWRITE);
    if (rBuffer == NULL) {
        if (hProcess) {
            CloseHandle(hProcess);
        }
        if (hThread) {
             CloseHandle(hThread);
        }
        return EXIT_FAILURE;
    }
    

    
    WriteProcessMemory(hProcess, rBuffer, dllPath, dllPathSize, NULL);


    hKernel32 = GetModuleHandleW(L"Kernel32");
    if (hKernel32 == NULL) {
        if (hProcess) {
            CloseHandle(hProcess);
        }
        if (hThread) {
            CloseHandle(hThread);
        }
        return EXIT_FAILURE;
    }

    startThis = (LPTHREAD_START_ROUTINE)GetProcAddress(hKernel32, "LoadLibraryW");
   

    hThread = CreateRemoteThread(hProcess, NULL, 0, startThis, rBuffer, 0, 0);
    if (hThread == NULL) {
        if (hProcess) {
            CloseHandle(hProcess);
        }
        if (hThread) {
            CloseHandle(hThread);
        }
        return EXIT_FAILURE;
    }

    WaitForSingleObject(hThread, INFINITE);

    return EXIT_SUCCESS;
}