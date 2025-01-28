
DEST_F="$(pwd)/pretty_sleep.deb"

TEMP_D="$(mktemp -d)"
mkdir -p "${TEMP_D}/pkg/DEBIAN"

cmake -B "${TEMP_D}/build" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="${TEMP_D}/pkg/usr"
cd "${TEMP_D}/build"
make
make install
cd ..

cat > "${TEMP_D}/pkg/DEBIAN/control" << EOF
Package: psleep
Version: 0.0.0-git
Section: utils
Priority: optional
Architecture: all
Maintainer: Jim Konstantos <konstantosjim@gmail.com>
Description: A prettier sleep program
Depends: libc6
EOF

dpkg-deb --root-owner-group --build "${TEMP_D}/pkg" "${DEST_F}"
