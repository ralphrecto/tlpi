include ../Makefile.inc

GEN_EXE = tee

EXE = ${GEN_EXE}

all : ${EXE}

allgen : ${GEN_EXE}

clean :
	${RM} ${EXE} *.o
	${RM} -rf tests/testspace
	mkdir -P tests/testspace

showall :
	@ echo ${EXE}

${EXE} : ${TLPI_LIB}		# True as a rough approximation
