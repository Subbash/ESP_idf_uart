#include <stdio.h>
#include <string.h>
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

const uart_port_t uart_num = UART_NUM_2;
const int uart_buffer_size = (1024 * 2);
QueueHandle_t uart_queue;

void configure_uart_engine()
{
    //const uart_port_t uart_num = UART_NUM_0;
    uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };

    // Set UART pins(TX: IO4, RX: IO5, RTS: IO18, CTS: IO19)
    //ESP_ERROR_CHECK(uart_set_pin(uart_num, 1, 3, 18, 19));
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_0, uart_buffer_size,uart_buffer_size, 10, &uart_queue, 0));
    ESP_ERROR_CHECK(uart_param_config(UART_NUM_0, &uart_config));
    
 
}
void task_uart(void *pvParameters){

    configure_uart_engine();
    while(1)
    {
        char* test_str = "This is a test string.\n";
        uart_write_bytes(UART_NUM_0, (const char*)test_str, strlen(test_str));
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    
    
}

void app_main(void) {

    xTaskCreate(&task_uart, "Task Uart", 2048, NULL, 0, NULL);
}