#include <Arduino.h>


// #define LV_CONF_INCLUDE_SIMPLE
#include <lvgl.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <stdbool.h>
#include <Wire.h>

#include <lv_demo.h>
// #include <lv_demo_music.h>

/* ================= TOUCH FIX ================= */
#define TOUCH_SDA 2
#define TOUCH_SCL 1
#define FT6236_ADDR 0x38
TwoWire TouchWire = TwoWire(1);

/* ================= DISPLAY PINS ================= */
#define LCD_MOSI 13
#define LCD_MISO 14
#define LCD_SCK 12
#define LCD_CS 3
#define LCD_RST -1
#define LCD_DC 42
#define LCD_BL 46

/* ================= DISPLAY DRIVER ================= */
class LGFX : public lgfx::LGFX_Device
{
  lgfx::Panel_ILI9488 _panel_instance;
  lgfx::Bus_SPI _bus_instance;

public:
  LGFX(void)
  {
    auto cfg = _bus_instance.config();
    cfg.spi_host = SPI3_HOST;
    cfg.spi_mode = 0;
    cfg.freq_write = 60000000;
    cfg.freq_read = 16000000;
    cfg.spi_3wire = false;
    cfg.use_lock = true;
    cfg.dma_channel = 1;
    cfg.pin_sclk = LCD_SCK;
    cfg.pin_mosi = LCD_MOSI;
    cfg.pin_miso = LCD_MISO;
    cfg.pin_dc = LCD_DC;
    _bus_instance.config(cfg);
    _panel_instance.setBus(&_bus_instance);

    auto pcfg = _panel_instance.config();
    pcfg.pin_cs = LCD_CS;
    pcfg.pin_rst = LCD_RST;
    pcfg.memory_width = 320;
    pcfg.memory_height = 480;
    pcfg.panel_width = 320;
    pcfg.panel_height = 480;
    pcfg.offset_x = 0;
    pcfg.offset_y = 0;
    pcfg.bus_shared = true;
    _panel_instance.config(pcfg);

    setPanel(&_panel_instance);
  }
};

LGFX tft;

/* ================= LVGL ================= */
static const uint16_t screenWidth  = 480;
static const uint16_t screenHeight = 320;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 60 ];

/* ================= DISPLAY FLUSH ================= */
void my_disp_flush(lv_disp_drv_t *disp,
                   const lv_area_t *area,
                   lv_color_t *color_p)
{
  uint32_t w = area->x2 - area->x1 + 1;
  uint32_t h = area->y2 - area->y1 + 1;

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.writePixels((lgfx::rgb565_t *)&color_p->full, w * h);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

/* ================= TOUCH READ (CORRECT BUS) ================= */
bool readTouch(uint16_t &x, uint16_t &y)
{
  TouchWire.beginTransmission(FT6236_ADDR);
  TouchWire.write(0x02);
  if (TouchWire.endTransmission(false) != 0) return false;

  if (TouchWire.requestFrom(FT6236_ADDR, 1) != 1) return false;
  if (TouchWire.read() == 0) return false;

  uint8_t data[4];
  TouchWire.beginTransmission(FT6236_ADDR);
  TouchWire.write(0x03);
  if (TouchWire.endTransmission(false) != 0) return false;

  if (TouchWire.requestFrom(FT6236_ADDR, 4) != 4) return false;
  for (int i = 0; i < 4; i++) data[i] = TouchWire.read();

  x = ((data[0] & 0x0F) << 8) | data[1];
  y = ((data[2] & 0x0F) << 8) | data[3];

  return true;
}

/* ================= LVGL TOUCH DRIVER ================= */
void my_touchpad_read(lv_indev_drv_t *indev_driver,
                      lv_indev_data_t *data)
{
  (void)indev_driver;

  uint16_t rawX, rawY;

  if (readTouch(rawX, rawY))
  {
    data->state = LV_INDEV_STATE_PR;

    // Match your rotation(3)
    data->point.x = 480 - rawY;
    data->point.y = rawX;

    Serial.printf("x:%d y:%d\n", data->point.x, data->point.y);
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
}

/* ================= SETUP ================= */
void setup()
{
  Serial.begin(115200);

  tft.begin();
  tft.setRotation(3);

  pinMode(LCD_BL, OUTPUT);
  digitalWrite(LCD_BL, HIGH);

  /* 🔥 TOUCH FIX HERE */
  TouchWire.begin(TOUCH_SDA, TOUCH_SCL, 400000);

  lv_init();
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 20);

  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  lv_demo_widgets();

  Serial.println("Setup done");
}

/* ================= LOOP ================= */
void loop()
{
  lv_tick_inc(5);
  lv_timer_handler();
  delay(1);
}