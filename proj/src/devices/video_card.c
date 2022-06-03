#include "./devices/video_card.h"

static vbe_mode_info_t vmi;
static void *base_addr;
static uint16_t screen_center_x;
static uint16_t screen_center_y;
static uint16_t tetromino_spawn_offset = 20;

void *(vg_init)(uint16_t mode) {

  int r, a, b;

  if ((b = vbe_get_mode_info(mode, &vmi)) != 0) {
    return NULL;
  }

  if ((r = map_vm()) != 0) {
    return NULL; 
  }  

  if ((a = change_mode(mode)) != 0) {
    return NULL;
  }

  return base_addr;
}

int(change_mode)(uint16_t mode) {
  reg86_t r;
  memset(&r, 0, sizeof(r)); /* zbase_addrero the structure */

  r.intno = 0x10;
  r.ax = AH_DEFAULT << 8 | MODE_SET; // VBE call, function 02 -- set VBE mode
  r.bx = 1 << 14 | mode;

  if (sys_int86(&r) != CALL_SUCCESS) {
    printf("change_mode: sys_int86() failed \n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int(map_vm)() {
  int r;
  struct minix_mem_range mr; /* physical memory range */
  phys_bytes vram_base = vmi.PhysBasePtr;                                                                  /* VRAM's physical addresss */
  unsigned int vram_size = (vmi.XResolution * vmi.YResolution) * (vmi.BytesPerScanLine / vmi.XResolution); /* VRAM's size, but you can use frame the frame-buffer size, instead */

  /* Allow memory mapping */
  mr.mr_base = vram_base;
  mr.mr_limit = mr.mr_base + vram_size;
  if (OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);

  /* Map memory */
  base_addr = vm_map_phys(SELF, (void *) mr.mr_base, vram_size);
  if (base_addr == MAP_FAILED)
    panic("couldn't map video memory");

  return 0;
}

int(vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
  if (y + height > vmi.YResolution)
    height = vmi.YResolution - y;
  if (x + width > vmi.XResolution)
    width = vmi.XResolution - x;

  for (int i = 0; i < height; i++) {
    vg_draw_hline(x, y, width, color);
    y++;
  }

  return EXIT_SUCCESS;
}

int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  for (int i = 0; i < len; i++) {
    draw_pixel(x, y, color);
    x++;
  }

  return EXIT_SUCCESS;
}

void(draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
  uint64_t offset = ((y * vmi.XResolution) + x) * (vmi.BytesPerScanLine / vmi.XResolution);
  void *addr = (void *) ((char *) base_addr + offset);

  memcpy(addr, &color, vmi.BytesPerScanLine / vmi.XResolution);
}

void(draw_xpm)(xpm_image_t img, uint16_t x, uint16_t y) {
  if (y + img.height > vmi.YResolution)
    y = vmi.YResolution - img.height;
  if (x + img.width > vmi.XResolution)
    x = vmi.XResolution - img.width;

  uint64_t cnt = 0;
  uint16_t ox = x;

  for (int i = 0; i < img.height; i++) {
    for (int j = 0; j < img.width; j++) {
      uint64_t offset = ((y * vmi.XResolution) + x) * (vmi.BytesPerScanLine / vmi.XResolution);
      void *addr = (void *) ((char *) base_addr + offset);

      uint8_t bpp = img.size / (img.height * img.width);

      memcpy(addr, img.bytes + (cnt * bpp), vmi.BytesPerScanLine / vmi.XResolution);
      x++;
      cnt++;
    }
    y++;
    x = ox;
  }
}


int vg_draw_vline(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  for (int i = 0; i < len; i++) {
    draw_pixel(x, y, color);
    y++;
  }

  return EXIT_SUCCESS;
}

int draw_board(board_t *board) {
  screen_center_x = vmi.XResolution/2;
  screen_center_y = vmi.YResolution/2;

  uint16_t tetromino_side = (vmi.YResolution  - ((board->margin + board->stroke) * 2))/board->height;
  uint16_t top_left_corner_x = screen_center_x - tetromino_side * (board->width/2);
  uint16_t top_left_corner_y = screen_center_y - tetromino_side * (board->height/2);

  vg_draw_rectangle(top_left_corner_x - board->stroke, top_left_corner_y - board->stroke, (tetromino_side * board->width) + (board->stroke * 2), (tetromino_side *  board->height) + (board->stroke * 2), 0x1023DF);
  vg_draw_rectangle(top_left_corner_x, top_left_corner_y, tetromino_side * board->width, tetromino_side * board->height, board->color);

  return EXIT_SUCCESS;
}

int draw_tetromino(tetromino_t *tetromino, bool spawn) {

  xpm_image_t img;
  xpm_loader(tetromino->type, &img);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetromino->matrix[i][j]) {
        if (spawn) {
          draw_xpm(img, (img.width * j) + (screen_center_x - 2*img.width), (img.height * i) + (tetromino_spawn_offset));
        } else {
          draw_xpm(img, (img.width * j) + (tetromino->x * img.width), (img.height * i) + (tetromino->y * img.height));
        }
      }
    }
  }
  printf("shueryvewehdwokerojihfrjedrjihrfjeko");

  return EXIT_SUCCESS;
}

uint8_t *(xpm_loader)(const tetromino_type type, xpm_image_t *img) {
  switch(type) {
    case CLEAR:
      return NULL;
      break;
    case J:
      return xpm_load(tetromino_blue_xpm, XPM_8_8_8, img);
      break;
    case I:
      return xpm_load(tetromino_cyan_xpm, XPM_8_8_8, img);
      break;
    case L:
      return xpm_load(tetromino_orange_xpm, XPM_8_8_8, img);
      break;
    case S:
      return xpm_load(tetromino_green_xpm, XPM_8_8_8, img);
      break;
    case O:
      return xpm_load(tetromino_yellow_xpm, XPM_8_8_8, img);
      break;
    case T:
      return xpm_load(tetromino_purple_xpm, XPM_8_8_8, img);
      break;
    case Z:
      return xpm_load(tetromino_red_xpm, XPM_8_8_8, img);
      break;
  }
}

void draw_board_state() {
  tetromino_type mx[16][10] = {{1, 1, 2, 3, 4, 5, 6, 7, 7, 2},
                               {0, 1, 1, 0},
                               {0, 1, 1, 0},
                               {0, 0, 0, 0}};

  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 10; j++) {
      if (mx[i][j] != 0) {
        xpm_image_t img;
        xpm_loader(mx[i][j], &img);
        draw_xpm(img, screen_center_x - ((j-4) * img.width), ((vmi.YResolution-50) - (i * img.height)));
      }
    }
  }
}

void draw_menu() {
  xpm_image_t img;
  xpm_load(menu_800x600_xpm, XPM_8_8_8, &img);
  draw_xpm(img, 0, 0);
}

void draw_character(const char character, const bool is_number, uint16_t x, uint16_t y) {
  xpm_image_t img;
  xpm_load(font_xpm, XPM_8_8_8, &img);

  if (is_number) {
    int num = character - '0';
    uint8_t *pnt = img.bytes + ((18*img.width + 11*num) * img.size / (img.height * img.width));

    uint16_t ox = x;

    for (int i = 0; i < 18; i++) {
      for (int j = 0; j < 11; j++) {
        uint64_t offset = ((y * vmi.XResolution) + x) * (vmi.BytesPerScanLine / vmi.XResolution);
        void *addr = (void *) ((char *) base_addr + offset);

        uint8_t bpp = img.size / (img.height * img.width);

        memcpy(addr, pnt + ((i * img.width) + j) * bpp, vmi.BytesPerScanLine / vmi.XResolution);
        x++;
      }
      y++;
      x = ox;
    }
  } else {
    int num = (int) character - 65;
    printf("%d", num);
    uint8_t *pnt = img.bytes + (11*num) * img.size / (img.height * img.width);

    uint16_t ox = x;

    for (int i = 0; i < 18; i++) {
      for (int j = 0; j < 11; j++) {
        uint64_t offset = ((y * vmi.XResolution) + x) * (vmi.BytesPerScanLine / vmi.XResolution);
        void *addr = (void *) ((char *) base_addr + offset);

        uint8_t bpp = img.size / (img.height * img.width);

        memcpy(addr, pnt + ((i * img.width) + j) * bpp, vmi.BytesPerScanLine / vmi.XResolution);
        x++;
      }
      y++;
      x = ox;
    }
  }
}
