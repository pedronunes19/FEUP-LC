# name of the program (Minix service)
PROG=proj

.PATH: ${.CURDIR}
.PATH: ${.CURDIR}/devices
.PATH: ${.CURDIR}/game
.PATH: ${.CURDIR}/imgs

# source code files to be compiled
SRCS = proj.c video_card.c utils.c tetromino.c keyboard.c mouse.c timer.c device_utils.c rtc.c

# __LCOM_OPTIMIZED__ disables most of the LCF's overhead (and functionality!)
CFLAGS += -pedantic #-D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>>