DESCRIPTION = "Simple kernel recipe"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

inherit kernel

SRC_URI = "https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.3.8.tar.xz;name=kernel\
           file://defconfig"

S = "${WORKDIR}/linux-6.3.8"

SRC_URI[kernel.sha256sum] = "4323d421250e2e444c35d36f4aa8ddb56591dedc25c68d359d19c4ef9dd20955"
