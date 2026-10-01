from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes


BLOCK_SIZE = 16
oracle_queries = 0


def pkcs7_pad(data):
    padding_length = BLOCK_SIZE - (len(data) % BLOCK_SIZE)
    return data + bytes([padding_length]) * padding_length


def pkcs7_unpad(data):
    if len(data) == 0 or len(data) % BLOCK_SIZE != 0:
        raise ValueError("Invalid padding")

    padding_length = data[-1]

    if padding_length < 1 or padding_length > BLOCK_SIZE:
        raise ValueError("Invalid padding")

    if data[-padding_length:] != bytes([padding_length]) * padding_length:
        raise ValueError("Invalid padding")

    return data[:-padding_length]


def encrypt_message(key, plaintext):
    iv = get_random_bytes(BLOCK_SIZE)
    cipher = AES.new(key, AES.MODE_CBC, iv)
    ciphertext = cipher.encrypt(pkcs7_pad(plaintext))
    return iv, ciphertext


def padding_oracle(iv, ciphertext, key):
    global oracle_queries
    oracle_queries += 1

    try:
        cipher = AES.new(key, AES.MODE_CBC, iv)
        decrypted = cipher.decrypt(ciphertext)
        pkcs7_unpad(decrypted)
        return True
    except ValueError:
        return False


def xor_bytes(a, b):
    return bytes(x ^ y for x, y in zip(a, b))


def recover_block(previous_block, target_block, oracle):
    intermediate = bytearray(BLOCK_SIZE)
    recovered_plaintext = bytearray(BLOCK_SIZE)

    modified_block = bytearray(previous_block)

    for padding_value in range(1, BLOCK_SIZE + 1):

        position = BLOCK_SIZE - padding_value

        for j in range(position + 1, BLOCK_SIZE):
            modified_block[j] = (
                intermediate[j] ^ padding_value
            )

        found = False

        for guess in range(256):

            modified_block[position] = guess

            if oracle(bytes(modified_block), target_block):

                intermediate[position] = (
                    guess ^ padding_value
                )

                recovered_plaintext[position] = (
                    intermediate[position] ^ previous_block[position]
                )

                found = True
                break

        if not found:
            raise RuntimeError(
                f"Could not recover byte at position {position}"
            )

    return bytes(recovered_plaintext)


def padding_oracle_attack(iv, ciphertext, oracle):
    blocks = [
        ciphertext[i:i + BLOCK_SIZE]
        for i in range(0, len(ciphertext), BLOCK_SIZE)
    ]

    previous_blocks = [iv] + blocks[:-1]

    recovered_plaintext = bytearray()

    for i in range(len(blocks)):
        plaintext_block = recover_block(
            previous_blocks[i],
            blocks[i],
            oracle
        )

        recovered_plaintext.extend(plaintext_block)

        print(
            f"Recovered block {i + 1}: "
            f"{plaintext_block}"
        )

    return bytes(recovered_plaintext)


def main():

    global oracle_queries

    key = get_random_bytes(16)

    plaintext = (
        b"Padding oracle attacks demonstrate how "
        b"small error messages can leak plaintext."
    )

    iv, ciphertext = encrypt_message(
        key,
        plaintext
    )

    print("Original plaintext:")
    print(plaintext.decode())

    print("\nCiphertext:")
    print(ciphertext.hex())

    print("\nIV:")
    print(iv.hex())

    oracle_queries = 0

    def attacker_oracle(modified_previous, target):

        return padding_oracle(
            iv,
            modified_previous + target,
            key
        )

    recovered_padded = padding_oracle_attack(
        iv,
        ciphertext,
        attacker_oracle
    )

    recovered_plaintext = pkcs7_unpad(
        recovered_padded
    )

    print("\nRecovered plaintext:")
    print(recovered_plaintext.decode())

    print("\nTotal oracle queries:")
    print(oracle_queries)


if __name__ == "__main__":
    main()