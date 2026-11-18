import secrets
import string
import random



def generate_keystream(length, seed):

    
    rng = random.Random(seed)

    keystream = []

   
    for i in range(length):

        key_byte = rng.getrandbits(8)

        keystream.append(key_byte)

    return keystream



def encrypt_decrypt(data, seed):

  
    rng = random.Random(seed)

 
    result = bytearray()

  
    for byte in data:

        
        key_byte = rng.getrandbits(8)

        
        output_byte = byte ^ key_byte

    
        result.append(output_byte)

    return bytes(result)


def generate_special_plaintext():
    
    characters = string.ascii_letters + string.digits + string.punctuation + " "

    
    prefix_length = secrets.randbelow(16) + 5

   
    prefix = ''.join(
        secrets.choice(characters)
        for _ in range(prefix_length)
    )

   
    plaintext = (prefix + "A" * 14).encode("ascii")

    return plaintext

if __name__ == "__main__":

   
    plaintext = generate_special_plaintext()

    
    seed = secrets.randbelow(2**16)

   
    ciphertext = encrypt_decrypt(plaintext, seed)


    decrypted = encrypt_decrypt(ciphertext, seed)

  
    print("=" * 55)
    print("PART A: MT19937 STREAM CIPHER")
    print("=" * 55)

    print("\nOriginal Plaintext:")
    print(plaintext.decode("ascii"))

    print("\nPlaintext Length:", len(plaintext))

    print("\nRandom 16-bit Seed:", seed)

    print("\nCiphertext (Hex):")
    print(ciphertext.hex())

    print("\nCiphertext (Decimal):")
    print(list(ciphertext))

    print("\nDecrypted Plaintext:")
    print(decrypted.decode("ascii"))

    print("\nVerification:", decrypted == plaintext)

    print("\nKnown Pattern Found:", b"A" * 14 in plaintext)

    print("=" * 55)