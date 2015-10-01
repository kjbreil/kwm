#ifndef FFMOUSE_H
#define FFMOUSE_H

#include <ApplicationServices/ApplicationServices.h>
#include <CoreFoundation/CoreFoundation.h>
#include <Carbon/Carbon.h>

#include <iostream>
#include <vector>
#include <string>

#include <string.h>
#include <stdlib.h>

struct window_layout;

struct window_info
{
    std::string owner;
    std::string name;
    int layer;
    int pid;
    int x,y;
    int width, height;
    window_layout *layout;
    int layout_index;
};

struct window_layout
{
    std::string name;
    int x, y;
    int gap_x, gap_y;
    int gap_vertical, gap_horizontal;
    int width, height;
};

struct window_group_layout
{
    std::string name;
    std::vector<window_layout> layouts;
};

struct screen_info
{
    int id;
    int x, y;
    int width, height;
};

struct screen_layout
{
    int active_layout_index;
    int next_layout_index;
    int number_of_layouts;
    std::vector<window_group_layout> layouts;    
};

bool check_privileges();
void request_privileges();

void get_active_displays();
screen_info *get_display_of_window(window_info *window);
std::vector<window_info*> get_all_windows_on_display(int screen_index);

void apply_layout_for_screen(int screen_index);
void cycle_focused_window_for_screen_clockwise(int screen_index);
void cycle_focused_window_for_screen_counter_clockwise(int screen_index);
void cycle_focused_window_for_screen(int screen_index, int shift);

bool get_window_ref(window_info *window, AXUIElementRef *window_ref);
bool windows_are_equal(window_info *window, window_info *match);

void init_window_layouts();
void set_window_layout_values(window_layout *layout, int x, int y, int width, int height);
window_layout get_window_layout_for_screen(int screen_index, const std::string &name);
bool window_has_layout(window_info *window, window_layout *layout);

void set_window_dimensions(AXUIElementRef app_window, window_info *window, int x, int y, int width, int height);
void set_window_dimensions(int pid, int x, int y, int width, int height);

void send_window_to_prev_screen();
void send_window_to_next_screen();

bool toggle_tap_hotkey(bool cmd_key, bool ctrl_key, bool alt_key, CGKeyCode keycode);
bool system_hotkey_passthrough(bool cmd_key, bool ctrl_key, bool alt_key, CGKeyCode keycode);
bool custom_hotkey_commands(bool cmd_key, bool ctrl_key, bool alt_key, CGKeyCode keycode);

void detect_window_below_cursor();
void get_window_info(const void *key, const void *value, void *context);
CGEventRef cgevent_callback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon);

void fatal(const std::string &err);

#endif
