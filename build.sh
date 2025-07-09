#!/bin/bash

warnings="-Wno-writable-strings -Wno-format-security -Wno-deprecated-declarations -Wno-switch"

if [[ "$(uname)" == "Linux" ]]; then
    echo "Running on Linux"
    libs="-lGL -lglut"
    outputFile=map-editor
fi

clang $includes -g src/main.c -o$outputFile $libs $warnings
