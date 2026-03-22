#include <stdio.h>
#include <string.h>
#include<ctype.h>

char turkce_kucukHarf(char *c){
    switch (*c)
    {
    case 'Ç': return 'ç';
    case 'Ş': return 'ş';
    case 'Ğ': return 'ğ';
    case 'İ': return 'i';
    case 'I': return 'ı';
    case 'Ö': return 'ö';
    case 'Ü': return 'ü';

    
    default:return tolower(*c);
    }
}


int main(){
    

    char word[100];
    char line[1024];
    char lineLower[1024],wordLower[100];
    int satirNo=1;
    int totalCount = 0;
    
    printf("Enter your word:");
    fgets(word,sizeof(word),stdin);
    word[strcspn(word,"\n")] = '\0';

    strcpy(wordLower,word);
    turkce_kucukHarf(wordLower);

    FILE *fp = fopen("metin.txt","r");
    if(fp == NULL){
        printf("Dosya bulunamadi!!\n");
        system("pause");
        return 1;
    }
    FILE *out = fopen("sonuc.txt","w");
    if (out == NULL){
        printf("Sonuc dosyasi acilamadi!!");
        system("pause");
        return 1;
    }


    while (fgets(line,sizeof(line),fp) != NULL)
    {
        if(line[0] == '\n') continue;
        

        strcpy(lineLower,line);
        turkce_kucukHarf(lineLower);

        int count = 0;
        char *a = lineLower;
        while ((a = strstr(a,wordLower)) != NULL)
        {
            count++;
            a += strlen(wordLower);
        }
        if(count>0){
            fprintf(out,"Paragraf %d: %d kez bulundu\n",satirNo, count);
            printf("Paragraf %d: %d kez bulundu\n",satirNo, count);
            totalCount += count;
        }
        satirNo++;

        
    }
    
    fprintf(out,"Toplam: %d\n",totalCount);
    
    printf("Toplam: %d\n",totalCount);
    printf("Program bitti. Sonuc dosyasi aciliyor...\n");
    printf("Enter tusuna basin...\n");
    getchar(); 
    fclose(out);
    fclose(fp);
    system("start sonuc.txt");
    return 0;
}