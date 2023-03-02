#ifndef __IMGUI_SRC_H__
#define __IMGUI_SRC_H__

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "cimgui.h"


struct imgui_bool {
  bool the_bool;
};

bool imgui_begin1(const char*, int);
bool imgui_begin2(const char*, struct imgui_bool*, int);



struct imgui_text_buffer {
    char* buf;
    int maxlen;
};

void init_imgui_text_buffer(struct imgui_text_buffer*, int);
void set_imgui_text_buffer(struct imgui_text_buffer*, char*);
char* get_imgui_text_buffer(struct imgui_text_buffer*);
bool imgui_input_text_multiline_c(char*, struct imgui_text_buffer*, struct ImVec2_t, int);







void use_bool(struct imgui_bool*);
bool is_android();

#endif
