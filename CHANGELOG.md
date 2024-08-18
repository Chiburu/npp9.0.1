# Change logs for npp9.0.1

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
