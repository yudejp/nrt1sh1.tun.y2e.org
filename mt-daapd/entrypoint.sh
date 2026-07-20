#!/bin/sh

mkdir -p /var/cache/mt-daapd /var/log

python3 /mdns-publish.py &
/usr/sbin/mt-daapd -c /etc/mt-daapd/mt-daapd.conf -f
