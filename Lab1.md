Prep Assignment 1:
# What is a brute force attack?
A brute force attack is an attack that goes the "long way" of systematically guessing every combination to crack a password.

# What is a dictionary attack?
It is like brute force in systematically guessing but by some commonly used passwords. Common passwords like abc123.

# What is a time memory tradeoff attack?
It is an attack where the majority of the computation is done before the attack, "offline" so to speak.
Then during the attack, the attacker uses the precomputed data to reduce computation time during the attack.
The memory tradeoff comes from storing all the precomputed data.
The computed data can be all possible hashed values from a password of length n. 
Then during attack, it is simply a matter of lookup in the precomputed hashed table to find a match to the hash to be cracked.

# What is the difference between a rainbow table and an ordinary time memory tradedoff table?
A rainbow table does not store every possible hashed value but instead contain several chains consisting of a starting password and an end result hash value pair.
The chain computes the hash of the initial plaintext password into a hash value, which is then reduced with a reduction function which gives a new potential password
and then hashed again forming a new hashed value, and so on. The to be cracked hashed password is looked up in the rainbow table to find a matching hash value.
If no matches, you reduce the hashed value and hash it again. You check for each iteration if you find a matching hash value in any of your chains.
Once a matching hash value is found you simply recompute that chain till you get the same hash value and the previous password is the original password.


Prep Assignment 2:
# How is the LAN Manager (LM) hash produced, how is this hash used to authenticate a user, and what is the effective security of LM?
How the hash is produced:
1. The password is restricted to max 14 characters.
2. Password is converted to upper case.
3. Password is encoded.
4. Password is NULL padded to 14 bytes.
5. The fixed length password is split into 2 halves, 7 bytes each.
6. The two halves are used to create two DES keys from each half. 
    The 7 bytes are converted into a bitstream with the most significant bit first, inserting a parity bit
    after every 7th bit. Creating a 64 bit DES key. 
7. The DES keys are each applied to a particular ASCII string constant, giving two 8 byte ciphertexts.
8. The two ciphertexts are concatenated to a 16 byte value, which is the hash.

The effective security comes from the DES encrpytion of the string constant, yielding the two ciphertexts.
Or the challenge sent by the server.

Authentication of a user is done by sending a challenge, random 8 bytes which the client needs to encrypt
with the hash computed from the inputted password. The encrypted challenge is the response back to the server.
The server looks up the stored hash for that user, encrypts the same challenge and checks if it matches the response.

# How is the NT LAN Manager Version 1 (NTLM) hash produced, how is this hash used to authenticate a user, and what is the effective security of NTLM?
How the hash is produced:
1. Password is encoded with unicode.
2. The encoded password is passed once through MD4 which gives a 16 byte hash.

The effective security comes from the MD4 passthrough, the hash produced so to speak is the key.
Or the challenge sent by the server.

Authentication of a user is done by the server sending a challenge, random 8 byte number which the client needs to encrypt
with its own hash. The client responds with a 24 byte result which the server matches with its own computation of the same challenge with the hashed password.

# Ensure that you understand what a salt is, and why it is used.
A salt is random data that is fed into some input to a one way function that produces a hash. It is used to defend against time memory tradeoff attacks
such as rainbow tables. By adding a random salt to the input before hashing, the table size needed for an attack increases dramatically. 
The randomly generated salt is stored alongside the hashed input.

# PBKDF2
Is a key derivation function that applies a pseudorandom function (PRF) to the input password alongside a salt, which prdocues a derived key.
The function is applied many times to make the cracking of passwords more computationally expensive to combat brute force attacks. 
The process is also called key stretching.

The pseudorandom function used in PBKDF2 can be configured to use SHA-1. 
SHA-1 is a fast hashing function that produces a single hash from input. 
Depending on the number of iterations specified in the arguemtn for the PBKDF2 function, 
the PBKDF2 is that many times slower than SHA-1. Say 10,000 iterations in PBKDF2 would make it 10,000 times slower than SHA-1.
So in essence, the end result of PBKDF2 and SHA-1 is both a hash value, but one is intentionally much slower than the other to slow down brute force attacks.



