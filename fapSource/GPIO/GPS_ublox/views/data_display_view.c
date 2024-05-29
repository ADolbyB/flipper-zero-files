#include "data_display_view.h"

#include <gui/elements.h>

#define TAG "data_display_view"

typedef struct DataDisplayView {
    View* view;
    DataDisplayViewCallback callback;
    void* context;
} DataDisplayView;

typedef struct {
    DataDisplayState state;
    Ublox_NAV_PVT_Message nav_pvt;
    Ublox_NAV_ODO_Message nav_odo;
    UbloxLogState log_state;
} DataDisplayViewModel;

static void draw_buttons(Canvas* canvas, void* model) {
    DataDisplayViewModel* m = model;

    if(m->log_state == UbloxLogStateLogging) {
        elements_button_right(canvas, "Stop Log");
    } else {
	elements_button_left(canvas, "Config");
        elements_button_right(canvas, "Start Log");
    }
}

static void data_display_draw_callback(Canvas* canvas, void* model) {
    DataDisplayViewModel* m = model;
    if(m->state == DataDisplayGPSNotFound) {
        canvas_set_font(canvas, FontPrimary);
        canvas_draw_str(canvas, 27, 20, "GPS not found!");

        canvas_set_font(canvas, FontSecondary);
        canvas_draw_str(canvas, 5, 34, "Connect u-blox 8 series GPS.");

    } else if(m->state == DataDisplayHandheldMode) {
        // TODO: check invalidLlh flag in flags3?
        Ublox_NAV_PVT_Message message = m->nav_pvt;
        Ublox_NAV_ODO_Message nav_odo = m->nav_odo;
        draw_buttons(canvas, model);
        FuriString* s = furi_string_alloc();

        /*** Draw fix ***/
        canvas_set_font(canvas, FontPrimary);
        canvas_draw_str(canvas, 0, 9, "F/S:");

        canvas_set_font(canvas, FontSecondary);

        if(message.fixType == 0) {
            furi_string_printf(s, "N");
        } else if(message.fixType == 1) {
            furi_string_printf(s, "R");
        } else if(message.fixType == 2) {
            furi_string_printf(s, "2D");
        } else if(message.fixType == 3) {
            furi_string_printf(s, "3D");
        } else if(message.fixType == 4) {
            furi_string_printf(s, "G+D");
        } else if(message.fixType == 5) {
            furi_string_printf(s, "TO");
        }

        /*** Draw number of satellites ***/
        furi_string_cat_printf(s, "/%u", message.numSV);
        canvas_draw_str(canvas, 23, 9, furi_string_get_cstr(s));

        /*** Draw odometer ***/
        canvas_set_font(canvas, FontPrimary);
        canvas_draw_str(canvas, 58, 9, "Od:");

        canvas_set_font(canvas, FontSecondary);
        // distance values are in meters
        if(locale_get_measurement_unit() == LocaleMeasurementUnitsMetric) {
            furi_string_printf(s, "%.1fkm", (double)(nav_odo.distance / 1e3)); // km
        } else {
            furi_string_printf(s, "%.1fmi", (double)(nav_odo.distance / 1e3 * 0.6214)); // km to mi
        }
        canvas_draw_str(canvas, 77, 9, furi_string_get_cstr(s));

	// Former logging indicator
	// We now use just the button as the indicator
        /*canvas_set_font(canvas, FontPrimary);
        canvas_draw_str(canvas, 112, 9, "L:");

        canvas_set_font(canvas, FontSecondary);
        if(m->log_state == UbloxLogStateLogging) {
            canvas_draw_str(canvas, 122, 9, "Y"); // yes
        } else {
            canvas_draw_str(canvas, 122, 9, "N"); // no
	    }*/

        /*** Draw latitude ***/
        canvas_set_font(canvas, FontPrimary);
        canvas_draw_str(canvas, 0, 22, "Lat:");

        canvas_set_font(canvas, FontSecondary);
        furi_string_printf(s, "%.4f", (double)(message.lat / 1e7));
        canvas_draw_str(canvas, 22, 22, furi_string_get_cstr(s));

        /*** Draw longitude ***/
        canvas_set_font(canvas, FontPrimary);
        canvas_draw_str(canvas, 0, 35, "Lon:");

        canvas_set_font(canvas, FontSecondary);
        furi_string_printf(s, "%.4f", (double)(message.lon / 1e7));
        canvas_draw_str(canvas, 23, 35, furi_string_get_cstr(s));

        /*** Draw altitude ***/
        canvas_set_font(canvas, FontPrimary);
        canvas_draw_str(canvas, 75, 22, "Alt:");

        canvas_set_font(canvas, FontSecondary);
        // hMSL is height above mean sea level in mm
        if(locale_get_measurement_unit() == LocaleMeasurementUnitsMetric) {
            furi_string_printf(s, "%.0fm", (double)(message.hMSL / 1e3));
        } else {
            furi_string_printf(s, "%.0fft", (double)(message.hMSL / 1e3 * 3.281));
        }
        canvas_draw_str(canvas, 96, 22, furi_string_get_cstr(s));

        /*** Draw heading ***/
        canvas_set_font(canvas, FontPrimary);
        canvas_draw_str(canvas, 75, 35, "Head:");

        canvas_set_font(canvas, FontSecondary);
        furi_string_printf(s, "%.0f", (double)(message.headMot / 1e5));
        canvas_draw_str(canvas, 105, 35, furi_string_get_cstr(s));

        /*** Draw time and battery ***/
	// Note that these are not retrieved from an external state
	// variable, because they don't have to be.
	canvas_set_font(canvas, FontPrimary);
	canvas_draw_str(canvas, 0, 48, "Time:");
	
	DateTime datetime;
	furi_hal_rtc_get_datetime(&datetime);
	locale_format_time(s, &datetime, locale_get_time_format(), false);

	canvas_set_font(canvas, FontSecondary);
	canvas_draw_str(canvas, 30, 48, furi_string_get_cstr(s));

	// draw Flipper battery charge
	canvas_set_font(canvas, FontPrimary);
	canvas_draw_str(canvas, 75, 48, "Batt:");

	canvas_set_font(canvas, FontSecondary);
	furi_string_printf(s, "%u%%", furi_hal_power_get_pct());
	canvas_draw_str(canvas, 101, 48, furi_string_get_cstr(s));
	
	furi_string_free(s);
	
    } else if(m->state == DataDisplayCarMode) {
        Ublox_NAV_PVT_Message message = m->nav_pvt;
        Ublox_NAV_ODO_Message nav_odo = m->nav_odo;
        FuriString* s = furi_string_alloc();
        draw_buttons(canvas, model);
        // TODO: imperial/metric
        canvas_set_font(canvas, FontPrimary);
        // gSpeed is in mm/s
        if(locale_get_measurement_unit() == LocaleMeasurementUnitsMetric) {
            canvas_draw_str(canvas, 0, 12, "Spd (km/s):");
            furi_string_printf(s, "%.1f", (double)(message.gSpeed / 1e3));
        } else {
            canvas_draw_str(canvas, 0, 12, "Spd (mph):");
            furi_string_printf(s, "%.1f", (double)(message.gSpeed / 1e3 * 2.23694));
        }

        canvas_set_font(canvas, FontBigNumbers);
        canvas_draw_str(canvas, 60, 15, furi_string_get_cstr(s));

        canvas_set_font(canvas, FontPrimary);
        canvas_draw_str(canvas, 0, 29, "Heading:");

        canvas_set_font(canvas, FontBigNumbers);
        furi_string_printf(s, "%.0f", (double)(message.headMot / 1e5));
        canvas_draw_str(canvas, 60, 32, furi_string_get_cstr(s));

        canvas_set_font(canvas, FontPrimary);
        // distance is in meters
        if(locale_get_measurement_unit() == LocaleMeasurementUnitsMetric) {
            canvas_draw_str(canvas, 0, 45, "Odo (km):");
            furi_string_printf(s, "%.2f", (double)(nav_odo.distance / 1e3));
        } else {
            canvas_draw_str(canvas, 0, 45, "Odo (mi):");
            furi_string_printf(s, "%.2f", (double)(nav_odo.distance / 1e3 * 0.6214));
        }

        canvas_set_font(canvas, FontBigNumbers);
        canvas_draw_str(canvas, 60, 49, furi_string_get_cstr(s));

        furi_string_free(s);
    }
}

static bool data_display_input_callback(InputEvent* event, void* context) {
    DataDisplayView* data_display = context;
    // this method of getting the model breaks the whole app
    //DataDisplayViewModel* model = view_get_model(data_display->view);
    bool consumed = false;

    if(event->type == InputTypeShort) {
        if(event->key == InputKeyLeft) {
            if(data_display->callback) {
                data_display->callback(data_display->context, event->key);
            }
            consumed = true;
        } else if(event->key == InputKeyRight) { // && model->state != DataDisplayGPSNotFound) {
            if(data_display->callback) {
                data_display->callback(data_display->context, event->key);
            }
            consumed = true;
        }
    }
    return consumed;
}

DataDisplayView* data_display_alloc() {
    DataDisplayView* data_display = malloc(sizeof(DataDisplayView));
    data_display->view = view_alloc();

    view_allocate_model(data_display->view, ViewModelTypeLocking, sizeof(DataDisplayViewModel));
    view_set_context(data_display->view, data_display);

    view_set_draw_callback(data_display->view, data_display_draw_callback);
    view_set_input_callback(data_display->view, data_display_input_callback);

    return data_display;
}

void data_display_free(DataDisplayView* data_display) {
    furi_assert(data_display);
    view_free(data_display->view);
    free(data_display);
}

void data_display_reset(DataDisplayView* data_display) {
    furi_assert(data_display);
    Ublox_NAV_PVT_Message p = {0};
    Ublox_NAV_ODO_Message o = {0};
    with_view_model(
        data_display->view,
        DataDisplayViewModel * model,
        {
            model->state = DataDisplayHandheldMode;
            model->nav_pvt = p;
            model->nav_odo = o;
        },
        false);
}

View* data_display_get_view(DataDisplayView* data_display) {
    furi_assert(data_display);
    return data_display->view;
}

void data_display_set_callback(
    DataDisplayView* data_display,
    DataDisplayViewCallback callback,
    void* context) {
    furi_assert(data_display);
    furi_assert(callback);
    data_display->callback = callback;
    data_display->context = context;
}

void data_display_set_nav_messages(
    DataDisplayView* data_display,
    Ublox_NAV_PVT_Message pvt_message,
    Ublox_NAV_ODO_Message odo_message) {
    furi_assert(data_display);
    with_view_model(
        data_display->view,
        DataDisplayViewModel * model,
        {
            model->nav_pvt = pvt_message;
            model->nav_odo = odo_message;
        },
        true);
}

void data_display_set_log_state(DataDisplayView* data_display, UbloxLogState log_state) {
    furi_assert(data_display);
    with_view_model(
        data_display->view, DataDisplayViewModel * model, { model->log_state = log_state; }, true);
}

void data_display_set_state(DataDisplayView* data_display, DataDisplayState state) {
    furi_assert(data_display);
    with_view_model(
        data_display->view,
        DataDisplayViewModel * model,
        { model->state = state; },
        // do refresh
        true);
}

DataDisplayState data_display_get_state(DataDisplayView* data_display) {
    DataDisplayState state;
    furi_assert(data_display);
    with_view_model(
        data_display->view,
        DataDisplayViewModel * model,
        { state = model->state; },
        // no refresh
        false);

    return state;
}
