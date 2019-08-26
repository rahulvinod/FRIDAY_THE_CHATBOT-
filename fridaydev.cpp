
/* Including Files */
//include<iostream.h>
# include<conio.h>
# include<string.h>
# include<time.h>
# include<math.h>
# include<stdlib.h>
# include<dos.h>
# include<stdio.h>
# include<fstream>
#include<iostream>
#include<dos.h>
#include<conio.h>
//#include<graphics.h>
#include<unistd.h>
using namespace std;
void loading()
{
  // clrscr();

	cout<<endl<<endl<<endl<<endl<<endl<<"                                F.R.I.D.A.Y"<<endl;
	cout<<"                                   ";
       //	outtextxy(250,320,"FRIDAY");
	for(int i=0; i<3; i++)
	{
	       for(int i=0; i<2; i++)
	       {
			usleep(1);
			cout<<".";
		}
	 }
}
/* Defining Costants*/
// Max. length in characters of any automated reply ( Keyword only)
# define MAX_RESP_LEN 65
// Max. number of responses for any keyword
# define MAX_RESP_NO 20
// Max. number of keywords
# define MAX_KEY 13
// Max. number of Transpositions
# define TRANSPOSE 12
// Max. Size Of User Input
# define MAX_USER_INPUT 100
// Max. Length of Keyword
# define MAX_KWD_LEN 20
// Delay involved in typing (in ms)
# define DELAY 20

/* Defining Global Variables */

// for getting the user name
char user[30];
// for word transpositions
char wordin[TRANSPOSE][MAX_RESP_LEN];
char wordout[TRANSPOSE][MAX_RESP_LEN];
int RanNum(int max);
void initialize_global();

class progstr
{
public:
char userip[MAX_USER_INPUT];
char keyword[30];
int keyfound;
int keyno;
int nullip;
	// constructor
	progstr()
	{
	keyno=-1;
	nullip=0;
	}
}ip;

class resp
{
int tot_resp;
int last_resp;
char replys[MAX_RESP_NO][MAX_RESP_LEN];
char word[MAX_KWD_LEN];
public:
	// constructor
	resp()
	{
	tot_resp=0;
	last_resp=-1;
	}
	int getcount()
	{
	return last_resp;
	}
	void addword(char str[MAX_KWD_LEN])
	{
	strcpy(word,str);
	}
	char * getword()
	{
	return word;
	}
	void addresp(char  str[MAX_RESP_LEN])
	{
	strcpy(replys[++last_resp],str);
	}
	void display_resp(int num);
	void quit_display_resp(int num);

};
void display_logo()
{

cout<<"	   FFFFFFF  RRRRRRR   IIIIIII DDDDDDDD   AAAAAAAA  YY           YY "<<endl;
usleep(1);
cout<<"	   F        R      R	 II           D  A       A   YYY      YYY"<<endl;
usleep(1);
cout<<"	   FFFFFF   R    R       II            D A AAAAA A      YYYYY      "<<endl;
usleep(1);
cout<<"	   F        R    R       II           D  A       A        Y  "<<endl;
usleep(1);
cout<<"	   F        R      R  IIIIIII DDDDDDD    A       A        Y   "<<endl;
usleep(1);
cout<<"	                                       "<<endl;
usleep(1);
cout<<"	                        . chat - mode .                                                "<<endl;
}
/*
void display_line()
{
int width=80;
int i=0;
int x=wherex();
int y=wherey()+1;
x=40;
for(int k=0;k<40;k++)
{
delay(DELAY);
gotoxy(x+k,y);
cout<<(char)240;
gotoxy(x-k,y);
delay(DELAY);
cout<<(char)240;
}
cout<<"\n";
}
*/

void resp :: display_resp(int num)
	{
	cout<<"F.R.I.D.A.Y >> ";
	for(int i=0;i<strlen(replys[num]);i++)
	{
		// for deliberate typing errors
		if(RanNum(6)==0)
		{       char c=RanNum(100);
			if(c=='\n' || c=='\b' || c==13)
				cout<<"w";
			else
				cout<<c;
			usleep(RanNum(DELAY));
			cout<<"\b";
		}

		if(replys[num][i]=='*')
		{
		char * s1=ip.userip+strlen(ip.keyword);
		short int flag=0;
		for(int m=0;m<TRANSPOSE;m++)
			{
			char * s2=wordin[m];
			char *ptr=NULL;
			ptr=strstr(s1,s2);

			if(ptr!=NULL)
				{
				// transposition word found in the
				// user input
				flag=1;

				// printing text before wordin[m]
				int times=ptr-s1;
				for(int i=0;i<times;i++)
					{
					usleep(DELAY);
					cout<<ip.userip[strlen(ip.keyword)+i];
					}
				// printing the wordout
				cout<<wordout[m];
				// printing the left overs
				char c;
				c=*(ptr+strlen(wordin[m]));
				int t=0;
				while(c!='\0')
					{
					cout<<*(ptr+strlen(wordin[m])+t);
					t++;
					c=*(ptr+strlen(wordin[m])+t);
					}
				}
			} // end of for
			// if flag is still zero , this means no transpose.
			if(0==flag)
			{
			char c;
			c=*(s1+strlen(ip.keyword));
			int t=0;
			while(c!='\0')
				{
				cout<<*(s1+t);
				t++;
				c=*(s1+t);
				}
			} // end of if
			break;
		}
	else
			{
				cout<<replys[num][i];
				usleep(RanNum(DELAY));
			}
	} // end of for
	cout<<"\n"<<user<<" > ";
	}
void resp :: quit_display_resp(int num)
{
	cout<<"F.R.I.D.A.Y >> ";
	for(int i=0;i<strlen(replys[num]);i++)
	{
		// for deliberate typing errors
		if(RanNum(6)==0)
		{       char c=RanNum(100);
			if(c=='\n' || c=='\b' || c==13)
				cout<<"w";
			else
				cout<<c;
			usleep(RanNum(DELAY));
			cout<<"\b";
		}
		cout<<replys[num][i];
		usleep(RanNum(DELAY));
	} // end of for
}
resp keys[MAX_KEY];
int RanNum(int max)
{
rand();
return rand() % max;
}
void find_keyword()
{
int len=0;
int lenkey=0;
int key_no=0;
char teststr[50];
while((ip.keyfound==0) &&(key_no!=MAX_KEY))
{
// getting the length of the keyword
lenkey=strlen(keys[key_no].getword());

char *ptr=NULL;
ptr=strstr(ip.userip,keys[key_no].getword());
if (ptr!=NULL)
	{
	// keyword found !
	ip.keyfound=1;
	ip.keyno=key_no;
	strcpy(ip.keyword,keys[key_no].getword());
	break;
	}
///////////////////////////////////////////
int i;
for(i=0;i<lenkey;i++)
	{
	teststr[i]=ip.userip[i];
	}
teststr[i]='\0';
if (strcmp(teststr,keys[key_no].getword())==0)
	{
	     ip.keyfound=1;
	     ip.keyno=key_no;
	     strcpy(ip.keyword,keys[key_no].getword());
	}
//////////////////////////////////////////*/
key_no++;
}
}

void read_from_file()
{
ifstream fin;
int index=-1;
fin.open("friday.dat");
char line[MAX_RESP_LEN];
while(fin)
{
	fin.getline(line,MAX_RESP_LEN);
	char *ptr=NULL;
	ptr=strstr("@KWD@",line);
	if(strlen(line)<1)
	{
		break;
	}
	else if(ptr!=NULL)
	{
		// the next line is a keyword
		fin.getline(line,MAX_RESP_LEN);
		keys[++index].addword(line);
	}
	else
	{
		// it is a response
		keys[index].addresp(line);
	}

} // end of while
} // end of function

void fridaymain()
{
system("cls");

//display_line();
display_logo();
//display_line();
// for initializing the global variables
initialize_global();

// for no response by the user.
resp null_resp;
null_resp.addresp("HUH ?");
null_resp.addresp(" SAY ANYTHING ..!!");
null_resp.addresp("COME AGAIN ?");
null_resp.addresp("HOW I AM SUPPOSED TO TALK IF YOU DON'T SAY ANYTHING ?");

// upon  logging in
resp signon;
signon.addresp("HI, I'M F.R.I.D.A.Y.. WHAT DO YOU WANT TO TALK ABOUT ?");
signon.addresp("SO HOW ARE YOU DOING TODAY ?");
signon.addresp("HELLO, WHAT'S UP TODAY ?");

// when no key found
resp no_key;
no_key.addresp("PLEASE GO ON...");
no_key.addresp("WHAT DOES THAT SUGGEST TO YOU ?");
no_key.addresp("I SEE ");
no_key.addresp("I'M NOT SURE I KNOW WHAT YOU ARE TALKING ABOUT ");
no_key.addresp("WHAT'S THAT SUPPOSED TO MEAN ?");
no_key.addresp("CAN YOU CLARIFY THAT A BIT ?");
no_key.addresp("THAT'S INTERESTING...");
no_key.addresp("AND ????");

resp bye;
bye.addresp("GOOD BYE, HAVE A NICE DAY...");
bye.addresp("BYE, HOPE TO SEE YOU SOON...");
bye.addresp("BYE AND KEEP IN TOUCH...");
// reading data from dictionary
read_from_file();

// STARTING CONVERSATION WITH THE USER
// welcoming the user

cout<<"F.R.I.D.A.Y >> (PLEASE TYPE IN ALL CAPS) WHAT'S YOUR NAME DEAR ?\n";
cin>>user;
signon.display_resp(RanNum(signon.getcount()));
fflush(stdin);
gets(ip.userip);
strcpy(ip.userip,strupr(ip.userip));
while(strcmp(ip.userip,"BYE")!=0)
{
	find_keyword();
if(strlen(ip.userip)<1)
{
	null_resp.display_resp(RanNum(null_resp.getcount()));
}
else if(ip.keyfound==1)
	{
	keys[ip.keyno].display_resp(RanNum(keys[ip.keyno].getcount()));
	}
else
	{
	no_key.display_resp(RanNum(no_key.getcount()));
	}
// again returning to normal values of the data items
strcpy(ip.userip," ");
ip.keyno=-1;
ip.keyfound=0;
fflush(stdin);
gets(ip.userip);
strcpy(ip.userip,strupr(ip.userip));
} // end of while
	bye.quit_display_resp(RanNum(null_resp.getcount()));
	cout<<endl;
	//display_line();
	//display_line();
getch();
}


void initialize_global()
{
strcpy(wordin[0],"ARE");
strcpy(wordout[0],"AM");

strcpy(wordin[1],"AM");
strcpy(wordout[1],"ARE");

strcpy(wordin[2],"WERE");
strcpy(wordout[2],"WAS");

strcpy(wordin[3],"WAS");
strcpy(wordout[3],"WERE");

strcpy(wordin[4],"YOU");
strcpy(wordout[4],"ME");

strcpy(wordin[5]," I ");
strcpy(wordout[5],"YOU");

strcpy(wordin[6],"YOUR");
strcpy(wordout[6],"MY");

strcpy(wordin[7],"MY");
strcpy(wordout[7],"YOUR");

strcpy(wordin[8],"I'VE");
strcpy(wordout[8],"YOU'VE");

strcpy(wordin[9],"YOU'VE");
strcpy(wordout[9],"I'VE");

strcpy(wordin[10],"I'M");
strcpy(wordout[10],"YOU'RE");

strcpy(wordin[11],"YOU'RE");
strcpy(wordout[11],"I'M");

strcpy(wordin[12],"ME");
strcpy(wordout[12],"YOU");

strcpy(wordin[13],"YOU");
strcpy(wordout[13],"ME");

}
//////////////////////////////////////
//This Program Will Encrypt And Decrypt Any File Text Document
//Provides The Maximum Security


/* This Program Will Encrypt Any Type Of Text Document */

#include<fstream>
#include<conio.h>
#include<stdio.h>
using namespace std;
string name,target;

int cryptographymain()
{
char ch,mod;                             //Declare
//Variables
int num[100],i,option;

cout<<"Enter Your Option "<<endl;
cout<<"1. To Encrypt The File "<<endl;
cout<<"2. To Decrypt The File "<<endl;
cout<<"Option : ";
cin>>option;

if(option==1)
{

cout<<"Enter The Path Of A File Which Is To Be Encrypted : ";
gets(name);

ifstream fin(name,ios::binary);                              //Open The
//Input File In A Binary Mode
if(!fin)
 {                                                          //Show
//ErrorOccur If File Does Not Exist
  cout<<"Error In Openinig Of A File : ";                 //Or Any
//ErrorOccurs
  return 1;
 }

cout<<"Enter The New Encrypted File Name : ";
gets(target);

ofstream fout(target,ios::binary);                         //Open The
//OutPut File In A Binary Mode
if(!fout)
 {
  cout<<"Error In Opening Of Target File : ";            //Show Error
//If
//Any Error Occrs In Opening Of A File
  return 1;
 }

for(i=0;i<9;i++)
 {                                                         //Multiple
//ForLoops For Storing The Numbers
  num[i]=i;                                                //In An
//Array
 }

for(i=14;i<31;i++)                                         //Loops Will
//Store 100 Numbers
 {
  num[i-5]=i;                                              //Which Will
//Encrypt The Contents Of A File
 }

for(i=33;i<=68;i++)                                        //To Avoid
//The
//Error Ocuur Caused By The
 {                                                         //Enter Key
//,
//Tab Key & Space Key
  num[i-7]=i;                                              //These
//Variations In Loops Is Made
 }

for(i=97;i<=122;i++)
 {
  num[i-35]=i;
 }

while(fin)
{                                                       //Open The
//Inputfile
fin.get(ch);

if(ch==EOF)break;                                       //Exit To Loop
//When End Of File

if((ch>=97) && (ch<=122))
 {                                                     //Encrypt The
//SmallLetters
  i=97;
  mod=num[ch-i];
  fout<<mod;
 }

if((ch>=65) && (ch<=90))
 {
  i=39;                                                 //Encrypt The
//Capital Letters
  mod=num[ch-i];                                        //And Store In
//AnOutput File
  fout<<mod;
 }

if((ch>=48) && (ch<=57))
 {
  i=4;                                                //Encrypt The
//Numbers
  mod=num[ch+i];
  fout<<mod;
 }

if((ch==10)||(ch==13))
 {
  mod=ch;                                             //For Enter Key
  fout<<mod;
 }

if(ch==32)
fout<<ch;                                             //For Space Key

if(ch==9)
fout<<ch;                                             //For Tab Key

if((ch>=33)&&(ch<=47))
 {                                                    //For Special
//Symbols
  mod=ch+64;
  fout<<mod;
 }

if((ch>=58)&&(ch<=64))
 {                                                    //For Special
//Symbols
  mod=ch+54;
  fout<<mod;
 }

if((ch>=91)&&(ch<=96))
 {
  mod=ch+28;                                          //For Special
//Symbols
  fout<<mod;
 }

if((ch>=123)&&(ch<=126))
 {
  mod=ch-40;                                          //For Special
//Symbols
  fout<<mod;
 }
}

fin.close();                                          //Close The Input
//File
fout.close();                                         //Close The
//OutputFile

cout<<"Your File Is Encrypted and secured ! its safe to delete the original ";
getch();
return 0;
}




/*========================================================================
=======================================*/


/* This Program Will Decrypt The Document */


if(option==2)
{
char name[30],target[30],ch,mod;                             //Declare
//Variables
int num[100],i,flag;

cout<<"Enter The Path Of A File Name Which Is To Be Decrypted : ";
gets(name);

ifstream fin(name,ios::binary);
if(!fin)                                                     //Open The
//Encryped File In A Binary Mode
{
cout<<"Error In Opening Of A File : ";
return 1;                                                    //Show
//ErrorIf File Does Not Exist
}                                                            //Or Any
//Occurs In Opening Of A File

cout<<"Enter The New Decrypted File Name : ";
gets(target);

ofstream fout;
fout.open(target,ios::binary);                              //Opens The
//Output File In An Binary Mode
if(!fout)
 {                                                          //Show
//ErrorIf Any Error Occurs In Opening Of A File
  cout<<"Error In Opening Of A Target File : ";
  return 1;
 }

for(i=0;i<9;i++)
 {                                                          //Same
//Multiple For Loops For Storing The Numbers
  num[i]=i;                                                 //In An
//Array
 }

for(i=14;i<31;i++)
 {
  num[i-5]=i;                                               //Loops
//WillStore 100 Numbers
 }

for(i=33;i<=68;i++)                                         //Which
//Encrypts The Document Also Decrypt It
 {
  num[i-7]=i;
 }

while(fin)
{                                                           //Opens The
//Encryped File
fin.get(ch);
flag=0;                                                        //Turn
//OffFlag
if(ch==EOF)break;

for(i=26;i<52;i++)
 {
  if(ch==num[i])                                            //Loop For
//Match The Small Letters Letters
  {
	mod=i+39;                                                //If Match
//ThenPut Appropriate Letter
	fout<<mod;                                               //In A OutPut
//File
	flag=1; break ;                                             //Turn On
//Flag And Exit The Loop
  }
 }

if (flag==1) continue ;                                        //If
//FlagIs On Then Continue Outer Loop

for(i=0;i<26;i++)
 {                                                          //Loop For
//Match The Capital Letters
  if(ch==num[i])
  {                                                        //If Match
//ThenPut Appropriate Letter
	mod=i+97;                                               //In A OutPut
//File
	fout<<mod;
	flag=1;break;                                              //Turn On
//FlagAnd Exit From This Loop
  }
 }

if (flag==1) continue ;                                       //If Flag
//IsOn Then Continue Outer Loop

for(i=52;i<62;i++)
 {                                                         //Loop For
//Numerical Numbers
  if(ch==num[i])
  {
	mod=i-4;
	fout<<mod;
	flag=1; break ;
  }
}

if (flag==1) continue ;

if((ch==10)||(ch==13))
 {
  mod=ch;                                             //Condition For
//Enter Key
  fout<<mod;
 }

if(ch==32)
fout<<ch;                                             //Condition For
//Space Key

if(ch==9)
fout<<ch;                                             //Condition For
//TabKey

if((ch>=97)&&(ch<=111))
 {
  mod=ch-64;                                          //For Special
//Symbols
  fout<<mod;
 }

if((ch>=112)&&(ch<=118))
 {
  mod=ch-54;                                         //For Special
///Symbols
  fout<<mod;
 }

if((ch>=119)&&(ch<=124))
 {
  mod=ch-28;                                         //For Special
//Symbols
  fout<<mod;
 }

if((ch>=83)&&(ch<=86))
 {                                                   //For Special
//Symbols
  mod=ch+40;
  fout<<mod;
 }

}

fin.close();                                        //Close The
//EncryptedFile
fout.close();                                       //Close Your
//OriginalDecrypted File

cout<<"The File Is Being Decrypted............ ";
getch();
return 0;
}
return 0;
}

////////////////////////////////////
void addfile()
{
	system("cls");
	char n[20],A[100];
	int i;
	cout<<"Enter the file name in .txt :";
	gets(n);
	ofstream file;
	file.open(n);
	cout<<"Enter the data : ";
	gets(A);
	file<<A<<endl;
	file.close();
}
int main()
{
	 system("cls");
	loading();
	//display_line();
      //	display_logo();
	///display_line();
	int a,i;
	do
	{
		//loading();
		cout<<endl<<"F.R.I.D.A.Y initializing : what should i do for you ?"<<endl<<endl;
		cout<<"1.Have a talk with me  "<<endl;
		cout<<"2.Add a file "<<endl;
		cout<<"3.Encrypt/Decrypt your file "<<endl;
		cout<<"4.Quit "<<endl<<endl<<endl;
		cout<<"OPTION:";
		cin>>a;
	system("cls");
		switch(a)
		{
			case 1:
				fridaymain();
				system("cls");
				break;
			case 2:
				loading();
			system("cls");
				addfile();
				break;
			case 3:
				loading();
			system("cls");
				cryptographymain();
				break;
			default:
			break;
		}
		system("cls");
		cout<<endl<<"PRESS ANY KEY ";
		getch();
		system("cls");
		cout<<endl<<endl<<endl<<endl<<"                    coding by RAHUL";
		getch();
	system("cls");
	}while(a!=4);
}
