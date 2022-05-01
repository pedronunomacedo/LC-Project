# name of the program (Minix service)
PROG=proj 

.PATH: ${.CURDIR}
.PATH: ${.CURDIR}/lib/devices
.PATH: ${.CURDIR}/lib/sprite
.PATH: ${.CURDIR}/lib/utils
.PATH: ${.CURDIR}/menu
.PATH: ${.CURDIR}/events

# source code files to be compiled
SRCS = proj.c events.c timer.c kbc.c graphics.c sprite.c main_menu.c rules_menu.c utils.c

# additional compilation flags
CPPFLAGS += -pedantic -D __LCOM_OPTIMIZED__

# list of library dependencies
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
