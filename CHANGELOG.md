# Change logs for npp9.0.1

## 0.0.5-2024.09.15

- `every<T>` を定義
- `some<T>` を定義
  - modified: include\npp9.0.1\utils.h

## 0.0.4-2024.09.14

- `*.bak` を追跡対象外にする。
- `*.org` を追跡対象外にする。
  - modified: .gitignore
- `arch` 値を、 `PRODUCT` 経由から引数経由に変更
- `mode` 値を、 `PRODUCT` 経由から引数経由に変更
  - modified: installer/gulpfile.js
  - modified: installer/product.js
- `minimist` をインストール
- `build:x64:debug` スクリプトを追加
- `build:x64:release` スクリプトを追加
- `build:x86:debug` スクリプトを追加
- `build:x86:release` スクリプトを追加
  - modified: installer/package.json

## 0.0.4-2024.08.26

- installer/presets を追跡対象外にする。
  - modified: .gitignore
- ターゲット名(win32) のデバッグ版に `d` を付加する。
  - modified: qmake.pro
  - modified: test/x64/qmake.pro
  - modified: test/x86/qmake.pro
- gulp スクリプトを accessview2025 ベースで構築したもので置き換える。
  - modified: installer/gulpfile.js
  - new file: installer/product.js

## 0.0.3-2024.08.19-Linux

- `build.sh` を追跡対象外に追加
  - modified: .gitignore
- 余分な名前空間指定を削除
  - modified: include/npp9.0.1/hook.h

## 0.0.2-2024.08.18

- Windows で表示されるコンパイル警告を無視するパラメータを追加
  - modified: notesapi.pri
- ライブラリエクスポートを証明するマクロ名を修正
  - modified: qmake.pro
- npp2025 から定義を移植
  - new file: include/npp9.0.1/env.h
  - new file: include/npp9.0.1/fs.h
  - new file: include/npp9.0.1/hook.h
  - new file: include/npp9.0.1/os.h
  - new file: include/npp9.0.1/path.h
  - new file: include/npp9.0.1/status.h
  - new file: include/npp9.0.1/utils.h
  - new file: src/env.cpp
  - new file: src/fs.cpp
  - new file: src/hook.cpp
  - new file: src/os.cpp
  - new file: src/path.cpp
  - new file: src/status.cpp

## 0.0.1-2024.08.18

- .vscode ディレクトリを追跡対象外にする。
- 各 build ディレクトリを追跡対象外にする。
- local.pri ファイルを追跡対象外にする。
- test/x64/local.ini ファイルを追跡対象外にする(x64 テスト用バッチファイルの環境設定)。
- installer/node_modules ディレクトリを追跡対象外にする。
- installer/package-lock.json ファイルを追跡対象外にする。
- installer/work ディレクトリを追跡対象外にする(インストーラ作成用作業ディレクトリ)。
- installer/local.js ファイルを追跡対象外にする(インストーラ作成用の環境設定)。
  - new file: .gitignore
- Notes C API リンク設定
  - new file: notesapi.pri
- ライブラリ構築用 qmake 設定
  - new file: qmake.pro
- `addin::logMessageText<...Args>(const QByteArray&, STATUS, Args...)` を定義
- `addin::logMessageText(const QByteArray&)` を定義
  - new file: include/npp9.0.1/addin.h
  - new file: src/addin.cpp
- マクロ `NPP_EXPORT` を定義
- マクロ `PUSH_PACK1` を定義
- マクロ `POP_PACK` を定義
  - new file: include/npp9.0.1/npp_global.h
- `removeWorkDir` を定義
- `makeDir` を定義
- `buildXml` を定義
- `writeXml` を定義
- `copyFile` を定義
- `execute` を定義
- `buildConfigXml` を定義
- `buildNppPackage` を定義
- `buildPackages` を定義
- `buildInstaller` を定義
- `main` を定義
  - new file: installer/gulpfile.js
- `scripts.start` を定義
- `scripts.dependencies.date-fns` を追加
- `scripts.dependencies.gulp` を追加
- `scripts.dependencies.rxjs` を追加
- `scripts.dependencies.xmlbuilder2` を追加
  - new file: installer/package.json
- 64 ビット系ユニットテストを定義
  - new file: test/x64/qmake.pro
  - new file: test/x64/run.bat
  - new file: test/x64/src/main.cpp
- 32 ビット系ユニットテストを定義
  - new file: test/x86/qmake.pro
  - new file: test/x86/src/main.cpp

## 0.0.0-2024.08.11

- 次のコマンドを使って、環境を初期化

```sh
$ mkdir npp9.0.1
$ cd npp9.0.1
$ git init
$ git config user.name "Takahide Kondoh"
$ git config user.email tkondoh@chiburu.com
$ git branch -m main
$ touch README.md
$ touch CHANGELOG.md
```
