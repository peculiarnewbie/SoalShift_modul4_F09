#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>

static const char *dirpath = "/home/peculiarnewbie/Desktop/modul4/folderthingy";
char charlist[] = "qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";
int key = 17;
int abkey = 0;

static int xmp_getattr(const char *path, struct stat *stbuf){
    printf("path getattr %s\n\n", path);
    char entr[] = "qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";
    int res, i, j, k;
    char fpath[1000];
    char content[1000];
    char encrypted[1000];
    memset(fpath, 0, sizeof(fpath));
    memset(content, 0, sizeof(content));
    memset(encrypted, 0, sizeof(encrypted));
    strcpy(content, path);
    for(i=0; i<strlen(content); i++){               //encrypting
        char charCheck = content[i];
        if(charCheck == '/'){
            encrypted[i] = charCheck;
            continue;
        }
        for(j=0;j<strlen(charlist); j++){
            if(charCheck == charlist[j]){
                int keyChar = j+key;
                keyChar = keyChar % strlen(charlist);
                encrypted[i] = charlist[keyChar];
            }
        }
    }

    printf("sebelum getattr: %s\n\n", fpath);

    sprintf(fpath,"%s%s",dirpath,encrypted);

    printf("setelah getattr: %s\n\n", fpath);

    res = lstat(fpath, stbuf);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi)
{
    printf("path readdir %s\n\n", path);
    char fpath[1001];
    memset(fpath, 0, sizeof(fpath));
    int res = 0;
    if(strcmp(path, "/") == 0){
        path=dirpath;
        sprintf(fpath, "%s", path);
    }
    else{
        //char entr[] = "qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";
        int i, j, k;
        //char fpath[1000];
        char content[1000];
        char encrypted[1000];
        
    memset(content, 0, sizeof(content));
    memset(encrypted, 0, sizeof(encrypted));
        strcpy(content, path);
        for(i=0; i<strlen(content); i++){               //encrypting
            char charCheck = content[i];
            if(charCheck == '/'){
                encrypted[i] = charCheck;
                continue;
            }
            for(j=0;j<strlen(charlist); j++){
                if(charCheck == charlist[j]){
                    int keyChar = j+key;
                    keyChar = keyChar % strlen(charlist);
                    encrypted[i] = charlist[keyChar];
                }
            }
        }
        sprintf(fpath,"%s%s",dirpath,encrypted);
        printf("setelah readdir: %s\n\n", fpath);
    }


	DIR *dp;
	struct dirent *de;

	(void) offset;
	(void) fi;

	dp = opendir(fpath);
	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL) {

        if((strcmp(".",de->d_name)==0||strcmp("..",de->d_name)==0)){
               continue; 
        }

        int i, j, k;
        //char fpath[1000];
        char content[1000];
        char decrypted[1000];
        memset(content, 0, sizeof(content));
        memset(decrypted, 0, sizeof(decrypted));
        strcpy(content, de->d_name);
        for(i=0; i<strlen(content); i++){               //decrypting
            char charCheck = content[i];
            if(charCheck == '/'){
                decrypted[i] = charCheck;
                continue;
            }
            for(j=0;j<strlen(charlist); j++){
                if(charCheck == charlist[j]){
                    int keyChar = j-key+strlen(charlist);
                    keyChar = keyChar % strlen(charlist);
                    decrypted[i] = charlist[keyChar];
                }
            }
        }
        strcpy(de->d_name, decrypted);
        printf("name setelah read: %s\n\n", de->d_name);
		struct stat st;
		memset(&st, 0, sizeof(st));
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;
		if (filler(buf, de->d_name, &st, 0))
			break;

	}

	closedir(dp);
	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
		    struct fuse_file_info *fi)
{
    printf("path read: %s\n\n", path);
  char fpath[1000];
    memset(fpath, 0, sizeof(fpath));
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
        printf("setelah read: %s\n\n", fpath);
	}
	else {
        int i, j, k;
        //char fpath[1000];
        char content[1000];
        char encrypted[1000];
        memset(content, 0, sizeof(content));
        memset(encrypted, 0, sizeof(encrypted));
        strcpy(content, path);
        for(i=0; i<strlen(content); i++){               //encrypting
            char charCheck = content[i];
            if(charCheck == '/'){
                encrypted[i] = charCheck;
                continue;
            }
            for(j=0;j<strlen(charlist); j++){
                if(charCheck == charlist[j]){
                    int keyChar = j+key;
                    keyChar = keyChar % strlen(charlist);
                    encrypted[i] = charlist[keyChar];
                }
            }
        }
        sprintf(fpath,"%s%s",dirpath,encrypted);
        printf("setelah read: %s\n\n", fpath);
    }
    int res = 0;
  int fd = 0 ;

	(void) fi;
	fd = open(fpath, O_RDONLY);
	if (fd == -1)
		return -errno;

	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}


static struct fuse_operations xmp_oper = {
	.getattr	= xmp_getattr,
	.readdir	= xmp_readdir,
	.read		= xmp_read,
};

int main(int argc, char *argv[])
{
    umask(0);
    return fuse_main(argc, argv, &xmp_oper, NULL);
}