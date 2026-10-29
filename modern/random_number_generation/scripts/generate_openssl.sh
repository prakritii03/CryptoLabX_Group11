#!/usr/bin/env bash
set -euo pipefail

OUTPUT_DIR="$(dirname "$0")/../data"
mkdir -p "$OUTPUT_DIR"

if ! command -v openssl >/dev/null 2>&1; then
    echo "Error: OpenSSL is not installed." >&2
    exit 1
fi

openssl rand -out "$OUTPUT_DIR/openssl_rand.bin" 1048576

echo "Generated OpenSSL random data:"
wc -c "$OUTPUT_DIR/openssl_rand.bin"
