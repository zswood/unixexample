//#define __CHAPTER_TEST1__

#ifdef	__CHAPTER_TEST1__
/*
 * @brief	目录文件list
 * @date	2017.02.14
 */
#include"stdio.h"
#include"dirent.h"

int main(int argc, char* argv[])
{
	if(argc != 2){
		return -1;
	}

	DIR* dir_ptr = opendir(argv[1]);
	if (dir_ptr == NULL){
		printf("errinfo: opendir %s fail.\n", argv[1]);
		return -1;
	}

	struct dirent* files_ptr = readdir(dir_ptr);
	while (files_ptr != NULL){
	printf("file:%s, type:%d \n", files_ptr->d_name, files_ptr->d_type);
	files_ptr = readdir(dir_ptr);
	}
	closedir(dir_ptr);
	return 0;
}
#endif /*__CHAPTER_TEST1__*/

#ifdef  __CHAPTER_TEST2__
/*
 * @brief	copy file STD**_FILENO;
 * @note1	Ctrl+D end the STDIN_FILENO;重定向标准输入输出进行数据拷贝;
 * @note2	不带缓冲的I/O: open|read|write|lseek|close;
 * @date	2017.02.14
 */
#include"stdio.h"
#include"unistd.h"

#ifdef	__CHAPTER_TEST2-1__
#define BUFF_SIZE 1024
int main(int argc, char* argv[])
{
	char buffer[BUFF_SIZE] = {0};
	int read_size = read(STDIN_FILENO, (void*)buffer, BUFF_SIZE);
	while (read_size > 0){
		if (write(STDOUT_FILENO, (void*)buffer, read_size) != read_size){
			printf("errinfo: write fail.\n");
			return -1;
		}
		read_size = read(STDIN_FILENO, (void*)buffer, BUFF_SIZE);
	}
	if (read_size < 0){
		printf("errinfo: read fail.\n");
		return -1;
	}

	return 0;
}
#else
int main(int argc, char* argv[])
{
	int character = 0;
	while ((character = getc(stdin)) != EOF){
		if (putc(character, stdout) == EOF){
			printf("errinfo: putc fail.\n");
			return -1;
		}
	}
	return 0;
}
#endif /*__CHAPTER_TEST2-1__*/
#endif /*__CHAPTER_TEST2__*/

#ifdef __CHAPTER_TEST3__
/*
 * @brief	进程控制实例
 * @note	进程控制主要函数：fork,exec,waitpid;
 */
#include"unistd.h"
#include"stdio.h"
#include"string.h"
#include"sys/wait.h"
#include"errno.h"
#include"signal.h"

#define BUFF_SIZE 255 //可执行文件最大文件名(非商业化系统);

void sigfunc(int sig){
	printf("catch signal %d.\n", sig);
	return ;
}

int main(int argc, char* argv[])
{
	if (signal(SIGINT, sigfunc) == SIG_ERR){
		printf("errinfo: set signal fail.\n");
		return -1;
	}

	char buffer[BUFF_SIZE] = {0};
	pid_t pid;
	while (fgets(buffer, BUFF_SIZE, stdin) != NULL){
		// execlp函数参数以空字符结束;
		buffer[strlen(buffer) - 1] = '\0';
		if ((pid = fork()) < 0){
			printf("errinfo: fork fail.\n");
			return -1;
		}else if (pid == 0){
			// 子进程;
			execlp(buffer, buffer, NULL);
			printf("errinfo: exec %s fail with errno:%d, errstr:%s.\n", buffer, errno, strerror(errno));
			perror(NULL);
			return -1;
		}

		// 父进程;
		int pidstatus;
		if (waitpid(pid, &pidstatus, 0) == -1){
			printf("errinfo: waitpid %ld fail.\n", (long)pid);
			return -1;
		}
	//	printf("dbginfo: process %ld exit.\n", pid);
	}
	return 0;
}
#endif /*__CHAPTER_TEST3__*/


#ifdef __CHAPTER_TEST4__
#include"stdio.h"
#include"unistd.h"

int main(int argc, char* argv[])
{
	printf("user'id:%d, user'groupid:%d.\n", getuid(), getgid()); //现今unix用户id及组id为32位;
	return 0;
}
#endif /*__CHAPTER_TEST4__*/


/*
 * @brief	习题
 * @note	文本略
 */
