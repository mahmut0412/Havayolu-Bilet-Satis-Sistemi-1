#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>

struct ucus
{
    int ucus_no;
    char kalkis_yeri[50];
    char varis_yeri[50];
    int kalkis_saati;
    int kalkis_dakikasi;
    int koltuk_kapasitesi;
    float baslangic_fiyati;
};

struct bilet
{
    char TC[11];
    int ucus_no;
    float bilet_fiyati;
};

void systemHeader()
{
    printf("\t\t\t<><><><><><><><><><><><><><><><><><><><><><><>--------------||\n");
    printf("\t\t\t||    MMA Havayolu Bilet Satis Sistemine hosgeldiniz\t    ||\n");
    printf("\t\t\t||--------------<><><><><><><><><><><><><><><><><><><><><><><>\n");

    printf("\n\n\n\n");

    printf("\tA) Sorgulama islemleri\n");
    printf("\t\t1) Bir ucusun bilgilerinin listelenmesi\n");
    printf("\t\t2) Bir ucusun bilgilerinin ve o ucusa iliskin satilan biletlerin listelenmesi\n");
    printf("\t\t3) Bir Yerden kalkan ucuslarin bilgilerinin listelenmesi\n");
    printf("\t\t4) Koltuk doluluk orani yuzde 50`nin altinda olan ucuslarin listelenmesi\n");
    printf("\t\t5) Bir yolcunun biletlerinin listelenmesi\n\n");

    printf("\tB) Guncelleme islemleri\n");
    printf("\t\t1) Yeni bir ucusun eklenmesi\n");
    printf("\t\t2) Bir ucusun kaydinin silinmesi\n");
    printf("\t\t3) Bir ucusun kalkis zamaninin degistirilmesi\n");
    printf("\t\t4) Bir ucusa iliskin bilet satilmasi\n\n\n");
}

void yeniUcusEkleme();

int birUcusunBilgileriListele();

void biletSatis();

void birUcusaIliskinBiletleriListele();

void birYerdenUcusunBilgileriListele();

void dolulukOrani50ninAltindaListele();

void birYolcuBiletleriniListele();

void birUcusKaydininSilinmesi();

void kalkisZamanDegistirmesi();

int checkTC(char []);

int checkKarikter(char kalkisVaris[]);

float fiyatBelirleme(float, float);

int main()
{
    systemHeader(); // call System header function to print system basic info

    char islem_turu[2];

    printf("-> Lutfen yapmak istediginiz islemi seciniz (A1,A2,..,B1,B2..) :"); // Get operation type from user
    gets(islem_turu);

    if (strcmp(islem_turu, "A1") == 0)
    {
        printf("Bir ucusun bilgilerinin listelenmesi\n");
        birUcusunBilgileriListele();
    }
    else if (strcmp(islem_turu, "A2") == 0)
    {
        printf("Bir ucusun bilgilerinin ve o ucusa iliskin satilan biletlerin listelenmesi\n");
        birUcusaIliskinBiletleriListele();
    }
    else if (strcmp(islem_turu, "A3") == 0)
    {
        printf("Bir Yerden kalkan ucuslarin bilgilerinin listelenmesi\n");
        birYerdenUcusunBilgileriListele();
    }
    else if (strcmp(islem_turu, "A4") == 0)
    {
        printf("Koltuk doluluk orani yuzde 50`nin altinda olan ucuslarin listelenmesi\n");
        dolulukOrani50ninAltindaListele();
    }
    else if (strcmp(islem_turu, "A5") == 0)
    {
        printf("Bir yolcunun biletlerinin listelenmesi\n\n");
        birYolcuBiletleriniListele();
    }
    else if (strcmp(islem_turu, "B1") == 0)
    {
        printf("Yeni bir ucusun eklenmesi\n");
        yeniUcusEkleme();
    }
    else if (strcmp(islem_turu, "B2") == 0)
    {
        printf("Bir ucusun kaydinin silinmesi\n");
        birUcusKaydininSilinmesi();
    }
    else if (strcmp(islem_turu, "B3") == 0)
    {
        printf("Bir ucusun kalkis zamaninin degistirilmesi\n");
        kalkisZamanDegistirmesi();
    }
    else if (strcmp(islem_turu, "B4") == 0)
    {
        printf("Bir ucusa iliskin bilet satilmasi\n");
        biletSatis();
    }

    return 0;
}

void yeniUcusEkleme()
{
    struct ucus ucus_bilgileri;
    int ucus_numarasi, flag = 0;

    printf("- Lutfen ucus numarasini giriniz : ");
    scanf("%d", &ucus_numarasi);

    FILE *flPtr;

    flPtr = fopen("ucuslar.txt", "r");

    while (fscanf(flPtr, "%d %s %s %d %d %d %f",
                  &ucus_bilgileri.ucus_no,
                  ucus_bilgileri.kalkis_yeri,
                  ucus_bilgileri.varis_yeri,
                  &ucus_bilgileri.kalkis_saati,
                  &ucus_bilgileri.kalkis_dakikasi,
                  &ucus_bilgileri.koltuk_kapasitesi,
                  &ucus_bilgileri.baslangic_fiyati) == 7)
    {
        if (ucus_bilgileri.ucus_no == ucus_numarasi)
        {
            flag = 1;
            break;
        }
    }

    fclose(flPtr);

    if (flag == 0)
    {
        do{
        printf("- Kalkis yeri giriniz : ");
        scanf("%s", ucus_bilgileri.kalkis_yeri);
        }while(checkKarikter(ucus_bilgileri.kalkis_yeri)>=20);
        do{
        printf("- Varis yeri giriniz : ");
        scanf("%s", ucus_bilgileri.varis_yeri);
        }while(checkKarikter(ucus_bilgileri.varis_yeri)>=20);

        printf("- kalkis zamani giriniz (12:34 vs.) : ");
        scanf("%d:%d", &ucus_bilgileri.kalkis_saati, &ucus_bilgileri.kalkis_dakikasi);

        printf("- Koltuk kapasitesi giriniz : ");
        scanf("%d", &ucus_bilgileri.koltuk_kapasitesi);

        printf("- Biletin baslangic fiyatini giriniz : ");
        scanf("%f", &ucus_bilgileri.baslangic_fiyati);

        FILE *ucuslar_dosyasi;

        ucuslar_dosyasi = fopen("ucuslar.txt", "a");

        fprintf(ucuslar_dosyasi, "%d  %s  %s  %d  %d  %d  %.2f\n",
                ucus_numarasi,
                ucus_bilgileri.kalkis_yeri,
                ucus_bilgileri.varis_yeri,
                ucus_bilgileri.kalkis_saati,
                ucus_bilgileri.kalkis_dakikasi,
                ucus_bilgileri.koltuk_kapasitesi,
                ucus_bilgileri.baslangic_fiyati);

        fclose(ucuslar_dosyasi);
    }
    else
    {
        printf("\n* %d ucus numaraya ait bir ucus bulundu :( lutfen tekre deneyiniz\n", ucus_numarasi);
    }
}

int birUcusunBilgileriListele()
{
    struct ucus ucus_bilgileri;
    struct bilet bilet_bilgileri;
    int ucus_numarasi;

    printf("- Lutfen ucus numarasini giriniz : ");
    scanf("%d", &ucus_numarasi);

    FILE *flPtr,*flPtr2;

    flPtr = fopen("ucuslar.txt", "r");

    printf("\t\tUcus no  Kalkis yeri  Varis yeri  Zamani  Kapasite  Bos koltuk  Doluluk orani\n");
    printf("\t\t-------  -----------  ----------  ------  --------  ----------  -------------\n");

    while (fscanf(flPtr, "%d %s %s %d %d %d %f",
                  &ucus_bilgileri.ucus_no,
                  ucus_bilgileri.kalkis_yeri,
                  ucus_bilgileri.varis_yeri,
                  &ucus_bilgileri.kalkis_saati,
                  &ucus_bilgileri.kalkis_dakikasi,
                  &ucus_bilgileri.koltuk_kapasitesi,
                  &ucus_bilgileri.baslangic_fiyati) == 7)
    {
        if (ucus_bilgileri.ucus_no == ucus_numarasi)
        {
            int count = 0;
            flPtr2 = fopen("bilet.txt", "r");

            while (fscanf(flPtr2, "%d %s %f",
                          &bilet_bilgileri.ucus_no,
                          bilet_bilgileri.TC,
                          &bilet_bilgileri.bilet_fiyati
                         ) == 3)
            {
                if(ucus_bilgileri.ucus_no == bilet_bilgileri.ucus_no)
                    count++;
            }

            fclose(flPtr2);

            int bos_koltuk_say = ucus_bilgileri.koltuk_kapasitesi - count;
            float doluluk_orani = ((float)(ucus_bilgileri.koltuk_kapasitesi- bos_koltuk_say)/(float)ucus_bilgileri.koltuk_kapasitesi)*100;

            printf("\t\t%7d  %11s  %10s  %2d:%d  %9d  %10d  %13.2f\n",
                   ucus_bilgileri.ucus_no,
                   ucus_bilgileri.kalkis_yeri,
                   ucus_bilgileri.varis_yeri,
                   ucus_bilgileri.kalkis_saati,
                   ucus_bilgileri.kalkis_dakikasi,
                   ucus_bilgileri.koltuk_kapasitesi,
                   bos_koltuk_say,
                   doluluk_orani
                  );
        }
    }

    fclose(flPtr);

    return ucus_numarasi;
}

void biletSatis()
{
    struct ucus ucus_bilgileri;
    struct bilet bilet_bilgileri;

    int flag = 0;
    FILE *flPtr;

    flPtr = fopen("ucuslar.txt", "r");

    printf("\t\tUcus no  Kalkis yeri  Varis yeri  \tZamani  Kapasite  \tBBF\n");
    printf("\t\t-------  -----------  ----------  \t------  --------  \t------\n");

    while (fscanf(flPtr, "%d %s %s %d %d %d %f",
                  &ucus_bilgileri.ucus_no,
                  ucus_bilgileri.kalkis_yeri,
                  ucus_bilgileri.varis_yeri,
                  &ucus_bilgileri.kalkis_saati,
                  &ucus_bilgileri.kalkis_dakikasi,
                  &ucus_bilgileri.koltuk_kapasitesi,
                  &ucus_bilgileri.baslangic_fiyati) == 7)
    {

        printf("\t\t%7d  %11s  %10s  \t%2d:%d  %9d  \t%5.2f\n",
               ucus_bilgileri.ucus_no,
               ucus_bilgileri.kalkis_yeri,
               ucus_bilgileri.varis_yeri,
               ucus_bilgileri.kalkis_saati,
               ucus_bilgileri.kalkis_dakikasi,
               ucus_bilgileri.koltuk_kapasitesi,
               ucus_bilgileri.baslangic_fiyati
              );
    }

    fclose(flPtr);

    flPtr = fopen("ucuslar.txt", "r");

    printf("lutfen ucus numarasi giriniz : ");
    scanf("%d", &bilet_bilgileri.ucus_no);

    int ucus_no = bilet_bilgileri.ucus_no;

    while (fscanf(flPtr, "%d %s %s %d %d %d %f",
                  &ucus_bilgileri.ucus_no,
                  ucus_bilgileri.kalkis_yeri,
                  ucus_bilgileri.varis_yeri,
                  &ucus_bilgileri.kalkis_saati,
                  &ucus_bilgileri.kalkis_dakikasi,
                  &ucus_bilgileri.koltuk_kapasitesi,
                  &ucus_bilgileri.baslangic_fiyati) == 7)
    {
        if (ucus_bilgileri.ucus_no == bilet_bilgileri.ucus_no)
        {
            flag = 1;
            break;
        }
    }
    fclose(flPtr);

    if (flag == 1)
    {
        int bilet_sayisi, count = 0;

        printf("Satin almak istediginiz bilet sayisi giriniz :");
        scanf("%d", &bilet_sayisi);

        flPtr = fopen("bilet.txt", "r");

        while (fscanf(flPtr, "%d %s %f",
                      &bilet_bilgileri.ucus_no,
                      bilet_bilgileri.TC,
                      &bilet_bilgileri.bilet_fiyati
                     ) == 3)
        {
            if(ucus_no == bilet_bilgileri.ucus_no)
                count++;
        }

        fclose(flPtr);
        int bos_koltuk_say;
        float top_fiyat = 0,bos_koltuk_orani;

        for(int k = 0 ; k < bilet_sayisi ; k++)
        {
            count++;
            bos_koltuk_say = ucus_bilgileri.koltuk_kapasitesi - count;
            bos_koltuk_orani = ((float)bos_koltuk_say/(float)ucus_bilgileri.koltuk_kapasitesi)*100;

            top_fiyat += fiyatBelirleme(bos_koltuk_orani,ucus_bilgileri.baslangic_fiyati);
        }

        int durum = 0;
        printf("-> Toplam bilet fiyatlari : %.2f\n", top_fiyat);
        printf("* Onayliyormusunuz (1/0) :");
        scanf("%d",&durum);

        if(durum == 1)
        {
            if(bos_koltuk_say >= bilet_sayisi)
            {
                char TC_arr[11][bilet_sayisi];
                int i = 0, j = 0;

                while(i < bilet_sayisi)
                {
                    int length = 0;
                    while(1)
                    {
                        printf("%d . Biletin TC sini giriniz : ",i+1);
                        scanf("%s",TC_arr);
                        length = checkTC(TC_arr);
                        if (length == 11)
                            break;

                    }

                    ///////////////////////////////////////////

                    flPtr = fopen("bilet.txt", "a");

                    fprintf(flPtr, "%d %s %.2f\n",
                            ucus_no,
                            TC_arr,
                            fiyatBelirleme(bos_koltuk_orani,ucus_bilgileri.baslangic_fiyati)
                           );

                    fclose(flPtr);

                    ////////////////////////////////////////////

                    flPtr = fopen("bilet.txt", "r");

                    while (fscanf(flPtr, "%d %s %f",
                                  &bilet_bilgileri.ucus_no,
                                  bilet_bilgileri.TC,
                                  &bilet_bilgileri.bilet_fiyati
                                 ) == 3)
                    {
                        if(ucus_no == bilet_bilgileri.ucus_no)
                            count++;
                    }

                    fclose(flPtr);

                    bos_koltuk_say = ucus_bilgileri.koltuk_kapasitesi - count;
                    bos_koltuk_orani = ((float)bos_koltuk_say/(float)ucus_bilgileri.koltuk_kapasitesi)*100;

                    ////////////////////////////////////////////

                    j++;
                    i++;
                }
            }
            else
            {
                printf("%d ucus numaraya ait bos koltuk bulunmadi :(\n",ucus_no);
            }
        }
        else
        {
            printf("Memnun olduk :)\n");
        }



    }
    else
    {
        printf("\nGirmis oldugunuz ucus numaraya ait bir ucus bulunmadi :(\n");
    }
}

void birUcusaIliskinBiletleriListele()
{
    struct bilet bilet_bilgileri;
    int ucus_no = birUcusunBilgileriListele();

    printf("Satilan biletler :\n");
    printf("TC kinlik No   Fiyat   \n");
    printf("------------   --------\n");

    int count = 0;
    float top_fiyat = 0;

    FILE *flPtr;

    flPtr = fopen("bilet.txt", "r");

    while (fscanf(flPtr, "%d %s %f",
                  &bilet_bilgileri.ucus_no,
                  bilet_bilgileri.TC,
                  &bilet_bilgileri.bilet_fiyati
                 ) == 3)
    {
        if(ucus_no == bilet_bilgileri.ucus_no)
        {
            printf("%s  %8.2f\n",bilet_bilgileri.TC,bilet_bilgileri.bilet_fiyati);
            count++;
            top_fiyat += bilet_bilgileri.bilet_fiyati;
        }

    }
    printf("--------------------------------\n");
    printf("Toplam bilet sayisi : %d\n",count);
    printf("Toplam kazanc : %.2f TL\n",top_fiyat);
    printf("Ortalam bilet fiyati : %.2f TL\n",top_fiyat/(float)count);

    fclose(flPtr);

}

void birYerdenUcusunBilgileriListele()
{
    struct ucus ucus_bilgileri;
    struct bilet bilet_bilgileri;
    char kalkis_yeri[50];

    printf("- Lutfen kalkis yeri giriniz : ");
    scanf("%s", kalkis_yeri);

    FILE *flPtr,*flPtr2;

    flPtr = fopen("ucuslar.txt", "r");

    printf("\t\tUcus no  Kalkis yeri  Varis yeri  Zamani  Kapasite  Bos koltuk  Doluluk orani\n");
    printf("\t\t-------  -----------  ----------  ------  --------  ----------  -------------\n");

    while (fscanf(flPtr, "%d %s %s %d %d %d %f",
                  &ucus_bilgileri.ucus_no,
                  ucus_bilgileri.kalkis_yeri,
                  ucus_bilgileri.varis_yeri,
                  &ucus_bilgileri.kalkis_saati,
                  &ucus_bilgileri.kalkis_dakikasi,
                  &ucus_bilgileri.koltuk_kapasitesi,
                  &ucus_bilgileri.baslangic_fiyati) == 7)
    {
        if (strcmp(ucus_bilgileri.kalkis_yeri,kalkis_yeri) == 0)
        {
            int count = 0;
            flPtr2 = fopen("bilet.txt", "r");

            while (fscanf(flPtr2, "%d %s %f",
                          &bilet_bilgileri.ucus_no,
                          bilet_bilgileri.TC,
                          &bilet_bilgileri.bilet_fiyati
                         ) == 3)
            {
                if(ucus_bilgileri.ucus_no == bilet_bilgileri.ucus_no)
                    count++;
            }

            fclose(flPtr2);

            int bos_koltuk_say = ucus_bilgileri.koltuk_kapasitesi - count;
            float doluluk_orani = ((float)(ucus_bilgileri.koltuk_kapasitesi- bos_koltuk_say)/(float)ucus_bilgileri.koltuk_kapasitesi)*100;

            printf("\t\t%7d  %11s  %10s  %2d:%d  %9d  %10d  %13.2f\n",
                   ucus_bilgileri.ucus_no,
                   ucus_bilgileri.kalkis_yeri,
                   ucus_bilgileri.varis_yeri,
                   ucus_bilgileri.kalkis_saati,
                   ucus_bilgileri.kalkis_dakikasi,
                   ucus_bilgileri.koltuk_kapasitesi,
                   bos_koltuk_say,
                   doluluk_orani
                  );
        }
    }

    fclose(flPtr);
}

void dolulukOrani50ninAltindaListele()
{
    struct ucus ucus_bilgileri;
    struct bilet bilet_bilgileri;
    char kalkis_yeri[50];

    FILE *flPtr,*flPtr2;

    flPtr = fopen("ucuslar.txt", "r");

    printf("\t\tUcus no  Kalkis yeri  Varis yeri  Zamani  Kapasite  Bos koltuk  Doluluk orani\n");
    printf("\t\t-------  -----------  ----------  ------  --------  ----------  -------------\n");

    while (fscanf(flPtr, "%d %s %s %d %d %d %f",
                  &ucus_bilgileri.ucus_no,
                  ucus_bilgileri.kalkis_yeri,
                  ucus_bilgileri.varis_yeri,
                  &ucus_bilgileri.kalkis_saati,
                  &ucus_bilgileri.kalkis_dakikasi,
                  &ucus_bilgileri.koltuk_kapasitesi,
                  &ucus_bilgileri.baslangic_fiyati) == 7)
    {
        int count = 0;

        flPtr2 = fopen("bilet.txt", "r");

        while (fscanf(flPtr2, "%d %s %f",
                      &bilet_bilgileri.ucus_no,
                      bilet_bilgileri.TC,
                      &bilet_bilgileri.bilet_fiyati
                     ) == 3)
        {
            if(ucus_bilgileri.ucus_no == bilet_bilgileri.ucus_no)
                count++;
        }

        fclose(flPtr2);

        int bos_koltuk_say = ucus_bilgileri.koltuk_kapasitesi - count;
        float doluluk_orani = ((float)(ucus_bilgileri.koltuk_kapasitesi- bos_koltuk_say)/(float)ucus_bilgileri.koltuk_kapasitesi)*100;

        if(doluluk_orani < 50)
        {
            printf("\t\t%7d  %11s  %10s  %2d:%d  %9d  %10d  %13.2f\n",
                   ucus_bilgileri.ucus_no,
                   ucus_bilgileri.kalkis_yeri,
                   ucus_bilgileri.varis_yeri,
                   ucus_bilgileri.kalkis_saati,
                   ucus_bilgileri.kalkis_dakikasi,
                   ucus_bilgileri.koltuk_kapasitesi,
                   bos_koltuk_say,
                   doluluk_orani
                  );
        }

    }

    fclose(flPtr);
}

void birYolcuBiletleriniListele()
{
    struct bilet bilet_bilgileri;
    struct ucus ucus_bilgileri;
    char tc[11];
    printf("Lutfen TC numarasi giriniz : ");
    scanf("%s",tc);

    int res = checkTC(tc);

    if(res == 11)
    {

        FILE * flPtr, *flPtr2;

        flPtr = fopen("bilet.txt", "r");

        while (fscanf(flPtr, "%d %s %f",
                      &bilet_bilgileri.ucus_no,
                      bilet_bilgileri.TC,
                      &bilet_bilgileri.bilet_fiyati
                     ) == 3)
        {
            if(strcmp(tc,bilet_bilgileri.TC) == 0)
            {
                flPtr2 = fopen("ucuslar.txt", "r");

                printf("\t\tUcus no  Kalkis yeri  Varis yeri  Zamani  BBF\n");
                printf("\t\t-------  -----------  ----------  ------  ------\n");

                while (fscanf(flPtr2, "%d %s %s %d %d %d %f",
                              &ucus_bilgileri.ucus_no,
                              ucus_bilgileri.kalkis_yeri,
                              ucus_bilgileri.varis_yeri,
                              &ucus_bilgileri.kalkis_saati,
                              &ucus_bilgileri.kalkis_dakikasi,
                              &ucus_bilgileri.koltuk_kapasitesi,
                              &ucus_bilgileri.baslangic_fiyati) == 7)
                {
                    if(bilet_bilgileri.ucus_no == ucus_bilgileri.ucus_no)
                    {
                        printf("\t\t%7d  %11s  %10s  %2d:%d  %5.2f\n",
                               ucus_bilgileri.ucus_no,
                               ucus_bilgileri.kalkis_yeri,
                               ucus_bilgileri.varis_yeri,
                               ucus_bilgileri.kalkis_saati,
                               ucus_bilgileri.kalkis_dakikasi,
                               ucus_bilgileri.baslangic_fiyati
                              );
                    }
                }
            }
        }
        fclose(flPtr2);
        fclose(flPtr);
    }
    else
    {
        printf("Yanlis TC numarasi girdiniz :(\n");
    }



}

void birUcusKaydininSilinmesi()
{
    int numara;
    struct ucus ucus_bilgileri;
    char a[] = "ucuslar.txt";
    char b[] = "yeni.txt";

    printf("Lutfen silmek istediginiz ucus numarasi giriniz : ");
    scanf("%d", &numara);

    FILE *flPtr;
    FILE *yeni;

    flPtr = fopen("ucuslar.txt", "r");
    yeni = fopen("yeni.txt", "a+");

    while (fscanf(flPtr, "%d %s %s %d %d %d %f",
                  &ucus_bilgileri.ucus_no,
                  ucus_bilgileri.kalkis_yeri,
                  ucus_bilgileri.varis_yeri,
                  &ucus_bilgileri.kalkis_saati,
                  &ucus_bilgileri.kalkis_dakikasi,
                  &ucus_bilgileri.koltuk_kapasitesi,
                  &ucus_bilgileri.baslangic_fiyati) == 7)
    {
        if (numara != ucus_bilgileri.ucus_no)
        {
            fprintf(yeni, "%d  %s  %s  %d  %d  %d  %.2f\n",
                    ucus_bilgileri.ucus_no,
                    ucus_bilgileri.kalkis_yeri,
                    ucus_bilgileri.varis_yeri,
                    ucus_bilgileri.kalkis_saati,
                    ucus_bilgileri.kalkis_dakikasi,
                    ucus_bilgileri.koltuk_kapasitesi,
                    ucus_bilgileri.baslangic_fiyati);
        }
    }
    fclose(flPtr);
    fclose(yeni);
    remove("ucuslar.txt");
    rename(b, a);
}

void kalkisZamanDegistirmesi()
{
    struct ucus ucus_bilgileri;
    int yenisa;
    int yenidk;
    int numara;
    char a[] = "ucuslar.txt";
    char b[] = "yeni.txt";
    FILE *flPtr;
    FILE *yeni;

    printf("lutfen zamani degistirilecek ucus numarasi giriniz : ");
    scanf("%d", &numara);

    flPtr = fopen("ucuslar.txt", "r");
    while (fscanf(flPtr, "%d %s %s %d %d %d %f",
                  &ucus_bilgileri.ucus_no,
                  ucus_bilgileri.kalkis_yeri,
                  ucus_bilgileri.varis_yeri,
                  &ucus_bilgileri.kalkis_saati,
                  &ucus_bilgileri.kalkis_dakikasi,
                  &ucus_bilgileri.koltuk_kapasitesi,
                  &ucus_bilgileri.baslangic_fiyati) == 7)
    {
        if (numara == ucus_bilgileri.ucus_no)
        {
            printf("lutfen yeni saat ve dakika giriniz (12:34) :");
            scanf("%d:%d", &yenisa, &yenidk);
            ucus_bilgileri.kalkis_saati = yenisa;
            ucus_bilgileri.kalkis_dakikasi = yenidk;
        }
        yeni = fopen("yeni.txt", "a");

        fprintf(yeni, "%d  %s  %s  %d  %d  %d  %.2f\n",
                ucus_bilgileri.ucus_no,
                ucus_bilgileri.kalkis_yeri,
                ucus_bilgileri.varis_yeri,
                ucus_bilgileri.kalkis_saati,
                ucus_bilgileri.kalkis_dakikasi,
                ucus_bilgileri.koltuk_kapasitesi,
                ucus_bilgileri.baslangic_fiyati);
    }

    fclose(flPtr);
    fclose(yeni);
    remove("ucuslar.txt");
    rename(b, a);
}

int checkTC(char TC_arr[])
{
    int length = 0;

    for(int i = 0 ; TC_arr[i] != '\0' ; i++)
    {
        length++;
    }

    return length;
}

float fiyatBelirleme(float bko, float bbf)  //bbf (Baslangic bilet fiyati) bko (bos koltuk orani)
{
    if     (bko > 90 && bko <= 100)
        return bbf;
    else if(bko > 80 && bko <= 90)
        return bbf*1.1;
    else if(bko > 70 && bko <= 80)
        return bbf*1.2;
    else if(bko > 60 && bko <= 70)
        return bbf*1.3;
    else if(bko > 50 && bko <= 60)
        return bbf*1.4;
    else if(bko > 40 && bko <= 50)
        return bbf*1.5;
    else if(bko > 30 && bko <= 40)
        return bbf*1.6;
    else if(bko > 20 && bko <= 30)
        return bbf*1.7;
    else if(bko > 10 && bko <= 20)
        return bbf*1.8;
    else if(bko > 0 && bko <= 10)
        return bbf*1.9;
}
int checkKarikter(char kalkisVaris[]){
    int length = 0;
    for(int i = 0 ; kalkisVaris[i] !='\0' ; i++)
    {
        length++;
    }

    return length;
}


