#!/usr/bin/env bash
set -euo pipefail

OUTPUT_DIR="$(dirname "$0")/../data"
mkdir -p "$OUTPUT_DIR"

dd if=/dev/urandom \
   of="$OUTPUT_DIR/linux_urandom.bin" \
   bs=1048576 count=1 iflag=fullblock status=none

echo "Generated Linux random data:"
wc -c "$OUTPUT_DIR/linux_urandom.bin"
