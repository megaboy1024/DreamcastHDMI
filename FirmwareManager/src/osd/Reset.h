#include "../global.h"
#include "../Menu.h"

void writeCurrentResetMode();

Menu resetMenu("ResetMenu", (uint8_t*) OSD_RESET_MENU, MENU_RST_FIRST_SELECT_LINE, MENU_RST_LAST_SELECT_LINE, [](uint16_t controller_data, uint8_t menu_activeLine, bool isRepeat) {
    if (!isRepeat && CHECK_MASK(controller_data, CTRLR_BUTTON_B)) {
        currentMenu = &mainMenu;
        currentMenu->Display();
        return;
    }
    if (!isRepeat && CHECK_MASK(controller_data, CTRLR_BUTTON_A)) {
        switch (menu_activeLine) {
            case MENU_RST_LED_LINE:
                CurrentResetMode = RESET_MODE_LED;
                break;
            case MENU_RST_GDEMU_LINE:
                CurrentResetMode = RESET_MODE_GDEMU;
                break;
            case MENU_RST_USB_GDROM_LINE:
                CurrentResetMode = RESET_MODE_USBGDROM;
                break;
        }

        writeCurrentResetMode();
        fpgaTask.Write(I2C_RESET_CONF, CurrentResetMode, [](uint8_t Address, uint8_t Value) {
            currentMenu->Display();
        });
        return;
    }
}, [](uint8_t* menu_text, uint8_t menu_activeLine) {
    // restore original menu text
    for (int i = MENU_RST_FIRST_SELECT_LINE ; i <= MENU_RST_LAST_SELECT_LINE ; i++) {
        menu_text[i * MENU_WIDTH] = '-';
    }
    uint8_t line = (MENU_RST_FIRST_SELECT_LINE + CurrentResetMode);
    menu_text[line * MENU_WIDTH] = '>';
    return line;
}, NULL, true);

