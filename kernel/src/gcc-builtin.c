#include <string.h>
/*
int strcmp( const char* s1, const char* s2)
{
	while( 1 ){
		// they are different or they are the same but at 
		// the end of the string.
		if( *s1 != *s2 ) return (*s1 - *s2);
		else if( *s1 == 0 ) return 0;
		s1++; s2++;
	}
	return 0;
}

int strncmp( const char* s1, const char* s2, size_t n)
{
	for(; n > 0; --n, s1++, s2++){
		if( *s1 != *s2 ) return (*s1 - *s2);
		else if( *s1 == 0 ) return 0;
	}
	return 0;
}

char* strncpy( char* d, const char* s, size_t n)
{
	char* tmp = d;
	while( n ){
		*d = *s;
		if( *s ) s++;
		d++;
		n--;
	}
	return tmp;
}

char* strcpy( char* d, const char* s)
{
	char* tmp = d;
	while( *s ){
		*(d++) = *(s++);
	}
	*d = 0;
	return tmp;
}

char* strchr( const char* str, int character )
{
	for(; *str != 0; str++){
		if( *str == (char)character ){
			return ((char*)(str));
		}
	}
	if( character == 0 ) return (char*)(str);
	return (char*)0;
}

size_t strlen( const char* s )
{
	size_t len = 0;
	while(*s){
		len++;
		s++;
	}
	return len;
}

int memcmp(const void *s1, const void *s2, size_t n)
{
	for(size_t i = 0; i < n; ++i){
		if( ((const char*)s1)[i] > ((const char*)s2)[i] ) return 1;
		else if( ((const char*)s1)[i] < ((const char*)s2)[i] ) return -1;
	}
	return 0;
}*/


