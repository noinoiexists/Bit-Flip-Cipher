# Bit Flip Cipher

Bit Flip Cipher is a simple cryptography tool that encrypts text using a key-derived SHA-256 hash with XOR bit flipping and gives a Base64 output. Since this is a symmetric cipher, decryption is performed using the same key that was used for encryption.
This tool was created as a fun project.

**Latest Version**: 1.1.0

## Disclaimer
This cipher was created for educational purposes and is definitely **not** secure.

## How the Cipher Works  

### Encryption
1. The user provides a key (password) and the text to be encrypted.
2. A SHA-256 hash of the key is generated.
3. Each byte of the input text is XOR-ed with the corresponding byte from the hash (looping through the hash as needed).
4. The resultant is encoded to Base64 to ensure that it is printable.
5. The Base64 ciphertext is the output.

### Decryption
1. The user provides a key (password) and the Base64 encoded text obtained from encryption.
2. The Base64 text is decoded back to the original XOR-ed encrypted form.
3. A SHA-256 hash of the key is generated.
4. Each byte of the encrypted text is XOR-ed with the corresponding byte from the hash (looping through the hash as needed). This produces the original text, as this process is symmetric.
5. The resultant plaintext is the output

## Installation

As of now, a package file is available only for Debian-based distros (Debian, Ubuntu, Mint, Kali, etc) and can be installed using **Method 1**. For others, you can follow **Method 2**.

### Method 1: Install via Debian Package

- Download the latest `.deb` package by running this command:
  ```sh
  wget https://github.com/noinoiexists/Bit-Flip-Cipher/releases/download/bflip-v1.1.0/bflip_1.1.0_amd64.deb
  ```
- Install it using your package manager (`apt`):
   ```sh
   sudo apt install ./bflip_1.1.0_amd64.deb && rm ./bflip_1.1.0_amd64.deb
   ```
The tool is now installed and can be run as `bflip`.  
**Note**: For ARM devices (Mac, Raspberry Pi, Mobile, etc), use the [arm64 package](https://github.com/noinoiexists/Bit-Flip-Cipher/releases/download/bflip-v1.1.0/bflip_1.1.0_arm64.deb) instead.

### Method 2: Compile from Source

**Requirements**:  `gcc`,  `make`, `git`, `libssl-dev`
- Install the required tools and libraries using your package manager.
- Clone this repository, compile and install the code:
  ```sh
  git clone https://github.com/noinoiexists/Bit-Flip-Cipher.git
  cd Bit-Flip-Cipher/
  make
  sudo make install
  ```

This will compile the binary and install it in `/usr/local/bin/`. It can be run as `bflip`.  

---
**Note**: If you wish to install a different version instead, replace the version numbers (vX.Y.Z) in the above steps with the one you want **or** you can find the respective files in the [Releases](https://github.com/noinoiexists/Bit-Flip-Cipher/releases) page.

## Usage

Encrypt: `bflip -k <key> [text]`  
Decrypt: `bflip -d -k <key> [base64_text]`

Examples:  
  `bflip -k secretkey 'hello world'`  
  `bflip -k 'multi-word secretkey' 'hello world'`   
  `echo -n 'hello world' | bflip -k secretkey`  
  `bflip -d -k secretkey 'BASE64_ENCODED_TEXT'`  

Options:  
```
  -k <key>      Specify the encryption/decryption key (string).
  -d            Decrypt bflip encrypted text (Base64 string).
  -h, --help    Display the help menu.
  -v, --version Display the version information.
```


## Credits

This implementation was created by me, [noinoiexists](https\://github.com/noinoiexists). Kindly credit me if you use it anywhere or modify this code.

## Licence

This project is protected under the MIT Licence. You can learn more about it in the [LICENCE](https://github.com/noinoiexists/Bit-Flip-Cipher/blob/main/LICENSE) file.
