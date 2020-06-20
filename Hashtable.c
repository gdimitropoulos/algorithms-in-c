#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int prime_numbers[]={1999, 3989, 7993, 15907, 29989,
    59921, 119923, 239893, 479879, 959873, 1919839, 3839839};

 int non_prime_numbers[]={ 2000, 4000, 8000, 16000,
    32000, 64000, 128000, 256000, 512000, 1024000, 2056000, 4112000,
    8224000, 16456000 };



int count_size = 0;
int hashsize=997;
double load_factor=0;
double count_ele=0;
int colision=0;

/* χρησιμοποιούμε struct για να εκφράσουμε τις  επισκέψεις που θέλουμε να κράτησουμε πληροφορίες */


struct visit {
char card[17];
char day[4];
int payment;
int key;
};

/* *δημιουργία του πίνακα hash table*/
struct visit* create_hash(int size){

struct visit* hashtable = (struct visit*) malloc(size * sizeof(struct visit));

return hashtable;


}
/*function που χρησιμοποιείται για την αρχικοποίηση των επισκέψεων με τις κατάλληλες τιμές*/

struct visit   createvisit(char acard[17],char aday[4], int apay,int akey){
struct visit b ;
strcpy(b.card,acard);
strcpy(b.day,aday);
b.payment=apay;
b.key=akey;

return b;

}
/* Αρχικοποιούμε σε όλες τις θέσεις την μεταβλητή payment με 0 ωστε να γνωρίζουμε οτι αν σε καποια θέση του
hashtable βρούμε την μεταβλητή αυτη 0  θα σημαίνει ότι είναι αδεια, μιας και σύμφωνα με την εκφώνυση οι επιτρεπτές τιμές των
πληρωνμών είναι απο 10 ως 100*/
void init(struct visit * hashtable, int size) {
	int i;
	for (i = 0; i < size; i++) {
		hashtable[i].payment = 0;
	}
}

/* function που χρησιμοποιείται για την εισαγωγή στοιχείων στο hash table*/
void insert(struct visit * hashtable,struct visit vis){

int temp=0;
int temp1=0;
int i=vis.key;
if(hashtable[i].payment!=0){
        if(strcmp(hashtable[i].card,vis.card)!=0){
                colision+=1; //αν κατα την εισαγωγή της κάρτας βρεθεί κατειλλημένη η θέση απο διαφορετική κάρτα αυξάνουμε collision
                 temp=search(hashtable,vis);// ψαχνουμε αν υπάρχει ήδη η κάρτα που εισάγουμε στον πίνακα αν ναι διαγράφουμε το collision
    if(temp>=1){colision=colision-1;}

        }

}

int counter=1;
while(hashtable[i].payment!= 0){

    i =(i+1) % hashsize ;
    counter+=1;

}


hashtable[i]=vis;
}






void RandomCardNum(char array[16]) {
    int temp1,temp2,temp3,temp4 ;

    char temp5[]="1234567890123456"; // initial number of card
    strcpy(array,temp5);


    /* Choose  random position of chars X Y Z W  */

            temp1=rand()%16;
            temp2=rand()%16;
            while(temp1==temp2){

                temp2=rand()%16;
            }
        temp3=rand()%16;
        while(temp1==temp3 || temp2==temp3){
            temp3=rand()%16;
        }
        temp4=rand()%16;
        while(temp4==temp2 || temp4==temp3 || temp4==temp1){

            temp4=rand()%16;
        }
        array[temp1]='X';
        array[temp2]='Y';
        array[temp3]='Z';
        array[temp4]='W';
        array[16]='\0';  /* finalize string of randomCode*/
}
/*δημιουργια τυχαίων ημερών*/
void RandomDay(char days[4]){
    int randDay ;
    randDay=rand()%6;
    if (randDay==0){strcpy(days,"MON");}
    else if (randDay==1){strcpy(days,"TUE");}
    else if (randDay==2){strcpy(days,"WED");}
    else if (randDay==3){strcpy(days,"THU");}
    else if (randDay==4){strcpy(days,"FRI");}
    else {strcpy(days,"SAT");}
    days[3]='\0';
}
/*δημιουργια τυχαίων αριθμών πληρωμής*/
int RandomPayment(void){
    int randPay;
    randPay=rand()%91 +10;
    return randPay;
}

//Hash function from Dan Berstein //
int keygen(char *card){

        unsigned long hash = 0;
    int c;

    while ((c = *card++))
        hash = ((hash << 5) + hash) + c; //Hash function from Dan Berstein //

  return hash%hashsize;
}





 /* Search function που χρησιμοποιηται για να μετρήσουμε το πλήθος της κάθε καρτας στον πίνακα hashtable */
int search(struct visit* hashtable, struct visit vis){
    int counter=0,key;
    key=vis.key;
    int counter1=1;
    while(hashtable[key].payment!=0){
        if(strcmp(vis.card,hashtable[key].card)==0){counter+=1;}
        key=(key+1)%hashsize;
    }

return counter;
}





 /* Search function που χρησιμοποιειται για να μετρήσουμε το πλήθος της κάθε καρτας στον πίνακα hashtable */
int search_pay(struct visit* hashtable, struct visit vis){
    int counter=0,key;
    key=vis.key;

    while(hashtable[key].payment!=0){
        if(strcmp(vis.card,hashtable[key].card)==0){counter+=hashtable[key].payment;}
        key=(key+1)%hashsize;

    }

return counter;
}





/* rehash function που κανει resize στο hashtable και rehashing σε όσα στοιχεία ηταν μέσα στον αρχικό πίνακα*/

struct visit *  rehashing( struct visit * a){
colision=0;
int temp;
int last_size=hashsize;
int i,key;
struct visit * hashtable;
hashtable= (struct visit*) malloc(prime_numbers[count_size] * sizeof(struct visit));

hashsize=prime_numbers[count_size];

for(i=0;i<hashsize;i++){
    hashtable[i].payment=0; // αρχικοποίηση νέου πίνακα
}

for(i=0;i<last_size;i++){
    if(a[i].payment!=0){
    key=keygen(a[i].card);
    a[i].key=key;
    insert(hashtable,a[i]); // rehashing των στοιχείων του παλιού πίνακα
}
}
free(a);

count_size+=1; // χρησιμοποιείται για τον πίνακα που περιέχει τους αριθμους των μεγεθων  του hash table

return hashtable;


}


int main()
{
srand(1053649); //seed
int i,pay;
int key;
char ar3[17];
char ar1[4];
struct visit a;
struct visit* hashtable=create_hash(hashsize);
init(hashtable,hashsize);



for(i=0;i<1000000;i++){
count_ele+=1; //ποσα στοιχέια έχουν εισαχθει
load_factor=count_ele/hashsize;
RandomCardNum(ar3);
RandomDay(ar1);                 // αρχικοποίηση επίσκεψης
pay=RandomPayment();
key=keygen(ar3);
a=createvisit(ar3,ar1,pay,key);
insert(hashtable,a); // εισαγωγή επίσκεψης στο hashtable

if(load_factor>0.6){hashtable=rehashing(hashtable);}//ελέγχουμε το load factor ωστε αν χρειαστεί να κάνουμε rehashing
}
printf("%d collisions \n",colision); // print τα collisions

//1o erwtima

/* μετράμε για κάθε κάρτα το σύνολο πληρωμής και κρατάμε κάθε φορά το μέγιστο*/
int maxpay=0;
int counter3=0;
char temp_card[17];
for(i=0;i<hashsize;i++){
    if(hashtable[i].payment!=0){
            counter3=search_pay(hashtable,hashtable[i]);

    }
    if(counter3>maxpay){
        maxpay=counter3;
        strcpy(temp_card,hashtable[i].card);
    }

}

printf("%d euros  from %s\n",maxpay,temp_card);



//2o erwtima  μετράμε τον αριθιμό επισκέψεων που  είχαμε για κάθε κάρτα και κρατάμε το μεγαλύτερο  */
int maxfind=0;
int counter1=0;
for(i=0;i<hashsize;i++){
    if(hashtable[i].payment!=0){
            counter1=search(hashtable,hashtable[i]);

    }
    if(counter1>maxfind){
        maxfind=counter1;
        strcpy(temp_card,hashtable[i].card);
    }

}

printf("the most visits are %d from %s\n",maxfind,temp_card);


/*3o erwtima χρησιμοποιούμε 6 counters 1 για κάθε μέρα,ανατρέχουμε τον πίνακα εξετάζοντας για όλα τα στοιχεία
την μέρα επίσκεψης και αυξάνοντας τον αντίστοιχο counter κάθε φορά κατα 1.
Στο τέλος κρατάμε την μέρα με το μεγαλύτερο αριθμό επισκέψεων*/
int day1=0,day2=0,day3=0,day4=0,day5=0,day6=0,max_day;
char temp_day[4];
for(i=0;i<hashsize;i++){
    if(hashtable[i].payment!=0){
        if(strcmp(hashtable[i].day,"MON")==0){day1+=1;}
        else if(strcmp(hashtable[i].day,"TUE")==0){day2+=1;}
        else if(strcmp(hashtable[i].day,"WED")==0){day3+=1;}
        else if(strcmp(hashtable[i].day,"THU")==0){day4+=1;}
        else if(strcmp(hashtable[i].day,"FRI")==0){day5+=1;}
        else if(strcmp(hashtable[i].day,"SAT")){day6+=1;}
}
}
max_day=day1;
strcpy(temp_day,"MON");
if(day2>max_day){
    max_day=day2;
    strcpy(temp_day,"TUE");
    }

if(day3>max_day){
        max_day=day3;
        strcpy(temp_day,"WED");
}
if(day4>max_day){
        max_day=day4;
        strcpy(temp_day,"THU");
}
if(day5>max_day){
        max_day=day5;
        strcpy(temp_day,"FRI");
}
if(day6>max_day){
        max_day=day6;
        strcpy(temp_day,"SAT");
}
printf("%d  %s  ",max_day,temp_day);
    return 0;
}

