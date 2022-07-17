
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <asm/uaccess.h>
#include <linux/unistd.h>
#include <linux/printk.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>
#include <linux/err.h>
#include <linux/errno.h>
#include <linux/file.h>
#include <linux/fcntl.h>

SYSCALL_DEFINE2(my_syscall_6, int, param1, int, param2)
{

    if(param1==0)
    {
        printk( "Right Usage:\n  -all prints some information (process id and its argument/s)about all processes\n  -p takes process id and prints the details of it\n  -k takes process id\n");
                          
    }
    if(param1==1)
    {
        struct task_struct *task;
    	struct file *f;
        char buffer [200]; 
    	char* buf = NULL;
    	char* token;
    	char*stringp;
    	char* info_uid;
    	char* info_ppid;
    	
    	char* info_name;
    	char* info_state;
    	int idd ;
        int pdd;
    	const size_t size = 512;
    	mm_segment_t fs;
    	buf= kmalloc(size, GFP_KERNEL);
    	  
    	printk(KERN_INFO "My module is loaded\n");
    	for_each_process(task)
        {
        	int cx;
    		idd = task->pid;
                pdd = task_ppid_nr(task);
        	cx = snprintf ( buffer, 200, "/proc/%d/status",idd);
        	if(cx>=0 && cx<100)
        	{
             	     f = filp_open(buffer, O_RDONLY, 0); 
             	     if(IS_ERR(f) || f == NULL)
             	     {
                 	 printk(KERN_ALERT "filp_open error!!.\n");
             	     }
            	     else
	    	    {
                	fs = get_fs();
       	        	set_fs(get_ds());
       	        	f->f_op->read(f, buf, size, &f->f_pos);
                	set_fs(fs);
                	stringp = buf;
                        printk("Pid:    %d",idd);
                        printk("Ppid:   %d",pdd);
                	while (stringp != NULL) 
	      		{
                   	     token = strsep(&stringp, "\n");
             	    	     info_uid = strstr(token,"Uid:");
            	    	     info_ppid = strstr(token,"Ppid:");
             	    	     info_name = strstr(token,"Name:");
            	    	     info_state = strstr(token,"State:");
              	    	     if(info_uid != NULL)
                             {
                    		 printk( "%s\n", token);
            	    	     }
                    	     if(info_ppid != NULL)
                    	     {    
                        	 printk( "%s\n", token);
           	    	     }
             	    	     if(info_name!= NULL)
            	   	     {
                		  printk( "%s\n", token);
                    	     }
                    	     if(info_state != NULL)
                    	     {
                	          printk( "%s\n", token);
                   	     }
	               }
                        
            	   }
            	    
        	}
        	printk("----------*******-----------");
        	filp_close(f,NULL); 
   	 }     
    }    
    if(param1==2)
    {
        struct file *file;
        char path_str[200];
    	char* bufile = NULL; 
	const size_t size = 512;
    	mm_segment_t fs;
        bufile= kmalloc(size, GFP_KERNEL);
    	printk(KERN_INFO "My module is loaded\n");
    	sprintf(path_str, "/proc/%d/cmdline", param2); 
        file = filp_open(path_str, O_RDONLY, 0); 
        if(IS_ERR(file) || file == NULL)
        {

            printk(KERN_ALERT "filp_open error!!.\n");
        }
        else
        {
            fs = get_fs();
       	    set_fs(get_ds());
       	    file->f_op->read(file, bufile, size, &file->f_pos);
            set_fs(fs);
            printk(KERN_INFO "%d:     %s \n",param2, bufile);
        }
        filp_close(file,NULL);       		           
    }
    if(param1==3)
    {
        if(kill_pid(find_vpid(param2),SIGKILL,1) == 0)
        { 
             printk("%d killed\n",param2);
        }
        else
        {
            printk("Process could not be killed\n");
        } 
    }
    return 0;    
}       








	
        
     
              
	

