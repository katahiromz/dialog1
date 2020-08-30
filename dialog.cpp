#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <strsafe.h>

static HICON s_hIcon = NULL;
static HICON s_hIconSmall = NULL;

LPWSTR LoadStringDx(INT nID)
{
    static UINT s_index = 0;
    const UINT cchBuffMax = 1024;
    static WCHAR s_sz[4][cchBuffMax];

    WCHAR *pszBuff = s_sz[s_index];
    s_index = (s_index + 1) % _countof(s_sz);
    pszBuff[0] = 0;
    ::LoadStringW(NULL, nID, pszBuff, cchBuffMax);
    return pszBuff;
}

BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    HINSTANCE hinst = GetModuleHandle(NULL);
    s_hIcon = LoadIcon(hinst, MAKEINTRESOURCE(1));
    s_hIconSmall = 
        (HICON)LoadImage(hinst, MAKEINTRESOURCE(1), IMAGE_ICON,
            GetSystemMetrics(SM_CXSMICON),
            GetSystemMetrics(SM_CYSMICON), 0);
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)s_hIcon);
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)s_hIconSmall);
    return TRUE;
}

void OnOK(HWND hwnd)
{
    INT n = GetDlgItemInt(hwnd, edt1, NULL, TRUE) * 2;
    SetDlgItemInt(hwnd, edt1, n, TRUE);
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id)
    {
    case IDOK:
        OnOK(hwnd);
        break;
    case IDCANCEL:
        EndDialog(hwnd, id);
        break;
    }
}

INT_PTR CALLBACK
DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        HANDLE_MSG(hwnd, WM_INITDIALOG, OnInitDialog);
        HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
    }
    return 0;
}

INT WINAPI
WinMain(HINSTANCE   hInstance,
        HINSTANCE   hPrevInstance,
        LPSTR       lpCmdLine,
        INT         nCmdShow)
{
    InitCommonControls();
    DialogBox(hInstance, MAKEINTRESOURCE(1), NULL, DialogProc);
    DestroyIcon(s_hIcon);
    DestroyIcon(s_hIconSmall);
    return 0;
}
