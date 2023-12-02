#include <stdio.h>					// c dili ve yaz�m� i�in gerekli olan genel k�t�phane
#include <conio.h>					// kbhit ve getch fonksiyonlar�n� kullanabilmek i�in gerekli olan k�t�phane
#include <time.h>					// srand fonksiyonunu kullanabilmek i�in gerekli olan k�t�phane
#include <stdlib.h>					// random fonksiyonunu kullanabilmek i�in gerekli olan k�t�phane
#include <unistd.h>					// sleep fonksiyonunu kullanabilmek i�in gerekli olan k�t�phane

int yemx,yemy,uzunluk=3,basx=4,basy=6,Gameover=0;	// oyun i�in gerekli olan verileri tutan int t�r�ndeki de�erler.
int konum[100][100];				// y�lan�n koordinatlar�n� tutan int t�r�ndeki dizi
int tahta[10][10]={0};				// oyun tahtas�n� olu�turan int t�r�ndeki dizi
int i,j;							// genellikle for gibi d�ng�ler i�in kullan�lan int t�r�ndeki de�erler.
char girdi,eskigirdi;				// girilen y�n bilgisini tutmak i�in kullan�lan char t�r�ndeki veriler.

// oyun tahtas�n� g�stermek i�in kullan�lan fonksiyon
void goster(){
	for(i=0;i<10;i++){				// tahtadaki y koordinatlar�n� gezmek i�in kullan�lan for d�ng�s�
		for(j=0;j<10;j++){			// tahtadaki x koordinatlar�n� gezmek i�in kullan�lan for d�ng�s�
			
			switch(tahta[i][j]){	// tahta i�erisindeki de�erlerin 0,1 veya 2 olmas�na g�re verece�i ��kt�lar
				case 0: printf(".   "); break;
				case 1: printf("O   "); break;
				case 2: printf("X   "); break;
			}
		}
		printf("\n\n");				// her sat�r bitiminde yeni sat�r i�in a�a�� inmesini ger�ekle�tirir.
	}
}
//y�lan yeminin koordinat�n� ayarlayan fonksiyon
void yemhazirla(){
	tekrar:							// gerekli durumlarda kod blo�unun buraya d�nmesini sa�lar.
	yemx=rand()%9;					// yemin x koordinat� i�in 0-9 aras�nda bir random de�er atar.
	yemy=rand()%9;					// yemin y koordinat� i�in 0-9 aras�nda bir random de�er atar.
	for(i=0;i<uzunluk;i++){			// uzunluk say�s�na kadar d�nen bir for d�ng�s�d�r.
		if(yemx==konum[i][0] && yemy==konum[i][1]){	
			goto tekrar;			// yem koordinatlar� ile y�lan koordinatlar� e�it olmas� durumunda yukar�da belirtilen "tekrar" isimli kod blo�una geri d�ner.
		}	
	}
	tahta[yemx][yemy]=2;								// yemi koordinatlar� kullanarak tahtaya yerle�tirir.
}
//hareket koordinatlar�n� kaydeden, yemin yenme durumu ve y�lan uzunlu�unu belirleyen fonksiyon
void oyun(){

	for(i=0;i<10;i++){									// tahtadaki y koordinatlar�n� gezmek i�in kullan�lan for d�ng�s�
		for(j=0;j<10;j++){								// tahtadaki x koordinatlar�n� gezmek i�in kullan�lan for d�ng�s�
			if(tahta[i][j]!=2){
				tahta[i][j]=0;							// tahtadaki yem d���nda t�m de�erleri s�f�ra e�itleyerek y�lan� g�r�nt�den siler
			}	
		}
	}
	
	for(i=uzunluk;i>0;i--){								// y�lan�n hareket eden ba� k�sm�n� konum dizisine yerle�tirmek i�in en �st te bir bo�luk olu�turur.
		konum[i][0]=konum[i-1][0];
		konum[i][1]=konum[i-1][1];
	}
	
	konum[0][0]=basx;									// olu�an bir sat�rl�k konum dizisine y�lan�n ba� k�sm�n�n x koordinatlar�n� yerle�tirir.
	konum[0][1]=basy;									// olu�an bir sat�rl�k konum dizisine y�lan�n ba� k�sm�n�n y koordinatlar�n� yerle�tirir.
	
	for(i=0;i<uzunluk;i++)	{	tahta[konum[i][0]][konum[i][1]]=1;	}	// konum dizisinin koordinatlar� ile y�lan� tahtaya yazar.
	
	system("cls");										// sayfay� temizler
	if(yemx==basx && yemy==basy){						// yemin yenme durumunu kontrol eder.
		yemhazirla();									// yem yenmesi sonras� yeni yem olu�turmak i�in fonksiyon �al��t�r�l�r.
		uzunluk+=1;										// yem yendi�i i�in uzunluk de�eri bir birim art�r�l�r.
	}
	goster();											// g�r�nt� tazelenmesi i�in yeniden g�ster fonksiyonu �al��t�r�l�r.
	eskigirdi=girdi;									// y�lan�n gerigidememesi i�in eski gidilen yonu kaydeder.	
}
//y�lan�n kendi koordinatlar�na �zerine gelerek kaybetme durumunu olu�turan fonksiyon
void basmak(){
	
	for(i=0;i<uzunluk;i++){ 							// y�lan�n t�m bedeni kontrol edilece�inden dolay� uzunluk boyutunda bir for d�ng�s� kullan�ld�.
		if(basx==konum[i][0] && basy==konum[i][1]){		//gidilen son koordinatlar ile y�lan�n beden koordinatlar� e�it mi kontrol eder. bu y�lan bedeninin a�z� ile kar��la�t��� anlam�na gelir.
			Gameover=1;									// gameover de�erini bir e e�itler. bu sayede oyun sonuna gidilebilir.
			break;										// for d�ng�s�nden ��kmas�n� sa�lar. sonras�nda ise fonksiyondan ��k�l�r.
		}
	}
}

void bekle(float saniye) {
    
    struct timespec bekleme_zamani;									// bekleme_zamani adl� bir timespec yap�s� olu�turuyoruz.
    bekleme_zamani.tv_sec = (int)saniye;    						// saniye de�erini tam say� k�sm�n� alarak saniye cinsinden ayarl�yoruz.
    bekleme_zamani.tv_nsec = (saniye - (int)saniye) * 1000000000;	// saniye de�erinden tam say� k�sm�n� ��kararak kalan� nanosaniye cinsinden ayarl�yoruz.
    nanosleep(&bekleme_zamani, NULL);			    				// nanosleep fonksiyonunu kullanarak bekleme i�lemini ger�ekle�tiriyoruz.
}

int main(){
	
	srand(time(NULL));				//random de�erlerinin her yenilemede farkl� gelmesini sa�lar
	float bekleme_suresi = 0.23;  	// uygulama bekleme moduna almak i�in gereken s�re belirlenir	
	tahta[4][4]={1};				//y�lan ilk uzunluk koordinatlar�n� tahtaya yerle�tirir 
	tahta[4][5]={1};				//y�lan ilk uzunluk koordinatlar�n� tahtaya yerle�tirir 
	tahta[4][6]={1};				//y�lan ilk uzunluk koordinatlar�n� tahtaya yerle�tirir 
	
	konum[0][0]=4;	konum[0][1]=6;	//y�lan ilk uzunluk koordinatlar�n� belirler.
	konum[1][0]=4;	konum[1][1]=5;	//y�lan ilk uzunluk koordinatlar�n� belirler.
	konum[2][0]=4;	konum[2][1]=4;	//y�lan ilk uzunluk koordinatlar�n� belirler.
	
	eskigirdi='d';					// y�lan ilk hareketinin sa� y�ne do�ru oldu�unu belirler.
	yemhazirla();					// yemhazirla fonksiyonunu �al��t�r�r.
	goster();						// g�ster fonksiyonunu �al��t�r�r.
	
	while(true){					// oyun i�erisini sonsuz d�ng�de tutar.
		if(kbhit()) {				// klavyede herhangi bir tu�a bas�ld�m� kontrol�n� yapar
			girdi=getch();			// klavyede bas�lan tu�un hangisi oldu�unu belirler.
		}
	
	   bekle(bekleme_suresi);		// uygulamay� bekleme uyku moduna alarak ilerlememesi i�in s�re say�m� yapar.
	
		switch(girdi){				// basulan tu�un y�n hareketlerinden hangisi oldupuna g�re se�im yapar.
			case 'w':	if(eskigirdi=='s'){ eskigirdi='s'; break; }	else if(basx==0){ Gameover=1; }	else { basx-=1; basmak();	oyun();  }	break;	// eski girdi de�eri koontrol edilerek y�lan�n geri gitmesi engellenir.		
			case 's': 	if(eskigirdi=='w'){ eskigirdi='w'; break; }	else if(basx==9){ Gameover=1; }	else { basx+=1; basmak();	oyun();  }	break;	// basx ve basy nin 0 ve 9 olmas� yan� duvarlara �arpma olay� de�erlendirilir		
			case 'a':	if(eskigirdi=='d'){ eskigirdi='d'; break; }	else if(basy==0){ Gameover=1; }	else { basy-=1; basmak();	oyun();  }	break;	// gidilen y�ne g�re basx ve basy de�erleri artar veya azal�r.			
			case 'd': 	if(eskigirdi=='a'){ eskigirdi='a'; break; }	else if(basy==9){ Gameover=1; }	else { basy+=1; basmak();	oyun();  }	break;	// basmak fonksiyonu ve oyun fonksiyonu yeniden �al��t�r�l�r. bu sayede oyun devam eder ve kendi �zerine basma durumu da kontrol edilir.  			
		}				
	
		if(Gameover==1){			// oyunun kaybedilmesi durumunda ne olaca��na karar verir.
			printf("kaybettin !");	// konsol ekran�nda yaz� ��kt�s� verir.
		    bekle(bekleme_suresi);			
			return 0;				// d�nme de�erini s�f�ra ayarlayarak uygulamay� sonland�r�r.
		}
	}
}
