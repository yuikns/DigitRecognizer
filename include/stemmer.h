#ifndef __STEMMER_H__
#define __STEMMER_H__

/* Make this header file easier to include in C++ code */
#ifdef __cplusplus
extern "C" {
#endif


struct stemmer;
struct stemmer * create_stemmer(void);
void free_stemmer(struct stemmer * z);
int stem(struct stemmer * z, char * b, int k);


#ifdef __cplusplus
}
#endif



#endif // __STEMMER_H__


