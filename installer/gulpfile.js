const { series } = require('gulp');
const { from, zip, concatMap, map } = require('rxjs');
const { join } = require('path');
const { removeDirRecursive, makeDir, execute } = require('./presets/common');
const {
  PRODUCT,
  buildConfigXml,
  buildPackage: buildProductPackage,
} = require('./product');
const { BINARYCREATOR_PATH } = require('./local');

const qtGetCompiler = ({ arch }) => `msvc2019${arch === 'x64' ? '_64' : ''}`;

/**
 * パッケージ群の生成
 * @param workDir 作業ディレクトリ
 * @param options {
 *  mode: 'release' | 'debug',
 *  arch: 'x86' | 'x64',
 * }
 */
const buildPackages = (workDir, options) =>
  makeDir(join(workDir, 'packages')).pipe(
    concatMap((packageDir) => {
      return zip(buildProductPackage(packageDir, options, qtGetCompiler));
    })
  );

/**
 * インストーラ生成コマンドの実行
 * @param workDir ワークディレクトリ
 * @param baseName  インストーラファイルのベース名
 * @param options {
 *  mode: 'release' | 'debug',
 *  arch: 'x86' | 'x64',
 * }
 */
const buildInstaller = (workDir, baseName, { mode }) => {
  return execute(
    [
      BINARYCREATOR_PATH,
      '--offline-only',
      '-c config/config.xml',
      '-p packages',
      `${baseName}-${mode}`,
    ].join(' '),
    { cwd: workDir }
  );
};

function main() {
  // ワークディレクトリをクリア
  return removeDirRecursive(PRODUCT.WORKDIR).pipe(
    // ワークディレクトリを作成
    concatMap(() => makeDir(PRODUCT.WORKDIR)),

    concatMap(() =>
      from(PRODUCT.OPTIONS).pipe(
        map((options) => ({
          workDir: join(PRODUCT.WORKDIR, options.arch, options.mode),
          options,
        }))
      )
    ),

    // インストーラに含む情報を生成し、ファイルを配置
    concatMap(({ workDir, options }) => {
      return zip(
        buildConfigXml(workDir, options),
        buildPackages(workDir, options)
      ).pipe(map(() => ({ workDir, options })));
    }),

    // インストーラを生成
    concatMap(({ workDir, options }) =>
      buildInstaller(
        workDir,
        PRODUCT.getBaseName(options, qtGetCompiler),
        options
      )
    )
  );
}

exports.default = series(main);
