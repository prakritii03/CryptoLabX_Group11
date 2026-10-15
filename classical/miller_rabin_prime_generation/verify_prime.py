from pathlib import Path
from sympy import isprime

BITS = 512
BASES = [
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
    31, 37, 41, 43, 47, 53, 59, 61, 67, 71
]

n = int(Path("outputs/prime_candidate.txt").read_text().strip())

def miller_rabin_round(n, a):
    if n in (2, 3):
        return True
    if n < 2 or n % 2 == 0:
        return False

    d = n - 1
    s = 0
    while d % 2 == 0:
        d //= 2
        s += 1

    x = pow(a, d, n)
    if x in (1, n - 1):
        return True

    for _ in range(s - 1):
        x = x * x % n
        if x == n - 1:
            return True

    return False

round_results = [miller_rabin_round(n, a) for a in BASES]
sympy_result = isprime(n)
passed = (
    n.bit_length() == BITS
    and n % 2 == 1
    and all(round_results)
    and sympy_result
)

lines = [
    "Independent Prime Verification",
    f"Assigned bit length: {BITS}",
    f"Actual bit length: {n.bit_length()}",
    f"Odd candidate: {n % 2 == 1}",
    f"Number of Miller-Rabin bases: {len(BASES)}",
    f"Bases: {BASES}",
    f"Passed all Miller-Rabin rounds: {all(round_results)}",
    f"Passed rounds: {sum(round_results)} out of {len(BASES)}",
    f"SymPy isprime result: {sympy_result}",
    f"Final verification: {'PASS' if passed else 'FAIL'}"
]

report = "\n".join(lines) + "\n"
Path("outputs/verification_results.txt").write_text(report)
print(report)
