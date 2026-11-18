import random
import time


def generate_token():
    # Step 1: Get current Unix timestamp
    timestamp = int(time.time())

    # Step 2: Initialize MT19937 using timestamp as seed
    rng = random.Random(timestamp)

    # Step 3: Generate 16 consecutive 8-bit values
    token_bytes = bytearray()

    for i in range(16):
        token_byte = rng.getrandbits(8)
        token_bytes.append(token_byte)

    # Step 4: Convert token bytes into hexadecimal
    token_hex = bytes(token_bytes).hex()

    return timestamp, token_hex


if __name__ == "__main__":

    timestamp, token = generate_token()

    print("=" * 50)
    print("PART B: PREDICTABLE TOKEN GENERATION")
    print("=" * 50)

    print("Unix Timestamp:", timestamp)
    print("Token Length:", len(bytes.fromhex(token)))
    print("Generated Token (Hex):", token)

    print("=" * 50)