DESCRIPTION = "Simple git recipe"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=218947f77e8cb8e2fa02918dc41c50d0"

SRC_URI = "git://github.com/DaveGamble/cJSON.git;protocol=http"

SRCREV = "${AUTOREV}"

PROVIDES += "sbcsgithello"

S = "${WORKDIR}/git"

inherit cmake
