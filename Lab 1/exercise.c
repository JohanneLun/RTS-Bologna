#include <stdio.h>

void read(){
	char name[100];
	printf("Enter filename: ");
	gets(str);
	int fd = fopen(name,"r");
	if (fd == NULL){
		printf("open failed");
	}
	else {
	printf("file is: \n", fd);
	}
	fclose(fd);
}

void write(){
	char name;
	//aapne fil som over 
	//ta inn input
	//spòrre om mer
	//lukke
}

void main(){
	read();
	write();
	return 0;
}
