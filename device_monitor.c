#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Device {
    char name[30];
    int type; // 0: Temperature, 1: Pressure, 2: Voltage
    union {
        float temperature;
        int pressure;
        float voltage;
    } reading;
};

// Generic engine router executing functions over memory spaces via callback pointers
void process_device(struct Device *dev, void (*callback)(struct Device*)) {
    callback(dev);
}

// Target metrics monitors acting as callbacks
void temperature_monitor(struct Device *d) {
    if (d->type == 0) {
        printf("[TEMP MONITOR] %s: Value = %.2f C %s\n", 
               d->name, d->reading.temperature, 
               (d->reading.temperature > 85.0f) ? "!! CRITICAL OVERHEAT !!" : "[OK]");
    }
}

void pressure_monitor(struct Device *d) {
    if (d->type == 1) {
        printf("[PNEUMATIC MONITOR] %s: Value = %d PSI %s\n", 
               d->name, d->reading.pressure, 
               (d->reading.pressure > 120) ? "!! PRESSURE SPIKE !!" : "[OK]");
    }
}

void voltage_monitor(struct Device *d) {
    if (d->type == 2) {
        printf("[POWER MONITOR] %s: Value = %.2f V %s\n", 
               d->name, d->reading.voltage, 
               (d->reading.voltage < 11.0f || d->reading.voltage > 13.0f) ? "!! VOLTAGE INSTABILITY !!" : "[OK]");
    }
}

int main() {
    srand((unsigned int)time(NULL));
    int total_devices = 10;

    // Dynamically Allocate Memory for 10 Devices
    struct Device *fleet = (struct Device *)malloc(total_devices * sizeof(struct Device));
    if (!fleet) return 1;

    // Simulate random device setup definitions
    struct Device *ptr = fleet;
    for (int i = 0; i < total_devices; i++, ptr++) {
        ptr->type = rand() % 3;
        sprintf(ptr->name, "Node-%03d", 200 + i);
        
        if (ptr->type == 0) {
            ptr->reading.temperature = 20.0f + ((float)rand() / RAND_MAX) * 80.0f; // 20 to 100C
        } else if (ptr->type == 1) {
            ptr->reading.pressure = 80 + rand() % 60; // 80 to 140 PSI
        } else {
            ptr->reading.voltage = 10.0f + ((float)rand() / RAND_MAX) * 4.0f; // 10 to 14V
        }
    }

    printf("=== Activating Callback Processing Loop (10 Transmissions) ===\n\n");

    // Loop through arrays utilizing pointer traversal and dynamic pointer mapping callbacks
    for (struct Device *curr = fleet; curr < fleet + total_devices; curr++) {
        if (curr->type == 0) {
            process_device(curr, temperature_monitor);
        } else if (curr->type == 1) {
            process_device(curr, pressure_monitor);
        } else if (curr->type == 2) {
            process_device(curr, voltage_monitor);
        }
    }

    free(fleet);
    return 0;
}
