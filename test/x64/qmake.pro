# ターゲット名
TARGET = nppx64test

# Makefile 生成用テンプレートの指定
TEMPLATE = app

# Qtモジュールのカスタマイズ(coreのみにする)
QT -= gui

# 各種プロジェクト設定とコンパイラオプション
CONFIG += c++17 cmdline
# C++17 サポートを有効にする。
# コマンドラインアプリを生成

# ソースコードのエンコードをUTF-8に設定する
win32: QMAKE_CXXFLAGS += /utf-8
# 自動検出ではBOM付きでないと判断できないため、明示的に指定する

# Qt非推奨関数を無効化するバージョン(5.14以降を推奨)
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x050E00

# バージョン
VERSION = 1.0.0.0

# 製品情報(Windowsのみ)
QMAKE_TARGET_PRODUCT = npp9.0.1 x64 テスト
QMAKE_TARGET_DESCRIPTION = npp9.0.1 x64 ユニットテスト
QMAKE_TARGET_COMPANY = チブル・システムズ
QMAKE_TARGET_COPYRIGHT = Copyright (C) 2024 Chiburu Systems

# 環境依存定義
include(../../local.pri)

# Notes C API
include(../../notesapi.pri)

# ヘッダーファイル

# ソースファイル
SOURCES += \
  src/main.cpp

# npp9.0.1 リンク
INCLUDEPATH += ../../include
LIBS += notes0.obj notesai0.obj -llegacy_stdio_definitions -luser32 -lnpp090001_v1 -L../../../build/msvc2019_64-Qt5.15.2-debug/debug
