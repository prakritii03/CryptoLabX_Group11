import random


def generate_token_from_timestamp(timestamp):

  
    rng = random.Random(timestamp)

    
    token_bytes = bytearray()

    for i in range(16):
        token_byte = rng.getrandbits(8)
        token_bytes.append(token_byte)

    return bytes(token_bytes).hex()


def predict_token(target_token, approximate_timestamp):

  
    start_time = approximate_timestamp - 300
    end_time = approximate_timestamp + 300

    tested_timestamps = 0
    recovered_timestamp = None

   
    for candidate_timestamp in range(start_time, end_time + 1):

        generated_token = generate_token_from_timestamp(
            candidate_timestamp
        )

        tested_timestamps += 1

        if generated_token == target_token:
       
            if recovered_timestamp is None:
                recovered_timestamp = candidate_timestamp


    return recovered_timestamp, tested_timestamps


if __name__ == "__main__":

    print("=" * 55)
    print("MT19937 PREDICTABLE TOKEN ATTACK")
    print("=" * 55)

  
    approximate_timestamp = int(
        input("Enter approximate Unix timestamp: ")
    )

    target_token = input(
        "Enter target token (hex): "
    ).strip().lower()


    try:
        token_bytes = bytes.fromhex(target_token)

        if len(token_bytes) != 16:
            raise ValueError("Token must contain exactly 16 bytes.")

    except ValueError as error:
        print("Invalid token:", error)
        raise SystemExit(1)

  
    recovered_timestamp, tested = predict_token(
        target_token,
        approximate_timestamp
    )

    print("\nTotal timestamps tested:", tested)

    if recovered_timestamp is not None:

        print("Recovered Timestamp:", recovered_timestamp)

      
        verification_token = generate_token_from_timestamp(
            recovered_timestamp
        )

        print("Regenerated Token:", verification_token)

        print(
            "Token Verification:",
            verification_token == target_token
        )

    else:
        print("No matching timestamp found.")

    print("=" * 55)