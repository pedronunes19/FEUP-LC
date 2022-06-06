#include "./devices/video_card.h"

static vbe_mode_info_t vmi;
static void *base_addr;
static uint16_t screen_center_x;
static uint16_t screen_center_y;
static uint16_t tetromino_offset = 20;

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
  screen_center_x = vmi.XResolution/2;
  screen_center_y = vmi.YResolution/2;

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

int draw_board(xpm_image_t board) {
  uint8_t tetromino_side = (vmi.YResolution - 30)/16;
  uint8_t x = screen_center_x - (tetromino_side * 5) - 10;

  draw_xpm(board, x, 10);

  return EXIT_SUCCESS;
}

int draw_tetromino(tetromino_t *tetromino) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetromino->matrix[i][j]) {
          draw_xpm(tetromino->image, (tetromino->image.width * j) + (tetromino->x * tetromino->image.width) + (screen_center_x - 5 * tetromino->image.width), (tetromino->image.height * i) + (tetromino->y * tetromino->image.height) + tetromino_offset);
      }
    }
  }

  return EXIT_SUCCESS;
}

void draw_board_space(xpm_image_t img, uint8_t x, uint8_t y) {
  draw_xpm(img, (img.width * x) + (screen_center_x - 5 * img.width), ((vmi.YResolution-55) - (y * img.height)));
}

void draw_character(const char character, const bool is_number, uint16_t x, uint16_t y) {
  xpm_image_t img;

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

int clear_tetromino(tetromino_t *tetromino, xpm_image_t clear) {
  uint8_t y;
  if (tetromino->y == 0) {
    y = 0;
  } else {
    y = tetromino->y - 1;
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      draw_xpm(clear, (clear.width * j) + (tetromino->x * clear.width) + (screen_center_x - 5 * clear.width), (clear.height * i) + (y * clear.height) + 20);
    }
  }

  return EXIT_SUCCESS;
}
