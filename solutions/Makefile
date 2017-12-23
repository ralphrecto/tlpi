include ../Makefile.inc

GEN_EXE = tee cp

EXE = ${GEN_EXE}

all : ${EXE}

allgen : ${GEN_EXE}

clean :
	${RM} ${EXE} *.o
	${RM} -rf tests/testspace
	mkdir -p tests/testspace

showall :
	@ echo ${EXE}

${EXE} : ${TLPI_LIB}		# True as a rough approximation
