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


Problem 1: 
Because the echo command is disabled for the duration of the password input.

Problem 2: 
So that the attacker does not get any info on what users exists on the system.

Problem 3:
So that an attacker cannot brute force passwords to login
Two step verification.

Proboem 4:
If you are the real user, you might accidentally be locked out.

Problem 5:
The program can get into unexpected states.

Problem 6: 
code

Problem 7: 
The real user of a program is the user who initiated the process. The effective user
is then the child of that process we just created.

Problem 8:
uid: 1000
gid: 1000
group: 1000
Because when forking a process, the main process is copied which becomes the child process.
Starting a new process is also a privilege of root

Problem 9:
owner linuxuser
user: rwx
group: rwx
others: r-x

Problem 10:
It changes the owner of the file to root
We can no longer change permissions of the file.

Problem 11:
uid =2001
guid = 2001
We need to setguid before setuid since if we change uid first, we wont have permissions to set
guid afterwards. Since we are effective root user in the beginning (file owner)

Problem 12:
--x:
cd works
list doesnt work
display works
creating copy doesnt work

Problem 13:
r--:
cd no
list no
display no
copy no

r-x:
cd yes
list yes
display yes
copy no

rwx:
cd yes
list yes
display yes
copy yes

Problem 14:
you need write permission

Problem 15:
1: no
2: no
3: yes
4: no
5: no
6: no
7: no
8: yes
9: no
10: no
11: no 
12: no
13: no
14: no
15: no

Problem 16:
Cant read any.
3: facl sets group perm to ---
8: facl sets group permission to ---
13: 13 works, since ACL sets r for group students
10: doesnt work, r is for group students

Problem 17:

Problem 18:
bob: chmod u+s hello
