#!/usr/bin/env python3
import socket
import time
import logging
from zeroconf import Zeroconf, ServiceInfo

logging.basicConfig(level=logging.INFO, format="mdns: %(message)s")
log = logging.getLogger()

IP = "192.168.100.26"
HOST = "retro-music.local."
MACHINE_ID = "beddab1edeadbea7"

INFO = ServiceInfo(
    "_daap._tcp.local.",
    "nrt1-mt-daapd._daap._tcp.local.",
    address=socket.inet_aton(IP),
    port=3689,
    properties={
        "txtvers": "1",
        "iTSh Version": "131073",
        "Machine ID": MACHINE_ID,
        "Password": "0",
    },
    server=HOST,
)

def run():
    zconf = Zeroconf(interfaces=[IP])
    try:
        zconf.register_service(INFO)
        log.info(f"published on {IP}:3689 as {HOST}")
        while True:
            time.sleep(15)
    finally:
        zconf.unregister_service(INFO)
        zconf.close()

if __name__ == "__main__":
    log.info(f"starting on {IP}")
    while True:
        try:
            run()
        except Exception as e:
            log.error(f"crashed: {e}")
        time.sleep(3)
