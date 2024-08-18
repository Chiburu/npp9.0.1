const { series } = require('gulp');
const { of, from, zip, concatMap, map } = require('rxjs');
const { rm, mkdir, writeFile, copyFile: fsCopyFile } = require('fs/promises');
const { join } = require('path');
const { create } = require('xmlbuilder2');
const { format } = require('date-fns');
const util = require('node:util');
const exec = util.promisify(require('node:child_process').exec);
const { BINARYCREATOR_PATH } = require('./local');

/**
 * ワークディレクトリを削除
 */
const removeWorkDir = (dir) => from(rm(dir, { recursive: true, force: true }));

/**
 * ディレクトリ作成
 */
const makeDir = (path) =>
  from(mkdir(path, { recursive: true })).pipe(map(() => path));

/**
 * JSONデータをXMLにフォーマット
 */
const buildXml = (json) => {
  const xml = create({ version: '1.0', encoding: 'UTF-8' }, json);
  return of(xml.end({ prettyPrint: true }));
};

/**
 * XMLデータをファイルに書き出し
 * @param path 書き出すXMLファイルパス
 * @param xml XML形式のテキスト
 */
const writeXml = (path, xml) => {
  const content = new Uint8Array(Buffer.from(xml));
  return from(writeFile(path, content));
};

/**
 * ファイルコピー
 * @param src ソースパス
 * @param dest コピー先パス
 * @param mode コピーモード (https://nodejs.org/docs/latest-v18.x/api/fs.html#fspromisescopyfilesrc-dest-mode)
 */
const copyFile = (src, dest, mode) => from(fsCopyFile(src, dest, mode));

/**
 * 外部コマンドの実行
 * @param cmd 引数を含むコマンドテキスト
 * @param options オプション (https://nodejs.org/docs/latest-v18.x/api/fs.html#fspromisescopyfilesrc-dest-mode)
 */
const execute = (cmd, options) => from(exec(cmd, options)).pipe(() => cmd);

/**
 * インストーラ設定ファイルの生成
 * @param workDir ワークディレクトリ
 */
const buildConfigXml = (workDir) =>
  zip(
    makeDir(join(workDir, 'config')),
    buildXml({
      Installer: {
        Name: 'npp9.0.1',
        Version: '1.0.0.0',
        Title: 'npp9.0.1 Installer',
        Publisher: 'Chiburu Systems',
        TargetDir: `@RootDir@/chiburu.com/npp9.0.1`,
      },
    })
  ).pipe(
    concatMap(([configDir, xml]) =>
      writeXml(join(configDir, 'config.xml'), xml)
    )
  );

/**
 * nppパッケージの生成
 * @param packageDir パッケージルート
 */
const buildNppPackage = (packageDir) =>
  makeDir(join(packageDir, 'com.chiburu.npp9.0.1')).pipe(
    concatMap((nppDir) => {
      // パッケージ設定XMLの生成
      const oMeta = zip(
        makeDir(join(nppDir, 'meta')),
        buildXml({
          Package: {
            Description: 'Notes C++ Library for 9.0.1',
            Version: '1.0.0.0',
            ForcedInstallation: true,
            ReleaseDate: format(new Date(), 'yyyy-MM-dd'),
          },
        })
      ).pipe(
        concatMap(([metaDir, xml]) =>
          writeXml(join(metaDir, 'package.xml'), xml)
        )
      );

      // パッケージするファイルを構成
      const oData = makeDir(join(nppDir, 'data')).pipe(
        concatMap((dataDir) => {
          const dllFile = 'npp090001_v1.dll';
          const list = [
            { arch: 'x64', comp: 'msvc2019_64', mode: 'debug' },
            { arch: 'x64', comp: 'msvc2019_64', mode: 'release' },
            { arch: 'x86', comp: 'msvc2019', mode: 'debug' },
            { arch: 'x86', comp: 'msvc2019', mode: 'release' },
          ].map(({ arch, comp, mode }) =>
            makeDir(join(dataDir, arch)).pipe(
              concatMap((dir) =>
                copyFile(
                  join('../build', `${comp}-Qt5.15.2-${mode}`, mode, dllFile),
                  join(dir, mode === 'debug' ? 'npp090001d_v1.dll' : dllFile)
                )
              )
            )
          );
          return zip(...list);
        })
      );
      return zip(oMeta, oData);
    })
  );

/**
 * パッケージ群の生成
 */
const buildPackages = (workDir) =>
  makeDir(join(workDir, 'packages')).pipe(
    concatMap((packageDir) => zip(buildNppPackage(packageDir)))
  );

/**
 * インストーラを生成
 * @param workDir ワークディレクトリ
 * @param baseName  インストーラファイルのベース名
 */
const buildInstaller = ({ workDir, baseName }) => {
  return execute(
    [
      BINARYCREATOR_PATH,
      '--offline-only',
      '-c config/config.xml',
      '-p packages',
      baseName,
    ].join(' '),
    { cwd: workDir }
  );
};

function main() {
  const workDir = 'work';

  // ワークディレクトリをクリア
  return removeWorkDir(workDir).pipe(
    // ワークディレクトリを作成
    concatMap(() => makeDir(workDir)),

    // インストーラに含む情報を生成し、ファイルを配置
    concatMap(() => zip(buildConfigXml(workDir), buildPackages(workDir))),

    // インストーラを生成
    concatMap(() =>
      buildInstaller({ workDir, baseName: `setup-npp9.0.1-msvc2019-Qt5.15.2` })
    )
  );
}

exports.default = series(main);
