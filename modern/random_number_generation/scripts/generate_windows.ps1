$ErrorActionPreference = "Stop"

$OutputDir = Join-Path $PSScriptRoot "..\data"
New-Item -ItemType Directory -Force -Path $OutputDir | Out-Null

$OutputFile = Join-Path $OutputDir "windows_cng.bin"
$RandomBytes = New-Object byte[] 1048576
$Rng = [System.Security.Cryptography.RandomNumberGenerator]::Create()

try {
    $Rng.GetBytes($RandomBytes)
    [System.IO.File]::WriteAllBytes($OutputFile, $RandomBytes)
}
finally {
    $Rng.Dispose()
}

Write-Host "Generated Windows cryptographic random data:"
Get-Item $OutputFile | Select-Object Name, Length
