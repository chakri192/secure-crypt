# secure-crypt 🔐

A fast, lightweight CLI utility written in C that encrypts and decrypts files using an XOR cipher. Built with buffered I/O for performance and proper error handling throughout.

> ⚠️ **Note:** XOR encryption with a single-byte key is not cryptographically secure. This project is intended for learning, obfuscation, or CTF use cases — not for protecting sensitive production data.

---

## Features

- Encrypts any file type (binary or text) using XOR
- Decrypts `.enc` files back to their original content
- Buffered I/O — handles large files efficiently
- Clean error messages and exit codes
- CI pipeline via GitHub Actions

---

## Requirements

- GCC or Clang
- GNU Make
- Linux or macOS

---

## Build

```bash
git clone https://github.com/chakri192/secure-crypt.git
cd secure-crypt
make
```

This produces a `crypt` binary in the project directory.

---

## Usage

```bash
./crypt <filename> <key>
```

| Argument   | Description                          |
|------------|--------------------------------------|
| `filename` | Path to the file you want to encrypt |
| `key`      | Integer key (0–255) used for XOR     |

### Example

```bash
# Encrypt a file
./crypt secret.txt 42

# This produces:
#   secret.txt.enc   — encrypted output
#   secret.txt.dec   — decrypted verification copy
```

To decrypt an `.enc` file, run the same command with the same key:

```bash
./crypt secret.txt.enc 42
# Produces: secret.txt.enc.dec (the original content)
```

> XOR is its own inverse — encrypting twice with the same key restores the original data.

---

## How It Works

The program reads the input file in 1 KB chunks and XORs every byte with the provided key. Since XOR is symmetric, the same operation decrypts the file.

```
byte_out = byte_in XOR key
```

The encrypted file is written to `<filename>.enc`. The program then immediately reads that file back and decrypts it to `<filename>.dec` to verify correctness.

---

## Project Structure

```
secure-crypt/
├── crypt.c              # Core encryption/decryption logic
├── Makefile             # Build instructions
├── .github/workflows/   # CI pipeline
└── .gitignore
```

---

## Limitations & Future Improvements

- [ ] Add a separate `enc` / `dec` mode flag so encrypt and decrypt are independent operations
- [ ] Support multi-byte string keys (Vigenère-style) for stronger obfuscation
- [ ] Add `--in-place` flag to overwrite the original file
- [ ] Add progress output for large files

---

## License

MIT License — see [LICENSE](LICENSE) for details.
