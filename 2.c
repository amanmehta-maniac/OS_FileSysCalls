#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
//user defined function using system call write to perform a function similar to printf in c
void ferr(char *err){
	write(STDERR_FILENO,err,strlen(err));return;
}
int main(int argc,char *argv[])
{
	if(argc!=2) ferr("Err: This program requires exactly 2 arguments\nUsage: ./a.out <inputFilename>\n");
	char *outFile;
	struct stat yy;
	int err1 = stat("./Assignment",&yy);
	if(err1==-1) ferr("Checking whether directory has been created: No\n");
	else ferr("Checking whether directory has been created: Yes\n");
//	chdir("../");
	//assuming length of argv is less than 
	char str1[10000];
//"+10" just to be on safe side
	char str2[strlen(argv[1])+10];
	char *fstr;
	strcpy(str1,"./Assignment/output_");
	strcpy(str2, argv[1]);
	fstr = strcat(str1,str2);
	//check for creation of output file
	int outCheck = open(fstr,O_RDONLY);
	if(outCheck == -1)
	{
		ferr("Checking whether the file has been created: No\n");
	}
	else 
		ferr("Checking whether the file has been created: Yes\n");
	struct stat y;
	stat(fstr,&y);
	if(y.st_mode & S_IRUSR)
		ferr("Checking whether output file has permission to read for owner: Yes\n");
	else
		ferr("Checking whether output file has permission to read for owner: No\n");
	if(y.st_mode & S_IWUSR)
		ferr("Checking whether output file has permission to write for owner: Yes\n");
	else
		ferr("Checking whether output file has permission to write for owner: No\n");
	if(y.st_mode & S_IXUSR)
		ferr("Checking whether output file has permission to execute for owner: Yes\n");
	else
		ferr("Checking whether output file has permission to execute for owner: No\n");
	if(y.st_mode & S_IRGRP)
		ferr("Checking whether output file has permission to read for owner's group members: Yes\n");
	else
		ferr("Checking whether output file has permission to read for owner's group members: No\n");
	if(y.st_mode & S_IWGRP)
		ferr("Checking whether output file has permission to write for owner's group members : Yes\n");
	else
		ferr("Checking whether output file has permission to write for owner's group members: No\n");
	if(y.st_mode & S_IXGRP)
		ferr("Checking whether output file has permission to execute for owner's group members: Yes\n");
	else
		ferr("Checking whether output file has permission to execute for owner's group members: No\n");
	if(y.st_mode & S_IROTH)
		ferr("Checking whether output file has permission to read for others: Yes\n");
	else
		ferr("Checking whether output file has permission to read for others: No\n");
	if(y.st_mode & S_IWOTH)
		ferr("Checking whether output file has permission to write for others: Yes\n");
	else
		ferr("Checking whether output file has permission to write for others: No\n");
	if(y.st_mode & S_IXOTH)
		ferr("Checking whether output file has permission to execute for others: Yes\n");
	else
		ferr("Checking whether output file has permission to execute for others: No\n");
	struct stat z;
	stat("./Assignment",&z);
	if(z.st_mode & S_IRUSR)
		ferr("Checking whether directory has permission to read for owner: Yes\n");
	else
		ferr("Checking whether directory has permission to read for owner: No\n");
	if(z.st_mode & S_IWUSR)
		ferr("Checking whether directory has permission to write for owner: Yes\n");
	else
		ferr("Checking whether directory has permission to write for owner: No\n");
	if(z.st_mode & S_IXUSR)
		ferr("Checking whether directory has permission to execute for owner: Yes\n");
	else
		ferr("Checking whether directory has permission to execute for owner: No\n");
	if(z.st_mode & S_IRGRP)
		ferr("Checking whether directory has permission to read for owner's group members: Yes\n");
	else
		ferr("Checking whether directory has permission to read for owner's group members: No\n");
	if(z.st_mode & S_IWGRP)
		ferr("Checking whether directory has permission to write for owner's group members : Yes\n");
	else
		ferr("Checking whether directory has permission to write for owner's group members: No\n");
	if(z.st_mode & S_IXGRP)
		ferr("Checking whether directory has permission to execute for owner's group members: Yes\n");
	else
		ferr("Checking whether directory has permission to execute for owner's group members: No\n");
	if(z.st_mode & S_IROTH)
		ferr("Checking whether directory has permission to read for others: Yes\n");
	else
		ferr("Checking whether directory has permission to read for others: No\n");
	if(z.st_mode & S_IWOTH)
		ferr("Checking whetherdirectorye has permission to write for others: Yes\n");
	else
		ferr("Checking whether directory has permission to write for others: No\n");
	if(z.st_mode & S_IXOTH)
		ferr("Checking whether directory has permission to execute for others: Yes\n");
	else
		ferr("Checking whether directory has permission to execute for others: No\n");
	int outoff = 0;
	int inpoff = 0;
	int inp,out;
	inp = open(argv[1],inpoff,SEEK_SET);
	out = open(fstr,outoff,SEEK_END);
	stat(argv[1],&y);
	stat(fstr,&z);
	if (inp == - 1) 
	{ 
		ferr("Some error occurred while opening the input file\n");
		ferr("Checking whether the output file is reversed correctly: Check failed because of the failure to open input file\n");
		return 0;
	}
	if(out==-1) {
		ferr("Some error occurred while opening the output file\n");
		ferr("Checking while the output file is reversed correctly: Check failed because the output file could not be opened\n");
		return 0;
	}
	int match=1;
	int one=1,temp1,temp2;
	int w1,w2;
	char x,xx;
	while(1)
	{
		temp1 = lseek(inp,inpoff,SEEK_SET);
		temp2 = lseek(out,-1L+outoff,SEEK_END);
		if(temp1 < 0 || temp2<0) break;
		w1=read(inp,&x,one);
		w2=read(out,&xx,one);
		if(w1==-1 || w2==-1) {ferr("Some error occurred while reading the files\n");return 0;}
		if(x!=xx) {match=0;break;}
		outoff--;
		inpoff++;
	}
	if(!match) ferr("Checking whether the output file is reversed correctly: No\n");
	if(match) ferr("Checking whether the output file is reversed correctly: Yes\n");
	return 0;
}

