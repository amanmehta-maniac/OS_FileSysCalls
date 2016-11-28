#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include<string.h>
//ferr is a user defined function which uses <write> call to print any message to the terminal 
void ferr(char *err){
		write(STDERR_FILENO,err,strlen(err));return; 
}
int main(int argc, char *argv[])
{
	char *err1;
	char *outFile;
	if(argc!=2) { 
		ferr("Err: This program requires exactly two arguments\nUsage: ./a.out <filename>\n");
		return 0;
	}
	//711 is set of permissions of the directory
	int e1 = mkdir("./Assignment",0711);
	if(e1!=0)
	{
		ferr("Some error occured in creating a new directory, this could be because a directory with same name already exists.\n");
		return 0;
	}
	char a[10000];
	strcpy(a,"./Assignment/output_");
	char b[10000];
	strcpy(b, argv[1]);
	outFile = strcat(a,b);
	// create a output file name "output_<argv[1]>"
	int e2 = creat(outFile,0600);
	if(e2 == -1) {
		ferr("Err: The answer file could not be generated\n");
		return 0;
	}
	int inp = open(argv[1],O_RDONLY);
	if(inp == -1) {
		ferr("Err: The input file could not be opened\n");
		return 0;
	}
	int out = open(outFile,O_WRONLY | O_APPEND);
	if(out == -1) {
		ferr("Err: The answer file could not be generated\n");
		return 0;
	}
	int w=0,i=0,j=0,temp,one=1;
	char x;
	while(1)
	{
		temp = lseek(inp,-1L+i-1,SEEK_END);
		if(temp < 0) break;
		//read one character
		w=read(inp,&x,one);
		// write the read character into outFile
		w=write(out,&x,one);
		i--;
	}
	//close the files that were opened during this program
	close(inp);
	close(out);
	return 0;
}
