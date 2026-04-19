#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include "sensor_sim.h"

LOG_MODULE_REGISTER(app, LOG_LEVEL_INF);

K_MSGQ_DEFINE(sensor_msgq, sizeof(struct sensor_data), 10, 4);

enum system_state {
    NORMAL,
    WARNING,
    FAULT
};

#define PRODUCER_STACK_SIZE 1024
#define CONSUMER_STACK_SIZE 1024
#define THREAD_PRIORITY 5

enum system_state check_system_state(struct sensor_data data)
{
    if (data.temperature > 38 || data.vibration > 28) {
        return FAULT;
    }

    if (data.temperature > 35 || data.vibration > 25) {
        return WARNING;
    }

    return NORMAL;
}

void producer_thread(void)
{
    struct sensor_data data;

    while (1) {
        generate_sensor_data(&data);

        if (k_msgq_put(&sensor_msgq, &data, K_NO_WAIT) == 0) {
            LOG_INF("Produced: temp=%d vib=%d", data.temperature, data.vibration);
        } else {
            LOG_WRN("Queue full, data dropped");
        }

        k_sleep(K_SECONDS(1));
    }
}

void consumer_thread(void)
{
    struct sensor_data data;
	static enum system_state previous_state = NORMAL;
    while (1) {
        if (k_msgq_get(&sensor_msgq, &data, K_FOREVER) == 0) {
            LOG_INF("Consumed: temp=%d vib=%d", data.temperature, data.vibration);
		enum system_state state = check_system_state(data);
if (data.temperature > 38) {
    LOG_ERR("Temperature fault: %d", data.temperature);
}
else if (data.temperature > 35) {
    LOG_WRN("Temperature warning: %d", data.temperature);
}

if (data.vibration > 28) {
    LOG_ERR("Vibration fault: %d", data.vibration);
}
else if (data.vibration > 25) {
    LOG_WRN("Vibration warning: %d", data.vibration);
}

		if (state != previous_state) {

    if (state == WARNING) {
        LOG_WRN("State changed: WARNING");
    }
    else if (state == FAULT) {
        LOG_ERR("State changed: FAULT");
    }
    else {
        LOG_INF("State changed: NORMAL");
    }

    previous_state = state;
}		
        }
    }
}

K_THREAD_DEFINE(producer_tid, PRODUCER_STACK_SIZE, producer_thread,
                NULL, NULL, NULL, THREAD_PRIORITY, 0, 0);

K_THREAD_DEFINE(consumer_tid, CONSUMER_STACK_SIZE, consumer_thread,
                NULL, NULL, NULL, THREAD_PRIORITY, 0, 0);