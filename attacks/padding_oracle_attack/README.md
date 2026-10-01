\# Padding Oracle Attack



\## Objective



The objective of this experiment is to understand and demonstrate how a Padding Oracle Attack can recover plaintext from an AES-CBC encrypted message without knowing the AES encryption key.



\## AES-CBC



AES is a block cipher with a block size of 16 bytes. In CBC mode, each plaintext block is XORed with the previous ciphertext block before encryption.



For the first block, the IV is used:



C0 = IV



Encryption:



Ci = AES\_K(Pi XOR C(i-1))



Decryption:



Pi = AES\_K^-1(Ci) XOR C(i-1)



Because the previous ciphertext block is XORed with the decrypted block, modifying it changes the resulting plaintext.



\## PKCS#7 Padding



AES requires data to be a multiple of 16 bytes. PKCS#7 padding adds bytes so that the plaintext length becomes a multiple of the block size.



For example, if 3 padding bytes are required:



03 03 03



If 1 padding byte is required:



01



Valid padding therefore has a predictable structure.



\## Padding Oracle



A padding oracle is a system that reveals whether the decrypted ciphertext contains valid PKCS#7 padding.



The oracle returns only whether the padding is valid or invalid.



The AES key is not provided to the attacker.



\## Attack Principle



The attack targets one ciphertext block at a time.



For a target block Ci:



Pi = Dk(Ci) XOR C(i-1)



The attacker modifies C(i-1) while keeping Ci unchanged.



For every plaintext byte, the attacker tries different values until the padding oracle reports valid padding.



The attack begins with the last byte and proceeds from right to left.



For padding value 01, the attacker searches for:



... 01



For padding value 02:



... 02 02



For padding value 03:



... 03 03 03



This process continues until the complete plaintext block is recovered.



\## Intermediate Value



Let:



Ii = Dk(Ci)



Then:



Pi = Ii XOR C(i-1)



Once the attacker discovers the modified previous ciphertext byte that produces valid padding, the intermediate byte can be calculated.



Ii\[j] = modified\_C(i-1)\[j] XOR padding\_value



The original plaintext byte is then:



Pi\[j] = Ii\[j] XOR C(i-1)\[j]



\## Query Process



For each byte, the attack tries possible byte values from 0 to 255.



The padding oracle is queried for each candidate.



When valid padding is obtained, the corresponding intermediate byte and plaintext byte are recovered.



The process is repeated from the last byte toward the first byte.



\## Why Modifying the Previous Ciphertext Block Works



CBC decryption is:



Pi = Dk(Ci) XOR C(i-1)



If C(i-1) is modified, the AES decryption of Ci does not change, but the XOR operation changes the plaintext.



Therefore, the attacker can deliberately manipulate the plaintext of the target block.



\## Oracle Query Count



The program maintains a counter for every call made to the padding oracle.



The theoretical maximum for recovering one 16-byte block is approximately:



16 × 256 = 4096 oracle queries



The actual number is usually lower because the correct byte may be found before all 256 possibilities are tested.



The exact number of queries is recorded in the program output.



\## Result



The attack successfully recovers the plaintext without directly accessing the AES key.



The original plaintext and recovered plaintext are compared to verify successful recovery.



\## Security Recommendations



Padding oracle attacks can be prevented by avoiding systems that reveal padding validity.



Recommended protections include:



1\. Use authenticated encryption such as AES-GCM.

2\. Authenticate ciphertext before accepting decrypted plaintext.

3\. Do not expose different error messages for padding and authentication failures.

4\. Use consistent failure behavior for invalid ciphertext.

5\. Avoid unauthenticated CBC encryption for applications where ciphertext can be modified by an attacker.



\## Conclusion



A Padding Oracle Attack demonstrates that even when the AES key remains secret, revealing whether CBC padding is valid can provide enough information to recover plaintext.



The attack exploits the CBC decryption equation and repeatedly modifies the previous ciphertext block until valid padding is produced.

