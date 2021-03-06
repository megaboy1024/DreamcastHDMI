#ifndef MENU_H
#define MENU_H

#include <inttypes.h>
#include <functional>
#include "global.h"
#include "task/FPGATask.h"

#define MENU_OFFSET 9
#define MENU_WIDTH 40

#define NO_SELECT_LINE 32
#define MENU_START_LINE "          A: Start    B: Back           "
#define MENU_BACK_LINE  "                B: Back                 "
#define MENU_BUTTON_LINE 12

#define MENU_RST_GDEMU_BUTTON_LINE  "     X: Reset DC  Y: GDEMU button       "
#define MENU_RST_NORMAL_BUTTON_LINE "              X: Reset DC               "

#define MENU_M_OR 2
#define MENU_M_SL 3
#define MENU_M_VM 4
#define MENU_M_FW 5
//#define MENU_M_INF 6
#define MENU_M_WIFI 6
#define MENU_M_RST 7
#define MENU_M_FIRST_SELECT_LINE 2
#define MENU_M_LAST_SELECT_LINE 7
char OSD_MAIN_MENU[521] = (
    "Main Menu                               "
    "                                        "
    "- Output Resolution                     "
    "- Scanlines                             "
    "- Video Mode Settings                   "
    "- Firmware Upgrade                      "
    "- WiFi Setup                            "
    "- Reset Options                         "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "          A: Select  B: Exit            "
);

#define MENU_OR_LAST_SELECT_LINE 5
#define MENU_OR_FIRST_SELECT_LINE (MENU_OR_LAST_SELECT_LINE-3)
char OSD_OUTPUT_RES_MENU[521] = (
    "Output Resolution                       "
    "                                        "
    "- VGA                                   "
    "- 480p                                  "
    "- 960p                                  "
    "- 1080p                                 "
    "                                        "
    "  '>' marks the stored setting          "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "          A: Apply   B: Back            "
);

#define MENU_SS_RESULT_LINE 4
char OSD_OUTPUT_RES_SAVE_MENU[521] = (
    "Output Resolution                       "
    "                                        "
    "         Keep this resolution?          "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "          A: Keep  B: Revert            "
);

#define MENU_VM_FORCE_VGA_LINE 2
#define MENU_VM_CABLE_DETECT_LINE 3
#define MENU_VM_SWITCH_TRICK_LINE 4
#define MENU_VM_FIRST_SELECT_LINE 2
#define MENU_VM_LAST_SELECT_LINE 4
char OSD_VIDEO_MODE_MENU[521] = (
    "Video Mode Settings                     "
    "                                        "
    "- Force VGA                             "
    "- Cable Detect                          "
    "- Switch Trick VGA                      "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "          A: Save  B: Cancel            "
);

char OSD_VIDEO_MODE_SAVE_MENU[521] = (
    "Video Mode Settings                     "
    "                                        "
    "    Apply changes and reset console?    "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "         A: Reset  B: Not now           "
);

char OSD_DC_RESET_CONFIRM_MENU[521] = (
    "Reset Dreamcast                         "
    "                                        "
    "      Do you really want to reset       "
    "          the dreamcast now?            "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "         A: Reset  B: Not now           "
);

char OSD_OPT_RESET_CONFIRM_MENU[521] = (
    "GDEMU button                            "
    "                                        "
    "      Do you really want to press       "
    "          the GDEMU button?             "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "         A: Press  B: Not now           "
);

#define MENU_FW_CHECK_LINE 2
#define MENU_FW_DOWNLOAD_LINE 3
#define MENU_FW_FLASH_LINE 4
#define MENU_FW_RESET_LINE 5
#define MENU_FW_FIRST_SELECT_LINE 2
#define MENU_FW_LAST_SELECT_LINE 5
char OSD_FIRMWARE_MENU[521] = (
    "Firmware                                "
    "                                        "
    "- Check                                 "
    "- Download                              "
    "- Flash                                 "
    "- Restart                               "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "          A: Select  B: Exit            "
);

#define MENU_FWC_FPGA_LINE 4
#define MENU_FWC_ESP_LINE 5
#define MENU_FWC_INDEXHTML_LINE 6
#define MENU_FWC_RESULT_LINE 8
char OSD_FIRMWARE_CHECK_MENU[521] = (
    "Check Firmware                          "
    "                                        "
    "Check, if newer firmware is available.  "
    "                                        "
    "FPGA        ________  ________          "
    "ESP         ________  ________          "
    "index.html  ________  ________          "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    MENU_START_LINE
);

#define MENU_FWD_FPGA_LINE 4
#define MENU_FWD_ESP_LINE 5
#define MENU_FWD_INDEXHTML_LINE 6
#define MENU_FWD_RESULT_LINE 8
char OSD_FIRMWARE_DOWNLOAD_MENU[521] = (
    "Download Firmware                       "
    "                                        "
    "Download firmware files.                "
    "                                        "
    "FPGA        [                    ]      "
    "ESP         [                    ]      "
    "index.html  [                    ]      "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    MENU_START_LINE
);

#define MENU_FWF_FPGA_LINE 4
#define MENU_FWF_ESP_LINE 5
#define MENU_FWF_INDEXHTML_LINE 6
#define MENU_FWF_RESULT_LINE 8
char OSD_FIRMWARE_FLASH_MENU[521] = (
    "Flash Firmware                          "
    "                                        "
    "Flash downloaded firmware files.        "
    "                                        "
    "FPGA        [                    ]      "
    "ESP         [                    ]      "
    "index.html  [                    ]      "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    MENU_START_LINE
);

char OSD_FIRMWARE_RESET_MENU[521] = (
    "Restart Firmware                        "
    "                                        "
    "           Restart DCHDMI?              "
    "   This will also reset the dreamcast!  "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "          A: Ok    B: Cancel            "
);

#define MENU_SL_ACTIVE 2
#define MENU_SL_INTENSITY 3
#define MENU_SL_ODDEVEN 4
#define MENU_SL_THICKNESS 5
#define MENU_SL_FIRST_SELECT_LINE 2
#define MENU_SL_LAST_SELECT_LINE 5
char OSD_SCANLINES_MENU[521] = (
    "Scanlines                               "
    "                                        "
    "- On/Off:    _____                      "
    "- Intensity: _____                      "
    "- Odd/Even:  _____                      "
    "- Thickness: _____                      "
    "                                        "
    "  left/right (d-pad): change value.     "
    "  A: save settings and exit.            "
    "  B: discard changes and exit.          "
    "                                        "
    "                                        "
    "          A: Save  B: Cancel            "
);

#define MENU_INF_RESULT_LINE 2
#define MENU_INF_RESULT_HEIGHT 9
char OSD_INFO_MENU[521] = (
    "Debug Info                              "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                B: Back                 "
);

#define MENU_RST_LED_LINE 2
#define MENU_RST_GDEMU_LINE 3
#define MENU_RST_USB_GDROM_LINE 4
#define MENU_RST_FIRST_SELECT_LINE 2
#define MENU_RST_LAST_SELECT_LINE 4
char OSD_RESET_MENU[521] = (
    "Reset Options                           "
    "                                        "
    "- LED                                   "
    "- GDEMU                                 "
    "- USB-GDROM                             "
    "                                        "
    "  '>' marks the stored setting          "
    "                                        "
    "LED:       OPT -> not connected         "
    "GDEMU:     OPT -> GDEMU button          "
    "USB-GDROM: OPT -> USB-GDROM reset       "
    "                                        "
    "          A: Apply   B: Back            "
);

#define MENU_WIFI_SSID_LINE 2
#define MENU_WIFI_PASSWORD_LINE 3
#define MENU_WIFI_RESTART_LINE 4
#define MENU_WIFI_FIRST_SELECT_LINE 2
#define MENU_WIFI_LAST_SELECT_LINE 4
char OSD_WIFI_MENU[521] = (
    "WiFi Setup                              "
    "                                        "
    "- SSID:     ___________________________ "
    "- Password: ___________________________ "
    "- Restart to apply changes              "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "          A: Select  B: Back            "
);

#define MENU_WIFI_EDIT_NAME_LINE 2
#define MENU_WIFI_EDIT_VALUE_LINE 3
#define MENU_WIFI_EDIT_CURSOR_LINE 4
char OSD_WIFI_EDIT_MENU[521] = (
    "WiFi Setup Edit                         "
    "                                        "
    " ______________________________________ "
    "\x10______________________________________\x11"
    "                                        "
    "                                        "
    "- D-pad left/right to move cursor       "
    "- D-pad up/down to cylce thru chars     "
    "- Trailing whitespace is removed on save"
    "                                        "
    "                                        "
    "                                        "
    "          A: Save  B: Cancel            "
);

typedef std::function<void(uint16_t controller_data, uint8_t menu_activeLine, bool isRepeat)> ClickHandler;
typedef std::function<uint8_t(uint8_t* menu_text, uint8_t menu_activeLine)> PreDisplayHook;

extern FPGATask fpgaTask;
bool OSDOpen = false;

class Menu
{
  public:
    Menu(const char* name, uint8_t* menu, uint8_t first_line, uint8_t last_line, ClickHandler handler, PreDisplayHook pre_hook, WriteCallbackHandlerFunction display_callback, bool autoUpDown) :
        name(name),
        menu_text(menu),
        first_line(first_line),
        last_line(last_line),
        handler(handler),
        pre_hook(pre_hook),
        display_callback(display_callback),
        menu_activeLine(first_line),
        inTransaction(false),
        autoUpDown(autoUpDown)
    { };

    const char* Name() {
        return name;
    }

    void startTransaction() {
        inTransaction = true;
    }

    void endTransaction() {
        inTransaction = false;
    }

    void StoreMenuActiveLine(uint8_t line) {
        menu_activeLine = line;
    }

    void Display() {
        if (pre_hook != NULL) {
            menu_activeLine = pre_hook(menu_text, menu_activeLine);
        }
        fpgaTask.DoWriteToOSD(0, 9, menu_text, [&]() {
            //DBG_OUTPUT_PORT.printf("%i %i\n", menu_activeLine, MENU_OFFSET + menu_activeLine);
            fpgaTask.Write(I2C_OSD_ACTIVE_LINE, MENU_OFFSET + menu_activeLine, display_callback);
        });
    }

    void HandleClick(uint16_t controller_data, bool isRepeat) {
        if (inTransaction) {
            DBG_OUTPUT_PORT.printf("%s in transaction!\n", name);
            return;
        }

        if (autoUpDown) {
            // pad up down is handled by menu
            if (CHECK_MASK(controller_data, CTRLR_PAD_UP)) {
                menu_activeLine = menu_activeLine <= first_line ? first_line : menu_activeLine - 1;
                fpgaTask.Write(I2C_OSD_ACTIVE_LINE, MENU_OFFSET + menu_activeLine);
                return;
            }
            if (CHECK_MASK(controller_data, CTRLR_PAD_DOWN)) {
                menu_activeLine = menu_activeLine >= last_line ? last_line : menu_activeLine + 1;
                fpgaTask.Write(I2C_OSD_ACTIVE_LINE, MENU_OFFSET + menu_activeLine);
                return;
            }
        }
        // pass all other pads to handler
        handler(controller_data, menu_activeLine, isRepeat);
    }

    uint8_t* GetMenuText() {
        return menu_text;
    }

private:
    const char* name;
    uint8_t* menu_text;
    uint8_t first_line;
    uint8_t last_line;
    ClickHandler handler;
    PreDisplayHook pre_hook;
    WriteCallbackHandlerFunction display_callback;
    uint8_t menu_activeLine;
    bool inTransaction;
    bool autoUpDown;
};

void displayProgress(int read, int total, int line) {
    // download size may be yet unknown
    if (total <= 0) {
        return;
    }

    int stars = (int)(read * 20 / total);
    int blanks = 20 - stars;
    int percent = (int)(read * 100 / total);
    char result[32];

    if (blanks > 0) {
        snprintf(result, 32, "[%.*s%*c] %3d%% ", stars, "********************", blanks, ' ', percent);
    } else {
        snprintf(result, 32, "[%.*s] %3d%% ", stars, "********************", percent);
    }
    fpgaTask.DoWriteToOSD(12, MENU_OFFSET + line, (uint8_t*) result);
}

#include "osd/Main.h"
#include "osd/OutputResolution.h"
#include "osd/VideoMode.h"
#include "osd/Firmware.h"
#include "osd/FirmwareCheck.h"
#include "osd/FirmwareDownload.h"
#include "osd/FirmwareFlash.h"
#include "osd/FirmwareReset.h"
#include "osd/Scanlines.h"
//#include "osd/Info.h"
#include "osd/Reset.h"
#include "osd/Wifi.h"

void setOSD(bool value, WriteCallbackHandlerFunction handler) {
    OSDOpen = value;
    fpgaTask.Write(I2C_OSD_ENABLE, value, handler);
}

void openOSD() {
    currentMenu = &mainMenu;
    setOSD(true, [](uint8_t Address, uint8_t Value) {
        currentMenu->Display();
    });
}

void closeOSD() {
    setOSD(false, NULL);
}

FPGATask fpgaTask(1, [](uint16_t controller_data, bool isRepeat) {
    if (!isRepeat) {
        if (!OSDOpen && CHECK_BIT(controller_data, CTRLR_TRIGGER_OSD)) {
            openOSD();
            return;
        }
        if (CHECK_BIT(controller_data, CTRLR_TRIGGER_DEFAULT_RESOLUTION)) {
            switchResolution(RESOLUTION_VGA);
            return;
        }
    }
    if (OSDOpen) {
        //DBG_OUTPUT_PORT.printf("Menu: %s %x\n", currentMenu->Name(), controller_data);
        currentMenu->HandleClick(controller_data, isRepeat);
    }
});

#endif
