#!/bin/bash

# Set QMK_PATH before calling, eg: `QMK_PATH=~/code/qmk_firmware ./build.sh`
DEST_PATH=${QMK_PATH}/keyboards/planck/keymaps/

# Absolute path this script is in
SCRIPT_PATH=$(dirname `readlink -f $0`)

# Copy this dir to QMK's keymaps directory
cp -r $SCRIPT_PATH $DEST_PATH

# cd to qmk_firmware directory
cd $QMK_PATH
# Compile a bin file in this directory
make planck/ez:ng-planck-layout
cd -
