#include <stdio.h>
#include <unistd.h>

#ifdef __WIN32__
	#include <winsock2.h>
#else
	#include <sys/socket.h>
#endif

//#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

// Using
using namespace std

// Define
#define PORT 8080

int main(int argc, char const *argv[]) 
{
	int fd;
	struct ifreq ifr;
	
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	
	/* I want to get an IPv4 IP address */
	ifr.ifr_addr.sa_family = AF_INET;
	
	/* I want IP address attached to "eth0" */
	//strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);
	ioctl(fd, SIOCGIFADDR, &ifr);
	close(fd);
	
	/* display result */
	printf("%s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));

	return 0;
}

char int*array(char * ipaddr)
{
	if (ipaddr == "172.31.18.149")
		return 1234;
	if (ipaddr == "172.31.18.203")
		return 2345;
	if (ipaddr == "172.31.24.86")
		return 3456;
	if (ipaddr == "172.31.22.107")
		return 4567;
	if (ipaddr == "172.31.25.35")
		return 5678;
}
	

