/**************************************************************



**************************************************************/
#include "uthash.h" // Página del autor: https://github.com/troydhanson/uthash/
#include "qdbmp.h" // Página del autor: http://qdbmp.sourceforge.net/
#include "definitions.h"
#include "huffman.h"
#include "binaryread.h"
#include <stdio.h>

int main( int argc, char* argv[] )
{
  single_color *colors = NULL;
	UCHAR	r, g, b;
	UINT	width, height;
	UINT	x, y;
	BMP*	bmp_in;
	//BMP*	bmp_out;
  int i;

  /* ----------- FUNCIONES --------------*/
  void add_color(single_color *c) {
      HASH_ADD_INT( colors, id, c );
  }

  single_color *find_color(int color_id) {
    single_color *c;

    HASH_FIND_INT( colors, &color_id, c );
    return c;
  }

  void print_colors() {
    struct single_color *c;

    for(c=colors; c != NULL; c=c->hh.next) {
        printf("Color id: %d ||| Frequency: %u\n", c->id, c->frequency);
    }
  }
  /* -----------/FUNCIONES --------------*/

  /* Check arguments */
	if ( argc != 4 )
	{
		fprintf( stderr, "Uso: %s <modo> <input file> <output file>\n", argv[ 0 ] );
		return -1;
	}

  /* Open input BMP */
	bmp_in = BMP_ReadFile( argv[ 2 ] );
	BMP_CHECK_ERROR( stderr, -2 );		/* Check if any errors have occurred */

	/* Get image's dimensions */
	width = BMP_GetWidth( bmp_in );
	height = BMP_GetHeight( bmp_in );
	printf("Width: %lu , Height: %lu \n", width, height);

  // Iterate the pixels
  for ( x = 0 ; x < width ; ++x )
	{
		for ( y = 0 ; y < height ; ++y )
		{
      /* Get pixel's RGB values */
			BMP_GetPixelRGB( bmp_in, x, y, &r, &g, &b );
			/* Method 1: Manually check for an error */
			if ( BMP_GetError() != BMP_OK ){printf( "An error has occurred: %s (code %d)\n", BMP_GetErrorDescription(), BMP_GetError() );}
      //printf("Red: %u, Green: %u, Blue: %u \n", r, g, b); // DEBUG
      single_color *t_c= malloc(sizeof(single_color));
      t_c->r = r;
      t_c->g = g;
      t_c->b = b;
      t_c->id = r*1000000 + g*1000 + b;

      single_color *test;
      test = find_color(t_c->id);
      if (test == NULL)
      {
        add_color(t_c);
        t_c->frequency = 1;
      }
      else if (test->id != t_c->id) {
        printf("Mejora tu función de HASH!!!");
        return 1;
      }
      else
      {
        test->frequency += 1;
        free(t_c);
      }
    }
  }
	/* The input image is no longer required and may be freed */
	BMP_Free( bmp_in );

  // -------------------------- GOT THE INFORMATION ---------------------------
  /* ----------- FUNCIONES --------------*/
  int GetColorsLength(){
    int counter;
    counter=0;
    struct single_color *c;
    for(c=colors; c != NULL; c=c->hh.next) {
        counter+=1;
    }
    return counter;
  }

  void populateColorArrays(pixel cPixels[], int cFrequencies[]){
    int counter;
    counter=0;
    struct single_color *c;
    for(c=colors; c != NULL; c=c->hh.next) {
        pixel p;
        p.r = c->r;
        p.g = c->g;
        p.b = c->b;

        cPixels[counter] = p;
        cFrequencies[counter] = c->frequency;
        counter+=1;
    }
  }
  /* -----------/FUNCIONES --------------*/

  int ColorsLength;
  ColorsLength = GetColorsLength();

  if (ColorsLength<1){
    printf("ColorsLength size: %d\n", ColorsLength);
    return 1;
  }

  pixel colorPixels[ColorsLength];
  int colorFrequencies[ColorsLength];
  //huffmanColor hfColors[ColorsLength];

  populateColorArrays(colorPixels, colorFrequencies);

  // -------------------------- GOT THE ARRAYS ---------------------------
  // -------------------------- ??????????????? ---------------------------
  int size = sizeof(colorPixels)/sizeof(colorPixels[0]);

  if (sizeof(colorPixels) > 0 && sizeof(colorFrequencies) > 0 ){
    //HuffmanCodes(hfColors, colorPixels, colorFrequencies, size);
    HuffmanCodes(colorPixels, colorFrequencies, size);
  }
  else{
      printf("Size of colorPixels: %lu\n", sizeof(colorPixels));
      printf("Size of colorFrequencies: %lu\n", sizeof(colorFrequencies));
      return 1;
  }

  // ---------------------- Print file in binary -------------------------
  void adx_store_data(const char *filepath, const char *data)
  {
      FILE *fp = fopen(filepath, "ab");
      if (fp != NULL)
      {
          fputs(data, fp);
          fclose(fp);
      }
  }
  adx_store_data("output_binary.txt", binary_file(argc, argv));

  // ----------FINALIZAR PROGRAMA......
  return 0;
}
