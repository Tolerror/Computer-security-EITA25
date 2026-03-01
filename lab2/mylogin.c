/*
 * Shows user info from local pwfile.
 *  
 * Usage: userinfo username
 */
#define _GNU_SOURCE
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pwdblib.h"   /* include header declarations for pwdblib.c */
#include <crypt.h>
#include <signal.h>
#include <sys/wait.h>

/* Define some constants. */
#define USERNAME_SIZE (32)
#define NOUSER (-1)
#define PROGRAM "/usr/bin/kitty"


int print_info(const char *username)
{
  struct pwdb_passwd *p = pwdb_getpwnam(username);
  if (p != NULL) {
    printf("Name: %s\n", p->pw_name);
    printf("Passwd: %s\n", p->pw_passwd);
    printf("Uid: %u\n", p->pw_uid);
    printf("Gid: %u\n", p->pw_gid);
    printf("Real name: %s\n", p->pw_gecos);
    printf("Home dir: %s\n",p->pw_dir);
    printf("Shell: %s\n", p->pw_shell);
	return 0;
  } else {
    return NOUSER;
  }
}

void read_username(char *username)
{

  printf("login: ");
  fgets(username, USERNAME_SIZE, stdin);

  /* remove the newline included by getline() */
  username[strlen(username) - 1] = '\0';
}

int login_procedure(char* username){

    /* 
   * Write "login: " and read user input. Copies the username to the
   * username variable.
   */

    while(1){
        read_username(username);
        struct pwdb_passwd* p = pwdb_getpwnam(username);

        if(p == NULL){  //in case of interrupt
            continue;
        }

        if(p->pw_failed >= 3){
            printf("User blocked\n");
            return 0;
        }


        char* input_pwd = getpass("Enter password: ");

        if(p->pw_age >= 5)
            printf("Please reset your password.\n");

        if(p == NULL){
            printf("\nUnknown user or incorrect password.\n");
            continue;
        }

        char salt[3];
        strncpy(salt, p->pw_passwd, 3);
        salt[2] = '\0';
        char* hashed_pw = crypt(input_pwd, salt);
        int passwd_cmp = strcmp(p->pw_passwd, hashed_pw);   //0 on success
        if(strcmp(p->pw_name, username) || passwd_cmp){

            if(passwd_cmp){
                p->pw_failed++;
                if(pwdb_update_user(p) != 0)
                    printf("pwdb_update_user returned error %s\n", pwdb_err2str(pwdb_errno));
            }
                
            if(p->pw_failed >= 3){
                printf("failed 3 times\n");
            }

            printf("Unknwon user or incorrect password.\n");
            continue;
        }

        printf("User authenticated successfully\n");
        p->pw_failed = 0;
        p->pw_age++;
        if(pwdb_update_user(p) != 0)
            printf("pwdb_update_user returned error %s\n", pwdb_err2str(pwdb_errno));

        break;
    }
    return 1;
}

int update_user(int argc, char** argv){

    char* username;
    char* buf = NULL;
    size_t buflen = 0;
    size_t chread;
    struct pwdb_passwd *p, *oldp;

    // if(argc < 2){
    //     printf("Usage: update_user username\n");
    //     return 0;
    // }

    int user_exist = 0;

    username = argv[1];
    oldp = pwdb_getpwnam(username);
    if(oldp != NULL){
        user_exist = 1;     //user exists
    }else if(oldp == NULL && pwdb_errno == PWDB_NOUSER){
        user_exist = 0;     //user doesn't exist and pwdb_getpwnam succeeded
    }else{
        printf("pdwb_getpwnam error: %s\n", pwdb_err2str(pwdb_errno));  
        return 0;
    }

    p = (struct pwdb_passwd*) malloc(sizeof(struct pwdb_passwd));

    p->pw_name = username; 

    chread = 0;
    while(1){
        printf("Enter New Password: ");
        chread = getline(&buf, &buflen, stdin);
        buf[chread] = '\0';
        chread--;

        if(!user_exist && chread < 1)   //user doesnt exist & nothing was read
            printf("New user, you must enter data\n");

        if(user_exist && chread < 1){   //user exists already, default value chosen. Use old
            p->pw_passwd = oldp->pw_passwd; 
            break;
        }

        if(chread > 0){ //there is input
            p->pw_passwd = (char*) malloc(sizeof(char)*(chread+1));
            strncpy(p->pw_passwd, buf, chread);
            p->pw_passwd[chread] = '\0';
            break;
        }
    }

    chread = 0;
    while(1){
        printf("Enter New UID: ");
        chread = getline(&buf, &buflen, stdin);
        buf[chread] = '\0';
        chread--;

        if(!user_exist && chread < 1)
            printf("New user, you must enter data\n");

        if(user_exist && chread < 1){
            p->pw_uid = oldp->pw_uid;
            break;
        }

        if(chread > 0){
            p->pw_uid = atoi(buf);  //convert stringg to int
            break;
        }
    }

    chread = 0;
    while(1){
        printf("Enter New GID: ");
        chread = getline(&buf, &buflen, stdin);
        buf[chread] = '\0';
        chread--;

        if(!user_exist && chread < 1)   //user doesnt exist & nothing was read
            printf("New user, you must enter data\n");

        if(user_exist && chread < 1){   //user exists already, default value chosen. Use old
            p->pw_gid = oldp->pw_gid; 
            break;
        }

        if(chread > 0){ //there is input
            p->pw_gid = atoi(buf);
            break;
        }
    }

    chread = 0;
    while(1){
        printf("Enter New Name: ");
        chread = getline(&buf, &buflen, stdin);
        buf[chread] = '\0';
        chread--;

        if(!user_exist && chread < 1)   //user doesnt exist & nothing was read
            printf("New user, you must enter data\n");

        if(user_exist && chread < 1){   //user exists already, default value chosen. Use old
            p->pw_gecos = oldp->pw_gecos; 
            break;
        }

        if(chread > 0){ //there is input
            p->pw_gecos = (char*) malloc(sizeof(char)*(chread+1));
            strncpy(p->pw_gecos, buf, chread);
            p->pw_gecos[chread] = '\0';
            break;
        }
    }

    chread = 0;
    while(1){
        printf("Enter New Home directory: ");
        chread = getline(&buf, &buflen, stdin);
        buf[chread] = '\0';
        chread--;

        if(!user_exist && chread < 1)   //user doesnt exist & nothing was read
            printf("New user, you must enter data\n");

        if(user_exist && chread < 1){   //user exists already, default value chosen. Use old
            p->pw_dir = oldp->pw_dir; 
            break;
        }

        if(chread > 0){ //there is input
            p->pw_dir = (char*) malloc(sizeof(char)*(chread+1));
            strncpy(p->pw_dir, buf, chread);
            p->pw_dir[chread] = '\0';
            break;
        }
    }

    chread = 0;
    while(1){
        printf("Enter New Shell: ");
        chread = getline(&buf, &buflen, stdin);
        buf[chread] = '\0';
        chread--;

        if(!user_exist && chread < 1)   //user doesnt exist & nothing was read
            printf("New user, you must enter data\n");

        if(user_exist && chread < 1){   //user exists already, default value chosen. Use old
            p->pw_shell = oldp->pw_shell; 
            break;
        }

        if(chread > 0){ //there is input
            p->pw_shell = (char*) malloc(sizeof(char)*(chread+1));
            strncpy(p->pw_shell, buf, chread);
            p->pw_shell[chread] = '\0';
            break;
        }
    }

    chread = 0;
    while(1){
        printf("Enter New Failed: ");
        chread = getline(&buf, &buflen, stdin);
        buf[chread] = '\0';
        chread--;

        if(!user_exist && chread < 1)   //user doesnt exist & nothing was read
            printf("New user, you must enter data\n");

        if(user_exist && chread < 1){   //user exists already, default value chosen. Use old
            p->pw_failed= oldp->pw_failed; 
            break;
        }

        if(chread > 0){ //there is input
            p->pw_failed = atoi(buf);
            break;
        }
    }

    chread = 0;
    while(1){
        printf("Enter New Age: ");
        chread = getline(&buf, &buflen, stdin);
        buf[chread] = '\0';
        chread--;

        if(!user_exist && chread < 1)   //user doesnt exist & nothing was read
            printf("New user, you must enter data\n");

        if(user_exist && chread < 1){   //user exists already, default value chosen. Use old
            p->pw_age= oldp->pw_age; 
            break;
        }

        if(chread > 0){ //there is input
            p->pw_age = atoi(buf);
            break;
        }
    }

    if(pwdb_update_user(p) != 0){
        printf("pwdb_update_user error: %s\n", pwdb_err2str(pwdb_errno));
    }

return 0;
}

int main(int argc, char **argv){

    char username[USERNAME_SIZE];
    int status = 0;


    while(1){
        signal(SIGINT, SIG_IGN);    //disable SIGINT

        if(!login_procedure(username)){ //if login fails
            return 0;
        }
        signal(SIGINT, SIG_DFL);    //enable SIGINT

        struct pwdb_passwd* p = pwdb_getpwnam(username);
        if(p == NULL) return 0;

        pid_t pid;
        pid = fork();

        if(pid == 0){ //child process

            setgid(p->pw_gid);
            setuid(p->pw_uid);

            execl(PROGRAM, PROGRAM, "-e", p->pw_shell, "-l", NULL);
            _exit(-1);
        }else if(pid < 0){
            printf("fork() failed\n");
            status = -1;
        }else{
            if(waitpid(pid, &status, 0) != pid){
                status = -1;
            }else{
                // login_procedure(username);
            }
        }

        if(argc == 2)
            update_user(argc, argv);

    }
    

    return status;







    /* Show user info from our local pwfile. */
    // if (print_info(username) == NOUSER) {
    //     /* if there are no user with that usename... */
    //     printf("\nFound no user with name: %s\n", username);   
    //     return 0;
    // }
}


  
