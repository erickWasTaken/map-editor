#!/bin/bash

defines="-DAPP"
warnings="-Wno-writable-strings -Wno-format-security -Wno-deprecated-declarations -Wno-switch"
includes="-Ithird_party"

if [[ "$(uname)" == "Linux" ]]; then
    echo "Running on Linux"
    libs="-lGL -lglut"
    outputFile=map-editor
fi

clang -g $includes src/main.c -o$outputFile $libs $warnings $defines
