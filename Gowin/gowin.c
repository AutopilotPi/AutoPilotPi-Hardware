

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

/* 
Info:	"Read Device Codes" starting on device-1...
Info:	ID code is: 0x0900281B
Info:	User code is: 0x000044CE
Info:	Status code is: 0x0001F020
Info:	Cost 0.6 second(s)
*/


typedef struct{
    uint8_t command[4];
    uint8_t len;
}gowin_command;

#define READ_ID_CODE 0x11
#define USER_CODE 0x13
#define STATUS_CODE 0x41
gowin_command COMMAND_READ_ID_CODE={{0x11,0x00,0x00,0x00},4};
gowin_command COMMAND_USER_CODE={{0x13,0x00,0x00,0x00},4};
gowin_command COMMAND_STATUS_CODE={{0x41,0x00,0x00,0x00},4};

int transfer(int _fd,uint8_t *send, uint8_t *recv, unsigned len);
void get_codes(int fd,uint8_t code);
void get_all_codes(int fd);

#define GPIO_VAL(gpio_num)      "/sys/class/gpio/gpio" gpio_num "/value"
#define CS_VAL_DEVICE                  GPIO_VAL("144")

void set_gpio(char * device,char * level){
    int fd = open(device, O_WRONLY);
    if (fd == -1) {
        printf("Unable to open %s\n", device);
    }

    if (write(fd, level, 1) != 1) {
        printf("Error writing to /sys/class/gpio/gpio144/value\n");
    }
    close(fd);
}
void set_cs(char * target){
    set_gpio(CS_VAL_DEVICE,target);
}

void give_some_fucking_sclk_cycles(){
    uint8_t buf=0xff;
    // just for making gowin fpga happy
    int fd = open("/dev/spidev0.3", O_RDWR);
    transfer(fd,&buf,&buf,1);
    close(fd);
    
}

int transfer(int _fd,uint8_t *send, uint8_t *recv, unsigned len)
{
    int result=0;
	if ((send == 0) && (recv == 0)) {
		return -1;
	}

	struct spi_ioc_transfer spi_transfer={
        .tx_buf = (uint64_t)send,
        .rx_buf = (uint64_t)recv,
        .len = len,
        .speed_hz = 100000,
        .bits_per_word = 8,
    };
    
	result = ioctl(_fd, SPI_IOC_MESSAGE(1), &spi_transfer);
	if (result != (int)len) {
        printf("spi transfer error\n");
        printf("send len:%d result:%d\n", len,result);
	}

    return 0;
}


void get_codes(int fd,uint8_t code){
    uint8_t buf[8]={code};
    give_some_fucking_sclk_cycles();
    transfer(fd,buf,buf,8);
    printf("get code:0x%x  :",code);
    printf("0x%x \n",(uint32_t) buf[4]<<24 |(uint32_t) buf[5] <<16 |(uint32_t) buf[6] <<8 | buf[7]);
}

int write_enable(int fd){
    uint8_t buf[2]={0x15};
    give_some_fucking_sclk_cycles();
    return transfer(fd,buf,buf,2); 
}



int gpio_export(){
    int fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd == -1) {
        printf("Unable to open /sys/class/gpio/export\n");
    }

    if (write(fd, "144", 3) != 3) {
        printf("Error to export 144\n");
    }
    close(fd);

    fd = open("/sys/class/gpio/gpio144/direction", O_WRONLY);
    if (fd == -1) {
        printf("Unable to open /sys/class/gpio/gpio144/direction\n");

    }

    if (write(fd, "out", 3) != 3) {
        printf("Error writing to /sys/class/gpio/gpio144/direction\n");
    }
    close(fd);    

    return 0;
}

uint8_t file_buffer[81920]={0x3B};

int write_file(int fd, FILE* fp){
    int num=0;
    int i=0;
    int mode,ret;
    num=fread(file_buffer+1,1,81920,fp);
    printf("file size:%d\n",num);
    
    //transfer(fd,file_buffer,file_buffer,4096); 

    give_some_fucking_sclk_cycles();

    fd = open("/dev/spidev0.3", O_RDWR);

    gpio_export();

    set_cs("0");
    // control cs manually, use a fake spidev to output MOSI
    
    num+=1;
    for(i=0;i<num/4096;++i){
        printf("cycle:%d\n",i);
        transfer(fd,file_buffer+i*4096,file_buffer,4096); 
    }
    printf("last cycle num:%d\n",num%4096);
    transfer(fd,file_buffer+i*4096,file_buffer,num%4096);  

    set_cs("1");

    return 0;
} 

int rewrite(int fd){
    uint8_t buf[2]={0x3C};
    give_some_fucking_sclk_cycles();
    return transfer(fd,buf,buf,2);   
}

int erase_sram(int fd){
    uint8_t buf[2]={0x05};
    give_some_fucking_sclk_cycles();
    return transfer(fd,buf,buf,2);       
}

int write_disable(int fd){
    uint8_t buf[2]={0x3A};
    give_some_fucking_sclk_cycles();
    return transfer(fd,buf,buf,2);     
}

void get_all_codes(int fd){
    get_codes(fd,READ_ID_CODE);
    get_codes(fd,USER_CODE); 
    get_codes(fd,STATUS_CODE);
}


int main(int argc,char **argv){
    if (argc != 3){
        printf("error, please set the input filename and spidevice");
        return -1;
    }


    FILE *fp=0;
    int ret,mode,fd;
    ret=mode=fd=0;

    char *filename=argv[2];
    char *device=argv[1];
    fp = fopen(filename,"rb");

    //gpio_export();
    
    printf("open datafile:%s\n",filename);

    fd = open(device, O_RDWR);
    printf("open spidevice:%s\n",device);

    mode = SPI_MODE_0;
    ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);

	if (ret == -1)
		printf("can't set spi mode\n");

	ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
	if (ret == -1)
		printf("can't get spi mode\n");

    if(mode!=SPI_MODE_0){
        printf("can't set spi mode!\n");
    }
    get_all_codes(fd);
    //erase_sram(fd);
    //sleep(1);
    rewrite(fd);
    write_enable(fd);
    write_file(fd,fp);
    write_disable(fd);

    get_all_codes(fd);

    close(fd);
    fclose(fp);
    return 0;
}