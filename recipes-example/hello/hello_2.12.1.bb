DESCRIPTION = "Simple GNU Helloworld autotools recipe"

LICENSE = "GPLv3+"
LIC_FILES_CHKSUM = "file://COPYING;md5=1ebbd3e34237af26da5dc08a4e440464"

SRC_URI = "https://ftp.gnu.org/gnu/hello/hello-2.12.1.tar.gz"

SRC_URI[sha256sum] = "8d99142afd92576f30b0cd7cb42a8dc6809998bc5d607d88761f512e26c7db20"


inherit autotools-brokensep gettext
