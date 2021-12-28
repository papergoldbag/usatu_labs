#include <stdio.h>
#include <stdlib.h>


// Strlen
int Strlen1(char* s){
  int i = 0;
  while(1){
    if (s[i] == '\0'){
      break;
    }
    i++;
  }
  return i;
}

int Strlen2(char* s) {
  char *sc = s;
  while (1){
    if (!*sc) return sc - s;
    sc++;
  }
}

int Strlen3(char* s){
  int i=0;
  for(; s[i]!=0; ++i);
  return i;
}

int Strlen4(char* s){
  int i = 0;
  for(;s[i]!='\0';i++);
  return i;
}

void tests_strlen(char* test_s){
  int strlen1_res = Strlen1(test_s);
  printf("Strlen1(\"%s\")=%d\n", test_s, strlen1_res);

  int strlen2_res = Strlen2(test_s);
  printf("Strlen2(\"%s\")=%d\n", test_s, strlen2_res);

  int strlen3_res = Strlen3(test_s);
  printf("Strlen3(\"%s\")=%d\n", test_s, strlen3_res);

  int strlen4_res = Strlen4(test_s);
  printf("Strlen4(\"%s\")=%d", test_s, strlen4_res);
}


// Strcmp
int Strcmp1(char* s1, char* s2)
{
    while (*s1 && (*s1 == *s2))
        s1++, s2++;
    int dif = *(const unsigned char*)s1 - *(const unsigned char*)s2;
    if (dif == 0) return 0;
    else if (dif > 0) return 1;
    else return -1;
}

int Strcmp2(char* s1, char* s2){
  for( ; *s1 == *s2; ++s1, ++s2 )
      if ( *s2 == '\0' )
          return 0;
  int dif = (unsigned char) *s1 - (unsigned char) *s2;
  if (dif == 0) return 0;
  else if (dif > 0) return 1;
  else return -1;
}

int Strcmp3 (char* s1, char* s2){
  const unsigned char *p1 = ( const unsigned char * )s1;
  const unsigned char *p2 = ( const unsigned char * )s2;

  while ( *p1 && *p1 == *p2 ) ++p1, ++p2;

  return ( *p1 > *p2 ) - ( *p2  > *p1 );
}

int Strcmp4(char *s1, char *s2)
{
    int ret=0;
    while( !(ret = *(unsigned char*)s1 - *(unsigned char*)s2 ) && *s1 )
    {
        s1++;
        s2++;
    }
    if(ret < 0)
        return -1;
    else if(ret > 0)
        return 1;
    return 0;
}

void tests_strcmp(char* s1, char* s2){
  int strcmp1_res = Strcmp1(s1, s2);
  printf("Strcmp1(\"%s\", \"%s\")=%d\n", s1, s2, strcmp1_res);

  int strcmp2_res = Strcmp2(s1, s2);
  printf("Strcmp2(\"%s\", \"%s\")=%d\n", s1, s2, strcmp2_res);

  int strcmp3_res = Strcmp3(s1, s2);
  printf("Strcmp3(\"%s\", \"%s\")=%d\n", s1, s2, strcmp3_res);

  int strcmp4_res = Strcmp4(s1, s2);
  printf("Strcmp4(\"%s\", \"%s\")=%d", s1, s2, strcmp4_res);
}


// Strcopy
void Strcpy1(char* dst, char* src){
  while ((*dst++=*src++)!='\0');
}

void Strcpy2(char* dst, char* src){
  while(*src != '\0'){
      *dst = *src;
      dst++;
      src++;
  }
  *dst = '\0';
}

void tests_strcpy(char* src){
  char* dest;

  Strcpy1(dest, src);
  printf("Strcpy1(dest, \"%s\")\n", src);
  printf("dest=\"%s\"\n", dest);

  Strcpy2(dest, src);
  printf("Strcpy2(dest, \"%s\")\n", src);
  printf("dest=\"%s\"", dest);
}


int main(){
  printf("1)Пустая строка\n");
  tests_strlen("");
  printf("\n\n");
  printf("2)Не пустая строка\n");
  tests_strlen("Hello world");
  printf("\n\n");

  printf("1) Сравнение с пустой строкой\n");
  tests_strcmp("aaaaa", "");
  printf("\n\n");
  printf("2) Первая строка больше, но короче\n");
  tests_strcmp("zzzzz", "aaaaaa");
  printf("\n\n");
  printf("2) Первая строка больше и длиннее\n");
  tests_strcmp("zzzzzz", "aaaaa");
  printf("\n\n");
  printf("4) Первая строка больше и имеет такую же длину, как и вторая\n");
  tests_strcmp("zzzzz", "aaaaa");
  printf("\n\n");
  printf("5) Вторая строка больше, но короче\n");
  tests_strcmp("aaaaaa", "zzzzz");
  printf("\n\n");
  printf("6) Вторая строка больше и длиннее\n");
  tests_strcmp("aaaaa", "zzzzzzzz");
  printf("\n\n");
  printf("7) Обе строки равны\n");
  tests_strcmp("aaaaa", "aaaaa");
  printf("\n\n");

  printf("1)Src пуста\n");
  tests_strcpy("");
  printf("\n\n");
  printf("2)Src не пуста\n");
  tests_strcpy("Hello");
  printf("\n\n");

  return 0;
}
