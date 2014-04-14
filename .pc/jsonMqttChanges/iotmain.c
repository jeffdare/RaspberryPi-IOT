#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char propFileLoc[20] = "./iot.properties";
char lockFileLoc[10] = "./.lck";
char pidFileLoc[10] = "./.pid";

#define MAXBUF 100

struct config {
	char hostname[MAXBUF];
	char timout[MAXBUF];
	char tenantprefix[MAXBUF];
};

float getCPUTemp();
char *getmac(char *iface);
void get_config(char* filename, struct config * configstr);
char *getClientId(char* tenant_prefix, char* mac_address);

int main(int argc, char **argv) {
	printf("***********Entering the IOT raspberry pi device********************\n");

	struct config configstr;
	char* clientId;
	int lckStatus;

	float temp = getCPUTemp();
	char* mac_address = getmac("eth0");

	//first check if there is another process already started
	if (access(lockFileLoc, F_OK) != -1) {
		printf("There is another process of IOT-Raspberry running. Please close that before starting. If there are no other IOT-Raspberry process running, please delete the .lck file and start again\n");
	} else {
		FILE *fp;
		fp = fopen(lockFileLoc, "w");
		printf("Creating the .lck file\n");
		fclose(fp);
	}

	// to load the config files
	get_config(propFileLoc, &configstr);

	printf("The temp is %.2f\n", temp);
	printf("THe mac address is %s\n", mac_address);

	clientId = getClientId(configstr.tenantprefix, mac_address);

	printf("THe value of hostname is %s\n", configstr.hostname);

	return 0;
}

void get_config(char * filename, struct config * configstr) {

	FILE* prop;
	char str1[10], str2[10];
	prop = fopen(filename, "r");
	if( prop == NULL )
   	{
      		perror("Error while opening the properties file. Please ensure that the properties file exist in this directory\n");
      		exit(1);
   	}
	char line[256];
	int linenum = 0;
	while (fgets(line, 256, prop) != NULL) {
		char prop[256], value[256];

		linenum++;
		if (line[0] == '#')
			continue;

		if (sscanf(line, "%s %s", prop, value) != 2) {
			fprintf(stderr, "Syntax error, line %d\n", linenum);
			continue;
		}
		if (strcmp(prop, "hostname") == 0)
			strncpy(configstr->hostname, value, MAXBUF);
		else if (strcmp(prop, "timout") == 0)
			strncpy(configstr->timout, value, MAXBUF);
		else if (strcmp(prop, "tenantprefix") == 0)
			strncpy(configstr->tenantprefix, value, MAXBUF);

	}

}

char *getClientId(char* tenant_prefix, char* mac_address) {
	char* clientid;

	clientid = strcat(tenant_prefix, ":");
	clientid = strcat(clientid, mac_address);

	return clientid;
}

