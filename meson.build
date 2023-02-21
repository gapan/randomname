project('randomname', 'c',
  version: '0.1.0',
  license: 'GPLv3',
  meson_version: '>= 0.56'
)
package = meson.project_name()
version = meson.project_version()
soversion = '0'

subdir('src')

prefix = get_option('prefix')
datadir = join_paths(prefix, get_option('datadir'))
docdir = join_paths(datadir, 'doc', package + '-' + version)

docs = [
  'AUTHORS',
  'COPYING',
  'README.md'
]

install_data(docs, install_dir: docdir)
