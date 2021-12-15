# Huffman Compressor
Utility for lossles compression of any file
## Principles
Program uses huffman trees to assess frequency of bytes in file, encode them such as the most frequent byte has the shortst code and write it to output
## Usage
### Check entropy of a file
```./Huffman entropy -input file.txt```
### Compress file
```./Huffman compress -input file.txt -output file.cmp```
### Decompress file
```./Huffman decompress -input file.cmp -output file2.txt```
## Recommendations
Most commonly used files are already very well compressed (entropy >7) as such the gains using program are usually minute or even detrimental.
The best target are .txt files, and any format that stores plaintext