# Preparatory assignment 1: 
read

# Preparatory assignment 2:
The difference is that in the pwfile we have 2 additional fields at the end, pw_failed and pw_age. 
Where pw_failed is the number of contigious failed logins, and pw_age is the number of successful logins.

# Preparatory assignment 3:
code

# Preparatory assignment 4:
code

# Preparatory assignment 5:
setuid - sets the actual uid permanently meaning both euid and uid.
seteuid - sets only the euid, meaning temporary permission.

# Preparatory assignment 6:
code

# Preparatory assingment 7:
chmod, chown, chgrp

# Preparatory assignment 8:
getfacl = read ACLs of a file/dir
setfacl = set ACLs of a file/dir
example: setfacl -m u:bob:x file.txt
give user bob execute rights to file.txt
-m = mody/add ACL entry
-x = remove ACL entry
