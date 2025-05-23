MODULES = 
BOARD = edu-ciaa-nxp
MUJU = ./muju

include $(MUJU)/module/base/makefile

# Generar documentación con Doxygen
doc:
	doxygen doxyfile
