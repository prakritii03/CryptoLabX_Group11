from stream_cipher import encrypt_decrypt


def recover_seed(ciphertext):

    known_pattern = b"A" * 14

    tested_seeds = 0
    recovered_seed = None
    recovered_plaintext = None


    for candidate_seed in range(2**16):

        candidate_plaintext = encrypt_decrypt(
            ciphertext, candidate_seed
        )

        tested_seeds += 1

    
        position = candidate_plaintext.find(known_pattern)

        if position != -1:

      
            prefix = candidate_plaintext[:position]
            valid_length = 5 <= len(prefix) <= 20

      
            printable = all(
                32 <= byte <= 126 for byte in prefix
            )

          
            valid_structure = (
                valid_length
                and printable
                and position + 14 == len(candidate_plaintext)
            )

            if valid_structure and recovered_seed is None:
               
                recovered_seed = candidate_seed
                recovered_plaintext = candidate_plaintext


    return recovered_seed, recovered_plaintext, tested_seeds


if __name__ == "__main__":

    ciphertext_hex = input("Enter ciphertext in hex: ").strip()

    try:
        ciphertext = bytes.fromhex(ciphertext_hex)

        recovered_seed, recovered_plaintext, tested = recover_seed(
            ciphertext
        )

        print("\n" + "=" * 50)
        print("MT19937 SEED RECOVERY ATTACK")
        print("=" * 50)

        print("Total seeds tested:", tested)

        if recovered_seed is not None:

            print("Recovered Seed:", recovered_seed)

            print(
                "Recovered Plaintext:",
                recovered_plaintext.decode("ascii")
            )

            print(
                "Known Pattern Found:",
                b"A" * 14 in recovered_plaintext
            )

            # Final independent verification
            verification = encrypt_decrypt(
                ciphertext, recovered_seed
            )

            print(
                "Full Plaintext Verification:",
                verification == recovered_plaintext
            )

        else:
            print("No matching seed found.")

        print("=" * 50)

    except ValueError:
        print("Invalid hexadecimal ciphertext.")