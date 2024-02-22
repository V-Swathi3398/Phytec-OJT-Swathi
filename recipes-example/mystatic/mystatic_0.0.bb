DESCRIPTION = "Simple static library application"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://print.c\
           file://arith.c\
           file://mylib.h"

S = "${WORKDIR}"

do_compile() {
	${CC} -c print.c
	${CC} -c arith.c
	${AR} rcs libarp.a print.o arith.o
}	

do_install() {
	install -d ${D}${libdir}
	install -m 0755 libarp.a ${D}${libdir}
	install -d ${D}${includedir}
	install -m 0755 mylib.h ${D}${includedir}
}

ALLOW_EMPTY_${PN} = "1"
