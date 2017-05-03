#include <Windows.h>
#include <Iphlpapi.h>
#include <TlHelp32.h>
#include <string>
#include <functional>

using namespace std;

typedef void(*ProcessTerminateCallback)(void *, unsigned char);

class WinProcessUtilityAPIs {
public:
	static string GetNameByPID(unsigned int pid) {
		string pname;
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hSnapshot) {
			PROCESSENTRY32 pe32;
			pe32.dwSize = sizeof(PROCESSENTRY32);
			if (Process32First(hSnapshot, &pe32)) {
				do {
					if (pid == pe32.th32ProcessID) {
						pname = pe32.szExeFile;
						break;
					}
				} while (Process32Next(hSnapshot, &pe32));
			}
			CloseHandle(hSnapshot);
		} return pname;
	}

	static string getProcessLiteningAtTcpPort(u_short port)	{
		DWORD(WINAPI *pGetExtendedTcpTable)(
			PVOID pTcpTable,
			PDWORD pdwSize,
			BOOL bOrder,
			ULONG ulAf,
			TCP_TABLE_CLASS TableClass,
			ULONG Reserved
			);
		MIB_TCPTABLE_OWNER_PID *pTCPInfo;
		MIB_TCPROW_OWNER_PID *owner;
		DWORD size;
		DWORD dwResult;

		HMODULE hLib = LoadLibrary("iphlpapi.dll");

        pGetExtendedTcpTable = (DWORD(WINAPI *)(PVOID, PDWORD, BOOL, ULONG
                                                , TCP_TABLE_CLASS, ULONG))
			GetProcAddress(hLib, "GetExtendedTcpTable");

        dwResult = pGetExtendedTcpTable(NULL, &size, false
                                        , AF_INET, TCP_TABLE_OWNER_PID_ALL, 0);
		pTCPInfo = (MIB_TCPTABLE_OWNER_PID*)malloc(size);
        dwResult = pGetExtendedTcpTable(pTCPInfo, &size, false, AF_INET
                                        , TCP_TABLE_OWNER_PID_ALL, 0);
		for (DWORD dwLoop = 0; dwLoop < pTCPInfo->dwNumEntries; dwLoop++)
		{
			owner = &pTCPInfo->table[dwLoop];
			if (port == ntohs(owner->dwLocalPort)) {
				return GetNameByPID(owner->dwOwningPid);
			}

		}
		return "";
	}

    static std::string GetLastErrorAsString()
    {
        DWORD errorMessageID = ::GetLastError();
        if (errorMessageID == 0)
            return std::string(); //No error message has been recorded

        LPSTR messageBuffer = nullptr;
        size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER
                                     | FORMAT_MESSAGE_FROM_SYSTEM
                                     | FORMAT_MESSAGE_IGNORE_INSERTS,
                                     NULL, errorMessageID,
                                     MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)
                                     , (LPSTR)&messageBuffer, 0, NULL);

        std::string message(messageBuffer, size);

        //Free the buffer.
        LocalFree(messageBuffer);

        return message;
    }

    static VOID CALLBACK WaitOrTimerCallback(
        _In_  PVOID lpParameter,
        _In_  BOOLEAN TimerOrWaitFired
        )
    {
#if 0
        MessageBox(0, "The process has exited.", "INFO", MB_OK);
#endif
        PROCESS_INFORMATION *pi = (PROCESS_INFORMATION*)lpParameter;
        CloseHandle(pi->hProcess);
        CloseHandle(pi->hThread);
        return;
    }


#if 1
    static bool createProcess(std::string cmd
                              , HANDLE &pHandle
                              , bool noWindow = false
                              , bool waitForExit = false
                              , ProcessTerminateCallback terminateCallback = nullptr) {
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));
        si.dwFlags = STARTF_USESHOWWINDOW;
        si.wShowWindow = SW_MINIMIZE;

        if (!CreateProcess(NULL,
            const_cast<char*>(cmd.c_str()),
            NULL,
            NULL,
            FALSE,
            (noWindow ? CREATE_NO_WINDOW : 0),
            NULL,
            NULL,
            &si,
            &pi)) {
            std::cout << "CreateProcess() error: "<< GetLastErrorAsString() << std::endl;
            return false;
        }
        else {
            pHandle = pi.hProcess;
            if (waitForExit) {
                bool success = true;
                if (WAIT_OBJECT_0 != WaitForSingleObject(pi.hProcess, INFINITE))
                    success = false;
                if (!CloseHandle(pi.hProcess)) success = false;
                if (!CloseHandle(pi.hThread)) success = false;
                return success;
            } else {
                HANDLE hNewHandle = nullptr;
                PROCESS_INFORMATION *context = new PROCESS_INFORMATION(pi);

                /* For below function to have any visible effect it is importent that the
                 * parent process does not terminate before this process, reason being
                 * below function creats a thread with in parent process and there it calls
                 * WaitForSingleObject function upon the parent process. So if the parent
                 * process terminates before the child process this thread will terminate
                 * as well.
                 */
                if (RegisterWaitForSingleObject(&hNewHandle, pi.hProcess
                                                , (nullptr != terminateCallback) ? terminateCallback : WaitOrTimerCallback
                                                , context   /* Here context is the void pointer input parameter
                                                             * to the call back function
                                                             */
                                                , INFINITE
                                                , WT_EXECUTEONLYONCE)) {

                }
            }
            return true;
        }
    }
#endif
};
