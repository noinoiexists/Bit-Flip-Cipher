# Bit Flip Cipher

Bit Flip Cipher is a simple encryption tool that encrypts text using a key-derived SHA-256 hash with XOR bit flipping. Since this is a symmetric cipher, decryption is performed using the same key that was used for encryption.
This tool was created as a fun project for me to learn more about C and Linux.

**Version**: 1.0.0

## How the Cipher Works

1. The user provides a key (password) for encryption/decryption.
2. A SHA-256 hash of the key is generated.
3. Each byte of the input text is XOR-ed with the corresponding byte from the hash (looping through the hash as needed).
4. The resulting text is the output.
5. Applying the process again with the same key will decrypt the text.

## Installation

As of now, a package file is available only for Debian-based distros (Debian, Ubuntu, Mint, Kali, etc) running on amd64/x86_64 systems and can be installed using **Method 1**. For other systems, you can follow **Method 2**.

### Method 1: Install via Debian Package ( `amd64` )

- Download the latest `.deb` package by running this command:
  ```sh
  wget https://github.com/noinoiexists/Bit-Flip-Cipher/releases/download/v1.0.0/bflip_1.0.0_amd64.deb
  ```
- Install it using your package manager (`apt`):
   ```sh
   sudo apt install ./bflip_1.0.0_amd64.deb
   ```
The tool is now installed and can be run as `bflip`.  
If you wish to install another version instead, you can download the respective `.deb` file from the [Releases](https://github.com/noinoiexists/Bit-Flip-Cipher/releases) page.

### Method 2: Compile from Source

**Requirements**:  `gcc`,  `make`,  `libssl-dev`
- Install the required tools and libraries using your package manager.
- Run the following commands:

```sh
wget https://github.com/noinoiexists/Bit-Flip-Cipher/archive/refs/heads/main.zip
unzip main.zip
cd Bit-Flip-Cipher-main
make
sudo make install
```

This will compile the binary and install it in `/usr/local/bin/`. It can be run as `bflip`.  
If you wish to install another version instead, you can download the respective `.zip` file from the [Releases](https://github.com/noinoiexists/Bit-Flip-Cipher/releases) page.

## Usage


`bflip -k <key> [text]`

Examples:  
 `bflip -k secretkey 'hello world'`  
 `bflip -k 'multi-word secretkey' 'hello world'`   
  `printf 'hello world' | bflip -k secretkey`  

```
Options:
  -k <key>      Specify the encryption/decryption key (string).
  -h, --help    Display the help menu.
  -v, --version Display the version information.
```


## Credits

This implementation was created by me, [noinoiexists](https\://github.com/noinoiexists). Kindly credit me if you use it anywhere or modify this code.

## Licence

This project is protected under the GNU Affero General Public Licence v3 (2007). You can learn more about it in the [LICENCE](https://github.com/noinoiexists/Bit-Flip-Cipher/blob/main/LICENSE) file.
