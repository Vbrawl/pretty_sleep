# Maintainer: Vbrawl <konstantosjim@gmail.com>
pkgname=pretty_sleep-git
pkgver=0.0.1
pkgrel=1
pkgdesc=""
arch=('any')
url="https://github.com/Vbrawl/pretty_sleep"
license=('MIT')
options=('!debug')
source=('git+https://github.com/Vbrawl/pretty_sleep.git')
md5sums=('SKIP')

build() {
  cd "$srcdir/pretty_sleep"
  cmake -Bbuild -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
  cd build
  make -j $(nproc)
}

package() {
	cd "$srcdir/pretty_sleep/build"
	make DESTDIR="$pkgdir/" install
}
