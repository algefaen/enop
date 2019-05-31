#include <stdio.h>	// standard input / output functions
#include <stdlib.h>
#include <string.h>	// string function definitions
#include <unistd.h>	// UNIX standard function definitions
#include <fcntl.h>	// File control definitions
#include <errno.h>	// Error number definitions
#include <termios.h>	// POSIX terminal control definitions


using namespace std;

int main() 
{

	/* Open File Descriptor */
	int USB = open( "/dev/wind", O_RDONLY | O_NOCTTY );

	/* Error Handling */
	if ( USB < 0 )
	{
		perror("Error when opening /dev/wind");
		return 1;
	}

	/* *** Configure Port *** */
	struct termios tty;
	memset (&tty, 0, sizeof tty);

	/* Error Handling */
	if ( tcgetattr ( USB, &tty ) != 0 )
	{
		perror("Error from tcgetattr");
		return 1;
	}

	/* Set Baud Rate */
	cfsetospeed (&tty, (speed_t)B9600);
	cfsetispeed (&tty, (speed_t)B9600);

	/* Setting other Port Stuff */
	tty.c_cflag	&=  ~PARENB;	    // Make 8n1
	tty.c_cflag	&=  ~CSTOPB;
	tty.c_cflag	&=  ~CSIZE;
	tty.c_cflag	|=  CS8;

	tty.c_cflag	&=  ~CRTSCTS;	    // no flow control
	tty.c_cc[VMIN]	    =	1;		    // read doesn't block
	tty.c_cc[VTIME]     =	5;		    // 0.5 seconds read timeout
	tty.c_cflag	|=  CREAD | CLOCAL;	// turn on READ & ignore ctrl lines


	/* Make raw */
	cfmakeraw(&tty);

	/* Flush Port, then applies attributes */
	tcflush( USB, TCIFLUSH );
	if ( tcsetattr ( USB, TCSANOW, &tty ) != 0)
	{
		perror("Error from tcsetattr");
		return 1;
	}

	fd_set set;
	struct timeval timeout;
	FD_ZERO(&set);
	FD_SET(USB, &set);
	while (true) 
	{

		int n = 0;

		char buf[2] = { 0 };
		const size_t result_size = 1024;
		char result[result_size] = { 0 };

		do
		{
			fprintf(stderr, ".");
			timeout.tv_sec = 5;
			timeout.tv_usec = 0;
			int sel_return = select(USB+1, &set, NULL, NULL, &timeout);
			switch (sel_return) {
				case -1:
					perror("error while reading");
					exit(1);
				case 0: 
					fprintf(stderr, "timeout while waiting for read");
					exit(1);
			}
			n = read( USB, &buf, 1 );
			strcat(result, buf);
		}
		while( buf[0] != '\n' && n > 0);

		// (string terminates with \r\n - let's strip them away)
		if (strnlen(result, result_size) > 2)
		{
			result[strnlen(result, result_size) - 2] = '\0';
		}


		if (n <= 0)
		{
			perror("Error when reading");
			exit(1);
		}
		else
		{
			printf("%s\n", result);
		}
		fflush(0);
	}
}
