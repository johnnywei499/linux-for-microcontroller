#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <termios.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/types.h>
#include <stdint.h>

ssize_t safe_write(int fd, const void *vptr, size_t n)
{
    size_t  nleft;
    ssize_t nwritten;
    const unsigned char *ptr;

    ptr = (const unsigned char *)vptr;
    nleft = n;

    while (nleft > 0)
    {
    	if ((nwritten = write(fd, ptr, nleft)) <= 0) {
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0;
            else
                return -1;
        }
        nleft -= nwritten;
        ptr   += nwritten;
    }
    return(n);
}

ssize_t safe_read(int fd, unsigned char *vptr, size_t n)
{
    size_t nleft;
    ssize_t nread;
    unsigned char *ptr;
	int i;

    ptr = (unsigned char *)vptr;
    nleft = n;

	int total = 0;
	while (nleft > 0) {
		nread = read(fd, ptr + total, nleft);
		if (nread == 0) {
			printf("%s: %d\n", __func__, __LINE__);
            break;
        }
		int num = 0;
		//printf("\nread len: %d\n", nread);

		total += nread;
		nleft -= nread;
	}

    return (n - nleft);
}

int uart_open(int fd,const char *pathname)
{
    assert(pathname);

    /*打开串口*/
    fd = open(pathname, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        perror("Open UART failed!");
        return -1;
    }

    /*清除串口非阻塞标志*/
    if (fcntl(fd, F_SETFL, 0) < 0)
    {
        fprintf(stderr,"fcntl failed!\n");
        return -1;
    }

    return fd;
}

int uart_set(int fd, int baude, int c_flow, int bits, char parity, int stop)
{
    struct termios options;

    /*获取终端属性*/
    if (tcgetattr(fd, &options) < 0) {
        perror("tcgetattr error");
        return -1;
    }

    /*设置输入输出波特率，两者保持一致*/
    switch (baude) {
        case 4800:
            cfsetispeed(&options, B4800);
            cfsetospeed(&options, B4800);
            break;
        case 9600:
            cfsetispeed(&options, B9600);
            cfsetospeed(&options, B9600);
            break;
        case 19200:
            cfsetispeed(&options, B19200);
            cfsetospeed(&options, B19200);
            break;
        case 38400:
            cfsetispeed(&options, B38400);
            cfsetospeed(&options, B38400);
            break;
		case 115200:
            cfsetispeed(&options, B115200);
            cfsetospeed(&options, B115200);
            break;
		case 230400:
            cfsetispeed(&options, B230400);
            cfsetospeed(&options, B230400);
            break;
		case 460800:
            cfsetispeed(&options, B460800);
            cfsetospeed(&options, B460800);
            break;
		case 500000:
            cfsetispeed(&options, B500000);
            cfsetospeed(&options, B500000);
            break;
		case 576000:
            cfsetispeed(&options, B576000);
            cfsetospeed(&options, B576000);
            break;
		case 921600:
            cfsetispeed(&options, B921600);
            cfsetospeed(&options, B921600);
            break;
		case 1000000:
            cfsetispeed(&options, B1000000);
            cfsetospeed(&options, B1000000);
            break;
		case 1152000:
            cfsetispeed(&options, B1152000);
            cfsetospeed(&options, B1152000);
            break;
		case 1500000:
            cfsetispeed(&options, B1500000);
            cfsetospeed(&options, B1500000);
            break;
		case 2000000:
            cfsetispeed(&options, B2000000);
            cfsetospeed(&options, B2000000);
            break;
		case 2500000:
            cfsetispeed(&options, B2500000);
            cfsetospeed(&options, B2500000);
            break;
		case 3000000:
            cfsetispeed(&options, B3000000);
            cfsetospeed(&options, B3000000);
            break;
		case 3500000:
            cfsetispeed(&options, B3500000);
            cfsetospeed(&options, B3500000);
            break;
		case 4000000:
            cfsetispeed(&options, B4000000);
            cfsetospeed(&options, B4000000);
            break;
        default:
            fprintf(stderr, "Unkown baude!\n");
            return -1;
    }

    /*设置控制模式*/
    options.c_cflag |= CLOCAL;//保证程序不占用串口
    options.c_cflag |= CREAD;//保证程序可以从串口中读取数据

    /*设置数据流控制*/
    switch (c_flow) {
        case 0://不进行流控制
            options.c_cflag &= ~CRTSCTS;
            break;
        case 1://进行硬件流控制
            options.c_cflag |= CRTSCTS;
            break;
        case 2://进行软件流控制
            options.c_cflag |= IXON|IXOFF|IXANY;
            break;
        default:
            fprintf(stderr, "Unkown c_flow!\n");
            return -1;
    }

    /*设置数据位*/
    switch (bits) {
        case 5:
            options.c_cflag &= ~CSIZE;//屏蔽其它标志位
            options.c_cflag |= CS5;
            break;
        case 6:
            options.c_cflag &= ~CSIZE;//屏蔽其它标志位
            options.c_cflag |= CS6;
            break;
        case 7:
            options.c_cflag &= ~CSIZE;//屏蔽其它标志位
            options.c_cflag |= CS7;
            break;
        case 8:
            options.c_cflag &= ~CSIZE;//屏蔽其它标志位
            options.c_cflag |= CS8;
            break;
        default:
            fprintf(stderr, "Unkown bits!\n");
            return -1;
    }

    /*设置校验位*/
    switch (parity) {
        /*无奇偶校验位*/
        case 'n':
        case 'N':
            options.c_cflag &= ~PARENB;//PARENB：产生奇偶位，执行奇偶校验
            options.c_cflag &= ~INPCK;//INPCK：使奇偶校验起作用
            //options.c_cflag &= (~ISTRIP);////禁止将所有接收的字符裁减为7比特
            
            break;
        /*设为空格,即停止位为2位*/
        case 's':
        case 'S':
            options.c_cflag &= ~PARENB;//PARENB：产生奇偶位，执行奇偶校验
            options.c_cflag &= ~CSTOPB;//CSTOPB：使用两位停止位
            break;
        /*设置奇校验*/
        case 'o':
        case 'O':
            options.c_cflag |= PARENB;//PARENB：产生奇偶位，执行奇偶校验
            options.c_cflag |= PARODD;//PARODD：若设置则为奇校验,否则为偶校验
            options.c_cflag |= INPCK;//INPCK：使奇偶校验起作用
            options.c_cflag |= ISTRIP;//ISTRIP：若设置则有效输入数字被剥离7个字节，否则保留全部8位
            break;
        /*设置偶校验*/
        case 'e':
        case 'E':
            options.c_cflag |= PARENB;//PARENB：产生奇偶位，执行奇偶校验
            options.c_cflag &= ~PARODD;//PARODD：若设置则为奇校验,否则为偶校验
            options.c_cflag |= INPCK;//INPCK：使奇偶校验起作用
            options.c_cflag |= ISTRIP;//ISTRIP：若设置则有效输入数字被剥离7个字节，否则保留全部8位
            break;
        default:
            fprintf(stderr, "Unkown parity!\n");
            return -1;
    }
	
    /*设置停止位*/
    switch (stop) {
        case 1:
            options.c_cflag &= ~CSTOPB;//CSTOPB：使用两位停止位
            break;
        case 2:
            options.c_cflag |= CSTOPB;//CSTOPB：使用两位停止位
            break;
        default:
            fprintf(stderr, "Unkown stop!\n");
            return -1;
    }

	options.c_iflag &= ~ISTRIP;

    /*设置输出模式为原始输出*/
    options.c_oflag &= ~OPOST;//OPOST：若设置则按定义的输出处理，否则所有c_oflag失效

    /*设置本地模式为原始模式*/
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    /*
     *ICANON：允许规范模式进行输入处理
     *ECHO：允许输入字符的本地回显
     *ECHOE：在接收EPASE时执行Backspace,Space,Backspace组合
     *ISIG：允许信号
     */

    /*设置等待时间和最小接受字符*/
    options.c_cc[VTIME] = 0;//可以在select中设置
    options.c_cc[VMIN] = 1;//最少读取一个字符

    /*如果发生数据溢出，只接受数据，但是不进行读操作*/
    tcflush(fd, TCIFLUSH);

	options.c_cflag |= CS8;
	//预防0D强制变0A
	options.c_iflag &= ~ICRNL;

	options.c_iflag &= ~(ICRNL | IXON); 
	
    /*激活配置*/
    if (tcsetattr(fd, TCSANOW, &options) < 0) {
        perror("tcsetattr failed");
        return -1;
    }

    return 0;
}

int uart_read(int fd, unsigned char *r_buf,size_t len)
{
	int ret;
    ssize_t cnt = 0;
    fd_set rfds;
    struct timeval time;

    /*将文件描述符加入读描述符集合*/
    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);

    /*设置超时为15s*/
    time.tv_sec = 90;
    time.tv_usec = 0;

    /*实现串口的多路I/O*/
    ret = select(fd + 1, &rfds, NULL, NULL, NULL);
    switch (ret) {
        case -1:
            fprintf(stderr, "select error!\n");
            return -1;
        case 0:
            fprintf(stderr, "time over!\n");
            return -1;
        default:
            cnt = safe_read(fd, r_buf, len);
            if (cnt == -1)
            {
                fprintf(stderr, "read error!\n");
                return -1;
            }
            return cnt;
    }
}

int uart_write(int fd, const unsigned char *w_buf, size_t len)
{
    ssize_t cnt = 0;

    cnt = safe_write(fd, w_buf, len);
    if (cnt == -1) {
        fprintf(stderr, "write error!\n");
        return -1;
    }

    return cnt;
}

int uart_close(int fd)
{
    assert(fd);
    close(fd);

    /*可以在这里做些清理工作*/

    return 0;
}

int uart_show(int fd)
{
	struct termios options; 
	if (tcgetattr(fd, &options) != 0) { 
		perror("tcgetattr 1");     
		return -1;  
	}
	printf("options.c_cflag: 0x%0x\n", options.c_cflag);
	printf("options.c_iflag: 0x%0x\n", options.c_iflag);
	printf("options.c_lflag: 0x%0x\n", options.c_lflag);
	printf("options.c_oflag: 0x%0x\n", options.c_oflag);
	printf("options.c_ispeed: 0x%0x\n", options.c_ispeed);
	printf("options.c_ospeed: 0x%0x\n", options.c_ospeed);
	printf("options.c_cc[VTIME]: 0x%0x\n", options.c_cc[VTIME]);
	printf("options.c_cc[VMIN]: 0x%0x\n", options.c_cc[VMIN]);
	return 0;
}

int read_file(char *filename, unsigned char *buffer)
{
	FILE *fp;
	fpos_t fpos;
	int len;
	
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("open failed\n");
		return -1;
	}

	fgetpos(fp, &fpos);
	
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);

	fsetpos(fp, &fpos);

	fread(buffer, 1, len, fp);

	fclose(fp);
	
	return len;
}

#define MAX_FILE_SIZE (12 * 1024 * 1024)
#define MAX_UART_SIZE 255
int main(int argc, char **argv)
{
	int i, ret, filelen, remainlen;
	uint16_t checksum = 0, result;
	unsigned char *buffer, wbuffer[MAX_UART_SIZE + 1] = {0}, rbuffer[MAX_UART_SIZE + 1] = {0};
	int fd;

	if (argc != 2) {
		printf("argc error\n");
		return -1;
	}

    fd = uart_open(fd, "/dev/ttyUSB0");
    if (fd == -1) {
        printf("uart_open error\n");
        return -1;
    }
	
    if (uart_set(fd, 2000000, 0, 8, 'N', 1) == -1) {
        printf("uart set failed!\n");
        return -1;
    }

	buffer = malloc(MAX_FILE_SIZE);
	if (!buffer) {
		printf("malloc failed\n");
	}

	filelen = read_file(argv[1], buffer);
	if (filelen <= 0) {
		printf("read_file failed\n");
		return -1;
	}

	for (i = 0; i < filelen; i++) {
		checksum += buffer[i];
	}
	remainlen = filelen;

	//send file size
	wbuffer[3] = (filelen & 0xFF000000) >> 24;
	wbuffer[2] = (filelen & 0xFF0000) >> 16;
	wbuffer[1] = (filelen & 0xFF00) >> 8;
	wbuffer[0] = (filelen & 0xFF) >> 0;
	ret = uart_write(fd, wbuffer, 4);
	if (ret < 0) {
		printf("uart_write failed\n");
	}
	//ACK
	memset(rbuffer, 0, MAX_UART_SIZE + 1);
	ret = uart_read(fd, rbuffer, 2);
	if (ret < 0) {
		printf("uart_read failed\n");
	}
	
    while (remainlen > 0) {
		memset(wbuffer, 0, MAX_UART_SIZE + 1);
		
		if (remainlen < MAX_UART_SIZE)
			wbuffer[0] = remainlen;
		else
			wbuffer[0] = MAX_UART_SIZE;

		memcpy(wbuffer + 1, buffer + filelen - remainlen, MAX_UART_SIZE);

		ret = uart_write(fd, wbuffer, MAX_UART_SIZE + 1);
		if (ret < 0) {
			printf("uart_write failed\n");
		}

		//ACK
		memset(rbuffer, 0, MAX_UART_SIZE + 1);
		ret = uart_read(fd, rbuffer, 2);
		if (ret < 0) {
			printf("uart_read failed\n");
		}

		remainlen -= MAX_UART_SIZE;
		printf("\33[2K\r");
		printf("write: %d%%", ((filelen - remainlen) * 100) / filelen);
		fflush(stdout);
		if (remainlen == 0) {
			memset(wbuffer, 0, MAX_UART_SIZE + 1);
			uart_write(fd, wbuffer, MAX_UART_SIZE + 1);
			uart_read(fd, rbuffer, 2);
		}
    }
	printf("\n");
	printf("file size: %d\n", filelen);
	
	ret = uart_read(fd, rbuffer, 2);
	if (ret < 0) {
		printf("uart_read failed\n");
	} else {
		result = (rbuffer[1] << 8) | rbuffer[0];
		if (checksum == result) {
			printf("upgrade success\n");
		} else {
			printf("upgrade failed (%04X %04X)\n", result, checksum);
		}
	}

	free(buffer);
	
    uart_close(fd);

    return 0;
}
