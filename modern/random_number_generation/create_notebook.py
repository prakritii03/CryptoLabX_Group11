
from pathlib import Path
import nbformat as nbf

nb = nbf.v4.new_notebook()

nb.cells = [
    nbf.v4.new_markdown_cell(
        "# Random Number Generator Analysis\n"
        "Comparison of Linux /dev/urandom, OpenSSL rand, "
        "and Windows .NET RandomNumberGenerator. "
        "Each input file should contain 1 MiB."
    ),
    nbf.v4.new_code_cell("""
from pathlib import Path
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.stats import chisquare, binomtest

files = {
    "Linux urandom": "linux_urandom.bin",
    "OpenSSL": "openssl_rand.bin",
    "Windows CNG": "windows_cng.bin"
}

data_dir = Path("data")
samples = {}

for name, filename in files.items():
    path = data_dir / filename
    if not path.exists():
        raise FileNotFoundError(f"Missing {path}. Run the generator scripts first.")
    samples[name] = np.fromfile(path, dtype=np.uint8)
    print(name, len(samples[name]), "bytes")
    assert len(samples[name]) == 1048576
"""),
    nbf.v4.new_markdown_cell("## Byte frequency distribution"),
    nbf.v4.new_code_cell("""
rows = []

fig, axes = plt.subplots(3, 1, figsize=(12, 8))

for ax, (name, data) in zip(axes, samples.items()):
    counts = np.bincount(data, minlength=256)
    chi, p = chisquare(counts)
    rows.append({
        "Generator": name,
        "Chi-square": chi,
        "Chi-square p-value": p,
        "Minimum frequency": counts.min(),
        "Maximum frequency": counts.max()
    })
    ax.bar(range(256), counts)
    ax.set_title(name)
    ax.set_xlabel("Byte value")
    ax.set_ylabel("Frequency")

plt.tight_layout()
plt.show()
display(pd.DataFrame(rows))
"""),
    nbf.v4.new_markdown_cell("## Bit balance"),
    nbf.v4.new_code_cell("""
rows = []

for name, data in samples.items():
    ones = int(np.unpackbits(data).sum())
    total = len(data) * 8
    result = binomtest(ones, total, 0.5)
    rows.append({
        "Generator": name,
        "Zero bits": total - ones,
        "One bits": ones,
        "One-bit percentage": ones * 100 / total,
        "P-value": result.pvalue
    })

display(pd.DataFrame(rows))
"""),
    nbf.v4.new_markdown_cell("## Repeated patterns and correlation"),
    nbf.v4.new_code_cell("""
rows = []

for name, data in samples.items():
    equal_adjacent = int(np.sum(data[1:] == data[:-1]))
    blocks = data[:len(data) // 16 * 16].reshape(-1, 16)
    _, counts = np.unique(blocks, axis=0, return_counts=True)
    duplicate_blocks = int(np.sum(counts - 1))
    correlation = np.corrcoef(
        data[:-1].astype(float), data[1:].astype(float)
    )[0, 1]

    rows.append({
        "Generator": name,
        "Equal adjacent bytes": equal_adjacent,
        "Duplicate aligned 16-byte blocks": duplicate_blocks,
        "Lag-1 correlation": correlation
    })

display(pd.DataFrame(rows))
"""),
    nbf.v4.new_markdown_cell(
        "## Conclusion\n"
        "Frequency, bit balance, repeated-block and correlation checks "
        "can reveal some statistical anomalies. Passing these tests does "
        "not prove cryptographic security. Security depends on the generator "
        "design, operating system, entropy sources and implementation."
    )
]

Path("notebooks").mkdir(exist_ok=True)
nbf.write(nb, "notebooks/analysis.ipynb")
print("Notebook created successfully.")
