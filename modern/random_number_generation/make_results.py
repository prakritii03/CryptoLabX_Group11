
import numpy as np
import pandas as pd
from pathlib import Path
from scipy.stats import chisquare, binomtest

files = {
    "Linux urandom": "../data/linux_urandom.bin",
    "OpenSSL": "../data/openssl_rand.bin",
    "Windows CNG": "../data/windows_cng.bin"
}

rows = []

for name, filename in files.items():
    p = Path(filename)
    if not p.exists():
        p = Path("data") / Path(filename).name
    data = np.fromfile(p, dtype=np.uint8)

    if len(data) != 1048576:
        raise ValueError(f"Wrong file size: {p}")

    counts = np.bincount(data, minlength=256)
    bits = np.unpackbits(data)
    ones = int(bits.sum())
    blocks = data[:len(data)//16*16].reshape(-1, 16)
    _, freq = np.unique(blocks, axis=0, return_counts=True)

    rows.append({
        "Generator": name,
        "Bytes": len(data),
        "Chi-square": chisquare(counts).statistic,
        "Chi-square p-value": chisquare(counts).pvalue,
        "Zero bits": len(bits) - ones,
        "One bits": ones,
        "One-bit percentage": 100 * ones / len(bits),
        "Bit-balance p-value": binomtest(ones, len(bits), 0.5).pvalue,
        "Equal adjacent bytes": int(np.sum(data[1:] == data[:-1])),
        "Duplicate 16-byte blocks": int(np.sum(freq - 1)),
        "Lag-1 correlation": float(np.corrcoef(
            data[:-1].astype(float), data[1:].astype(float)
        )[0, 1])
    })

Path("results").mkdir(exist_ok=True)
pd.DataFrame(rows).to_csv("results/statistical_summary.csv", index=False)
print(pd.DataFrame(rows).to_string(index=False))
print("Saved results/statistical_summary.csv")
