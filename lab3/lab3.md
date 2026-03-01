## Preparatory assignment 1:
- Read gpg.
- Symmetric cryptography: Using the same key for encrypted and decrypted messages. Annoying to distribute key.
- Hash functions: One way functions to map arbitrary input to fixed size output.
- Signatures: 
Alice hashes message M. h = hash(M)
She encrypts h with her private key and sends to Bob.

Bob decrypts with Alice's public key. 
Compares the hashed M in the encryption with the message he hashes himself.
If they match it is authentic.

GPG commands:
create keypair:
gpg --gen-key

generate key revocation cert:
gpg --output revoke.asc --gen-revoke <mykey>
where mykey is the specified ID of the keypair.

list keys:
gpg --list-keys

Export public key:
gpg --output alice.gpg --export alice@cyb.org
where alice.gpg is name of output.
alice@cyb.org is a specified ID to the keypair

adding the --armor flag outputs the file in ASCII armored format.
gpg --armor --export alice@cyb.org

Import public key:
gpg --import blake.gpg

should validate key after importing:
gpg --edit-key blake@cyb.org
gpg> fpr (fingerprint)

Sign public key:
gpg> sign

Check key signatures:
gpg> check

Encrypt document:
gpg --output doc.gpg --encrypt --recipient blake@cyb.org doc

Decrypt document:
gpg --output doc --decrypt doc.gpg

Sign document:
gpg --output doc.sig --sign doc

Check signature and verify:
gpg --verify doc.sig

Check signature and recover document:
gpg --output doc --decrypt doc.sig

## Preparatory assignment 2:
A key revocation certificate is a certificate that states that the public key associated
with this certificate should no longer be trusted. You often create it in advance in the case
of ur key getting compromised in the future.
Its made with the private key, meaning no one but you can revoke the key pair.

## Preparatory assignment 3:
Web of trust is a decentralized trust model, unlike certificates like X.509 that
uses central authorities.
The point is that trust spreads between users.
Users vouch for each others trust like a web. There are different levels of trust you can have in others.
Uknown: you dont know yet
None: you dont trust this user in certifying others
Marginal: not quite trusting, but if the other user gets enough marginal signatures from others, you only then trust them.
Full: trust fully, their signature is enough to certify another user.
Ultimate: only your own key is ultimately trusted.

Commands:
set trust:
gpg --edit-key key_id
gpg> trust

sign key:
gpg --sign-key key_id
gpg --lsign-key key_id (only local trust, not shared)

Difference between trust and validity: 
trust is something you set to a key owner (another user Bob).
validity is about the validity of the key. GPG calculates based on ur trust settings 
Does this key really belong to Alice? It is the calculation for key validation where trust is the settings.

## Preparatory assignment 4:
Nmap Commands:
Ping scan:
nmap -sn <ip to scan>

Port scan:
nmap <ip to scan>
or 
nmap <domain to scan> "example.com"

specific port/s:
nmap -p 22,80,443 <ip to scan>

## Preparatory assignment 5:
Firewall: A network security tool to control incoming and outgoing traffic on a system or network.
Decides what packets are block or allowed to pass.
Hardware firewalls - standalone devices often network perimeter.
Software firewalls - run on the host OS, like iptables

iptables:
Utility for configuring firewall filter.
You can define rules for packets:
ACCEPT: accept packet
DROP: silently drop packet
REJECT: drop and send error

flags:
-A: append rule to input chain //end of chain
-I: insert rule at the top of input chain
-D: delete specific rule from input chain
-P: default policy for INPUT chain to drop  //default if nothing matches in the chain
-s <ip>: match source IP address
-d <ip>: match desination ip address
-p tcp: match specific source port

## Preparatory assignment 6:
POP3: retrieve email from mail server to local client
SMTP: relay email between servers or client to server. Handles sending email not reading
telnet: remote text based access to computer. Legacy remote administration
FTP: Transfer files between client and server over network. Upload/download files
SSH: Secure remote login and command execution. Encrypted channel for text based commands like file transfers (SCP, SFTP)

