#include <time.h>
#include <errno.h>
#include "daapd.h"
#include "err.h"

static int rend_initialized = 0;

int rend_init(char *user) {
    DPRINTF(E_LOG, L_REND, "Rendezvous disabled (no mDNS)\n");
    rend_initialized = 1;
    return 0;
}

int rend_running(void) {
    return rend_initialized;
}

int rend_stop(void) {
    rend_initialized = 0;
    DPRINTF(E_DBG, L_REND, "Rendezvous stopped\n");
    return 0;
}

int rend_register(char *name, char *type, int port) {
    DPRINTF(E_DBG, L_REND, "Would register %s/%s on port %d (disabled)\n",
            name, type, port);
    return 0;
}

int rend_unregister(char *name, char *type, int port) {
    return 0;
}
