#include "srj_consts.h"

bool SRJ_Consts:: check_message_type1(uint8_t x) {
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
bool SRJ_Consts:: check_source1(uint8_t x) {
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
