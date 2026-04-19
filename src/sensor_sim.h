#ifndef SENSOR_SIM_H
#define SENSOR_SIM_H

struct sensor_data {
    int temperature;
    int vibration;
};

void generate_sensor_data(struct sensor_data *data);

#endif