#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OGRENCI 100
#define MAX_NOT 3

typedef struct {
    int numara;
    char ad[100];
    char soyad[100];
    float notlar[MAX_NOT];
} ogrenci;

ogrenci ogrenciListesi[MAX_OGRENCI];
int ogrenciSayisi = 0;

// Fonksiyon prototipleri
void ogrenciEkle();
void ogrenciSil();
void ogrenciGuncelle();
void ogrenciListele();
float ortalamaHesapla(ogrenci ogr);
void dosyayaKaydet();
void dosyadanOku();

int main() {
    dosyadanOku(); // Program ba�lad���nda dosyadan verileri okur. (��renci bilgileri bir dosyaya kaydedilir ve program ba�lat�ld���nda dosyadan okunur, bununla veriler kal�c� olarak saklanm�� olur.)

    int secim;  //Yap�lmak istenen se�im sorulur.
    do {
        printf("\nOgrenci Yonetim Sistemi\n");
        printf("1. Ogrenci Ekle\n");
        printf("2. Ogrenci Sil\n");
        printf("3. Ogrenci Guncelle\n");
        printf("4. Ogrenci Listele\n");
        printf("5. Cikis\n");
        printf("Seciminizi girin: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                ogrenciEkle();
                break;
            case 2:
                ogrenciSil();
                break;
            case 3:
                ogrenciGuncelle();
                break;
            case 4:
                ogrenciListele();
                break;
            case 5:
                dosyayaKaydet(); // Program kapanmadan �nce verileri dosyaya kaydetmek i�in kullan�l�yor.
                printf("Cikis yapiliyor.\n");
                break;
            default:
                printf("Gecersiz secim.\n");
        }
    } while (secim != 5);

    return 0;
}

void ogrenciEkle() {    //��renci eklemek i�in kullan�lacak fonksiyon, s�rayla numaras� ad�, soyad� ve notu al�n�r. Ek olarak sisteme kaydedilen mevcut ��renci say�s� da hesaplan�r.
    if (ogrenciSayisi < MAX_OGRENCI) {
        ogrenci yeniOgrenci;
        printf("Ogrenci numarasi: ");
        scanf("%d", &yeniOgrenci.numara);
        printf("Ogrenci adi: ");
        scanf("%s", yeniOgrenci.ad); // G�venlik a��s�ndan fgets kullan�lmas� �nerilir.
        printf("Ogrenci soyadi: ");
        scanf("%s", yeniOgrenci.soyad); // G�venlik a��s�ndan fgets kullan�lmas� �nerilir.
        int i;
        for(i=0; i<MAX_NOT; i++){
            printf("%d. Notu giriniz:",i+1);
            scanf("%f",&yeniOgrenci.notlar[i]);
        }
        ogrenciListesi[ogrenciSayisi] = yeniOgrenci;
        ogrenciSayisi++;
        printf("Ogrenci eklendi.\n");
    } else {
        printf("Maksimum ogrenci sayisina ulasildi.\n");
    }
}

void ogrenciSil() {  //��renci silmek i�in kullan�lacak fonksiyon, ��rencinin numaras�n� al�p sistemden siliyor, mevcut ��renci say�s�n� da eksiltiyor.
    int numara;
    printf("Silinecek ogrencinin numarasini girin: ");
    scanf("%d", &numara);
    
    int i;
    for (i = 0; i < ogrenciSayisi; i++) {
        if (ogrenciListesi[i].numara == numara) {
        	int j;
            for (j = i; j < ogrenciSayisi - 1; j++) {
                ogrenciListesi[j] = ogrenciListesi[j + 1];
            }
            ogrenciSayisi--;
            printf("Ogrenci silindi.\n");
            return;
        }
    }

    printf("Ogrenci bulunamadi.\n");
}

void ogrenciGuncelle() {      // ��rencilerin bilgilerini d�zenlemek i�in kullan�lacak fonksiyon, ��rencinin numaras�n� al�p b�t�n bilgileri tekrardan sorup d�zenliyor.
    int numara;
    printf("Guncellenecek ogrencinin numarasini girin: ");
    scanf("%d", &numara);
    
    int i;
    for (i = 0; i < ogrenciSayisi; i++) {
        if (ogrenciListesi[i].numara == numara) {
            printf("Yeni ogrenci adi: ");
            scanf("%s", ogrenciListesi[i].ad); // G�venlik a��s�ndan fgets kullan�lmas� �nerilir.
            printf("Yeni ogrenci soyadi: ");
            scanf("%s", ogrenciListesi[i].soyad); // G�venlik a��s�ndan fgets kullan�lmas� �nerilir.
            int j;
            for(j=0; j<MAX_NOT; j++){
                printf("%d. Yeni Notu giriniz:",j+1);
                scanf("%f",&ogrenciListesi[i].notlar[j]);
            }
            printf("Ogrenci guncellendi.\n");
            return;
        }
    }

    printf("Ogrenci bulunamadi.\n");
}

void ogrenciListele() {  //��rencileri liste halinde g�rmek i�in kullan�lacak fonksiyon, e�er sisteme ��renci kaydedilmediyse kay�tl� ��renci olmad���n� belirten bir mesaj veriliyor, e�er kay�tl� ��renci varsa Numara, Ad, Soyad ve notlar �eklinde g�steriyor.
    if (ogrenciSayisi == 0) {
        printf("Kayitli ogrenci yok.\n");
        return;
    }

    printf("\nOgrenci Listesi:\n");
    int i;
    for (i = 0; i < ogrenciSayisi; i++) {
        printf("Numara: %d, Ad: %s, Soyad: %s, Notlar:", ogrenciListesi[i].numara, ogrenciListesi[i].ad, ogrenciListesi[i].soyad);
        int j;
        for(j=0; j<MAX_NOT; j++){
            printf(" %.2f",ogrenciListesi[i].notlar[j]);
        }
		float ortalama = ortalamaHesapla(ogrenciListesi[i]); // Ortalama hesaplan�yor
        printf(", Ortalama: %.2f\n", ortalama); // Ortalama ekrana yazd�r�l�yor
    }
}

float ortalamaHesapla(ogrenci ogr){   
    float toplam = 0;
    int i;
    for(i=0; i<MAX_NOT; i++){
        toplam += ogr.notlar[i];
    }
    return toplam / MAX_NOT;
}

void dosyayaKaydet() {
    FILE *dosya = fopen("ogrenciler.txt", "w");
    if (dosya == NULL) {
        printf("Dosya acilamadi.\n");
        return;
    }

    fprintf(dosya, "%d\n", ogrenciSayisi); // ��renci say�s�n� kaydet
    int i;
    for (i = 0; i < ogrenciSayisi; i++) {
        fprintf(dosya, "%d %s %s", ogrenciListesi[i].numara, ogrenciListesi[i].ad, ogrenciListesi[i].soyad);
        int j;
        for(j=0; j<MAX_NOT; j++){
            fprintf(dosya," %.2f",ogrenciListesi[i].notlar[j]);
        }
        fprintf(dosya,"\n");
    }

    fclose(dosya);
    printf("Veriler dosyaya kaydedildi.\n");
}

void dosyadanOku() {
    FILE *dosya = fopen("ogrenciler.txt", "r");
    if (dosya == NULL) {
        printf("Dosya bulunamadi. Yeni bir dosya olusturulacak.\n"); // Dosya yoksa sorun de�il, yeni olu�turulacak.
        return;
    }

    fscanf(dosya, "%d\n", &ogrenciSayisi);
    int i;
    for (i = 0; i < ogrenciSayisi; i++) {
        fscanf(dosya, "%d %s %s", &ogrenciListesi[i].numara, ogrenciListesi[i].ad, ogrenciListesi[i].soyad);
        int j;
        for(j=0; j<MAX_NOT; j++){
            fscanf(dosya," %f",&ogrenciListesi[i].notlar[j]);
        }
    }

    fclose(dosya);
    printf("Veriler dosyadan okundu.\n");
}
