#include <stdio.h>
#include "imgui_src.h"


bool imgui_begin1(const char* name, int flags) {
     return ImGui_Begin(name, NULL, flags);
}

bool imgui_begin2(const char* name, struct imgui_bool* x, int flags) {
    bool* show_ = &(x->the_bool);
    return ImGui_Begin(name, show_, flags);
}



void use_bool(struct imgui_bool* x) {
    printf("Hello use_bool!");
    printf(">>>>>Bool: -----%d-----", x->the_bool);
    bool* ptr = &(x->the_bool);
    printf("Address: %p-----", ptr);
    *ptr = !(*ptr);
    //x->the_bool = !x->the_bool;
    printf(">>>>>Bool: -----%d-----", x->the_bool);
    fflush(stdout);
}




void init_imgui_text_buffer(struct imgui_text_buffer* x, int len) {
    x->buf = malloc(len);
    x->maxlen = len;
    memset(x->buf,'\0', len);
}

void set_imgui_text_buffer(struct imgui_text_buffer* x, char* source) {
    strncpy (x->buf, source, x->maxlen);
}

char* get_imgui_text_buffer(struct imgui_text_buffer* x) {
    return x->buf;
}


bool imgui_input_text_multiline_c(char* label, struct imgui_text_buffer* txtbuf, struct ImVec2_t size, int flags) {
    char* buf = txtbuf->buf;
    int buf_size = txtbuf->maxlen;
    return ImGui_InputTextMultilineEx(label, buf, buf_size, size, flags, 0, 0);
}




bool is_android() {
    #ifdef __ANDROID__
        return true;
    #else
        return false;
    #endif
}

