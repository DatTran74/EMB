// ----------------------------------- framebf.h -------------------------------------
//font info
#define FONT_WIDTH 8
#define FONT_HEIGHT 8
#define FONT_BPC 8 //bytes per char
#define FONT_BPL 1 //bytes per line
#define FONT_NUMCHAR 224 //number of characters


#define SCR_WIDTH 1024
#define SCR_HEIGHT 768


void framebf_init(int xoffset, int yoffset);
void drawPixelARGB32(int x, int y, unsigned int attr);
void drawRectARGB32(int x1, int y1, int x2, int y2, unsigned int attr, int fill);
void draw_background(const unsigned long pixArr[], int width, int height);
void drawChar(unsigned char ch, int x, int y, unsigned char attr, int scale);
void drawString(int x, int y, char *s, unsigned char attr, int scale);
void drawPixel(int x, int y, unsigned char attr);
void drawCircle(int x0, int y0, int radius, unsigned char attr, int fill);
void drawRect(int x1, int y1, int x2, int y2, unsigned int attr, int fill);
void drawLine(int x1, int y1, int x2, int y2, unsigned char attr);

void game2();

void view();
void slideshow();
void video();
void names();
