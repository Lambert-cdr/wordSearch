#include <stdio.h>
#include <string.h>
#include <ctype.h>


void turkce_kucukHarf(char *str){
    for(int i = 0; str[i] != '\0'; i++){
        switch (str[i])
        {
        case 'Ç': str[i] = 'ç'; break;
        case 'Ş': str[i] = 'ş'; break;
        case 'Ğ': str[i] = 'ğ'; break;
        case 'İ': str[i] = 'i'; break;
        case 'I': str[i] = 'ı'; break;
        case 'Ö': str[i] = 'ö'; break;
        case 'Ü': str[i] = 'ü'; break;
        default: str[i] = tolower(str[i]);
        }
    }
}

int main(){
    char word[100];
    char line[1024];
    char lineLower[1024], wordLower[100];

    int satirNo = 1;
    int totalCount = 0;
    char fileName[256];

    printf("Dosya adini giriniz:");
    fgets(fileName,sizeof(fileName),stdin);
    fileName[strcspn(fileName,"\n")]='\0';

    printf("Enter your word: ");
    fgets(word, sizeof(word), stdin);
    word[strcspn(word, "\n")] = '\0';

    strcpy(wordLower, word);
    turkce_kucukHarf(wordLower);
    

    FILE *fp = fopen(fileName, "r");
    if(fp == NULL){
        printf("Dosya bulunamadi!\n");
        return 1;
    }

    FILE *out = fopen("sonuc2.txt", "w");
    if(out == NULL){
        printf("Sonuc dosyasi acilamadi!\n");
        fclose(fp);
        return 1;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if(line[0] == '\n') continue;

        strcpy(lineLower, line);
        turkce_kucukHarf(lineLower);

        int count = 0;
        char *a = lineLower;

        while ((a = strstr(a, wordLower)) != NULL)
        {
            count++;
            a += strlen(wordLower);
        }

        if(count > 0){
            printf("Satir %d: %d kez bulundu\n", satirNo, count);
            fprintf(out, "Satir %d: %d kez bulundu\n", satirNo, count);
            totalCount += count;
        }

        satirNo++;
    }

    printf("Toplam: %d\n", totalCount);
    fprintf(out, "Toplam: %d\n", totalCount);

    fclose(fp);
    fclose(out);

    printf("Program bitti. Sonuc dosyasi olusturuldu.\n");

    return 0;
}