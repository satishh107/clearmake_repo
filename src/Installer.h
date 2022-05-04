/* Copyright 2022 the SumatraPDF project authors (see AUTHORS file).
   License: GPLv3 */

#define kInstallerWindowClassName L"SUMATRA_PDF_INSTALLER_FRAME"

constexpr int kInstallerWinDy = 340;

#define kRegExplorerPdfExt L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.pdf"
#define kRegClassesPdf L"Software\\Classes\\.pdf"

enum class PreviousInstallationType { None = 0, User = 1, Machine = 2, Both = 3 };

struct PreviousInstallationInfo {
    WCHAR* installationDir = nullptr;
    PreviousInstallationType typ = PreviousInstallationType::None;
    bool searchFilterInstalled = false;
    bool previewInstalled = false;

    PreviousInstallationInfo() = default;
    ~PreviousInstallationInfo();
};

// This is the height of the lower part
extern int gBottomPartDy;

extern int gButtonDy;

#define WM_APP_INSTALLATION_FINISHED (WM_APP + 1)
#define WM_APP_START_INSTALLATION (WM_APP + 2)

extern WCHAR* gFirstError;
extern const WCHAR* gDefaultMsg;
extern HWND gHwndFrame;
extern WCHAR* gMsgError;

extern Gdiplus::Color COLOR_MSG_WELCOME;
extern Gdiplus::Color COLOR_MSG_OK;
extern Gdiplus::Color COLOR_MSG_INSTALLATION;
extern Gdiplus::Color COLOR_MSG_FAILED;
extern Gdiplus::Color gCol1;
extern Gdiplus::Color gCol1Shadow;
extern Gdiplus::Color gCol2;
extern Gdiplus::Color gCol2Shadow;
extern Gdiplus::Color gCol3;
extern Gdiplus::Color gCol3Shadow;
extern Gdiplus::Color gCol4;
extern Gdiplus::Color gCol4Shadow;
extern Gdiplus::Color gCol5;
extern Gdiplus::Color gCol5Shadow;

void OnPaintFrame(HWND hwnd, bool skipoMessage);
void AnimStep();
void NotifyFailed(const WCHAR* msg);
void SetMsg(const WCHAR* msg, Gdiplus::Color color);
void SetDefaultMsg();

int KillProcessesWithModule(const WCHAR* modulePath, bool waitUntilTerminated);

TempWstr GetShortcutPathTemp(int csidl);

bool ExtractInstallerFiles();
WCHAR* GetExistingInstallationDir();
WCHAR* GetInstallDirTemp();
TempWstr GetInstalledExePathTemp();
void GetPreviousInstallInfo(PreviousInstallationInfo* info);

WCHAR* GetInstallationFilePath(const WCHAR* name);
WCHAR* GetExistingInstallationFilePath(const WCHAR* name);

void RegisterPreviewer(bool allUsers);
void UnRegisterPreviewer();

void RegisterSearchFilter(bool allUsers);
void UnRegisterSearchFilter();

void UninstallBrowserPlugin();

bool CheckInstallUninstallPossible(bool silent = false);
char* GetInstallerLogPath();

TempWstr GetRegPathUninstTemp(const WCHAR* appName);

// RegistryInstaller.cpp

bool WriteUninstallerRegistryInfo(HKEY hkey);
bool WriteExtendedFileExtensionInfo(HKEY hkey);
bool RemoveUninstallerRegistryInfo(HKEY hkey);
void RemoveOwnRegistryKeys(HKEY hkey);
int GetInstallerWinDx();
