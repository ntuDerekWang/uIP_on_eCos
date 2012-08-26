#!/bin/bash
rm hello
rm server
rm client1017
rm client1117
rm clientStars
make INSTALL_DIR=/home/derek/桌面/eCos工作/0216RCdefault_install

arm-eabi-objcopy -O binary hello hello.bin
arm-eabi-objcopy -O binary client1017 client1017.bin
arm-eabi-objcopy -O binary client1117 client1117.bin
arm-eabi-objcopy -O binary server server.bin
arm-eabi-objcopy -O binary clientStars clientStars.bin
chmod 777 *
#rename clientStars client0908 clientStars.bin*

