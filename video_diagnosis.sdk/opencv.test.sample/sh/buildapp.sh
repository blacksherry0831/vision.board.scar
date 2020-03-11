#export ARCH=arm
#export CROSS_COMPILE=/home/cks-nj/share/tools/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain/bin/arm-none-linux-gnueabi-
#export PATH=$PATH:/home/cks-nj/share/tools/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain/bin
make clean
make 
cp bin/* ../../../release/app
