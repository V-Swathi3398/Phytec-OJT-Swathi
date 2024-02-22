DESCRIPTION = "Simple hello application"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://helloswathi.c"

S = "${WORKDIR}"

DEPENDS = "mystatic"

do_compile() {
	${CC} helloswathi.c ${LDFLAGS} -o helloswathi -larp
}	

do_install() {
	install -d ${D}${bindir}
	install -m 0755 helloswathi ${D}${bindir}
}
