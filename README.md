# Hamming Code Assignment

## Overview

In this assignment, you will implement a Hamming code encoder, decoder, and validator. Hamming codes are a family of linear error-correcting codes that can detect and correct single-bit errors in data transmission.

## Objectives

1. **Encoding**: Implement a function that encodes a binary vector using Hamming codes
2. **Decoding**: Implement a function that decodes a Hamming code word, potentially correcting single-bit errors
3. **Validation**: Implement a function that checks whether a given binary vector is a valid Hamming code word

## Requirements

### Implementation

Your solution must:

- Be compiled into a single binary executable using a `Makefile`
- Accept command-line arguments to perform the three operations described below
- Handle binary vectors as input (sequences of 0s and 1s)
- Output results in the specified format

### Command-Line Interface

Your program must support three commands:

#### 1. Encode

**Command**: `encode m n bin_vec`

**Parameters**:
- `m`: Original length of the data vector (number of information bits)
- `n`: Length of the resulting encoded vector (number of total bits including check bits)
- `bin_vec`: Binary vector to encode (sequence of 0s and 1s, length must equal `m`)

**Output**: The encoded Hamming code word (binary vector of length `n`)

**Example**:
```bash
./hamming encode 4 7 1011
# Output: 1011010
```

#### 2. Decode

**Command**: `decode n bin_vec`

**Parameters**:
- `n`: Length of the encoded vector (total number of bits)
- `bin_vec`: Binary vector to decode (sequence of 0s and 1s, length must equal `n`)

**Output**: 
- First line: Number of check bits (parity bits) used in the code
- Second line: The decoded data word (binary vector, possibly with corrected errors)

**Example**:
```bash
./hamming decode 7 1011010
# Output:
# 3
# 1011
```

#### 3. Is Valid

**Command**: `is_valid n bin_vec`

**Parameters**:
- `n`: Length of the vector to check
- `bin_vec`: Binary vector to validate (sequence of 0s and 1s, length must equal `n`)

**Output**: 
- `1` if the vector is a valid Hamming code word
- `0` if the vector is not a valid Hamming code word

**Example**:
```bash
./hamming is_valid 7 1011010
# Output: 1
```

### Makefile

Your submission must include a `Makefile` that:
- Compiles your source code into a binary executable
- The binary should be named `hamming` (or as specified by your instructor)
- Should work with standard `make` command

**Example Makefile structure**:
```makefile
all:
	# Your compilation commands here

clean:
	# Cleanup commands
```

## Testing

Your solution will be tested automatically. The test suite is divided into three difficulty levels:

- **Lite**: Basic functionality tests with small vectors
- **Medium**: More complex scenarios with larger vectors and error correction
- **Hard**: Edge cases, large vectors, and stress tests

Make sure your implementation handles all cases correctly, including:
- Single-bit error detection and correction
- Valid code word validation
- Proper encoding and decoding of various input sizes

## Bonus Points

**Bonus**: Solutions implemented in Haskell will receive bonus points. However, the binary must still be executable and follow the same command-line interface specification.

## Submission Guidelines

1. Include all source code files
2. Include a `Makefile` that compiles your code
3. Ensure the binary executable works correctly with the command-line interface
4. Test your solution thoroughly before submission
5. Include any necessary documentation or comments in your code

## Notes

- The Hamming code implementation should follow standard Hamming code construction (systematic or non-systematic)
- Your decoder should be able to detect and correct single-bit errors
- The number of check bits `r` is determined by the relationship: `2^r >= n + 1` where `n` is the total length
- For encoding, ensure that `n = m + r` where `r` is the number of check bits needed

## Example Workflow

```bash
# Compile the project
make

# Encode a vector
./hamming encode 4 7 1011
# Output: 1011010

# Decode a vector (possibly with error)
./hamming decode 7 1011010
# Output:
# 3
# 1011

# Check if a vector is valid
./hamming is_valid 7 1011010
# Output: 1

# Clean up
make clean
```

Good luck!

