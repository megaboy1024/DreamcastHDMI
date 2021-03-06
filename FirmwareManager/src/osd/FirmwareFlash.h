#include "../global.h"
#include "../Menu.h"

extern FlashTask flashTask;
extern FlashESPTask flashESPTask;
extern FlashESPIndexTask flashESPIndexTask;

bool newFWFlashed;
bool firmwareFlashStarted;

void flashCascade(int pos, bool force);
void readStoredMD5SumFlash(int pos, bool force, const char* fname, char* md5sum);
void checkStoredMD5SumFlash(int pos, bool force, int line, const char* fname, char* storedMD5Sum);
ProgressCallback createFlashProgressCallback(int pos, bool force, int line);

Menu firmwareFlashMenu("FirmwareFlashMenu", (uint8_t*) OSD_FIRMWARE_FLASH_MENU, NO_SELECT_LINE, NO_SELECT_LINE, [](uint16_t controller_data, uint8_t menu_activeLine, bool isRepeat) {
    if (!isRepeat && CHECK_MASK(controller_data, CTRLR_BUTTON_B)) {
        currentMenu = &firmwareMenu;
        currentMenu->Display();
        return;
    }
    if (!isRepeat && CHECK_MASK(controller_data, CTRLR_BUTTON_A)) {
        if (!firmwareFlashStarted) {
            firmwareFlashStarted = true;
            newFWFlashed = false;
            flashCascade(0, false);
        }
        return;
    }
}, NULL, [](uint8_t Address, uint8_t Value) {
    firmwareFlashStarted = false;
}, true);

void flashCascade(int pos, bool force) {
    DBG_OUTPUT_PORT.printf("flashCascade: %i\n", pos);
    switch (pos) {
        case 0:
            currentMenu->startTransaction();
            flashCascade(pos + 1, force);
            break;
        case 1:
            fpgaTask.DoWriteToOSD(0, MENU_OFFSET + MENU_BUTTON_LINE, (uint8_t*) MENU_BACK_LINE, [ pos, force ]() {
                flashCascade(pos + 1, force);
            });
            break;
        /*
            FPGA
        */
        case 2: // Check for FPGA firmware version
            if (force) {
                flashCascade(pos + 2, force);
            } else {
                readStoredMD5SumFlash(pos, force, STAGED_FPGA_MD5, md5FPGA);
            }
            break;
        case 3:
            checkStoredMD5SumFlash(pos, force, MENU_FWF_FPGA_LINE, LOCAL_FPGA_MD5, md5FPGA);
            break;
        case 4: // Flash FPGA firmware
            flashTask.SetProgressCallback(createFlashProgressCallback(pos, force, MENU_FWF_FPGA_LINE));
            taskManager.StartTask(&flashTask);
            break;
        /*
            ESP
        */
        case 5: // Check for ESP firmware version
            flashTask.ClearProgressCallback();
            if (force) {
                flashCascade(pos + 2, force);
            } else {
                readStoredMD5SumFlash(pos, force, STAGED_ESP_MD5, md5ESP);
            }
            break;
        case 6:
            checkStoredMD5SumFlash(pos, force, MENU_FWF_ESP_LINE, LOCAL_ESP_MD5, md5ESP);
            break;
        case 7: // Flash ESP firmware
            flashESPTask.SetProgressCallback(createFlashProgressCallback(pos, force, MENU_FWF_ESP_LINE));
            taskManager.StartTask(&flashESPTask);
            break;
        /*
            ESP INDEX
        */
        case 8: // Check for ESP index.html version
            flashESPTask.ClearProgressCallback();
            if (force) {
                flashCascade(pos + 2, force);
            } else {
                readStoredMD5SumFlash(pos, force, STAGED_ESP_INDEX_MD5, md5IndexHtml);
            }
            break;
        case 9:
            checkStoredMD5SumFlash(pos, force, MENU_FWF_INDEXHTML_LINE, LOCAL_ESP_INDEX_MD5, md5IndexHtml);
            break;
        case 10: // Flash ESP index.html
            flashESPIndexTask.SetProgressCallback(createFlashProgressCallback(pos, force, MENU_FWF_INDEXHTML_LINE));
            taskManager.StartTask(&flashESPIndexTask);
            break;
        case 11:
            flashESPIndexTask.ClearProgressCallback();
            const char* result;
            if (newFWFlashed) {
                result = (
                    "     Firmware successfully flashed!     "
                    "         Please restart system!         "
                );
            } else {
                result = (
                    "    Firmware is already up to date!"
                );
            }
            fpgaTask.DoWriteToOSD(0, MENU_OFFSET + MENU_FWF_RESULT_LINE, (uint8_t*) result, [ pos, force ]() {
                flashCascade(pos + 1, force);
            });
            break;
        default:
            currentMenu->endTransaction();
            break;
    }
}

void readStoredMD5SumFlash(int pos, bool force, const char* fname, char* md5sum) {
    char value[9] = "";
    _readFile(fname, md5sum, 33, DEFAULT_MD5_SUM);
    fpgaTask.DoWriteToOSD(0, 0, (uint8_t*) value, [ pos, force ]() {
        flashCascade(pos + 1, force);
    });
}

void checkStoredMD5SumFlash(int pos, bool force, int line, const char* fname, char* storedMD5Sum) {
    char value[9] = "";
    char md5Sum[48] = "";
    _readFile(fname, md5Sum, 33, DEFAULT_MD5_SUM);

    DBG_OUTPUT_PORT.printf("[%s] [%s] %i\n", storedMD5Sum, md5Sum, strncmp(storedMD5Sum, md5Sum, 32));

    if (strncmp(storedMD5Sum, DEFAULT_MD5_SUM, 32) == 0) {
        fpgaTask.DoWriteToOSD(12, MENU_OFFSET + line, (uint8_t*) "No file to flash available. ", [ pos, force ]() {
            flashCascade(pos + 2, force);
        });
    } else if (strncmp(storedMD5Sum, md5Sum, 32) == 0) {
        fpgaTask.DoWriteToOSD(12, MENU_OFFSET + line, (uint8_t*) "File already flashed.       ", [ pos, force ]() {
            flashCascade(pos + 2, force);
        });
    } else {
        // new firmware file available
        fpgaTask.DoWriteToOSD(0, 0, (uint8_t*) value, [ pos, force ]() {
            flashCascade(pos + 1, force);
        });
    }
}

ProgressCallback createFlashProgressCallback(int pos, bool force, int line) {
    return [ pos, force, line ](int read, int total, bool done, int error) {
        if (error != NO_ERROR) {
            // TODO: handle error
            flashCascade(pos + 1, force);
            return;
        }

        if (done) {
            fpgaTask.DoWriteToOSD(12, MENU_OFFSET + line, (uint8_t*) "[********************] done.", [ pos, force ]() {
                // IMPORTANT: do only advance here, if done is true!!!!!
                newFWFlashed |= true;
                flashCascade(pos + 1, force);
            });
            return;
        }

        displayProgress(read, total, line);
    };
}
