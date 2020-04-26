#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<conio.h>
#include<ctype.h>
#include <windows.h>	 

void fullscreen()
{  keybd_event(VK_MENU,
               0x38,
                0,
                0);
    keybd_event(VK_RETURN,
                0x1c,
                0,
                0);
    keybd_event(VK_RETURN,
                0x1c,
                KEYEVENTF_KEYUP,
                0);
    keybd_event(VK_MENU,
                0x38,
                KEYEVENTF_KEYUP,
                0);
}
int max_akun = 100;
int jmlh_akun;
//STRUKTUR DATA
struct data_akun{
	char id[9];
	char alamat[50];
	char nama[90];
	char tgl_lahir[50];
	char sex[10];
	char pin[8];
	int deposit;
}akun[100];
//PROCESS
int jumlah_akun(){
	FILE *fp = fopen("account_data.txt","r+");
	fscanf(fp,"%d\n",&jmlh_akun);
	fclose(fp);
	return jmlh_akun;
}
int jumlah_akun_hidden(){
	FILE *fp = fopen("account_hidden.txt","r+");
	fscanf(fp,"%d\n",&jmlh_akun);
	fclose(fp);
	return jmlh_akun;
}
int is_num(char cek_karakter){
	if(cek_karakter<'0' || cek_karakter>'9') return 0;
	return 1;
}
int cek_format_tanggal(struct data_akun ptr[]){
	// jika tidak sesuai format, return 0.
	if(!is_num(ptr[jmlh_akun].tgl_lahir[0]) || !is_num(ptr[jmlh_akun].tgl_lahir[1]) || ptr[jmlh_akun].tgl_lahir[2]!='/' || !is_num(ptr[jmlh_akun].tgl_lahir[3]) || !is_num(ptr[jmlh_akun].tgl_lahir[4]) || ptr[jmlh_akun].tgl_lahir[5]!='/' || !is_num(ptr[jmlh_akun].tgl_lahir[6]) || !is_num(ptr[jmlh_akun].tgl_lahir[7]) || !is_num(ptr[jmlh_akun].tgl_lahir[8]) || !is_num(ptr[jmlh_akun].tgl_lahir[9])) return 0;
	// sesuaikan digit tanggal.
	if(ptr[jmlh_akun].tgl_lahir[0]>'3') return 0;
	if(ptr[jmlh_akun].tgl_lahir[0]=='3' && ptr[jmlh_akun].tgl_lahir[1]>'1') return 0;
	if(ptr[jmlh_akun].tgl_lahir[0]=='0' && ptr[jmlh_akun].tgl_lahir[1]=='0') return 0;
	// sesuaikan digit bulan.
	if(ptr[jmlh_akun].tgl_lahir[3]>'1') return 0;
	if(ptr[jmlh_akun].tgl_lahir[3]=='1' && ptr[jmlh_akun].tgl_lahir[4]>'2') return 0;
	if(ptr[jmlh_akun].tgl_lahir[3]=='0' && ptr[jmlh_akun].tgl_lahir[4]=='0') return 0;
	// sesuaikan digit tanggal di bulan tertentu.
	if(ptr[jmlh_akun].tgl_lahir[3]=='0' && ptr[jmlh_akun].tgl_lahir[4]=='2'){ // Februari.
		if(ptr[jmlh_akun].tgl_lahir[0]=='3') return 0;
		if(ptr[jmlh_akun].tgl_lahir[0]=='2' && ptr[jmlh_akun].tgl_lahir[1]=='9'){
			if( ( (ptr[jmlh_akun].tgl_lahir[8]-'0')*10 + (ptr[jmlh_akun].tgl_lahir[9]-'0') ) % 4 != 0 ) return 0; // jika bukan tahun kabisat.
		}
	}
	else{
		if(ptr[jmlh_akun].tgl_lahir[4]<'7' && (ptr[jmlh_akun].tgl_lahir[4]-'0')%2==0){ // April atau Juni.
			if(ptr[jmlh_akun].tgl_lahir[0]=='3' && ptr[jmlh_akun].tgl_lahir[1]=='1') return 0;
		}
		else{
			if(ptr[jmlh_akun].tgl_lahir[4]=='9' || ptr[jmlh_akun].tgl_lahir[4]=='1'){ // September atau November.
				if(ptr[jmlh_akun].tgl_lahir[0]=='3' && ptr[jmlh_akun].tgl_lahir[1]=='1') return 0;
			}
		}
	}
	
	return 1;
}
int cek_format_id(struct data_akun ptr[]){
	if(!is_num(ptr[jmlh_akun].id[0])) return 0;
	if(!is_num(ptr[jmlh_akun].id[1])) return 0;
	if(!is_num(ptr[jmlh_akun].id[2])) return 0;
	if(!is_num(ptr[jmlh_akun].id[4])) return 0;
	if(!is_num(ptr[jmlh_akun].id[5])) return 0;
	if(!is_num(ptr[jmlh_akun].id[6])) return 0;
	if(!is_num(ptr[jmlh_akun].id[7])) return 0;
	return 1;
}
int cek_format_pin(struct data_akun ptr[]){
	if(!is_num(ptr[jmlh_akun].pin[0])) return 0;
	if(!is_num(ptr[jmlh_akun].pin[1])) return 0;
	if(!is_num(ptr[jmlh_akun].pin[2])) return 0;
	if(!is_num(ptr[jmlh_akun].pin[3])) return 0;
	if(!is_num(ptr[jmlh_akun].pin[4])) return 0;
	if(!is_num(ptr[jmlh_akun].pin[5])) return 0;
	return 1;
}
int cari_id(struct data_akun ptr[],char *id_search){ // return indeks jika ditemukan; return -1 jika tidak ditemukan.
	int indeks;
	for(indeks=0; indeks<=jmlh_akun; indeks++){
		if(strcmp(ptr[indeks].id, id_search) == 0) return indeks;
	}
	return -1;
}
int konfirmasi_pin(struct data_akun ptr[],char *pin_search){
	int indeks;
	int i;
	for(i = 0; i <= strlen(ptr[indeks].pin);i++){
		if(strcmp(ptr[indeks].pin,pin_search) == 0) return indeks; 
	}
	return -1;
}
int delete_akun_initialize(struct data_akun ptr[],int indeks){
	int i; 
	jmlh_akun = jmlh_akun - 1;
    for (i = indeks; i <= jmlh_akun; i++){
        ptr[i] = ptr[i + 1]; 
        getch();
	}
    return jmlh_akun; 
}
void generate_kode_petugas(char *kode){
	srand(time(NULL));
	kode[0] = rand()%26+'A';
	kode[1] = rand()%10+'0';
	kode[2] = rand()%26+'A';
	kode[3] = rand()%10+'0';
	kode[4] = rand()%26+'A';
	kode[5] = rand()%10+'0';
	kode[6] = rand()%26+'A';
	kode[7] = rand()%10+'0';
	kode[8] = rand()%26+'A';
	kode[9] = rand()%10+'0';
	kode[10] = rand()%26+'A';
	kode[11] = rand()%10+'0';
	
	return;
}
//FILE PROCESSING
void read_file(struct data_akun ptr[],int n){
	int i;
	jumlah_akun();
	FILE *fp = fopen("account_data.txt","r+");
	fscanf(fp,"%d\n",&jmlh_akun);
	fscanf(fp,"-----------------------------------------------------------------------------\n");
	fscanf(fp,"|                          Account Informations                             |\n");
	fscanf(fp,"=============================================================================\n");
	fscanf(fp,"|ID        |Nama             |Address                  |Birth Date     |Sex |\n");
	fscanf(fp,"-----------------------------------------------------------------------------\n");
	for(i=1;i<=jmlh_akun;i++){
		fscanf(fp,"%s %s %s %s %s\n",ptr[i].id,ptr[i].nama,ptr[i].alamat,ptr[i].tgl_lahir,&ptr[i].sex);
	}
	fclose(fp);
}
void read_file_hidden(struct data_akun ptr[],int n){
	int i;
	jumlah_akun_hidden();
	FILE *fp = fopen("account_hidden.txt","r+");
	fscanf(fp,"%d\n",&jmlh_akun);
	for(i = 1;i <= jmlh_akun;i++){
		fscanf(fp,"%s = %d = %s",ptr[i].id,&ptr[i].deposit,ptr[i].pin);
	}
}
void show_database(struct data_akun ptr[],int n){
	int i;
	system("color 80");
	jumlah_akun();
	printf("\n\n");
	printf("\t\t\t-------------------------------------------------------------------------------------------------------------\n");
	printf("\t\t\t|                                                Account Databases                                          |\n");
	printf("\t\t\t=============================================================================================================\n");
	printf("\t\t\t|ID        |Nama                          |Address                                   |Birth Date    |Sex    |\n");
	printf("\t\t\t-------------------------------------------------------------------------------------------------------------\n");
	for(i=1;i<=jmlh_akun;i++){
		printf("\t\t\t|%9s | %28s | %40s | %12s | %5s |\n",ptr[i].id,ptr[i].nama,ptr[i].alamat,ptr[i].tgl_lahir,ptr[i].sex);
	}
	printf("\t\t\t-------------------------------------------------------------------------------------------------------------\n");
}
void show_deposit(struct data_akun ptr[],int n){
	int i = 0,j = 0,tmp1 , m;
	char tmp2[9]; //tmp 2 = id
	char tmp3[90]; //tmp 3 = nama
	jumlah_akun();
	printf("\n\n");
	printf("\t\t\t\t\t----------------------------------------------------------------\n");
	printf("\t\t\t\t\t|                      Account's Deposit                       |\n");
	printf("\t\t\t\t\t================================================================\n");
	printf("\t\t\t\t\t|ID        |Nama                          |Deposit             |\n");
	printf("\t\t\t\t\t----------------------------------------------------------------\n");
    for (i = 0; i <= jmlh_akun; i++) {   // loop n times - 1 per element
        for (j = 0; j <= jmlh_akun - i - 1; j++) { // last i elements are sorted already
            if (ptr[j].deposit > ptr[j + 1].deposit) {  // swop if order is broken
                tmp1 = ptr[j].deposit;
                strcpy(tmp2,ptr[j].id);
                strcpy(tmp3,ptr[j].nama);
                ptr[j].deposit = ptr[j + 1].deposit;
                m = j + 1;
                strcpy(ptr[j].id, ptr[m].id);
                strcpy(ptr[j].nama, ptr[m].nama);
                ptr[j + 1].deposit = tmp1;
                strcpy(ptr[m].id, tmp2);
                strcpy(ptr[m].nama, tmp3);
            }
        }
    }
	for(i=1;i<=jmlh_akun;i++){
		printf("\t\t\t\t\t|%9s | %28s | %18d |\n",ptr[i].id,ptr[i].nama,ptr[i].deposit);
	}
	printf("\t\t\t\t\t----------------------------------------------------------------\n");
}
void write_file(struct data_akun ptr[],int n){
	int i;
	FILE *fp = fopen("account_data.txt","w+");
	fprintf(fp,"%d\n",jmlh_akun);
	fprintf(fp,"-----------------------------------------------------------------------------\n");
	fprintf(fp,"|                          Account Informations                             |\n");
	fprintf(fp,"=============================================================================\n");
	fprintf(fp,"|ID        |Nama             |Address                  |Birth Date     |Sex |\n");
	fprintf(fp,"-----------------------------------------------------------------------------\n");
	for(i=1;i<=jmlh_akun;i++){
		fprintf(fp,"%s %s %s %s %s\n",ptr[i].id,ptr[i].nama,ptr[i].alamat,ptr[i].tgl_lahir,ptr[i].sex);
	}
	fclose(fp);
}
void write_file_hidden(struct data_akun ptr[],int n){
	int i;
	FILE *fp = fopen("account_hidden.txt","w+");
	fprintf(fp,"%d\n",jmlh_akun);
	for(i = 1;i<=jmlh_akun;i++){
		fprintf(fp,"%s = %d = %s\n",ptr[i].id,ptr[i].deposit,ptr[i].pin);
	}
	fclose(fp);
}
/*ADMIN MODE*/
int input_data_akun(struct data_akun ptr[]){
	int i,ulang;
	char confirm;
	jumlah_akun();
	jmlh_akun = jmlh_akun + 1;
	printf("\n\t\t\t\t\t\t\t\t________________________________________\n");
	printf("\n\t\t\t\t\t\t\t\t|\t       WADIK'S BANK           \t|\n");
	printf("\t\t\t\t\t\t\t\t________________________________________\n");
	printf("\n\n________________________________________________________________________________________________________________________________________________________________________");
	printf("\n\n\t\t\t\t\t\t\t\t\t   CREATE NEW ACCOUNT");
    printf("\n________________________________________________________________________________________________________________________________________________________________________");
	srand(time(NULL));
	ptr[jmlh_akun].id[0] = rand()%9+'0';
	ptr[jmlh_akun].id[1] = rand()%9+'0';
	ptr[jmlh_akun].id[2] = rand()%9+'0';
	ptr[jmlh_akun].id[3] = rand()%9+'0';
	ptr[jmlh_akun].id[4] = rand()%9+'0';
	ptr[jmlh_akun].id[5] = rand()%9+'0';
	ptr[jmlh_akun].id[6] = rand()%9+'0';
	ptr[jmlh_akun].id[7] = rand()%9+'0';
	fflush(stdin);
	do{
		printf(" \n\n\n Name = ");
		gets(ptr[jmlh_akun].nama);
		if(strlen(ptr[jmlh_akun].nama) < 0 || strlen(ptr[jmlh_akun].nama) > 21){
			printf("\n Characters cannot be more than 21\n");
			getch();
		}
	}while(strlen(ptr[jmlh_akun].nama) < 0 || strlen(ptr[jmlh_akun].nama) > 21);
	do{
		printf("\n Address = ");
		gets(ptr[jmlh_akun].alamat);
		if(strlen(ptr[jmlh_akun].alamat) < 0 || strlen(ptr[jmlh_akun].alamat) > 40){
			printf("Characters cannot be more than 21\n");
			getch();
		}
	}while(strlen(ptr[jmlh_akun].alamat) < 0 || strlen(ptr[jmlh_akun].alamat) > 40);
	do{
		printf("\n Birth Date = ");
		gets(ptr[jmlh_akun].tgl_lahir);
		if(cek_format_tanggal(akun) == 0){
			printf("\n  X-------------- Date Format = dd/mm/yyyy --------------X\n");
			getch();
		}
	}while(cek_format_tanggal(akun) == 0);
	do{
		ulang = 1;
		printf("\n Sex [M/W] = ");
		fflush(stdin);
		gets(ptr[jmlh_akun].sex);
		if(strlen(ptr[jmlh_akun].sex) > 1){
			printf("\n Only 1 Character !\n ");
			getch();
		}
	}while(strlen(ptr[jmlh_akun].sex) > 1);
	do{
		printf("\n Login Pin = ");
		fflush(stdin);
		gets(ptr[jmlh_akun].pin);
		if(strlen(ptr[jmlh_akun].pin) < 5){
			printf("\n The pin is only in number format and not more than 6 digits\n");
		}
	}while(strlen(ptr[jmlh_akun].pin) < 5);
	ptr[jmlh_akun].deposit = 500000;
	
	/*konversi whitespace*/
		while (ptr[jmlh_akun].nama[i])
  	{
    	if (isspace(ptr[jmlh_akun].nama[i])) 
        	ptr[jmlh_akun].nama[i]='_';
    	i++;
  	}
  	
  	i = 0;
  		while (ptr[jmlh_akun].alamat[i])
  	{
    	if (isspace(ptr[jmlh_akun].alamat[i])) 
        	ptr[jmlh_akun].alamat[i]='_';
    	i++;
  	}
    printf("\n________________________________________________________________________________________________________________________________________________________________________");
  	printf("\n\n   Confirm New Account [Y/N]? ");
  	confirm = getch();
  	if(confirm == 'y' || confirm == 'Y'){
  	printf("\n\n_______________________________________________________________");
	printf("\n\n | Your account was successfully created | Your ID = %s  | Thank You |",ptr[jmlh_akun].id);
	printf("\n\n | Press ENTER to Back |");
	write_file(akun,jmlh_akun);
	write_file_hidden(akun,jmlh_akun);
	}else
	printf("\n\n   You Canceled to Create New Account!");
	getch();
	return;
}
void edit_data_admin(struct data_akun ptr[]){
	int i;
	int ulang,wrong,ulang1;
	int jumlah;
	char id[8];
	char confirm,confirm_ubah;
	int indeks;
	int jmlh_akun;
	jumlah_akun();
	do{do{do{
	system("cls");
	printf("\n\t\t\t\t\t\t\t\t________________________________________\n");
	printf("\n\t\t\t\t\t\t\t\t|\t       WADIK'S BANK           \t|\n");
	printf("\t\t\t\t\t\t\t\t________________________________________\n");
	printf("\n\n________________________________________________________________________________________________________________________________________________________________________");
	printf("\n\n\t\t\t\t\t\t\t\t\t   EDIT ACCOUNT");
    printf("\n________________________________________________________________________________________________________________________________________________________________________");
	show_database(akun,jmlh_akun);
	printf("\n");
	
	fflush(stdin);
	printf("\n Input ID = ");
	gets(id);
	if(strlen(id) != 8 || cek_format_id == 0){
		printf("\n\n| ID Invalid | Press X to Back |");
		wrong = getch();
		if(wrong == 'x'|| wrong == 'X'){
			ulang = 0;
			return;
		}
	}else{
			ulang == 1;
	}
	}while(strlen(id) != 8 || cek_format_id == 0 || ulang == 1);
	indeks = cari_id(akun,id);
	if(indeks != -1){
		printf(" You are about to change the account info = \n");
		printf("\n\t ID : %s \n",ptr[indeks].id);
		printf("\t Name : %s \n",ptr[indeks].nama);
		printf("\t Address : %s \n",ptr[indeks].alamat);
		printf("\t Birth Date : %s \n",ptr[indeks].tgl_lahir);
		printf("\t Sex : %s \n",ptr[indeks].sex);
		printf("\t Pin : %s \n",ptr[indeks].pin);
		printf("\t Deposit : %d \n",ptr[indeks].deposit);
		printf("\n Continue?[Y/N]");
		confirm_ubah = getch();
		if(confirm_ubah == 'y'){
			ulang1 = 0;
		}else{
			ulang1 = 1;
		}
	}else{
		printf("\n X-------------Data Not Found-------------X | Press X to Back! |\n");
		wrong = getch();
		if(wrong == 'x' || wrong == 'X'){
			ulang1 = 0;
			return;
		}else{
		ulang1 = 1;
		}
	}
	}while(ulang1 == 1);
	system("cls");
	printf("\n\t\t\t\t\t\t\t\t________________________________________\n");
	printf("\n\t\t\t\t\t\t\t\t|\t       WADIK'S BANK           \t|\n");
	printf("\t\t\t\t\t\t\t\t________________________________________\n");
	printf("\n\n________________________________________________________________________________________________________________________________________________________________________");
	printf("\n\n\t\t\t\t\t\t\t\t\t   EDIT ACCOUNT");
    printf("\n________________________________________________________________________________________________________________________________________________________________________");
	fflush(stdin);
	do{
		printf("\n\n Name = ");
		gets(ptr[indeks].nama);
		if(strlen(ptr[indeks].nama) < 0 || strlen(ptr[indeks].nama) > 21){
			printf(" Characters cannot be more than 21\n");
			getch();
		}
	}while(strlen(ptr[indeks].nama) < 0 || strlen(ptr[indeks].nama) > 21);
	do{
		printf("\n Address = ");
		gets(ptr[indeks].alamat);
		if(strlen(ptr[indeks].alamat) < 0 || strlen(ptr[indeks].alamat) > 40){
			printf(" Characters cannot be more than 30\n");
			getch();
		}
	}while(strlen(ptr[indeks].alamat) < 0 || strlen(ptr[indeks].alamat) > 40);
	do{
		printf("\n Birth Date = ");
		gets(ptr[indeks].tgl_lahir);
		if(cek_format_tanggal(akun) == 0){
			printf("\n  X-------------- Date Format dd/mm/yyyy --------------X");
			getch();
		}
	}while(cek_format_tanggal(akun) == 0);
	do{
		ulang = 1;
		printf("\n Sex [M/W] = ");
		fflush(stdin);
		gets(ptr[indeks].sex);
		if(strlen(ptr[indeks].sex) < 0){
			printf("\n Only One Character ! ");
			getch();
		}
	}while(strlen(ptr[indeks].sex) > 1);
	do{
		printf("\n Change Pin = ");
		fflush(stdin);
		gets(ptr[indeks].pin);
		if(strlen(ptr[indeks].pin) < 5){
			printf("\n The pin is only in number format and not more than 6 digits!\n");
		}
	}while(strlen(ptr[indeks].pin) < 5);
	
		printf("\n Add Deposit = ");
		scanf("%d",&jumlah);
		ptr[indeks].deposit = ptr[indeks].deposit + jumlah;
		printf("\n Deposit %s = %d",ptr[indeks].nama,ptr[indeks].deposit);
		getch();
		
	i = 0;
		/*konversi whitespace*/
		while (ptr[indeks].nama[i])
  	{
    	if (isspace(ptr[indeks].nama[i])) 
        	ptr[indeks].nama[i]='_';
    	i++;
  	}
  	
  	i = 0;
  		while (ptr[indeks].alamat[i])
  	{
    	if (isspace(ptr[indeks].alamat[i])) 
        	ptr[indeks].alamat[i]='_';
    	i++;
  	}
  	
  	printf("\n\n Confirm Edit Account ?[Y/N]");
	confirm = getch();
  	if(confirm == 'y'){
  	printf("\n\n____________________________________________________________________________________________");
	printf("\n\n | %s's Has Been Changed  | %s's ID = %s  | Thank You! |",ptr[indeks].nama,ptr[indeks].nama,ptr[indeks].id);
	printf("\n\n | Press ENTER to Back |");
	ulang = 0;
	write_file(akun,jmlh_akun);
	write_file_hidden(akun,jmlh_akun);
	getch();
	}else{
	printf("\n You Canceled to Edit Account!");
	getch();
	read_file(akun,jmlh_akun);
	read_file_hidden(akun,jmlh_akun);
	return;
	}
}
while(ulang == 1);
}
void delete_akun(struct data_akun ptr[]){
	char id[8];
	int i,ulang;
	int indeks;
	char konfirmasi,konfirmasi1;
	do{
	system("cls");
	printf("\n\t\t\t\t\t\t\t\t________________________________________\n");
	printf("\n\t\t\t\t\t\t\t\t|\t       WADIK'S BANK           \t|\n");
	printf("\t\t\t\t\t\t\t\t________________________________________\n");
	printf("\n\n________________________________________________________________________________________________________________________________________________________________________");
	printf("\n\n\t\t\t\t\t\t\t\t\t   DELETE ACCOUNT");
    printf("\n________________________________________________________________________________________________________________________________________________________________________");
	show_database(akun,jmlh_akun);
	printf("\n");
	do{
	fflush(stdin);
	printf(" Input ID : ");
	gets(id);
	}while(strlen(id) != 8 || cek_format_id == 0);
	indeks = cari_id(akun,id);
	if(indeks != -1){
		printf("\n You Will Delete Account : \n");
		printf(" ID : %s \n",ptr[indeks].id);
		printf(" Name : %s \n",ptr[indeks].nama);
		printf(" Address : %s \n",ptr[indeks].alamat);
		printf(" Birth Date : %s \n",ptr[indeks].tgl_lahir);
		printf(" Sex : %s \n",ptr[indeks].sex);
		printf("\n Delete ? [y/n] = ");
		scanf("%c",&konfirmasi);
		if(konfirmasi == 'y'){
			printf("\n Delete Account Successful! :)");
			jmlh_akun = delete_akun_initialize(akun,indeks);
			write_file(akun,jmlh_akun);
			write_file_hidden(akun,jmlh_akun);
		}else
		printf("\n You Canceled to Delete Account, Repeat?[Y/N]");
		konfirmasi1 = getch();
		if(konfirmasi1 == 'y'){
			ulang = 1;
		}else
			ulang = 0;
	}else{
		printf(" Data Is Not Found \n");
		getch();
		ulang = 1;
	}
}while(ulang == 1 || konfirmasi1 == 'y');
}
/*USER MODE*/
int login_user(struct data_akun ptr[]){
	fflush(stdin);
	int indeks,ulang;
	char id[8];
	char pin[8];
	char wrong;
	do{
	system("cls");
	printf("\n\n\t\t\t _______________________________________________________________________________________________________________________                            ");
	printf("\n\t\t\t|\t\t\t\t __        ______       _______     _    __     __                                      |");
	printf("\n\t\t\t|\t\t\t\t|  |      /      \\     /  _____|   |_|  |  \\   |  |                                     |");
	printf("\n\t\t\t|\t\t\t\t|  |     /   /\\   \\   /  / _____    _   |   \\  |  |                                     |");
	printf("\n\t\t\t|\t\t\t\t|  |    |   |  |   | |  | |___  |  | |  |    \\ |  |                                     |");
	printf("\n\t\t\t|\t\t\t\t|  |___  \\   \\/   /   \\  \\\____| |  | |  |  |\\ \\|  |                                     |");
	printf("\n\t\t\t|\t\t\t\t|______|  \\______/     \\________|  |_|  |__| \\____|                                     |");
	printf("\n\t\t\t|_______________________________________________________________________________________________________________________|");
	printf(" \n\n\n\n\n Input ID : ");
	gets(id);
	if(strlen(id) != 8 || cek_format_id == 0){
		printf("\n\n| ID Invalid | Press X to Back |");
		wrong = getch();
		if(wrong == 'x'|| wrong == 'X'){
			ulang == 1;
			return -2;
		}
	}else{
		ulang == 0;
	}
	}while(strlen(id) != 8 || cek_format_id == 0 || ulang == 1);
	indeks = cari_id(akun,id);
	if(indeks != -1){
		printf(" \n\t ID = %s \n",ptr[indeks].id);
		printf(" \n\t Name = %s \n",ptr[indeks].nama);
		printf(" \n\t PIN = ");
		gets(pin);
		if(strcmpi(pin,ptr[indeks].pin) == 0){
			printf("\n You Are Logged In!");
			getch();
			return indeks;
		}else
			printf("\n Wrong PIN![Enter to Back]");
			getch();
		return -1;
	}else{
	printf("\n| ID is Wrong / Invalid | Press X to Back |");
	wrong = getch();
	if(wrong == 'x')
	return -2;
	else
	return -1;
	}
	return -1;
}
void user_info(struct data_akun ptr[],int indeks){

	printf("\n\t\t\t\t\t\t\t\t________________________________________\n");
	printf("\n\t\t\t\t\t\t\t\t|\t       WADIK'S BANK           \t|\n");
	printf("\t\t\t\t\t\t\t\t________________________________________\n");
	printf("\n\n________________________________________________________________________________________________________________________________________________________________________");
	printf("\n\n\t\t\t\t\t\t\t\t\t   Account Info");
    printf("\n________________________________________________________________________________________________________________________________________________________________________");
	printf("\n\n ID : %s\n",ptr[indeks].id);
	printf("\n Name : %s \n",ptr[indeks].nama);
	printf("\n Address : %s \n",ptr[indeks].alamat);
	printf("\n Birth Date : %s \n",ptr[indeks].tgl_lahir);
	printf("\n Sex : %s \n",ptr[indeks].sex);
	printf("\n Deposit : Rp.%d \n",ptr[indeks].deposit);
	printf("\n\n Press Enter to Back");
}
void user_cash(struct data_akun ptr[],int indeks){
	int select1,nominal,loop;
	system("color 60");
	do{
	char kode[20];
	system("cls");
	printf("\n\t\t\t\t\t\t\t\t________________________________________\n");
	printf("\n\t\t\t\t\t\t\t\t|\t       WADIK'S BANK           \t|\n");
	printf("\t\t\t\t\t\t\t\t________________________________________\n");
	printf("\n\n________________________________________________________________________________________________________________________________________________________________________");
	printf("\n\n\tTake Cash                           \t\t\t\t\t\t\t\t\t\t\t\tDeposit : %d ",ptr[indeks].deposit);
	printf("\n\n________________________________________________________________________________________________________________________________________________________________________");
	printf("\n\nChoose Amount Cash : \n\n");
	printf("  1. Rp.50000           2. Rp.100000\n\n");
	printf("  3. Rp.150000          4. Rp.200000\n\n");
	printf("  5. Rp.250000          6. Rp.300000\n\n");
	printf("  7. Choose Nominal   8. Exit\n\n\n");
	printf(" Your Choice :");
	scanf("%d",&select1);
	switch(select1){
		case 1 : 	printf("\n_______________________________________________________________________________________________________________\n");
					printf("\n You Will Take Cash For Rp. 50000? [Press Enter to Continue]\n");
					printf("_______________________________________________________________________________________________________________\n");
					getch();
					if(ptr[indeks].deposit >= 50000){
					ptr[indeks].deposit = ptr[indeks].deposit - 50000;
					generate_kode_petugas(kode);
					printf("\n Verify the code below to the officer \n");
					printf(" | %s | \n",kode);
					printf("_______________________________________________________________________________________________________________\n");
					printf(" Your Current Deposit : \n");
					printf(" Rp. %d",ptr[indeks].deposit);
					write_file_hidden(akun,jmlh_akun);
					break;
					loop = 0;
					}else{
					printf(" Deposit insufficient!");
					getch();
					loop = 1;
					break;}
		case 2 :	printf("\n_______________________________________________________________________________________________________________\n");
					printf("\n You Will Take Cash For Rp. 100000? [Press Enter to Continue]\n");
					printf("_______________________________________________________________________________________________________________\n");
					getch();
					if(ptr[indeks].deposit >= 100000){
					ptr[indeks].deposit = ptr[indeks].deposit - 100000;
					generate_kode_petugas(kode);
					printf("\n Verify The Code Below to The Officer\n");
					printf(" | %s | \n",kode);
					printf("_______________________________________________________________________________________________________________\n");
					printf(" Your Current Deposit : \n");
					printf(" Rp. %d",ptr[indeks].deposit);
					write_file_hidden(akun,jmlh_akun);
					loop = 0;
					break;
					}else{
					printf(" Deposit Insufficient!");
					getch();
					loop = 1;
					break;
					}
		case 3 :	printf("\n_______________________________________________________________________________________________________________\n");
					printf("\n You Will Take Cash For Rp. 150000? [Press Enter to Continue]\n");
					printf("_______________________________________________________________________________________________________________\n");
					getch();
					if(ptr[indeks].deposit >= 150000){
					ptr[indeks].deposit = ptr[indeks].deposit - 150000;
					generate_kode_petugas(kode);
					printf("\n Verify the Code Below to The Officer \n");
					printf(" | %s | \n",kode);
					printf("_______________________________________________________________________________________________________________\n");
					printf(" Your Current Deposit : \n");
					printf(" Rp. %d",ptr[indeks].deposit);
					write_file_hidden(akun,jmlh_akun);
					loop = 0;
					break;
					}else{
					printf(" Deposit Insufficient!");
					getch();
					loop = 1;
					break;
					}
		case 4 : 	printf("\n_______________________________________________________________________________________________________________\n");
					printf("\n You Will Take Cash For Rp. 200000? [Press Enter to Continue]\n");
					printf("_______________________________________________________________________________________________________________\n");
					getch();
					if(ptr[indeks].deposit >= 200000){
					ptr[indeks].deposit = ptr[indeks].deposit - 200000;
					generate_kode_petugas(kode);
					printf("\n Verify the Code Below to The Officer \n");
					printf(" | %s | \n",kode);
					printf("_______________________________________________________________________________________________________________\n");
					printf(" Your Current Deposit : \n");
					printf(" Rp. %d",ptr[indeks].deposit);
					write_file_hidden(akun,jmlh_akun);
					loop = 0;
					break;
					}else{
					printf(" Deposit Insufficient!");
					getch();
					loop = 1;
					break;
					}
		case 5 :	printf("\n_______________________________________________________________________________________________________________\n");
					printf("\n You Will Take Cash For Rp. 250000? [Press Enter to Continue]\n");
					printf("_______________________________________________________________________________________________________________\n");
					getch();
					if(ptr[indeks].deposit >= 250000){
					ptr[indeks].deposit = ptr[indeks].deposit - 250000;
					generate_kode_petugas(kode);
					printf("\n Verify the Code Below to The Officer \n");
					printf(" | %s | \n",kode);
					printf("_______________________________________________________________________________________________________________\n");
					printf(" Your Current Deposit : \n");
					printf(" Rp. %d",ptr[indeks].deposit);
					write_file_hidden(akun,jmlh_akun);
					loop = 0;
					break;
					}else{
					printf(" Deposit Insufficient!");
					getch();
					loop = 1;
					break;
					}
		case 6 :	printf("\n_______________________________________________________________________________________________________________\n");
					printf("\n You Will Take Cash For Rp. 300000? [Press Enter to Continue]\n");
					printf("_______________________________________________________________________________________________________________\n");
					getch();
					if(ptr[indeks].deposit >= 300000){
					ptr[indeks].deposit = ptr[indeks].deposit - 300000;
					generate_kode_petugas(kode);
					printf("\n Verify the Code Below to The Officer\n");
					printf(" | %s | \n",kode);
					printf("_______________________________________________________________________________________________________________\n");
					printf("\n Your Current Deposit : \n");
					printf(" Rp. %d",ptr[indeks].deposit);
					write_file_hidden(akun,jmlh_akun);
					loop = 0;
					break;
					}else{
					printf(" Deposit Insufficient!");
					getch();
					loop = 1;
					break;
					}
		case 7 :	printf("\n_______________________________________________________________________________________________________________\n");
					printf("\n Input Nominal : ");
					scanf(" %d ",&nominal);
					printf(" You Will Take Cash For %d ? [Press Enter to Continue]\n",ptr[indeks].deposit);
					printf("_______________________________________________________________________________________________________________\n");
					getch();
					if(ptr[indeks].deposit >= nominal){
					ptr[indeks].deposit = ptr[indeks].deposit - nominal;
					generate_kode_petugas(kode);
					printf("\n Verify the Code Below to The Officer \n");
					printf(" | %s | \n",kode);
					printf("_______________________________________________________________________________________________________________\n");
					printf("\n Your Current Deposit : \n");
					printf(" Rp. %d",ptr[indeks].deposit);
					write_file_hidden(akun,jmlh_akun);
					loop = 0;
					break;
					}else{
					printf(" Deposit Insufficient!");
					getch();
					loop = 1;
					break;
					}
		case 8 : 	printf(" ENTER to Back");
					return;
	}
}while(select1 < 0 || select1 > 7 || loop == 1);
}
void user_transfer(struct data_akun ptr[],int indeks){
	char id[8];
	char confirm;
	char wrong;
	int ulang;
	int target,nominal,select;
	jumlah_akun();
	do{do{
	system("color 70");
	system("cls");
	printf("\n\t\t\t\t\t\t\t\t________________________________________\n");
	printf("\n\t\t\t\t\t\t\t\t|\t       WADIK'S BANK           \t|\n");
	printf("\t\t\t\t\t\t\t\t________________________________________\n");
	printf("\n\n________________________________________________________________________________________________________________________________________________________________________");
	printf("\n\n\t\t\t\t\t\t\t\t\t   TRANSFER ACCOUNT");
    printf("\n________________________________________________________________________________________________________________________________________________________________________");
	fflush(stdin);
	printf("\n\n Destination ID : ");
	gets(id);
	if(strlen(id) != 8 || cek_format_id == 0){
		printf(" ID Invalid | Press ENTER to Repeat | Press X to Back");
		wrong = getch();
		if(wrong == 'x'){
			ulang = 0;
			return;
		}else{
			ulang = 1;
		}
	}else{
		ulang = 0;
	}
	}while(strlen(id) != 8 || cek_format_id == 0 || ulang == 1);
	target = cari_id(akun,id);
	if(target != -1){
		printf("\n\tDestination ID = %s\n",ptr[target].id);
		printf("\n\tDestination Name = %s\n",ptr[target].nama);
		printf("\n\n | Is It Correct?[Y/N]");
		printf("\n_______________________________________________________________________________________________________________");
		confirm = getch();
		if((confirm == 'y') || (confirm == 'Y')){
	printf("\n\n\tTransfer Account                      \t\t\t\t\t\t\t\t\t\t\t\tDeposit : Rp.%d \n",ptr[indeks].deposit);
	printf("_______________________________________________________________________________________________________________");
	printf("\n\n Choose Amount Cash : \n\n");
	printf("  1. Rp.50000           2. Rp.100000\n\n");
	printf("  3. Rp.150000          4. Rp.200000\n\n");
	printf("  5. Rp.250000          6. Rp.300000\n\n");
	printf("  7. Choose Nominal   8. Exit\n\n\n");
	printf(" Your Choice :");
			scanf("%d",&select);
			switch(select){
				case 1 : 	printf("_______________________________________________________________________________________________________________\n");
							printf("\n You Will Trasfer Cash to %s's Account for Rp. 50000 [Press ENTER to continue]\n",ptr[target].nama);
							printf("_______________________________________________________________________________________________________________\n");
							getch();
							if(ptr[indeks].deposit >= 50000){
							ptr[target].deposit = ptr[target].deposit + 50000;
							ptr[indeks].deposit = ptr[indeks].deposit - 50000;
							printf("\n\t Transfer Succeed!");
							printf("\n\t Your current deposit :\n");
							printf("\t Rp. %d",ptr[indeks].deposit);
							write_file_hidden(akun,jmlh_akun);
							break;
							}else{
							printf("\n Deposit Insufficient! Press X to Back | ENTER to Repeat \n");
							wrong = getch();
								if(wrong == 'x'){
								ulang = 0;
								break;
								}else{
								ulang = 1;
								}break;
							}
				case 2 :	printf("_______________________________________________________________________________________________________________\n");
							printf("\n You Will Trasfer Cash to %s's Account for Rp. 100000 [Press ENTER to continue]\n",ptr[target].nama);
							printf("_______________________________________________________________________________________________________________\n");
							getch();
							if(ptr[indeks].deposit >= 100000){
							ptr[target].deposit = ptr[target].deposit + 100000;
							ptr[indeks].deposit = ptr[indeks].deposit - 100000;
							printf("\n\t Transfer Succeed!");
							printf("\n\t Your current deposit :\n");
							printf("\t Rp. %d",ptr[indeks].deposit);
							write_file_hidden(akun,jmlh_akun);
							break;
							}else{
							printf("\n Deposit Insufficient! Press X to Back | ENTER to Repeat\n");
							wrong = getch();
								if(wrong == 'x'){
								ulang = 0;
								break;
								}else{
								ulang = 1;
								}break;
							}
				case 3 :	printf("_______________________________________________________________________________________________________________\n");
							printf("\n You Will Trasfer Cash to %s's Account for Rp. 150000 [Press ENTER to continue]\n",ptr[target].nama);
							printf("_______________________________________________________________________________________________________________\n");
							getch();
							if(ptr[indeks].deposit >= 150000){
							ptr[target].deposit = ptr[target].deposit + 150000;
							ptr[indeks].deposit = ptr[indeks].deposit - 150000;
							printf("\n\t Transfer Succeed!");
							printf("\n\t Your current deposit \n");
							printf("\t Rp. %d",ptr[indeks].deposit);
							write_file_hidden(akun,jmlh_akun);
							break;
							}else{
							printf("\n Deposit Insufficient! Press X to Back | ENTER to Repeat\n");
							wrong = getch();
								if(wrong == 'x'){
								ulang = 0;
								break;
								}else{
								ulang = 1;
								}break;
							}
			case 4 :		printf("_______________________________________________________________________________________________________________\n");
							printf("\n You Will Trasfer Cash to %s's Account for Rp. 200000 [Press ENTER to continue]\n",ptr[target].nama);
							printf("_______________________________________________________________________________________________________________\n");
							getch();
							if(ptr[indeks].deposit >= 200000){
							ptr[target].deposit = ptr[target].deposit + 200000;
							ptr[indeks].deposit = ptr[indeks].deposit - 200000;
							printf("\n\t Transfer Succeed!");
							printf("\n\t Your current deposit \n");
							printf("\t Rp. %d",ptr[indeks].deposit);
							write_file_hidden(akun,jmlh_akun);
							break;
							}else{
							printf("\n Deposit Insufficient! Press X to Back | ENTER to Repeat\n");
							wrong = getch();
								if(wrong == 'x'){
								ulang = 0;
								break;
								}else{
								ulang = 1;
								}break;
							}
				case 5 :	printf("_______________________________________________________________________________________________________________\n");
							printf("\n You Will Trasfer Cash to %s's Account for Rp. 250000 [Press ENTER to continue]\n",ptr[target].nama);
							printf("_______________________________________________________________________________________________________________\n");
							getch();
							if(ptr[indeks].deposit >= 250000){
							ptr[target].deposit = ptr[target].deposit + 250000;
							ptr[indeks].deposit = ptr[indeks].deposit - 250000;
							printf("\n\t Transfer Succeed!");
							printf("\n\t Your current deposit \n");
							printf("\t Rp. %d",ptr[indeks].deposit);
							write_file_hidden(akun,jmlh_akun);
							break;
							}else{
							printf("\n Deposit Insufficient! Press X to Back | ENTER to Repeat\n");
							wrong = getch();
								if(wrong == 'x'){
								ulang = 0;
								break;
								}else{
								ulang = 1;
								}break;
							}
				case 6 	:	printf("_______________________________________________________________________________________________________________");
							printf("\n You Will Trasfer Cash to %s's Account for Rp. 300000 [Press ENTER to continue]\n",ptr[target].nama);
							printf("_______________________________________________________________________________________________________________\n");
							getch();
							if(ptr[indeks].deposit >= 300000){
							ptr[target].deposit = ptr[target].deposit + 300000;
							ptr[indeks].deposit = ptr[indeks].deposit - 300000;
							printf("\n\t Transfer Succeed!");
							printf("\n\t Your current deposit \n");
							printf("\t Rp. %d",ptr[indeks].deposit);
							write_file_hidden(akun,jmlh_akun);
							break;
							}else{
							printf("\n Deposit Insufficient! Press X to Back | ENTER to Repeat\n");
							wrong = getch();
								if(wrong == 'x'){
								ulang = 0;
								break;
								}else{
								ulang = 1;
								}break;
							}
				case 7 :	printf("_______________________________________________________________________________________________________________");
							printf("\n\n\t Input Nominal : ");
							scanf("%d",&nominal);
							printf("\n You Will Trasfer Cash to %s Account Rp. %d [Press ENTER to continue]\n",ptr[target].nama,nominal);
							printf("_______________________________________________________________________________________________________________\n");
							getch();
							if(ptr[indeks].deposit >= nominal){
							ptr[target].deposit = ptr[target].deposit + nominal;
							ptr[indeks].deposit = ptr[indeks].deposit - nominal;
							printf("\n\t Transfer Successful!");
							printf("\n\t Your current deposit \n");
							printf("\t Rp. %d",ptr[indeks].deposit);
							write_file_hidden(akun,jmlh_akun);
							break;
							}else{
							printf("\n Deposit Insufficient! Press X to Back | ENTER to Repeat\n");
							wrong = getch();
								if(wrong == 'x'){
								ulang = 0;
								break;
								}else{
								ulang = 1;
								}break;
							}
				case 8 : 	break;
				}
		}else{
		printf("\n\nYou Have Canceled the Transaction | Press X to Back to Menu |");
		wrong = getch();
			if(wrong == 'x'){
				ulang = 0;
			}else{
				ulang = 1;
			}
		}
	}else{
	printf(" ID not Found | Press X to Back to Menu | ENTER to Repeat ");
	wrong = getch();
		if(wrong == 'x'){
			ulang = 0;
		}else{
			ulang = 1;
		}
	}
}while(ulang == 1);
}
//TAMPILAN//
void menu_mode(){
	system("color C0");
	printf(" ");
	printf("\t\t ______                    ______  _________   __           ___________     __________         ____________________         _________");
	printf("\n\t\t \\     \\                  /     / |   ______| |  |         |   ________|   |  ______  |       /                    \\       |   ______|");
	printf("\n\t\t  \\     \\       $_$      /     /  |  |__      |  |         |  |            | |      | |      /      _        _      \\      |  |__   ");	
	printf("\n\t\t   \\     \\     /  \\     /     /   |     |__   |  |         |  |            | |      | |     /      / \\\      / \\      \\     |     |__");
	printf("\n\t\t    \\     \\   |	   |   /     /    |      __|  |  |         |  |            | |      | |    /      /   \\\    /   \\      \\    |      __|");
	printf("\n\t\t     \\     \\__|	   |__/     /     |   __|     |  |         |  |            | |      | |   /      /  $  \\\__/  $  \\      \\   |   __|  ");
	printf("\n\t\t      \\                    /      |  |______  |  |_______  |  |________    | |______| |  /      /                \\      \\  |  |______ ");
	printf("\n\t\t       \\__________________/       |_________| |__________| |___________|   |__________| /______/                  \\______\\ |_________| ");
	printf("\n\n\n\t\t\t\t\t\t\t       ________________________________________________\n");
	printf("\n\t\t\t\t\t\t\t       | |               Dear Customer               | |\n");
	printf("\t\t\t\t\t\t\t       ________________________________________________\n");
	printf("\n\n________________________________________________________________________________________________________________________________________________________________________");
	printf("\n\n\t\t\t\t\t\t\t\t\t\t LOGIN MODE");
	printf("\n________________________________________________________________________________________________________________________________________________________________________");
	printf("\n\n  1.Login as Admin");
	printf("\n\n  2.Login as User");
	printf("\n\n  3.Exit");
}
void menu_login(){
	system("color 02");
	printf("\n\n\t\t\t _______________________________________________________________________________________________________________________                            ");
	printf("\n\t\t\t|\t\t\t\t __        ______       _______     _    __     __                                      |");
	printf("\n\t\t\t|\t\t\t\t|  |      /      \\     /  _____|   |_|  |  \\   |  |                                     |");
	printf("\n\t\t\t|\t\t\t\t|  |     /   /\\   \\   /  / _____    _   |   \\  |  |                                     |");
	printf("\n\t\t\t|\t\t\t\t|  |    |   |  |   | |  | |___  |  | |  |    \\ |  |                                     |");
	printf("\n\t\t\t|\t\t\t\t|  |___  \\   \\/   /   \\  \\\____| |  | |  |  |\\ \\|  |                                     |");
	printf("\n\t\t\t|\t\t\t\t|______|  \\______/     \\________|  |_|  |__| \\____|                                     |");
	printf("\n\t\t\t|_______________________________________________________________________________________________________________________|");
}
void menu_admin(){
	system("color f2");
	printf("\n\n\n\t\t\t\t\t\t\t       ________________________________________________\n");
	printf("\n\t\t\t\t\t\t\t       | |             WADIK'S BANK                 | |\n");
	printf("\t\t\t\t\t\t\t       ________________________________________________\n");
    printf("\n\n________________________________________________________________________________________________________________________________________________________________________");
	printf("\n\n\t\t\t\t\t\t\t\t\t   ADMINISTRATOR MODE");
    printf("\n________________________________________________________________________________________________________________________________________________________________________");
	printf("\n\n  1.Create New Account");
	printf("\n\n  2.Edit Exiting Account");
	printf("\n\n  3.Show Databases");
	printf("\n\n  4.Show Deposits ");
	printf("\n\n  5.Exit/Logout");
}
void menu_admin_edit(){
	system("color df");
	printf("\n\n\n\t\t\t\t\t\t\t       ________________________________________________\n");
	printf("\n\t\t\t\t\t\t\t       | |             WADIK'S BANK                 | |\n");
	printf("\t\t\t\t\t\t\t       ________________________________________________\n");
	printf("\n\n________________________________________________________________________________________________________________________________________________________________________");
	printf("\n\n\t\t\t\t\t\t\t\t\t    EDIT ACCOUNT");
    printf("\n________________________________________________________________________________________________________________________________________________________________________");
	printf("\n\n  1. Edit Exiting Account\n\n");
	printf("  2. Delete Account\n\n");
	printf("  3. Back");
}
void menu_user(){
	system("color e0");
	printf("\n\n\n\t\t\t\t\t\t\t       ________________________________________________\n");
	printf("\n\t\t\t\t\t\t\t       | |             WADIK'S BANK                 | |\n");
	printf("\t\t\t\t\t\t\t       ________________________________________________\n"); 
	printf("\n\n________________________________________________________________________________________________________________________________________________________________________");
	printf("\n\n\t\t\t\t\t\t\t\t\t   USER MODE");
    printf("\n________________________________________________________________________________________________________________________________________________________________________");
	printf("\n\n  1.Account Info");
	printf("\n\n  2.Take Cash");
	printf("\n\n  3.Transfer Deposit");
	printf("\n\n  4.Exit/Logout");
}

	void exit_app(){
	system("cls");
	system(" color f0");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");	
	printf("\t\t\t\t\t     _________ 	    ___     ___	      ____	  __	 ______    ___   ____  ___________      	\n");
	printf("\t\t\t\t\t    |___   ___|    |   |   |   |     /	  \\	 |  |   /      |  |   | /   /  |  ________|      \n");
	printf("\t\t\t\t\t	| |	   |   |___|   |    /  /\\  \\	 |  |  /   /|  |  |   |/   /   | |________\n");
	printf("\t\t\t\t\t	| |	   |   	       |   /  /__\\  \\	 |  | /	  / |  |  |	   <   |_________ |\n");
	printf("\t\t\t\t\t	| |	   |   	___    |  /  ______  \\   |  |/   /  |  |  |   |\\   \\    ________| |\n");
	printf("\t\t\t\t\t	|_|	   |___|   |___| /__/	   \\__\\  |______/   |__|  |___| \\___\\  |__________| \n");
	getch();

}

void main(){
	fullscreen();
	int pilih_mode,pilih_admin,pilih_user,pilih_admin_edit;
	int indeks;
	char user[50],pass[50];
	char loop,kembali;
	jumlah_akun();
	read_file(akun,jmlh_akun);
	read_file_hidden(akun,jmlh_akun);
	doagain:
	do{
		system("cls");
		menu_mode();
		printf("\n\n Your Choice = ");
		scanf("%d",&pilih_mode);
		switch(pilih_mode){
			case 1 : do{
						system("cls");
						system("color 9c");
						printf("\n\n________________________________________________________________________________________________________________________________________________________________________");
						printf("\n\n\t\t\t\t\t\t\t\t\t WADIK'S BANK");
						printf("\n________________________________________________________________________________________________________________________________________________________________________");

						printf("\n\n\t\t\t\t\t\t_______________________________________________________________");
						printf("\n\n\t\t\t\t\t\t\t\tInput Username and password!");
						printf("\n\t\t\t\t\t\t_______________________________________________________________");
						menu_login();
						printf("\n\n\n  Username : ");
						fflush(stdin);
						gets(user);
						printf("\n\n  Password : ");
						fflush(stdin);
						gets(pass);
						if(strcmpi(user,"admin")!=0 || strcmpi(pass,"admin")!=0){
							printf("\n_______________________________________________________________");
							printf("\n\n| Username / Password is invalid |\n\n| Click ENTER to repeat or X to Back |");
							kembali = getch();
							if((kembali == 'x') | (kembali == 'X')) {
								goto doagain;
							}
						}
					}while( strcmpi(user,"admin")!=0 || strcmpi(pass,"admin")!=0 );
					//Tampilan menu admin
						do{system("cls");
						menu_admin();
						printf("\n\nYour Choice = ");
				 		scanf("%d",&pilih_admin);
				 		switch(pilih_admin){
				 			case 1 : 	system("cls");
				 						system("color 09");
				 						input_data_akun(akun);
							 			getch();
							 			loop = 'y';
							 			break;
							case 2 :	do{
										system("cls");
										menu_admin_edit();
										printf("\n\n\nYour Choice = ");
										scanf("%d",&pilih_admin_edit);
										switch(pilih_admin_edit){
											case 1 :	system("cls");
														system("color 02");
														edit_data_admin(akun);
														break;
											case 2 :	system("cls");
														system("color 04");
														delete_akun(akun);
														break;
										}
										}while(pilih_admin_edit < 3);
										loop = 'y';
										break;
				 			case 3 : 	system("cls");
				 						system("color 80");
				 						show_database(akun,jmlh_akun);
				 						printf("\n\n  Press any key to continue! \n");
							 			getch();
							 			loop = 'y';
							 			break;
							case 4 :	system("cls");
										system("color 20");
				 						show_deposit(akun,jmlh_akun);
				 						printf("\n\n  Press any key to continue! \n");
				 						read_file(akun,jmlh_akun);
										read_file_hidden(akun,jmlh_akun);
							 			getch();
							 			loop = 'y';
							 			break;
							case 5 : 	system("cls");
										system("color f0");
										getch();
										loop = 'n';
										goto doagain;
										break;
						 }
				 		system("cls");
						}while(pilih_admin < 0 || pilih_admin > 5 || loop == 'y');
						break;
			case 2 : 	do{
						system("color 94");
						system("cls");
						menu_login();
						indeks = login_user(akun);
						if(indeks == -2){
							goto doagain;
						}
						}while(indeks == -1);
						do{
						system("cls");
						menu_user(); 
						printf("\n\n\nYour Choice = ");
						scanf("%d",&pilih_user);
							switch(pilih_user){
								case 1: system("cls");
										user_info(akun,indeks);
										getch();
										loop = 'y';
										break;
								case 2: system("cls");
										user_cash(akun,indeks);
										getch();
										loop = 'y';
										break;
								case 3:	user_transfer(akun,indeks);
										getch();
										loop = 'y';
										break;	
								case 4: getch();
										loop = 'n';
										goto doagain;
										break;
							}
						}while(pilih_user < 0 || pilih_user > 4 || loop == 'y');
						break;
			case 3 : 	system("cls");
						exit_app(); 
						break;
		}
	}while(pilih_mode <= 0 || pilih_mode > 3  );
}
