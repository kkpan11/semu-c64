#!/usr/bin/env python3.8

kernel = open("Image", "rb").read()
dtb = open("minimal.dtb", "rb").read()
initrd = open("rootfs.cpio", "rb").read()

REUSIZE = 16 * 1024 * 1024
DTB_SIZE = 16384
INITRD_SIZE = (4 * 1024 * 1024)

with open("reufile.linux", "wb") as outf:
    outf.write(kernel)
    outf.write(b"\x00" * (REUSIZE - len(kernel) - DTB_SIZE - INITRD_SIZE))
    outf.write(dtb)
    outf.write(b"\x00" * (DTB_SIZE - len(dtb)))
    outf.write(initrd)
    outf.write(b"\x00" * (INITRD_SIZE - len(initrd)))
