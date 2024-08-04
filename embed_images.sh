#!/bin/bash

# This file converts images and other assets into byte array header files.
# The purpose is to include the file with the compiled executable.

ASSETS_DIR="src/assets"
OUTPUT_DIR="src/assets"

mkdir -p $OUTPUT_DIR

for filepath in $ASSETS_DIR/*; do
    filename=$(basename -- "$filepath")
    extension="${filename##*.}"
    filename="${filename%.*}"
    
    # Generate the header file with xxd
    xxd -i "$filepath" "$OUTPUT_DIR/${filename}.h"
    
    # Use awk to replace the length definition line with the correct format
    awk '{gsub("unsigned int", "static const unsigned int"); print}' "$OUTPUT_DIR/${filename}.h" > "$OUTPUT_DIR/${filename}.tmp"
    mv "$OUTPUT_DIR/${filename}.tmp" "$OUTPUT_DIR/${filename}.h"
done