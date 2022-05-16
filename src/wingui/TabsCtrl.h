/* Copyright 2022 the SumatraPDF project authors (see AUTHORS file).
   License: Simplified BSD (see COPYING.BSD) */

struct TabsCtrl;
class TabsCtrlState;

using TabSelectedCb = std::function<void(TabsCtrl*, TabsCtrlState*, int)>;
using TabClosedCb = std::function<void(TabsCtrl*, TabsCtrlState*, int)>;

class TabItem {
  public:
    TabItem(const char* title, const char* toolTip);

    str::Str title;
    str::Str toolTip;
};

class TabsCtrlState {
  public:
    Vec<TabItem*> tabs;
    int selectedItem = 0;
};

class TabsCtrlPrivate;

struct TabsCtrl {
    // creation parameters. must be set before CreateTabsCtrl
    HWND parent = nullptr;
    RECT initialPos{};

    TabSelectedCb onTabSelected = nullptr;
    TabClosedCb onTabClosed = nullptr;

    TabsCtrlPrivate* priv;
};

/* Creation sequence:
- AllocTabsCtrl()
- set creation parameters
- CreateTabsCtrl()
*/

TabsCtrl* AllocTabsCtrl(HWND parent, RECT initialPosition);
bool CreateTabsCtrl(TabsCtrl*);
void DeleteTabsCtrl(TabsCtrl*);
void SetState(TabsCtrl*, TabsCtrlState*);
SIZE GetIdealSize(TabsCtrl*);
void SetPos(TabsCtrl*, RECT&);
void SetFont(TabsCtrl*, HFONT);

struct TabsCtrl2 : WindowBase {
    str::WStr lastTabText;
    bool createToolTipsHwnd = false;
    str::WStr currTooltipText;

    WStrVec tooltips;

    // for all WM_NOTIFY messages
    WmNotifyHandler onNotify = nullptr;

    TabsCtrl2();
    ~TabsCtrl2() override;
    bool Create(HWND parent) override;

    void WndProc(WndEvent*) override;

    Size GetIdealSize() override;

    int InsertTab(int idx, const char* sv);
    int InsertTab(int idx, const WCHAR* ws);

    void RemoveTab(int idx);
    void RemoveAllTabs();

    void SetTabText(int idx, const char* sv);
    void SetTabText(int idx, const WCHAR* ws);

    void SetTooltip(int idx, const WCHAR*);
    const WCHAR* GetTooltip(int idx);

    WCHAR* GetTabText(int idx);

    int GetSelectedTabIndex();
    int SetSelectedTabByIndex(int idx);

    void SetItemSize(Size sz);
    int GetTabCount();

    void SetToolTipsHwnd(HWND);
    HWND GetToolTipsHwnd();

    void MaybeUpdateTooltip();
    void MaybeUpdateTooltipText(int idx);
};
