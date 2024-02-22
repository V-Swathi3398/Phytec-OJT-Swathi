DESCRIPTION = "Simple hellomakefile application"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://app.c\
           file://functions.c\
           file://functions.h"

S = "${WORKDIR}"

do_compile() {
	${CC} -c app.c
	${CC} -c functions.c
	${AR} rcs libfun.a app.o functions.o
}	

do_install() {
	install -d ${D}${libdir}
	install -m 0755 libfun.a ${D}${libdir}
	install -d ${D}${includedir}
	install -m 0755 functions.h ${D}${includedir}
}
