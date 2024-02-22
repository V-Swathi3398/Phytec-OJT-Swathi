DESCRIPTION = "Simple hello application"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://funsum.c"

S = "${WORKDIR}"

DEPENDS = "functionsmultfiles"

do_compile() {
	${CC} funsum.c ${LDFLAGS} -o funsum
}	

do_install() {
	install -d ${D}${bindir}
	install -m 0755 funsum ${D}${bindir}
}
