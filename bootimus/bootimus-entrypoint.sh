#!/bin/sh
set -eu

cat > /etc/resolv.conf <<'EOF'
nameserver 127.0.0.1
options ndots:0
EOF

/usr/local/bin/coredns -conf /etc/coredns/Corefile &

for _ in 1 2 3 4 5; do
    if grep -qi ':0035' /proc/net/udp /proc/net/udp6 2>/dev/null; then
        break
    fi
    sleep 0.2
done

DATA_DIR="${BOOTIMUS_DATA_DIR:-/data}"
SEED_SRC="/usr/share/bootimus/secureboot-official"
SEED_DST="$DATA_DIR/bootloaders/secureboot-official"

if [ -d "$SEED_SRC" ] && [ ! -d "$SEED_DST" ]; then
    mkdir -p "$DATA_DIR/bootloaders"
    cp -r "$SEED_SRC" "$SEED_DST"
    echo "Seeded Secure Boot bootloader set into $SEED_DST"
fi

exec /bootimus "$@"