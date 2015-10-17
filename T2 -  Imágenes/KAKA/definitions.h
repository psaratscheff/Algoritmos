/* ----------- STRUCTS --------------*/

typedef struct single_color {
  unsigned char r;
  unsigned char g;
  unsigned char b;
  int frequency;
  int id; // Definir como red*1,000,000 + green*1,000 + blue /* The key */
  UT_hash_handle hh; /* makes this structure hashable */
}single_color;
