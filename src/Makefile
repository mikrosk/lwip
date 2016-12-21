include Filelists.mk

TARGET = lwipftpd.ttp

LWIPDIR = .
SRCFILES = $(COREFILES) $(CORE4FILES) $(NETIFFILES) sys_now.c main.c #$(HTTPDFILES)
OBJFILES = $(SRCFILES:.c=.o)

CC = m68k-atari-mint-gcc
CFLAGS = -m68020-60 -O2 -fomit-frame-pointer -Iinclude -Wall
LDFLAGS = -m68020-60 -s

$(TARGET): $(OBJFILES)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -f $(TARGET) $(OBJFILES) *~
