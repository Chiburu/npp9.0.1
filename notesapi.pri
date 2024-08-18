#
# Notes C API 用プロジェクトインクルード
#
# このファイルをプロジェクトにインクルードする前に
# NotesCApiPath 変数で Notes C API のルートパスを指定しておく。
# Linux では NotesExecPath に Domino の実行ディレクトリも指定する必要がある。
#

# Notes C API ヘッダーファイルをインクルード先に指定する。
INCLUDEPATH += $$NotesCApiPath/include

# インポートライブラリnotes.lib/共有オブジェクトnotes.soを指定する。
LIBS += -lnotes

# 事前定義マクロ/リンクパスの指定
unix {
  DEFINES += UNIX LINUX LINUX64 ND64
  LIBS += -L$$NotesExecPath -Wl,-rpath,$$NotesExecPath
} else:contains(QMAKE_TARGET.arch, x86_64) {
  DEFINES += W32 W64
  LIBS += -L$$NotesCApiPath/lib/mswin64
} else {
  DEFINES += W32
  LIBS += -L$$NotesCApiPath/lib/mswin32
}
