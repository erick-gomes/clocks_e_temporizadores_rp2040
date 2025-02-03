#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_RED 11
#define LED_YELLOW 12
#define LED_GREEN 13
#define BTN_A 5
#define DEBOUNCE 250000

volatile bool atividade1_ativa = true;

int64_t semaforo_all_callback(alarm_id_t id, void *user_data)
{
    if (gpio_get(LED_RED) == 1)
    {
        gpio_put(LED_RED, 0);
        add_alarm_in_ms(3000, semaforo_all_callback, NULL, false);
    }
    else if (gpio_get(LED_YELLOW) == 1)
    {
        gpio_put(LED_YELLOW, 0);
        add_alarm_in_ms(3000, semaforo_all_callback, NULL, false);
    }
    else if (gpio_get(LED_GREEN) == 1)
    {
        gpio_put(LED_GREEN, 0);
        atividade1_ativa = true;
    }
    return 0;
}
void btn_action(uint gpio, uint32_t events)
{
    volatile static uint32_t last_time = 0;
    if (atividade1_ativa == false && gpio_get(LED_GREEN) == 1)
    {
        return;
    }
    uint32_t timestamp = to_us_since_boot(get_absolute_time());
    if (gpio == BTN_A && timestamp - last_time > DEBOUNCE)
    {
        last_time = timestamp;
        atividade1_ativa = false;
        gpio_put(LED_RED, 1);
        gpio_put(LED_YELLOW, 1);
        gpio_put(LED_GREEN, 1);
        add_alarm_in_ms(3000, semaforo_all_callback, NULL, false);
    }
}
bool semaforo_callback(repeating_timer_t *timer)
{
    static int estado = 0;
    if (atividade1_ativa == false)
    {
        estado = 0;
        return true;
    }
    switch (estado)
    {
    case 0:
        gpio_put(LED_RED, 1);
        gpio_put(LED_YELLOW, 0);
        gpio_put(LED_GREEN, 0);
        break;
    case 1:
        gpio_put(LED_RED, 0);
        gpio_put(LED_YELLOW, 1);
        gpio_put(LED_GREEN, 0);
        break;
    case 2:
        gpio_put(LED_RED, 0);
        gpio_put(LED_YELLOW, 0);
        gpio_put(LED_GREEN, 1);
        break;
    }
    estado = (estado + 1) % 3;
    return true;
}
void inicializar_pinos()
{
    gpio_init(LED_RED);
    gpio_init(LED_YELLOW);
    gpio_init(LED_GREEN);
    gpio_init(BTN_A);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_YELLOW, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(BTN_A, GPIO_IN);
    gpio_pull_up(BTN_A);
}
int main()
{
    stdio_init_all();
    inicializar_pinos();
    repeating_timer_t timer;
    add_repeating_timer_ms(3000, semaforo_callback, NULL, &timer);
    gpio_set_irq_enabled_with_callback(BTN_A, GPIO_IRQ_EDGE_FALL, true, btn_action);
    while (true)
    {
        printf("Executando rotina a cada 1000 ms\n");
        sleep_ms(1000);
    }
}
