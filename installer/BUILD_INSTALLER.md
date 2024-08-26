# インストーラを生成する

## ローカル環境依存の設定

installer パスに local.js ファイルを作成する。

```js
// 設定例
const settings = {
  QT: {
    PATH: 'C:/Qt',
    VER: '5.15.2',
  },
  BINARYCREATOR_PATH:
    'C:/Qt/Tools/QtInstallerFramework/4.6/bin/binarycreator.exe',
};
module.exports = settings;
```

## Node.js パッケージをインストール

installer パス上で以下のようにコマンドを実行する。
推奨 Node.js バージョン: 18 以上

```sh
$ npm install
```
