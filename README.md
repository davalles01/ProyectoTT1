# Proyecto_TT1 

# Instrucciones de compilación de aplicación (desde el directorio del proyecto):

g++ src/*.cpp -lm -o bin/EKF_GEOS3

cd bin
./EKF_GEOS3

# Dichas instrucciones se encuentran en el fichero Makefile.sh, que se puede ejecutar así: sh Makefile.sh

# Instrucciones de compilación de los tests (desde el directorio del proyecto):

SRC_FILES=$(find src -name '*.cpp' ! -name 'EKF_GEOS3.cpp')

g++ test/tests.cpp $SRC_FILES -lm -o bin/tests

cd bin
./tests

# Dichas instrucciones se encuentran en el fichero Makefile_tests.sh, que se puede ejecutar así: sh Makefile_tests.sh
