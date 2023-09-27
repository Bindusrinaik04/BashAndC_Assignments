//c programming for cpu intensive program
//1.changing to target directory where the processes are present
//2.traverse through each pid and check for the cpu utilization
//3.if utilization of any pid is exceeding then log the details to .csv file and kill the process

#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<stdlib.h>
#include<time.h>
#include<stdint.h>
#include <signal.h>
#include <sys/types.h>


time_t start_time;
int interval=1;

void logp(int pid,time_t end_time,double cpu_utilized){

     
FILE *fp=fopen("/home/bindu/cpu_usage_log.csv","a");
if (fp == NULL) {
        printf("Failed to open log file");
        exit(1);
    }
     char end_time_str[30];  
    strftime(end_time_str, sizeof(end_time_str), "%Y-%m-%d %H:%M:%S", localtime(&end_time));
    fprintf(fp, "PID,End Time,CPU Utilization\n");
    
    fprintf(fp, "%d,%s,%lf%%\n", pid, end_time_str, cpu_utilized);
    if (kill(pid, SIGKILL) == -1) {
        perror("Failed to kill the process");
    } else {
        printf("Killed process with PID %d\n", pid);
    }
    fclose(fp);

}


 uint64_t getSystemUptimeInSeconds() {
    FILE* uptimeFile = fopen("/proc/uptime", "r");
    if (uptimeFile == NULL) {
        perror("Failed to open /proc/uptime");
        exit(1);
    }
    
    double uptime;
    if (fscanf(uptimeFile, "%lf", &uptime) != 1) {
        perror("Failed to read /proc/uptime");
        fclose(uptimeFile);
        exit(1);
    }

    fclose(uptimeFile);
    return (uint64_t)(uptime);  // Return uptime in seconds
}

// CPU utilization calculation
void cpu_utilization(int pid, unsigned long utime, unsigned long stime, unsigned long long starttime) {
     time_t current_time;
    struct tm *timeinfo;
    char time_buffer[80];

    time(&current_time);
    timeinfo = localtime(&current_time);

    // Format the current time as a human-readable string
    strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    uint64_t systemUptime = getSystemUptimeInSeconds();
    
    // Calculate elapsed time in seconds
    double elapsed_time = (double)(systemUptime) - (double)(starttime / 100.0);
    
    // Calculate total CPU time in seconds
    double total_cpu_time = (double)(utime + stime) / 100.0;
    
    // Calculate CPU utilization percentage
    double cpu_utilized = (total_cpu_time / elapsed_time) * 100;
 
    
    if(cpu_utilized>50) {
    logp(pid,time_buffer,cpu_utilized);
    }
   
}


//for reading the contents of the file
int readstatfile(const char *proc_dir)
{
	char stat_path[256];
	snprintf(stat_path,sizeof(stat_path),"%s/stat",proc_dir);

	//processing the stat file
	FILE *fp=fopen(stat_path,"r");
	if(fp==NULL){
		 printf("error while opening the stat file of %s\n",proc_dir);
		 return 1;
	}

	char content[1024];
	if(fgets(content,sizeof(content),fp)==NULL)
	{
		printf("error reading stat file\n");
		fclose(fp);
		return 1;
	}
	int stat_pid;
    unsigned long utime, stime;
    unsigned long long starttime;
	  if (sscanf(content, "%d %*s %*c %*d %*d %*d %*d %*d %*u %*lu %*lu %*lu %*lu %lu %lu %*ld %*ld %*ld %*ld %*ld %*ld %llu",
               &stat_pid, &utime, &stime, &starttime) != 4) {
        printf("Error while parsing stat file\n");
        fclose(fp);
        return 1;
    }

      
    cpu_utilization(stat_pid, utime, stime, starttime);
	     	  

	    return 0;

}

int main(){
	 const char *target ="/proc";
	 DIR *dir;
	 struct dirent *entry;
	 
	 //opening /proc directory
	 dir =opendir(target);
	 if(dir ==NULL){
	  printf("error with opening target\n");
	  exit(1);
	  }
	  
	 //reading and printing the process directories and starting the timer
	 time(&start_time);
	 
	 while((entry =readdir(dir))!=NULL)
	 {
		 if(entry->d_type ==DT_DIR)
		 {
			  char *name = entry->d_name;
			  
		       	  int pid= atoi(name);
			if(pid>0)
			{
				  char process_dir[256];
				  snprintf(process_dir,sizeof(process_dir),"/proc/%s",name);
				  if(chdir(process_dir)==0)
				  {
					  char current[256];
					  if(getcwd(current ,sizeof(current))!=NULL)
					  {
						   
						  if(readstatfile(current)!=0)
						   {
						     printf("error while processing the contents of the directory\n");
						   }
						  printf("\n-----------------------------------------------------\n");
					  }
					  else {
					  printf("error with getcwd()\n");
					  
					  }
					  chdir(target);
			           }
				  else printf("error with chdir()");
			  }
		  }
	  }
	   closedir(dir);
        dir = opendir(target);

        // Sleep for the specified interval before taking the next snapshot
        sleep(interval);
	  
	  return 0;
  }
