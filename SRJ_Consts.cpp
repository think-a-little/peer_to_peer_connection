#include <cstdint>



const uint8_t INFORMATION_MESSAGE = 0x30;
const uint8_t WARNING_MESSAGE = 0x31;
const uint8_t START_PROCESS_MESSAGE = 0x32;
const uint8_t PROCESS_FINISH_MESSAGE = 0x33;
const uint8_t STOP_STATION_MESSAGE = 0x34;
const uint8_t START_STATION_MESSAGE = 0x35;

bool check_message_type1(uint8_t x) {
    if (x!= INFORMATION_MESSAGE &&
        x!= WARNING_MESSAGE &&
        x!= START_PROCESS_MESSAGE &&
        x!= PROCESS_FINISH_MESSAGE &&
        x!= STOP_STATION_MESSAGE &&
        x!= START_STATION_MESSAGE) {
        return false;
    }
    return true;
}
const uint8_t APCS = 0x30; // АСУ ТП
const uint8_t SCS = 0x31; // СКС
const uint8_t SYSTEM_MEASUREMENT_MOVEMENT = 0x34;
const uint8_t SYSTEM_OF_STABILIZATION = 0x35;
const uint8_t LBORDER_SYSTEM_TENZOMETRIA = 0x41;
const uint8_t RBORDER_SYSTEM_TENZOMETRIA = 0x5A;
const uint8_t LBORDER_SUBSYSTEM_DIST_VIS_WATCH = 0x61;
const uint8_t RBORDER_SUBSYSTEM_DIST_VIS_WATCH = 0x6F;
const uint8_t LBORDER_SUBSYSTEM_REGISTER_CRACK = 0x70;
const uint8_t RBORDER_SUBSYSTEM_REGISTER_CRACK = 0x7A;
const uint8_t LBORDER_ACUSTIC_SYSTEM = 0x21;
const uint8_t RBORDER_ACUSTIC_SYSTEM = 0x2F;

bool check_source(uint8_t x) {
    if (x!= APCS &&
        x!= SCS &&
        x!= SYSTEM_MEASUREMENT_MOVEMENT &&
        x!= SYSTEM_OF_STABILIZATION &&
        (x < LBORDER_SYSTEM_TENZOMETRIA || x > RBORDER_SYSTEM_TENZOMETRIA) &&
        (x < LBORDER_SUBSYSTEM_DIST_VIS_WATCH || x > RBORDER_SUBSYSTEM_DIST_VIS_WATCH) &&
        (x < LBORDER_SUBSYSTEM_REGISTER_CRACK || x > RBORDER_SUBSYSTEM_REGISTER_CRACK) &&
        (x < LBORDER_ACUSTIC_SYSTEM || x > RBORDER_ACUSTIC_SYSTEM)) {
        return false;
    }
    return true;
}
