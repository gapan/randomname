librandomname = library('librandomname', 'librandomname.c', install: true, version: version, soversion: soversion, name_prefix: '')
executable('randomname', 'randomname.c', link_with: librandomname, install: true)

install_headers('librandomname.h')

pkgconfig = import('pkgconfig')
pkgconfig.generate(librandomname, name: 'librandomname', description: 'Library for creating random names.')
