#include <stdio.h>
#include <stdlib.h>

const char *byte_to_binary(int x)
{
    static char b[9];
    b[0] = '\0';

    int z;
    char *p = b;
    for (z = 128; z > 0; z >>= 1)
    {
        *p++ = (x & z) ? '1' : '0';
        //printf("%d\n", ((x & z) ? '1' : '0')-48);
        //printf("bit: %s\n", *p);
    }

    return b;
}

char *binary_file( int ac, char* av[] )
{
  /* Check arguments */
	if ( ac != 2 )
	{
		fprintf( stderr, "Usage: %s <input file> <output file>\n", av[ 0 ] );
		return ;
	}

  FILE *ptr;
  ptr = fopen( av[1],"rb" );  // r for read, b for binary

  signed int length;
  //Obtener largo del archivo
  fseek(ptr, 0L, SEEK_END);
  length = ftell(ptr);
  //Volver al inicio del archivo
  fseek(ptr, 0L, SEEK_SET);

  //printf("length: %i\n", length);
  unsigned char buffer[length];

  fread(buffer,sizeof(buffer),1,ptr);

  int i;
  unsigned char *output = malloc(length+2); // One for trailing zero, one to spare.

  for(i = 0; i<length; i++)
    output[i] = *byte_to_binary(buffer[i]); //Guardo los bits del byte en el output
  return output;
}
