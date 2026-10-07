"""
Automated verification tests for the AES-CBC Padding Oracle Attack.

Tests verify:
1. Single-block plaintext recovery.
2. Multi-block plaintext recovery.
3. Recovery for different plaintext lengths.
4. Oracle query counting.
5. The attack function does not receive the AES key.

Run from repository root:

    python attacks/padding_oracle_attack/tests/test_padding_oracle.py
"""

import sys
import os
import inspect

# ------------------------------------------------------------
# Add the padding_oracle_attack directory to Python path
# ------------------------------------------------------------

CURRENT_DIR = os.path.dirname(os.path.abspath(__file__))
ATTACK_DIR = os.path.dirname(CURRENT_DIR)

if ATTACK_DIR not in sys.path:
    sys.path.insert(0, ATTACK_DIR)

import padding_oracle_attack as poa


# ------------------------------------------------------------
# Helper: create an oracle that hides the AES key
# ------------------------------------------------------------

def make_oracle(key):
    """
    Create a padding oracle that internally knows the AES key.

    The attack itself does NOT receive the key.
    """

    def oracle(iv, ciphertext):
        return poa.padding_oracle(
            iv,
            ciphertext,
            key
        )

    return oracle


# ------------------------------------------------------------
# Test 1: Single-block plaintext
# ------------------------------------------------------------

def test_single_block_plaintext():
    """
    Verify that the attack can recover a short plaintext.
    """

    key = poa.get_random_bytes(16)

    plaintext = b"Hello Padding!"

    iv, ciphertext = poa.encrypt_message(
        key,
        plaintext
    )

    oracle = make_oracle(key)

    recovered_padded = poa.padding_oracle_attack(
        iv,
        ciphertext,
        oracle
    )
    recovered=poa.pkcs7_unpad(recovered_padded)

    assert recovered == plaintext, (
        f"Expected {plaintext!r}, "
        f"but got {recovered!r}"
    )

    print("[PASS] Single-block plaintext recovery")


# ------------------------------------------------------------
# Test 2: Multi-block plaintext
# ------------------------------------------------------------

def test_multi_block_plaintext():
    """
    Verify recovery of plaintext spanning multiple AES blocks.
    """

    key = poa.get_random_bytes(16)

    plaintext = (
        b"Padding oracle attacks demonstrate how "
        b"small error messages can leak plaintext."
    )

    iv, ciphertext = poa.encrypt_message(
        key,
        plaintext
    )

    oracle = make_oracle(key)

    recovered_padded = poa.padding_oracle_attack(
        iv,
        ciphertext,
        oracle
    )
    recovered=poa.pkcs7_unpad(recovered_padded)
    assert recovered == plaintext, (
        f"Expected {plaintext!r}, "
        f"but got {recovered!r}"
    )

    print("[PASS] Multi-block plaintext recovery")


# ------------------------------------------------------------
# Test 3: Different plaintext lengths
# ------------------------------------------------------------

def test_different_plaintext_lengths():
    """
    Verify that the attack works for plaintexts of
    different lengths, including block boundaries.
    """

    test_messages = [
        b"A",
        b"123456789012345",
        b"1234567890123456",
        b"12345678901234567",
        b"Padding oracle testing",
        b"A" * 31,
        b"A" * 32,
        b"A" * 50,
    ]

    for plaintext in test_messages:

        key = poa.get_random_bytes(16)

        iv, ciphertext = poa.encrypt_message(
            key,
            plaintext
        )

        oracle = make_oracle(key)

        recovered_padded = poa.padding_oracle_attack(
            iv,
            ciphertext,
            oracle
        )
        recovered = poa.pkcs7_unpad(recovered_padded)
        assert recovered == plaintext, (
            f"Failed for plaintext length "
            f"{len(plaintext)}: "
            f"expected {plaintext!r}, "
            f"got {recovered!r}"
        )

    print("[PASS] Different plaintext lengths")


# ------------------------------------------------------------
# Test 4: Oracle query count
# ------------------------------------------------------------

def test_query_count():
    """
    Verify that the attack actually makes padding-oracle
    queries.

    The implementation may store the count globally.
    """

    key = poa.get_random_bytes(16)

    plaintext = b"Query count test for padding oracle."

    iv, ciphertext = poa.encrypt_message(
        key,
        plaintext
    )

    oracle = make_oracle(key)

    # Reset query counter if the implementation provides it.
    if hasattr(poa, "oracle_queries"):
        poa.oracle_queries = 0

    recovered_padded = poa.padding_oracle_attack(
        iv,
        ciphertext,
        oracle
    )
    recovered = poa.pkcs7_unpad(recovered_padded)
    assert recovered == plaintext

    if hasattr(poa, "oracle_queries"):

        assert poa.oracle_queries > 0

        print(
            f"[PASS] Oracle query count = "
            f"{poa.oracle_queries}"
        )

    else:
        print(
            "[PASS] Attack completed "
            "(oracle_queries variable not exposed)"
        )


# ------------------------------------------------------------
# Test 5: AES key isolation
# ------------------------------------------------------------

def test_key_is_not_passed_to_attack():
    """
    Verify that padding_oracle_attack() does not accept
    the AES key as an argument.

    This is important because the assignment requires
    the attacker to recover plaintext without knowing
    the encryption key.
    """

    signature = inspect.signature(
        poa.padding_oracle_attack
    )

    parameter_names = list(
        signature.parameters.keys()
    )

    assert "key" not in parameter_names, (
        "padding_oracle_attack() must not receive "
        "the AES key"
    )

    print(
        "[PASS] Attack function does not receive AES key"
    )


# ------------------------------------------------------------
# Main test runner
# ------------------------------------------------------------

if __name__ == "__main__":

    print("=" * 65)
    print(
        "AES-CBC PADDING ORACLE ATTACK - "
        "AUTOMATED VERIFICATION"
    )
    print("=" * 65)

    test_single_block_plaintext()

    test_multi_block_plaintext()

    test_different_plaintext_lengths()

    test_query_count()

    test_key_is_not_passed_to_attack()

    print("=" * 65)
    print("ALL TESTS PASSED")
    print("=" * 65)
