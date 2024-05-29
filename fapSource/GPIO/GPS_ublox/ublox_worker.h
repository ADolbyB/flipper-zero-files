#pragma once

#include "ublox_device.h"

typedef struct UbloxWorker UbloxWorker;

typedef enum {
    UbloxWorkerStateNone,
    UbloxWorkerStateReady,
    UbloxWorkerStateRead,
    UbloxWorkerStateSyncTime,
    UbloxWorkerStateResetOdometer,
    UbloxWorkerStateStop,
} UbloxWorkerState;

typedef enum {
    // reserve space for application events
    UbloxWorkerEventReserved = 50,

    UbloxWorkerEventSuccess,
    UbloxWorkerEventFailed,
    UbloxWorkerEventDataReady,
    UbloxWorkerEventOdoReset,
    // specific event to update the screen on log state changed
    UbloxWorkerEventLogStateChanged,
} UbloxWorkerEvent;

typedef void (*UbloxWorkerCallback)(UbloxWorkerEvent event, void* context);

UbloxWorker* ublox_worker_alloc();

UbloxWorkerState ublox_worker_get_state(UbloxWorker* ublox_worker);

void ublox_worker_free(UbloxWorker* ublox_worker);

void ublox_worker_start(
    UbloxWorker* ublox_worker,
    UbloxWorkerState state,
    UbloxWorkerCallback callback,
    void* context);

void ublox_worker_stop(UbloxWorker* ublox_worker);

bool ublox_worker_init_gps();

void ublox_worker_read_nav_messages(void* context);

void ublox_worker_sync_to_gps_time(void* context);
