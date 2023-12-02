#include <stdio.h>					// c dili ve yazýmý için gerekli olan genel kütüphane
#include <conio.h>					// kbhit ve getch fonksiyonlarýný kullanabilmek için gerekli olan kütüphane
#include <time.h>					// srand fonksiyonunu kullanabilmek için gerekli olan kütüphane
#include <stdlib.h>					// random fonksiyonunu kullanabilmek için gerekli olan kütüphane
#include <unistd.h>					// sleep fonksiyonunu kullanabilmek için gerekli olan kütüphane

int yemx,yemy,uzunluk=3,basx=4,basy=6,Gameover=0;	// oyun için gerekli olan verileri tutan int türündeki deðerler.
int konum[100][100];				// yýlanýn koordinatlarýný tutan int türündeki dizi
int tahta[10][10]={0};				// oyun tahtasýný oluþturan int türündeki dizi
int i,j;							// genellikle for gibi döngüler için kullanýlan int türündeki deðerler.
char girdi,eskigirdi;				// girilen yön bilgisini tutmak için kullanýlan char türündeki veriler.

// oyun tahtasýný göstermek için kullanýlan fonksiyon
void goster(){
	for(i=0;i<10;i++){				// tahtadaki y koordinatlarýný gezmek için kullanýlan for döngüsü
		for(j=0;j<10;j++){			// tahtadaki x koordinatlarýný gezmek için kullanýlan for döngüsü
			
			switch(tahta[i][j]){	// tahta içerisindeki deðerlerin 0,1 veya 2 olmasýna göre vereceði çýktýlar
				case 0: printf(".   "); break;
				case 1: printf("O   "); break;
				case 2: printf("X   "); break;
			}
		}
		printf("\n\n");				// her satýr bitiminde yeni satýr için aþaðý inmesini gerçekleþtirir.
	}
}
//yýlan yeminin koordinatýný ayarlayan fonksiyon
void yemhazirla(){
	tekrar:							// gerekli durumlarda kod bloðunun buraya dönmesini saðlar.
	yemx=rand()%9;					// yemin x koordinatý için 0-9 arasýnda bir random deðer atar.
	yemy=rand()%9;					// yemin y koordinatý için 0-9 arasýnda bir random deðer atar.
	for(i=0;i<uzunluk;i++){			// uzunluk sayýsýna kadar dönen bir for döngüsüdür.
		if(yemx==konum[i][0] && yemy==konum[i][1]){	
			goto tekrar;			// yem koordinatlarý ile yýlan koordinatlarý eþit olmasý durumunda yukarýda belirtilen "tekrar" isimli kod bloðuna geri döner.
		}	
	}
	tahta[yemx][yemy]=2;								// yemi koordinatlarý kullanarak tahtaya yerleþtirir.
}
//hareket koordinatlarýný kaydeden, yemin yenme durumu ve yýlan uzunluðunu belirleyen fonksiyon
void oyun(){

	for(i=0;i<10;i++){									// tahtadaki y koordinatlarýný gezmek için kullanýlan for döngüsü
		for(j=0;j<10;j++){								// tahtadaki x koordinatlarýný gezmek için kullanýlan for döngüsü
			if(tahta[i][j]!=2){
				tahta[i][j]=0;							// tahtadaki yem dýþýnda tüm deðerleri sýfýra eþitleyerek yýlaný görüntüden siler
			}	
		}
	}
	
	for(i=uzunluk;i>0;i--){								// yýlanýn hareket eden baþ kýsmýný konum dizisine yerleþtirmek için en üst te bir boþluk oluþturur.
		konum[i][0]=konum[i-1][0];
		konum[i][1]=konum[i-1][1];
	}
	
	konum[0][0]=basx;									// oluþan bir satýrlýk konum dizisine yýlanýn baþ kýsmýnýn x koordinatlarýný yerleþtirir.
	konum[0][1]=basy;									// oluþan bir satýrlýk konum dizisine yýlanýn baþ kýsmýnýn y koordinatlarýný yerleþtirir.
	
	for(i=0;i<uzunluk;i++)	{	tahta[konum[i][0]][konum[i][1]]=1;	}	// konum dizisinin koordinatlarý ile yýlaný tahtaya yazar.
	
	system("cls");										// sayfayý temizler
	if(yemx==basx && yemy==basy){						// yemin yenme durumunu kontrol eder.
		yemhazirla();									// yem yenmesi sonrasý yeni yem oluþturmak için fonksiyon çalýþtýrýlýr.
		uzunluk+=1;										// yem yendiði için uzunluk deðeri bir birim artýrýlýr.
	}
	goster();											// görüntü tazelenmesi için yeniden göster fonksiyonu çalýþtýrýlýr.
	eskigirdi=girdi;									// yýlanýn gerigidememesi için eski gidilen yonu kaydeder.	
}
//yýlanýn kendi koordinatlarýna üzerine gelerek kaybetme durumunu oluþturan fonksiyon
void basmak(){
	
	for(i=0;i<uzunluk;i++){ 							// yýlanýn tüm bedeni kontrol edileceðinden dolayý uzunluk boyutunda bir for döngüsü kullanýldý.
		if(basx==konum[i][0] && basy==konum[i][1]){		//gidilen son koordinatlar ile yýlanýn beden koordinatlarý eþit mi kontrol eder. bu yýlan bedeninin aðzý ile karþýlaþtýðý anlamýna gelir.
			Gameover=1;									// gameover deðerini bir e eþitler. bu sayede oyun sonuna gidilebilir.
			break;										// for döngüsünden çýkmasýný saðlar. sonrasýnda ise fonksiyondan çýkýlýr.
		}
	}
}

void bekle(float saniye) {
    
    struct timespec bekleme_zamani;									// bekleme_zamani adlý bir timespec yapýsý oluþturuyoruz.
    bekleme_zamani.tv_sec = (int)saniye;    						// saniye deðerini tam sayý kýsmýný alarak saniye cinsinden ayarlýyoruz.
    bekleme_zamani.tv_nsec = (saniye - (int)saniye) * 1000000000;	// saniye deðerinden tam sayý kýsmýný çýkararak kalaný nanosaniye cinsinden ayarlýyoruz.
    nanosleep(&bekleme_zamani, NULL);			    				// nanosleep fonksiyonunu kullanarak bekleme iþlemini gerçekleþtiriyoruz.
}

int main(){
	
	srand(time(NULL));				//random deðerlerinin her yenilemede farklý gelmesini saðlar
	float bekleme_suresi = 0.23;  	// uygulama bekleme moduna almak için gereken süre belirlenir	
	tahta[4][4]={1};				//yýlan ilk uzunluk koordinatlarýný tahtaya yerleþtirir 
	tahta[4][5]={1};				//yýlan ilk uzunluk koordinatlarýný tahtaya yerleþtirir 
	tahta[4][6]={1};				//yýlan ilk uzunluk koordinatlarýný tahtaya yerleþtirir 
	
	konum[0][0]=4;	konum[0][1]=6;	//yýlan ilk uzunluk koordinatlarýný belirler.
	konum[1][0]=4;	konum[1][1]=5;	//yýlan ilk uzunluk koordinatlarýný belirler.
	konum[2][0]=4;	konum[2][1]=4;	//yýlan ilk uzunluk koordinatlarýný belirler.
	
	eskigirdi='d';					// yýlan ilk hareketinin sað yöne doðru olduðunu belirler.
	yemhazirla();					// yemhazirla fonksiyonunu çalýþtýrýr.
	goster();						// göster fonksiyonunu çalýþtýrýr.
	
	while(true){					// oyun içerisini sonsuz döngüde tutar.
		if(kbhit()) {				// klavyede herhangi bir tuþa basýldýmý kontrolünü yapar
			girdi=getch();			// klavyede basýlan tuþun hangisi olduðunu belirler.
		}
	
	   bekle(bekleme_suresi);		// uygulamayý bekleme uyku moduna alarak ilerlememesi için süre sayýmý yapar.
	
		switch(girdi){				// basulan tuþun yön hareketlerinden hangisi oldupuna göre seçim yapar.
			case 'w':	if(eskigirdi=='s'){ eskigirdi='s'; break; }	else if(basx==0){ Gameover=1; }	else { basx-=1; basmak();	oyun();  }	break;	// eski girdi deðeri koontrol edilerek yýlanýn geri gitmesi engellenir.		
			case 's': 	if(eskigirdi=='w'){ eskigirdi='w'; break; }	else if(basx==9){ Gameover=1; }	else { basx+=1; basmak();	oyun();  }	break;	// basx ve basy nin 0 ve 9 olmasý yaný duvarlara çarpma olayý deðerlendirilir		
			case 'a':	if(eskigirdi=='d'){ eskigirdi='d'; break; }	else if(basy==0){ Gameover=1; }	else { basy-=1; basmak();	oyun();  }	break;	// gidilen yöne göre basx ve basy deðerleri artar veya azalýr.			
			case 'd': 	if(eskigirdi=='a'){ eskigirdi='a'; break; }	else if(basy==9){ Gameover=1; }	else { basy+=1; basmak();	oyun();  }	break;	// basmak fonksiyonu ve oyun fonksiyonu yeniden çalýþtýrýlýr. bu sayede oyun devam eder ve kendi üzerine basma durumu da kontrol edilir.  			
		}				
	
		if(Gameover==1){			// oyunun kaybedilmesi durumunda ne olacaðýna karar verir.
			printf("kaybettin !");	// konsol ekranýnda yazý çýktýsý verir.
		    bekle(bekleme_suresi);			
			return 0;				// dönme deðerini sýfýra ayarlayarak uygulamayý sonlandýrýr.
		}
	}
}
