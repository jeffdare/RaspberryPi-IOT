BINDIR=$(DESTDIR)/opt/iot

all: iot

.PHONY: all install clean distclean

iot:
	$(CC) iotmain.c cpustat.c mac.c -o $@
	strip $@

install: iot
	mkdir -p $(BINDIR)
	install iot $(BINDIR)/iot
	install iot.properties $(BINDIR)/iot.properties

clean:
	rm -f iot
