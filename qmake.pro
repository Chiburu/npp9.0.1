# ターゲット名
win32:TARGET = npp090001_v
# Windows の場合はメジャーバージョンが追加される
#  npp090001_v1.dll
unix:TARGET = npp090001
# Linux の場合は既定の4ファイルが作成される
#  npp090001.so.1.0.0
#  npp090001.so.1.0
#  npp090001.so.1
#  npp090001.so

# Makefile 生成用テンプレートの指定
TEMPLATE = lib

# Qtモジュールのカスタマイズ(coreのみにする)
QT -= gui

# 各種プロジェクト設定とコンパイラオプション
CONFIG += c++17
# C++17 サポートを有効にする。

# ソースコードのエンコードをUTF-8に設定する
win32: QMAKE_CXXFLAGS += /utf-8
# 自動検出ではBOM付きでないと判断できないため、明示的に指定する

# Qt非推奨関数を無効化するバージョン(5.14以降を推奨)
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x050E00

# ソースコード上の NPP090001_EXPORT マクロをエクスポート扱いにする。
DEFINES += NPP090001_LIBRARY
# NPP090001_LIBRARY が事前定義されていないとインポート扱いになる。

# バージョン
win32:VERSION = 1.0.0.0
unix:VERSION = 1.0.0

# ライブラリ用バージョンパート
PARSED_VER = $$split(VERSION, ".")
VER_MAJ = $$member(PARSED_VER, 0)
VER_MIN = $$member(PARSED_VER, 1)
VER_PAT = $$member(PARSED_VER, 2)

# 製品情報(Windowsのみ)
QMAKE_TARGET_PRODUCT = Notes C++ Library for 9.0.1
QMAKE_TARGET_DESCRIPTION = Notes C API 9.0.1 ライブラリの C++ 拡張
QMAKE_TARGET_COMPANY = チブル・システムズ
QMAKE_TARGET_COPYRIGHT = Copyright (C) 2024 Chiburu Systems

# 環境依存定義
include(./local.pri)

# Notes C API
include(./notesapi.pri)

# ヘッダーファイル
HEADERS += \
  include/npp9.0.1/addin.h \
  include/npp9.0.1/npp_global.h

# ソースファイル
SOURCES += \
  src/addin.cpp
