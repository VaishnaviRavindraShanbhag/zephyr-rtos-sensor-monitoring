#include "sensor_sim.h"

void generate_sensor_data(struct sensor_data *data)
{
    static int temp = 25;
    static int vibration = 10;

    temp += 1;
    vibration += 2;

    if (temp > 40) {
        temp = 25;
    }

    if (vibration > 30) {
        vibration = 10;
    }

    data->temperature = temp;
    data->vibration = vibration;
}
