#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


// additional funcs
int schet(int n){
    int count = 1;
    while ( n = n / 10 )
        count++;
    return count;
}


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

void Strcpy3(char *dst, const char *src)
{
  int i;
  for (i=0; src[i] != '\0'; ++i)
    dst[i] = src[i];
  dst[i]= '\0';
}

void Strcpy4(char* dst, char* src ){
     while((*dst++ = *src++));
  }

void tests_strcpy(char* src){
  char* dest;

  Strcpy1(dest, src);
  printf("Strcpy1(dest, \"%s\")\n", src);
  printf("dest=\"%s\"\n", dest);

  Strcpy2(dest, src);
  printf("Strcpy2(dest, \"%s\")\n", src);
  printf("dest=\"%s\"\n", dest);

  Strcpy3(dest, src);
  printf("Strcpy3(dest, \"%s\")\n", src);
  printf("dest=\"%s\"\n", dest);

  Strcpy4(dest, src);
  printf("Strcpy4(dest, \"%s\")\n", src);
  printf("dest=\"%s\"", dest);
}


// Strpos and Strstr
char *Strstr1(char *str, char *substring){
    char *a;
    char *b;

    b = substring;

    if (*b == 0) {
        return (char *) str;
    }

    for ( ; *str != 0; str += 1) {
        if (*str != *b) {
            continue;
        }

        a = str;
        while (1) {
            if (*b == 0) {
                return (char *) str;
            }
            if (*a++ != *b++) {
                break;
            }
        }
        b = substring;
    }

    return NULL;
}

int Strpos1(char *haystack, char *needle){
   char *p = Strstr1(haystack, needle);
   if (p != NULL)
      return p - haystack;
   return -1;
}

char *Strstr2(char *str, char *substring)
{
  char *a = str, *b = substring;
  for (;;) {
    if ( !*b ) return (char *) str;
    if ( !*a ) return NULL;
    if ( *a++ != *b++) { a = ++str; b = substring; }
  }
}

int Strpos2(char *haystack, char *needle){
   char *p = Strstr2(haystack, needle);
   if (p != NULL)
      return p - haystack;
   return -1;
}

char *Strstr3(char *str, char *substring)
{
  char *a, *b = substring;

  if ( !*b ) return (char *) str;
  for ( ; *str ; str++) {
    if (*str != *b) continue;
    a = str;
    for (;;) {
      if ( !*b ) return (char *) str;
      if (*a++ != *b++) break;
    }
    b = substring;
  }
  return NULL;
}

int Strpos3(char *haystack, char *needle){
   char *p = Strstr3(haystack, needle);
   if (p != NULL)
      return p - haystack;
   return -1;
}

char *Strstr4(char *s1, char *s2)
{
    size_t n = strlen(s2);
    while(*s1)
        if(!memcmp(s1++,s2,n))
            return (char *) (s1-1);
    return 0;
}

int Strpos4(char *haystack, char *needle){
   char *p = Strstr4(haystack, needle);
   if (p != NULL)
      return p - haystack;
   return -1;
}

void tests_strpos(char* src, char* sub){
  int pos1 = Strpos1(src, sub);
  printf("Strpos1(\"%s\", \"%s\")=%d\n", src, sub, pos1);

  int pos2 = Strpos2(src, sub);
  printf("Strpos2(\"%s\", \"%s\")=%d\n", src, sub, pos2);

  int pos3 = Strpos3(src, sub);
  printf("Strpos3(\"%s\", \"%s\")=%d\n", src, sub, pos3);

  int pos4 = Strpos4(src, sub);
  printf("Strpos4(\"%s\", \"%s\")=%d", src, sub, pos4);
}


// Strcut
char* Strcut1(int n, ...){
  char* full_string = (char*)calloc(n, sizeof(char));
  char* string;
  int add_pos = 0;
  va_list args;
  va_start(args, n);
  for(int i = 0; i<n; i++){
    string = va_arg(args, char *);
    strcpy(full_string+add_pos, string);
    add_pos += strlen(string);
  }
  va_end(args);

  return full_string;
}

void test_strcut(){
  // char** strings = (char**)calloc(n, sizeof(char*));
  // va_list arg_strings;
  // int len_syms = 0;
  // va_start(arg_strings, n);
  // for (int i=0; i<n; i++){
  //   strings[i] = va_arg(arg_strings, char*);
  //   len_syms += strlen(strings[i]);
  // }
  // va_end(arg_strings);
  //
  // int n_schet = schet(n);
  // char arg_s[len_syms+n*2+n_schet+2];
  // int add_pos = 0;
  //
  // char n_s[n_schet];
  // sprintf(n_s, "%d", n);
  // char *start_s = strcat(n_s, ", ");
  // strcpy(arg_s+add_pos, start_s);
  // add_pos += strlen(start_s);
  //
  // for (int i=0; i<n; i++){
  //   strcpy(arg_s+add_pos, strings[i]);
  //   add_pos+=strlen(strings[i]);
  //   if (i!=n-1){
  //     strcpy(arg_s+add_pos, ", ");
  //     add_pos+=2;
  //   }
  // }

  char *ss = Strcut1(5, "A", "B", "C", "D", "E");
  printf("%s\n", ss);
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

  printf("1) Src пуста и Sub пуста\n");
  tests_strpos("", "");
  printf("\n\n");
  printf("2) Src пуста и Sub не пуста, вхождений в src нет\n");
  tests_strpos("", "aaaa");
  printf("\n\n");
  printf("3) Src не пуста и Sub пуста\n");
  tests_strpos("aaaa", "");
  printf("\n\n");
  printf("4) Src не пуста и Sub не пуста, вхождений в src нет\n");
  tests_strpos("aaaa", "bbb");
  printf("\n\n");
  printf("5) Src не пуста и Sub не пуста, вхождение есть\n");
  tests_strpos("aaaa asfas as bbb as ass", "bbb");
  printf("\n\n");
  printf("6) Src не пуста и Sub не пуста, вхождение есть\n");
  tests_strpos("bbb asfas as bbb as ass", "bbb");
  printf("\n\n");
  printf("7) Src не пуста и Sub не пуста, вхождение есть\n");
  tests_strpos("asfas as as ass bbb", "bbb");
  printf("\n\n");

  printf("Test\n");
  test_strcut();

  return 0;
}
