#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

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


int get_user_id()
{
	int fd=open("user.dat",O_RDONLY,0777);
	user rec;
	lseek(fd,-sizeof(normalUser),SEEK_END);
	read(fd,&rec,sizeof(normalUser));
	close(fd);
	return rec.userID+1;
}

int get_joint_user_id()
{
	int fd=open("joint_user.dat",O_RDONLY,0777);
	joint_user rec;
	lseek(fd,-sizeof(joint_user),SEEK_END);
	read(fd,&rec,sizeof(joint_user));
	close(fd);
	return rec.userID+1;
}

int get_admin_id()
{
	int fd=open("admin.dat",O_RDONLY,0777);
	admin rec;
	lseek(fd,-sizeof(admin),SEEK_END);
	read(fd,&rec,sizeof(admin));
	close(fd);
	return rec.userID+1;
}

int main()
{
	int fd=open("admin.dat",O_RDWR | O_CREAT,0777);
	int choice=0;
	admin newAdmin;
	printf("Please enter the name of the admin: ");
	scanf("%s",newAdmin.username);
	printf("Please enter the password(max 10 characters): ");
	scanf("%s",newAdmin.password);
	newAdmin.userID=0001;
	printf("Your userID is : %d\n",newAdmin.userID);
	write(fd,&newAdmin,sizeof(newAdmin));
	printf("Do you want to enter another(0/1)? ");
	scanf("%d",&choice);
	while(choice)
	{
		printf("Please enter the name of the admin: ");
		scanf("%[^\n]",newAdmin.username);
		printf("Please enter the password(max 20 characters): ");
		scanf("%[^\n]",newAdmin.password);
		newAdmin.userID=get_admin_id();
		printf("Your userID is : %d\n",newAdmin.userID);
		write(fd,&newAdmin,sizeof(admin));
		printf("Do you want to enter another(0/1)? ");
		scanf("%d",&choice);
	}
	close(fd);

	fd=open("user.dat",O_RDWR | O_CREAT,0777);
	choice=1;
	user User;
	printf("Please enter the name of the normal user: ");
	scanf(" %[^\n]",user.name);
	printf("Please enter the password(max 20 characters): ");
	scanf(" %[^\n]",user.password);
	User.userID=0001;
	User.balance=1000;
	User.account_no=(User.userID)+100000;
	printf("Your userID is : %d\n",User.userID);
	strcpy(User.status,"ACTIVE");
	write(fd,&User,sizeof(user));

	printf("Do you want to add another(0/1)? ");
	scanf("%d",&choice);

	while(choice)
	{
		printf("Please enter the name of the user: ");
		scanf(" %[^\n]",User.name);
		printf("Please enter the password(max 20 characters): ");
		scanf(" %[^\n]",User.password);
		User.userID=get_user_id();
		User.balance=1000;
		User.account_no=(User.userID)+100000;
		printf("Your userID is : %d\n",User.userID);
		strcpy(User.status,"ACTIVE");
		write(fd,&User,sizeof(user));
		printf("Do you want to add another(0/1)? ");
		scanf("%d",&choice);
	}
	close(fd);

	fd=open("joint_user.dat",O_RDWR | O_CREAT,0777);
	choice=1;
	joint_user j_user;
	printf("Please enter the account name of the joint user: ");
	scanf(" %[^\n]",j_user.accname);
	printf("Please enter the password(max 20 characters): ");
	scanf(" %[^\n]",j_user.password);
	j_user.userID=0001;
	j_user.balance=1000;
	j_user.account_no=(j_user.userID)+100000;
	printf("Your userID is : %d\n",j_user.userID);
	strcpy(j_user.status,"ACTIVE");
	write(fd,&j_user,sizeof(joint_user));

	printf("Do you want to add another(0/1)? ");
	scanf("%d",&choice);

	while(choice)
	{
		printf("Please enter the accout name of the joint user: ");
		scanf(" %[^\n]",j_user.accname);
		printf("Please enter the password(max 20 characters): ");
		scanf(" %[^\n]",j_user.password);
		j_user.userID=get_joint_user_id();
		j_user.balance=1000;
		j_user.account_no=(j_user.userID)+100000;
		printf("Your userID is : %d\n",j_user.userID);
		strcpy(j_user.status,"ACTIVE");
		write(fd,&j_user,sizeof(joint_user));
		printf("Do you want to add another(0/1)? ");
		scanf("%d",&choice);
	}
	close(fd);
	return 0;
}

