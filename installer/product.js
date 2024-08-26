const {
  getSuffix,
  buildConfig,
  buildPackage: commonBuildPackage,
} = require('./presets/common');
const { join } = require('path');
const { QT } = require('./local');

/**
 * 製品バージョン
 */
const PRODUCT = {
  VER: '1.0.0.0',
  OPTIONS: [
    { arch: 'x64', mode: 'debug' },
    { arch: 'x64', mode: 'release' },
    { arch: 'x86', mode: 'debug' },
    { arch: 'x86', mode: 'release' },
  ],
  getBaseName: (options, getCompiler) =>
    `setup-npp9.0.1-${getCompiler(options)}-Qt${QT.VER}`,
  WORKDIR: 'work',
};

/**
 * インストーラ設定ファイルの生成
 * @param workDir ワークディレクトリ
 * @param options {
 *  mode: 'release' | 'debug',
 *  arch: 'x86' | 'x64',
 * }
 */
const buildConfigXml = (workDir, options) =>
  buildConfig(
    workDir,
    ({ mode, arch }) => ({
      Name: `npp9.0.1 (${arch} ${mode} edition)`,
      Version: PRODUCT.VER,
      Title: `npp9.0.1 (${arch} ${mode} edition) Installer`,
      Publisher: 'Chiburu Systems',
      TargetDir: `@RootDir@/chiburu.com/npp9.0.1`,
    }),
    options
  );

/**
 * 製品パッケージに設定するXML情報
 * @param options {
 *  mode: 'release' | 'debug',
 *  arch: 'x86' | 'x64',
 * }
 */
const createPackageXml = ({ mode, arch }) => ({
  Description: `npp9.0.1 (${arch} ${mode} edition)`,
  Version: PRODUCT.VER,
  ForcedInstallation: true,
});

/**
 * 製品パッケージの生成
 * @param packageDir パッケージルート
 */
const buildPackage = (packageDir, options, getCompiler) => {
  const suffix = getSuffix(options);
  const srcDir = join(
    '../build',
    `${getCompiler(options)}-Qt${QT.VER}-${options.mode}`,
    options.mode
  );
  return commonBuildPackage({
    packageDir,
    domain: 'com.chiburu.npp9.0.1',
    packageXml: createPackageXml(options),
    dataList: [{ srcDir, file: `npp090001${suffix}_v1.dll` }],
  });
};

module.exports = {
  PRODUCT,
  buildConfigXml,
  buildPackage,
};
