#!/bin/bash

LAYOUT_NAME=plonker

# Set QMK_PATH before calling, eg: `QMK_PATH=~/code/qmk_firmware ./build.sh`
DEST_PATH=${QMK_PATH}/keyboards/planck/keymaps/${LAYOUT_NAME}
mkdir $DEST_PATH

# Copy files to new dir in QMK's keymaps directory
cp -r * $DEST_PATH

# cd to qmk_firmware directory
cd $QMK_PATH
# Compile a bin file in this directory
make planck/ez:${LAYOUT_NAME}
cd -
