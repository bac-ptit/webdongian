#!/bin/sh

rm -rf tmp

mkdir tmp
cd tmp

##########################################################
## install oatpp
InstallOatppLibrary() {
MODULE_NAME=$1

git clone --depth=1 https://github.com/oatpp/$MODULE_NAME

cd $MODULE_NAME
mkdir build
cd build

cmake -DOATPP_BUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Release ..
make install -j 16

cd ../../

}

InstallLib() {
USER_NAME=$1
MODULE_NAME=$2
git clone --depth=1 https://github.com/$USER_NAME/$MODULE_NAME

cd $MODULE_NAME
cmake -DCMAKE_BUILD_TYPE=Release .
make install -j 16
cd ../
}

InstallLib "Thalhammer" "jwt-cpp"
InstallLib "karastojko" "mailio"
InstallOatppLibrary "oatpp"
InstallOatppLibrary "oatpp-swagger"
InstallOatppLibrary "oatpp-openssl"



##########################################################

cd ../

rm -rf tmp
