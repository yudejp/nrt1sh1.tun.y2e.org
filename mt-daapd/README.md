# mt-daapd (Firefly Media Server) - 古い Mac OS X 向け共有音楽ライブラリ

## 概要

Docker Compose で mt-daapd (Firefly Media Server) を動かし、
**Tiger / Leopard / Snow Leopard** 時代の Mac OS X 上の iTunes に
共有音楽ライブラリ (Shared Music Library / DAAP) を提供します。

## 必要条件

- Docker Engine 20.10+ および Docker Compose v2
- `network_mode: host` を使用するため Linux ホストが必須（macOS/Windows Docker Desktop では mDNS が機能しません）
- ホストネットワークを使用するため、ポート 3689 が空いていること

## 使い方

### 1. 音楽ファイルを配置

```
mkdir -p music
# music/ ディレクトリに .mp3 / .m4a / .wav / .flac などを置く
```

### 2. 起動

```
docker compose up -d
```

初回起動時に mt-daapd がソースコードからビルドされます。

### 3. iTunes 側で接続

1. Mac が同一ネットワーク（同一サブネット）にいることを確認
2. iTunes を開く
3. 左サイドバーの「共有」(Shared) セクションに **Retro Music Library** が表示される
4. クリックして接続（パスワードは不要）

**注意**: 同じネットワーク上にいないと Bonjour/mDNS による自動検出ができません。
その場合は iTunes の「詳細設定」→「共有ライブラリを探す」などから直接接続を試みてください。

## 設定

`mt-daapd.conf` で以下を変更できます:

| 項目 | 説明 |
|------|------|
| `servername` | iTunes に表示されるライブラリ名 |
| `password` | アクセスパスワード（空欄でなし） |
| `mp3_dir` | 音楽ファイルのディレクトリ（デフォルト: /music） |

## 古い iTunes との互換性について

### 対応バージョン

- **iTunes 4.0 以降** (Mac OS X 10.3 Panther 〜 10.6 Snow Leopard)
- DAAP プロトコル v2.0 / v3.0

### 注意点

- **文字コード**: mt-daapd.conf で `filename_encoding` や `playlist_encoding` を
  Shift_JIS にする必要がある場合があります（日本語環境の古い Mac の場合）。
  デフォルトは UTF-8 です。
- **mDNS/Bonjour**: `network_mode: host` が必要です。
  Docker の NAT ネットワークではマルチキャスト DNS が正しく動作しません。
- **iTunes のバージョンが古すぎる場合**: 手動で IP アドレスとポートを指定して
  接続する必要があるかもしれません。
