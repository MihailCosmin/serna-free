
PACKAGE_MAKEOPTS += DLL=1 
debug:PACKAGE_MAKEOPTS += DEBUG=1 MFLAGS=-MDd
release:PACKAGE_MAKEOPTS += MFLAGS=-MD