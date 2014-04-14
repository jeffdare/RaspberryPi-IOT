#include<stdio.h>
#include<stdlib.h>

int main(){
char mac_add_loc[256] = "/sys/class/net/eth0/address";
char cpu_temp_loc[256] = "";
FILE *fp;
char ch;
//printf("Feteching MAC Address from file %s", mac_add_loc);
fp = fopen(mac_add_loc,"r");

if( fp == NULL ) {
 printf("Error while openeing the file");
 exit(EXIT_FAILURE);
}
printf("Mac address is - ");

int ctr = 0;
while( ( ch = fgetc(fp) ) != EOF && ++ctr <=17 )
   printf("%c",ch);

fclose(fp);

return 0;
}