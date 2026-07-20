FROM debian:bullseye-slim AS builder

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential autoconf automake libtool pkg-config \
    autotools-dev wget ca-certificates \
    libssl-dev libgcrypt20-dev \
    libsqlite3-dev zlib1g-dev \
    libid3tag0-dev libogg-dev libvorbis-dev \
    libtag1-dev libflac-dev libgdbm-dev \
    && rm -rf /var/lib/apt/lists/*

RUN wget -O /tmp/mt-daapd-0.2.4.1.tar.gz \
    "https://sourceforge.net/projects/mt-daapd/files/mt-daapd/0.2.4.1/mt-daapd-0.2.4.1.tar.gz/download" \
    && tar xzf /tmp/mt-daapd-0.2.4.1.tar.gz -C /tmp

WORKDIR /tmp/mt-daapd-0.2.4.1

RUN cp /usr/share/misc/config.sub /tmp/mt-daapd-0.2.4.1/config.sub \
    && cp /usr/share/misc/config.guess /tmp/mt-daapd-0.2.4.1/config.guess

COPY patches/rend-stub.c /tmp/mt-daapd-0.2.4.1/src/rend-posix.c

RUN CFLAGS="-O2 -pipe -fcommon" CXXFLAGS="-O2 -pipe -fcommon" \
    ./configure \
        --prefix=/usr \
        --sysconfdir=/etc \
        --localstatedir=/var \
        --enable-sqlite3 \
        --enable-oggvorbis \
        --enable-flac \
        --enable-taglib \
        --disable-avahi \
        --disable-howl

RUN cd src \
    && make -j"$(nproc)" -k 2>&1 || true \
    && gcc -O2 -pipe -fcommon \
        -o mt-daapd \
        main.o uici.o webserver.o configfile.o err.o restart.o \
        daap-proto.o daap.o db-gdbm.o mp3-scanner.o playlist.o \
        lexer.o parser.o strcasestr.o strsep.o redblack.o \
        dynamic-art.o query.o ogg.o rend-unix.o rend-posix.o \
        -lpthread -lgdbm \
        -lid3tag -lz -logg -lvorbis \
    && mkdir -p /tmp/mt-daapd-install/usr/sbin /tmp/mt-daapd-install/usr/share/mt-daapd \
    && cp mt-daapd /tmp/mt-daapd-install/usr/sbin/ \
    && cp /tmp/mt-daapd-0.2.4.1/admin-root/*.html /tmp/mt-daapd-install/usr/share/mt-daapd/

FROM debian:bullseye-slim

RUN apt-get update && apt-get install -y --no-install-recommends \
    libgcrypt20 libsqlite3-0 zlib1g \
    libid3tag0 libogg0 libvorbis0a libvorbisfile3 \
    libtag1v5 libflac8 \
    libgdbm6 \
    python3 python3-zeroconf \
    && rm -rf /var/lib/apt/lists/*

COPY --from=builder /tmp/mt-daapd-install/usr/sbin/mt-daapd /usr/sbin/mt-daapd
COPY --from=builder /tmp/mt-daapd-install/usr/share/mt-daapd/ /usr/share/mt-daapd/

RUN mkdir -p /var/cache/mt-daapd /var/run/mt-daapd

COPY mt-daapd.conf /etc/mt-daapd/mt-daapd.conf
COPY mdns-publish.py /mdns-publish.py

RUN useradd -r -s /bin/false -M mt-daapd \
    && chown -R mt-daapd:mt-daapd /var/cache/mt-daapd /var/run/mt-daapd /etc/mt-daapd

EXPOSE 3689

COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

ENTRYPOINT ["/entrypoint.sh"]
