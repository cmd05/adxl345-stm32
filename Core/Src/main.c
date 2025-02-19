#include <stdint.h>
#include "i2c.h"
#include "adxl345.h"
#include "uart.h"

extern uint8_t g_data_rec[6];
const double FOUR_G_SCALE = 128;

int16_t g_x, g_y, g_z;
double g_xg, g_yg, g_zg;

int main() {
    uart2_rxtx_init();

    // enable I2C
    I2C1_init();
    I2C1_scan_bus();

    adxl_init();
    adxl_calibrate(0, 0, -7); // calibration value for 4g: (offset / 2)

    while(1) {
        adxl_read_values(DATA_START_ADDR);

        // note: we cannot directly read the result into a float.
        // read into an int16_t to properly interpret the twos complement number 
        // (float does not follow twos complement but IEEE754)
        g_x = (g_data_rec[1] << 8) | g_data_rec[0];
        g_y = (g_data_rec[3] << 8) | g_data_rec[2];
        g_z = (g_data_rec[5] << 8) | g_data_rec[4];

        g_xg = (g_x / FOUR_G_SCALE);
        g_yg = (g_y / FOUR_G_SCALE);
        g_zg = (g_z / FOUR_G_SCALE);

        printf("x: %d y: %d z: %d \n\r", g_x, g_y, g_z);
        printf("xg: %f yg: %f zg: %f \n\r", g_xg, g_yg, g_zg);

        systickDelayMs(500);
    }
}
