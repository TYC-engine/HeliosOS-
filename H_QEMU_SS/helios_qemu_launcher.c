#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <commdlg.h>
#include <stdio.h>

char qemuPath[MAX_PATH] = "";
char diskPath[MAX_PATH] = "";
int ramMB = 128;

const char* CONFIG_FILE = "helios_vm.cfg";

/* =========================
   SAVE / LOAD CONFIG
   ========================= */

void save_config()
{
    FILE* f = fopen(CONFIG_FILE, "w");
    if(!f) return;

    fprintf(f, "%s\n%s\n%d\n", qemuPath, diskPath, ramMB);
    fclose(f);
}

void load_config()
{
    FILE* f = fopen(CONFIG_FILE, "r");
    if(!f) return;

    fgets(qemuPath, MAX_PATH, f);
    fgets(diskPath, MAX_PATH, f);
    fscanf(f, "%d", &ramMB);

    // remove newline
    qemuPath[strcspn(qemuPath, "\n")] = 0;
    diskPath[strcspn(diskPath, "\n")] = 0;

    fclose(f);
}

/* =========================
   FILE PICKER
   ========================= */

int pick_file(HWND hwnd, char* out, const char* filter)
{
    OPENFILENAMEA ofn;
    ZeroMemory(&ofn, sizeof(ofn));

    char file[MAX_PATH] = "";

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = file;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = filter;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if(GetOpenFileNameA(&ofn))
    {
        strcpy(out, file);
        return 1;
    }

    return 0;
}

/* =========================
   FIRST RUN QEMU SELECT
   ========================= */

void select_qemu(HWND hwnd)
{
    pick_file(hwnd, qemuPath,
        "QEMU\0qemu-system-x86_64.exe\0All\0*.*\0");
}

/* =========================
   SELECT DISK
   ========================= */

void select_disk(HWND hwnd)
{
    pick_file(hwnd, diskPath,
        "Disk Images\0*.img;*.iso;*.vhd\0All\0*.*\0");
}

/* =========================
   RUN QEMU
   ========================= */

void run_qemu()
{
    if(qemuPath[0] == 0)
    {
        MessageBoxA(NULL, "QEMU path not set", "Error", MB_OK);
        return;
    }

    if(diskPath[0] == 0)
    {
        MessageBoxA(NULL, "No disk selected", "Error", MB_OK);
        return;
    }

    char cmd[1024];

    sprintf(cmd,
        "\"%s\" -m %d -drive file=\"%s\",format=raw -vga std",
        qemuPath,
        ramMB,
        diskPath
    );

    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    CreateProcessA(
        NULL,
        cmd,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi
    );
}

/* =========================
   WINDOW PROC
   ========================= */

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case 1: select_qemu(hwnd); break;
                case 2: select_disk(hwnd); break;
                case 3: run_qemu(); break;
                case 10: ramMB = 128; break;
                case 11: ramMB = 1024; break;
                case 12: ramMB = 4096; break;
            }

            save_config();
        }
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

/* =========================
   MAIN
   ========================= */

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
    load_config();

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "HeliosQEMU";

    RegisterClass(&wc);

    HWND hwnd = CreateWindow(
        "HeliosQEMU",
        "Helios VM Launcher",
        WS_OVERLAPPEDWINDOW,
        200,200,420,300,
        NULL,NULL,hInst,NULL
    );

    ShowWindow(hwnd, SW_SHOW);

    CreateWindow("button", "Select QEMU",
        WS_VISIBLE|WS_CHILD,
        20,20,150,30, hwnd, (HMENU)1, hInst, NULL);

    CreateWindow("button", "Select Disk",
        WS_VISIBLE|WS_CHILD,
        20,60,150,30, hwnd, (HMENU)2, hInst, NULL);

    CreateWindow("button", "Run VM",
        WS_VISIBLE|WS_CHILD,
        20,200,150,40, hwnd, (HMENU)3, hInst, NULL);

    CreateWindow("button", "128 MB",
        WS_VISIBLE|WS_CHILD,
        200,20,150,25, hwnd, (HMENU)10, hInst, NULL);

    CreateWindow("button", "1 GB",
        WS_VISIBLE|WS_CHILD,
        200,50,150,25, hwnd, (HMENU)11, hInst, NULL);

    CreateWindow("button", "4 GB",
        WS_VISIBLE|WS_CHILD,
        200,80,150,25, hwnd, (HMENU)12, hInst, NULL);

    MSG msg = {};
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    save_config();
    return 0;
}
