/* Copyright 2022 the SumatraPDF project authors (see AUTHORS file).
   License: Simplified BSD (see COPYING.BSD) */
#include "utils/BaseUtil.h"
#include "utils/WinUtil.h"

#include "Settings.h"
#include "GlobalPrefs.h"
#include "AppColors.h"
#include "Theme.h"

// For reference of what used to be:
// https://github.com/sumatrapdfreader/sumatrapdf/commit/74aca9e1b78f833b0886db5b050c96045c0071a0

#define COL_WHITE RGB(0xff, 0xff, 0xff)
#define COL_WHITEISH RGB(0xEB, 0xEB, 0xF9);
#define COL_BLACK RGB(0, 0, 0)
#define COL_BLUE_LINK RGB(0x00, 0x20, 0xa0)

// for tabs
#define COL_RED RGB(0xff, 0x00, 0x00)
#define COL_LIGHT_GRAY RGB(0xde, 0xde, 0xde)
#define COL_LIGHTER_GRAY RGB(0xee, 0xee, 0xee)
#define COL_DARK_GRAY RGB(0x42, 0x42, 0x42)

// "SumatraPDF yellow" similar to the one use for icon and installer
#define ABOUT_BG_LOGO_COLOR RGB(0xFF, 0xF2, 0x00)

// it's very light gray but not white so that there's contrast between
// background and thumbnail, which often have white background because
// most PDFs have white background
#define ABOUT_BG_GRAY_COLOR RGB(0xF2, 0xF2, 0xF2)

// for backward compatibility use a value that older versions will render as yellow
#define ABOUT_BG_COLOR_DEFAULT (RGB(0xff, 0xf2, 0) - 0x80000000)

// Background color comparison:
// Adobe Reader X   0x565656 without any frame border
// Foxit Reader 5   0x9C9C9C with a pronounced frame shadow
// PDF-XChange      0xACA899 with a 1px frame and a gradient shadow
// Google Chrome    0xCCCCCC with a symmetric gradient shadow
// Evince           0xD7D1CB with a pronounced frame shadow
#if defined(DRAW_PAGE_SHADOWS)
// SumatraPDF (old) 0xCCCCCC with a pronounced frame shadow
#define COL_WINDOW_BG RGB(0xCC, 0xCC, 0xCC)
#define COL_PAGE_FRAME RGB(0x88, 0x88, 0x88)
#define COL_PAGE_SHADOW RGB(0x40, 0x40, 0x40)
#else
// SumatraPDF       0x999999 without any frame border
#define COL_WINDOW_BG RGB(0x99, 0x99, 0x99)
#endif

// returns the background color for start page, About window and Properties dialog
static COLORREF GetAboutBgColor() {
    COLORREF bgColor = ABOUT_BG_GRAY_COLOR;

    ParsedColor* bgParsed = GetPrefsColor(gGlobalPrefs->mainWindowBackground);
    if (ABOUT_BG_COLOR_DEFAULT != bgParsed->col) {
        bgColor = bgParsed->col;
    }
    return bgColor;
}

// returns the background color for the "SumatraPDF" logo in start page and About window
static COLORREF GetLogoBgColor() {
#ifdef ABOUT_USE_LESS_COLORS
    return ABOUT_BG_LOGO_COLOR;
#else
    return GetAboutBgColor();
#endif
}

static COLORREF GetNoDocBgColor() {
    // use the system background color if the user has non-default
    // colors for text (not black-on-white) and also wants to use them

    COLORREF sysText = GetSysColor(COLOR_WINDOWTEXT);
    COLORREF sysWindow = GetSysColor(COLOR_WINDOW);
    bool useSysColor = gGlobalPrefs->useSysColors && (sysText != WIN_COL_BLACK || sysWindow != WIN_COL_WHITE);
    if (useSysColor) {
        return GetSysColor(COLOR_BTNFACE);
    }

    return GetAboutBgColor();
}

COLORREF GetAppColor(AppColor col) {
    if (col == AppColor::NoDocBg) {
        // GetCurrentTheme()->document.canvasColor
        return GetNoDocBgColor();
    }

    if (col == AppColor::AboutBg) {
        return GetAboutBgColor();
    }

    if (col == AppColor::LogoBg) {
        return GetLogoBgColor();
    }

    if (col == AppColor::MainWindowBg) {
        return GetAboutBgColor();
        // return ABOUT_BG_GRAY_COLOR;
    }

    if (col == AppColor::MainWindowText) {
        return COL_BLACK;
    }

    if (col == AppColor::MainWindowLink) {
        return COL_BLUE_LINK;
    }

    CrashIf(true);
    return COL_WINDOW_BG;
}
