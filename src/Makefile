include Filelists.mk

TARGET = lwipftpd.tos

LWIPDIR = .
SRCFILES = $(COREFILES) $(CORE4FILES) $(NETIFFILES) $(HTTPDFILES)
OBJFILES = $(SRCFILES:.c=.o)

CC = m68k-atari-mint-gcc
CFLAGS = -m68020-60 -O2 -fomit-frame-pointer -Iinclude
LDFLAGS = -m68020-60 -s

$(TARGET): $(OBJFILES)
	$(CC) $(LDFLAGS) -o $@ $^
