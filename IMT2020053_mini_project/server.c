#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<fcntl.h>
#include <pthread.h>

typedef struct user
{
	int userID;
	char name[30];
	char password[20];
	int account_no;
	float balance;
	char status[20];
}user;

typedef struct joint_user
{
	int userID;
	char accname[30];
	char password[20];
	int account_no;
	float balance;
	char status[20];
}joint_user;

typedef struct admin
{
	int userID;
	char username[30];
	char password[20];
}admin;

user get_user(int ID)
{
	int i=ID;
	user temp_user;
	int fd=open("user.dat",O_RDONLY,0744);
	
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(user);    	     
	lock.l_len=sizeof(user);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	


	lseek(fd,(i)*sizeof(user),SEEK_SET);  
	read(fd,&temp_user,sizeof(user));

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return temp_user;
}

joint_user get_joint_user(int ID)
{
	int i=ID;
	joint_user temp_user;
	int fd=open("joint_user.dat",O_RDONLY,0744);
	
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(joint_user);    	     
	lock.l_len=sizeof(joint_user);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	lseek(fd,(i)*sizeof(joint_user),SEEK_SET);  
	read(fd,&temp_user,sizeof(joint_user));

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return temp_user;
}

admin get_admin(int ID)
{
	int i=ID;
	admin temp_user;
	int fd=open("admin.dat",O_RDONLY,0744);
	
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(admin);    	     
	lock.l_len=sizeof(admin);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	lseek(fd,(i)*sizeof(admin),SEEK_SET);  
	read(fd,&temp_user,sizeof(admin));

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return temp_user;
}

bool check_user(user curr_user)
{
	int i=curr_user.userID;
	int fd=open("user.dat",O_RDONLY,0744);
	bool result;
	user temp;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(user);    	     
	lock.l_len=sizeof(user);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	lseek(fd,(i)*sizeof(user),SEEK_SET); 
	read(fd,&temp,sizeof(user));
	if(!strcmp(temp.password,curr_user.password) && !strcmp(temp.status,"ACTIVE"))	
		result=true;
	else						
		result=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool check_joint_user(joint_user curr_user)
{
	int i=curr_user.userID;
	int fd=open("joint_user.dat",O_RDONLY,0744);
	bool result;
	joint_user temp;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(joint_user);    	     
	lock.l_len=sizeof(joint_user);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	lseek(fd,(i)*sizeof(joint_user),SEEK_SET); 
	read(fd,&temp,sizeof(joint_user));

	if(!strcmp(temp.password,curr_user.password) && !strcmp(temp.status,"ACTIVE"))	
		result=true;
	else						
		result=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool check_admin(admin curr_user)
{
	int i=curr_user.userID;
	int fd=open("admin.dat",O_RDONLY,0744);
	bool result;
	user temp;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(admin);    	
	lock.l_len=sizeof(admin);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);

	lseek(fd,(i)*sizeof(admin),SEEK_SET);
	read(fd,&temp,sizeof(admin));

	if(!strcmp(temp.password,curr_user.password) && !strcmp(temp.status,"ACTIVE"))	
		result=true;
	else						
		result=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool depositMoney(int acc_type,int ID,float amount)
{
	int i=ID;
	if(acc_type==1)
	{
		int fd=open("user.dat",O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(user);   
		lock.l_len=sizeof(user);	            
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	

		user curr_user;
		lseek(fd,(i)*sizeof(user),SEEK_SET); 
		read(fd,&curr_user,sizeof(user));
		
		if(!strcmp(curr_user.status,"ACTIVE"))
		{
			curr_user.balance+=amount;
			lseek(fd,sizeof(user)*(-1),SEEK_CUR);
			write(fd,&curr_user,sizeof(user));
			result=true;
		}
		else	
			result=false;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;		
	}
	else if(acc_type==2)
	{
		int fd=open("joint_user.dat",O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(joint_user);    
		lock.l_len=sizeof(joint_user);	             
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	

		joint_user curr_user;
		lseek(fd,(i)*sizeof(joint_user),SEEK_SET); 
		read(fd,&curr_user,sizeof(joint_user));
		
		if(!strcmp(curr_user.status,"ACTIVE"))
		{
			curr_user.balance+=amount;
			lseek(fd,sizeof(joint_user)*(-1),SEEK_CUR);
			write(fd,&curr_user,sizeof(joint_user));
			result=true;
		}
		else	
			result=false;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;	
	}
	return false;
}

bool withdrawMoney(int acc_type,int ID,float amount)
{
	int i=ID;
	if(acc_type==1)
	{
		int fd=open("user.dat",O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(user);    
		lock.l_len=sizeof(user);	             
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	

		user curr_user;
		lseek(fd,(i)*sizeof(user),SEEK_SET);  
		read(fd,&curr_user,sizeof(user));
		
		if(!strcmp(curr_user.status,"ACTIVE") && curr_user.balance>=amount)
		{
			curr_user.balance-=amount;
			lseek(fd,sizeof(user)*(-1),SEEK_CUR);
			write(fd,&curr_user,sizeof(user));
			result=true;
		}
		else	
			result=false;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;	
	}
	else if(acc_type==2)
	{
		int fd=open("joint_user.dat",O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(joint_user);    
		lock.l_len=sizeof(joint_user);	             
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	

		joint_user curr_user;
		lseek(fd,(i)*sizeof(joint_user),SEEK_SET); 
		read(fd,&curr_user,sizeof(joint_user));
		
		if(!strcmp(curr_user.status,"ACTIVE") && curr_user.balance>=amount)
		{
			curr_user.balance-=amount;
			lseek(fd,sizeof(joint_user)*(-1),SEEK_CUR);
			write(fd,&curr_user,sizeof(joint_user));
			result=true;
		}
		else	
			result=false;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	return false;
}

float getBalance(int acc_type,int ID)
{
	int i=ID;
	float result;
	if(acc_type==1)
	{
		int i=ID;
		int fd=open("user.dat",O_RDONLY,0744);
		user temp;
	
		int fl1;
		struct flock lock;
		lock.l_type = F_RDLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(user);    	     
		lock.l_len=sizeof(user);	            
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	

		lseek(fd,(i)*sizeof(user),SEEK_SET);
		read(fd,&temp,sizeof(user));

		if(!strcmp(temp.status,"ACTIVE"))	
			result=temp.balance;
		else					
			result=0;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}

	else if(acc_type==2)
	{
		int i=ID;
		int fd=open("joint_user.dat",O_RDONLY,0744);
		joint_user temp;
	
		int fl1;
		struct flock lock;
		lock.l_type = F_RDLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(joint_user);    	    
		lock.l_len=sizeof(joint_user);	             
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	

		lseek(fd,(i)*sizeof(joint_user),SEEK_SET); 
		read(fd,&temp,sizeof(joint_user));

		if(!strcmp(temp.status,"ACTIVE"))	
			result=temp.balance;
		else					
			result=0;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	return 0;
}

bool alterPassword(int acc_type,int ID,char new_password[20])
{
	int i=ID;
	if(acc_type==1)
	{
		int fd=open("user.dat",O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(user);    
		lock.l_len=sizeof(user);	             
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	

		user curr_user;
		lseek(fd,(i)*sizeof(user),SEEK_SET); 
		read(fd,&curr_user,sizeof(user));
		
		if(!strcmp(curr_user.status,"ACTIVE"))
		{
			strcpy(curr_user.password,new_password);
			lseek(fd,sizeof(user)*(-1),SEEK_CUR);
			write(fd,&curr_user,sizeof(user));
			result=true;
		}
		else	
			result=false;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}

	else if(acc_type==2)
	{
		int fd=open("joint_user.dat",O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(joint_user);    
		lock.l_len=sizeof(joint_user);	             
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	

		joint_user curr_user;
		lseek(fd,(i)*sizeof(joint_user),SEEK_SET); 
		read(fd,&curr_user,sizeof(joint_user));
		
		if(!strcmp(curr_user.status,"ACTIVE"))
		{
			strcpy(curr_user.password,new_password);
			lseek(fd,sizeof(joint_user)*(-1),SEEK_CUR);
			write(fd,&curr_user,sizeof(joint_user));
			result=true;
		}
		else	
			result=false;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	return false;
}

bool add_user(user record)
{
	int fd=open("user.dat",O_RDWR,0744);
	bool result;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_END;
	lock.l_start=(-1)*sizeof(user);    
	lock.l_len=sizeof(user);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	user end_user;
	lseek(fd,(-1)*sizeof(user),SEEK_END); 
	read(fd,&end_user,sizeof(user));
		
	record.userID=end_user.userID+1;
	record.account_no=end_user.account_no+1;
	strcpy(record.status,"ACTIVE");
	
	int check=write(fd,&record,sizeof(user));
	if(check!=0)	
		result=true;
	else	
		result=false;
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return result;	
}

bool add_joint_user(joint_user record)
{
	int fd=open("joint_user.dat",O_RDWR,0744);
	bool result;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_END;
	lock.l_start=(-1)*sizeof(joint_user);    
	lock.l_len=sizeof(joint_user);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	joint_user end_user;
	lseek(fd,(-1)*sizeof(joint_user),SEEK_END);  
	read(fd,&end_user,sizeof(joint_user));
		
	record.userID=end_user.userID+1;
	record.account_no=end_user.account_no+1;
	strcpy(record.status,"ACTIVE");
	
	int check=write(fd,&record,sizeof(joint_user));
	if(check!=0)	
		result=true;
	else	
		result=false;
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return result;	
}

bool delete_user(int ID)
{
	int i=ID;
	int fd=open("user.dat",O_RDWR,0744);
	bool result;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(user);    
	lock.l_len=sizeof(user);	            
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	user curr_user;
	lseek(fd,(i)*sizeof(user),SEEK_SET); 
	read(fd,&curr_user,sizeof(user));
	
	if(!strcmp(curr_user.status,"ACTIVE"))
	{	
		strcpy(curr_user.status,"CLOSED");
		curr_user.balance=0;
		
		lseek(fd,(-1)*sizeof(user),SEEK_CUR); 
		int check=write(fd,&curr_user,sizeof(user));
		if(check!=0)	
			result=true;
		else		
			result=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return result;	
}

bool delete_joint_user(int ID)
{
	int i=ID;
	int fd=open("joint_user.dat",O_RDWR,0744);
	bool result;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(joint_user);   
	lock.l_len=sizeof(joint_user);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	joint_user curr_user;
	lseek(fd,(i)*sizeof(joint_user),SEEK_SET); 
	read(fd,&curr_user,sizeof(joint_user));
	
	if(!strcmp(curr_user.status,"ACTIVE"))
	{	
		strcpy(curr_user.status,"CLOSED");
		curr_user.balance=0;
		
		lseek(fd,(-1)*sizeof(joint_user),SEEK_CUR); 
		int check=write(fd,&curr_user,sizeof(joint_user));
		if(check!=0)	
			result=true;
		else		
			result=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return result;	
}

bool modify_user(user temp_user)
{
	int i=temp_user.userID;
	int fd=open("user.dat",O_RDWR,0744);
	bool result=false;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(user);    
	lock.l_len=sizeof(user);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	user curr_user;
	lseek(fd,(i)*sizeof(user),SEEK_SET); 
	read(fd,&curr_user,sizeof(user));
	
	if(!strcmp(curr_user.status,"ACTIVE") && (temp_user.account_no==curr_user.account_no))
	{	
		strcpy(temp_user.status,"ACTIVE");
		lseek(fd,(-1)*sizeof(user),SEEK_CUR); 
		int check=write(fd,&temp_user,sizeof(user));
		if(check!=0)	
			result=true;
		else		
			result=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return result;	
}

bool modify_joint_user(joint_user temp_user)
{
	int i=temp_user.userID;
	int fd=open("joint_user.dat",O_RDWR,0744);
	bool result=false;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(joint_user);   
	lock.l_len=sizeof(joint_user);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	joint_user curr_user;
	lseek(fd,(i)*sizeof(joint_user),SEEK_SET); 
	read(fd,&curr_user,sizeof(joint_user));
	
	if(!strcmp(curr_user.status,"ACTIVE")  && (temp_user.account_no==curr_user.account_no))
	{	
		strcpy(temp_user.status,"ACTIVE");
		lseek(fd,(-1)*sizeof(joint_user),SEEK_CUR); 
		int check=write(fd,&temp_user,sizeof(joint_user));
		if(check!=0)	
			result=true;
		else		
			result=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return result;	
}

void serverTask(int nsd)
{
	int len,select,type,option,acc_typ,curr_userID;
	bool result;
	while(1)
	{
		read(nsd,&option,sizeof(option));
		printf("choice : %d\n",option);

		if(option==1)
		{
			user curr_user;
			acc_type=1;
			len=read(nsd,&curr_user,sizeof(user));
			printf("Username : %d\n",curr_user.userID);
			printf("Password : %s\n",curr_user.password);
			curr_userID=curr_user.userID;
			result=check_user(curr_user);
			write(nsd,&result,sizeof(result));
		}
		else if(option==2)
		{
			joint_user j_user;
			acc_type=2;
			len=read(nsd,&j_user,sizeof(joint_user));
			curr_userID=j_user.userID;
			printf("Username : %d\n",j_user.userID);
			printf("Password : %s\n",j_user.password);
			result=check_joint_user(j_user);
			write(nsd,&result,sizeof(result));
		}
		else if(option==3)
		{
			admin curr_admin;
			acc_type=3;
			len=read(nsd,&curr_admin,sizeof(admin));
			curr_userID=curr_admin.userID;
			printf("Username : %d\n",curr_admin.userID);
			printf("Password : %s\n",curr_admin.password);
			result=check_admin(curr_admin);
			write(nsd,&result,sizeof(result));
		}
		else
		{
			result=false;
			write(nsd,&result,sizeof(result));
		}
		if(result)	
			break;		
	}

	while(1)
	{
		read(nsd,&select,sizeof(select));
		if(option==1 || option==2)
		{
			if(select==1)
			{
				float amt;
				read(nsd,&amt,sizeof(amount));
				result=depositMoney(acc_type,curr_userID,amt);
				write(nsd,&result,sizeof(result));
			}
			else if(select==2)
			{
				float amt;
				read(nsd,&amt,sizeof(float));
				result=withdrawMoney(acc_type,curr_userID,amt);
				write(nsd,&result,sizeof(result));
			}
			else if(select==3)
			{
				float amt;
				amt=getBalance(acc_type,curr_userID);
				write(nsd,&amt,sizeof(float));
			}
			else if(select==4)
			{
				char pwd[20];
				read(nsd,pwd,sizeof(pwd));
				result=alterPassword(acc_type,curr_userID,pwd);
				write(nsd,&result,sizeof(result));
			}
			else if(select==5)
			{
				if(option==1)
				{
					user user1=get_user(curr_userID);
					write(nsd,&user1,sizeof(user));
				}
				else if(option==2)
				{
					joint_user user2=get_joint_user(curr_userID);
					write(nsd,&user2,sizeof(joint_user));
				}
			}
			else if(select==6)	
				break;
		}
		else if(option==3)
		{
			read(nsd,&type,sizeof(int));
			if(select==1)
			{
				if(type==1)
				{
					user new_user;
					read(nsd,&new_user,sizeof(user));
					result=add_user(new_user);
					write(nsd,&result,sizeof(result));
				}
				else if(type==2)
				{
					joint_user new_user;
					read(nsd,&new_user,sizeof(joint_user));
					result=add_joint_user(new_user);
					write(nsd,&result,sizeof(result));
				}
			}
			else if(select==2)
			{
				if(type==1)
				{
					int userID;
					read(nsd,&userID,sizeof(int));
					result=delete_user(userID);
					write(nsd,&result,sizeof(result));
				}
				else if(type==2)
				{
					int userID;
					read(nsd,&userID,sizeof(int));
					result=delete_joint_user(userID);
					write(nsd,&result,sizeof(result));
				}
			}
			else if(select==3)
			{
				if(type==1)
				{
					user temp_user;
					read(nsd,&temp_user,sizeof(user));
					result=modify_user(temp_user);
					write(nsd,&result,sizeof(result));
				}
				else if(type==2)
				{
					joint_user temp_user;
					read(nsd,&temp_user,sizeof(joint_user));
					result=modify_joint_user(temp_user);
					write(nsd,&result,sizeof(result));
				}
			}
			else if(select==4)
			{
				if(type==1)
				{
					user search_user;
					int userID;
					read(nsd,&userID,sizeof(int));
					search_user=get_user(userID);
					write(nsd,&search_user,sizeof(user));
				}
				else if(type==2)
				{
					joint_user search_user;
					int userID;
					read(nsd,&userID,sizeof(int));
					search_user=get_joint_user(userID);
					write(nsd,&search_user,sizeof(joint_user));
				}
			}
			else if(select==5)	
				break;
		}
	}
	close(nsd);
	write(1,"Ended client session.....\n",sizeof("Ended client session.....\n"));
	return;
}

void *connection_handler(void *nsd) 
{
	int nsfd = *(int*)nsd;
	serverTask(nsfd);
}


int main()
{
	struct sockaddr_in server,client;
	int sd,nsd,client_len;
	pthread_t threads;
	bool result;

	sd=socket(AF_INET,SOCK_STREAM,0);

	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(5555);

	bind(sd,(struct sockaddr *)&server,sizeof(server));
	listen(sd,5);
	
	write(1,"Waiting for the client.....\n",sizeof("Waiting for the client.....\n"));

	while(1)
	{
		client_len=sizeof(client);
		nsd=accept(sd,(struct sockaddr *)&client,&client_len);

		write(1,"Connected to the client.....\n",sizeof("Connected to the client.....\n"));

		if(pthread_create(&threads,NULL,connection_handler,(void*) &nsd)<0)
		{
			perror("could not create thread");
			return 1;
		}		
	}
	pthread_exit(NULL);
	close(sd);
	return 0;
}