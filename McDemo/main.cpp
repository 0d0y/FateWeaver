#include <windows.h>
#include "McDemo.h"
#include "../Engine/Mengine.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    McDemo* pDemoProcess = new McDemo();
    pDemoProcess->Initialize(hInstance, "McDemo");
    pDemoProcess->Loop();
    pDemoProcess->Finalize();

    return 0; // (int)msg.wParam;
}
