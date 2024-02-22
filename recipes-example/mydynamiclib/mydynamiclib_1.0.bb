SUMMARY = "Example Library"
DESCRIPTION = "An example dynamic library for demonstration purposes."
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://print.c\
           file://arith.c\
           file://mylib.h"

S = "${WORKDIR}"

do_compile() {
    ${CC} -fPIC -c print.c -o print.o
    ${CC} -fPIC -c arith.c -o arith.o
    ${CC} ${LDFLAGS} -shared -o libarp.so print.o arith.o
}

do_install() {
	install -d ${D}${libdir}
	install -m 0755 libarp.so ${D}${libdir}
	install -d ${D}${includedir}
	install -m 0755 mylib.h ${D}${includedir}
}

INSANE_SKIP_${PN} += " ldflags"
INHIBIT_PACKAGE_STRIP = "1"
INHIBIT_SYSROOT_STRIP = "1"
SOLIBS = ".so"
FILES_SOLIBSDEV = ""

ALLOW_EMPTY_${PN} = "1"
