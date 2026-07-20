#include <time.h>
#include "daapd.h"
#include "err.h"
#include "rend.h"
#include "rend-unix.h"

int rend_private_init(char *user) {
    REND_MESSAGE msg;
    DPRINTF(E_LOG, L_REND, "mDNS disabled, using Python zeroconf\n");
    while (1) {
        rend_read_message(&msg);
        switch(msg.cmd) {
        case REND_MSG_TYPE_REGISTER:
        case REND_MSG_TYPE_UNREGISTER:
        case REND_MSG_TYPE_STATUS:
            rend_send_response(0);
            break;
        case REND_MSG_TYPE_STOP:
            rend_send_response(0);
            exit(0);
        }
    }
}
