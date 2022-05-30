#include "./devices/video_card.h"

static vbe_mode_info_t vmi;
static void *base_addr;

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
  uint16_t screen_center_x = vmi.XResolution/2;
  uint16_t screen_center_y = vmi.YResolution/2;

  uint16_t tetromino_side = (vmi.YResolution  - ((board->margin + board->stroke) * 2))/board->height;

  uint16_t top_left_corner_x = screen_center_x - tetromino_side * (board->width/2);
  uint16_t top_left_corner_y = screen_center_y - tetromino_side * (board->height/2);

  vg_draw_rectangle(top_left_corner_x - board->stroke, top_left_corner_y - board->stroke, (tetromino_side * board->width) + (board->stroke * 2), (tetromino_side *  board->height) + (board->stroke * 2), 0x1023DF);
  vg_draw_rectangle(top_left_corner_x, top_left_corner_y, tetromino_side * board->width, tetromino_side * board->height, board->color);

  return EXIT_SUCCESS;
}

int draw_tetromino(tetromino_t *tetromino) {
  switchMainColor(tetromino->tcolor);
  xpm_image_t img;
  xpm_load((xpm_row_t *)tetromino_xpm, XPM_8_8_8, &img);
  uint8_t mx[4][4] = {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}};
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (mx[i][j] == 1)
        draw_xpm(img, 0, 0);
    }
  }

  return EXIT_SUCCESS;
}
