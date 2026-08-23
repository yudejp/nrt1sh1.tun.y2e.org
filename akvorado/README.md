# Akvorado

NEC IX2215 から sFlow を受信して可視化するための最小構成です。

## 起動

```sh
docker compose up -d
```

## 接続先

- Web UI: http://<docker-host>:8081/
- sFlow 送信先: <docker-host>:6343/udp

## 構成メモ

- akvorado-inlet は bridge ネットワークで動かし、ホストの UDP 6343 を publish しています。
- IX2215 の sFlow を取り込むには、SNMP で interface metadata を引ける必要があります。初期値では SNMP community に public を使います。
- sampling rate が欠けるサンプル向けに default sampling rate を 2000 で補っています。IX 側の設定と違う場合は [config/outlet.yaml](config/outlet.yaml) を合わせてください。
- GeoIP と BMP は含めていません。