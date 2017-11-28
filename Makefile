LD=g++
CXX=g++ -g -c
NAME=save-channels
EXEC_SRC=\
        ${NAME}.cpp
MODULE_SRC=
MODULE_OBJ=${MODULE_SRC:.cpp=.o}
EXEC_OBJ=${EXEC_SRC:.cpp=.o}
EXEC_PRG=${EXEC_SRC:.cpp=}
all: ${EXEC_PRG} ${MODULE_OBJ} ${EXEC_OBJ}
${NAME}: ${NAME}.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@
.cpp.o: %.cpp %.hpp
	${CXX} $<
clean:
	rm -f ${EXEC_PRG} ${MODULE_OBJ} ${EXEC_OBJ}