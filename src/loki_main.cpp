#include "loki_main.hpp"
#include <stdio.h>
#include <iostream>
#include <chibi/eval.h>



#ifdef __ANDROID__
    #include <android/log.h>
    #define APPNAME "Loki"
#endif


#define BUF_SIZE 1024 * 16
static char text_out[BUF_SIZE] = "<outputs here>";


static sexp check_exception(sexp ctx, sexp res) {
    sexp_gc_var4(err, advise, sym, tmp);
    if (res && sexp_exceptionp(res)) {
        sexp_gc_preserve4(ctx, err, advise, sym, tmp);
        tmp = res;
        err = sexp_current_error_port(ctx);
        if (! sexp_oportp(err))
            err = sexp_make_output_port(ctx, stderr, SEXP_FALSE);
        sexp_print_exception(ctx, res, err);
        sexp_print_exception_stack_trace(ctx, res, err);
        sexp_gc_release4(ctx);
        //exit(70);
    }
    return res;
}



void imgui_init() {

    ImGuiIO& io = ImGui::GetIO();

    #ifdef __ANDROID__
        //int size_in_pixels = 36;
        //__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "The value of 1 + 1 is %d", 1+1);
        //FILE* file = fopen("/sdcard/Loki/<FONT>.ttf","r");
        //if (file == NULL) {
        //    __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "open failed - prob need to enable sd card permission on phone");
        //} else {
        //    __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "open worked");
        //    fclose(file);
        //}
        //io.Fonts->AddFontFromFileTTF("/sdcard/Loki/<FONT>.ttf", size_in_pixels);
    #else
        //int size_in_pixels = 14;
        //io.Fonts->AddFontFromFileTTF("deps/imgui/misc/fonts/<FONT>.ttf", size_in_pixels);
    #endif

    ImGui::StyleColorsLight();
    ImGuiStyle* style = &ImGui::GetStyle();
    style->FrameBorderSize = 1.0f;
    style->WindowMenuButtonPosition = ImGuiDir_Right;

    #ifdef __ANDROID__
        style->ScrollbarSize = 48.0f;
        style->ItemSpacing = ImVec2(8.0f, 20.0f);    
        style->FramePadding = ImVec2(16.0f, 16.0f);
    #else
        style->ScrollbarSize = 16.0f;
        style->ItemSpacing = ImVec2(8.0f, 8.0f);
        style->FramePadding = ImVec2(8.0f, 8.0f);
    #endif

    ImVec4* colors = style->Colors;

    colors[ImGuiCol_Text]                   = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(230/255.0, 235/255.0, 239/255.0, 1.00f);
    colors[ImGuiCol_Border]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.83f, 0.83f, 0.83f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.46f, 0.54f, 0.80f, 0.60f);
    colors[ImGuiCol_Button]                 = ImVec4(0.88f, 0.88f, 0.88f, 0.40f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.52f, 0.52f, 0.52f, 0.31f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.87f, 0.87f, 0.87f, 0.80f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.78f, 0.78f, 0.78f, 1.00f);
    colors[ImGuiCol_Separator]              = ImVec4(0.39f, 0.39f, 0.39f, 0.62f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.14f, 0.44f, 0.80f, 0.78f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.14f, 0.44f, 0.80f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.80f, 0.80f, 0.80f, 0.56f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.71f, 0.71f, 0.71f, 0.95f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.85f, 0.85f, 0.85f, 0.95f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.83f, 0.82f, 0.84f, 0.95f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.92f, 0.92f, 0.94f, 0.95f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.74f, 0.82f, 0.91f, 1.00f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.45f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colors[ImGuiCol_NavHighlight]           = colors[ImGuiCol_HeaderHovered];
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(0.70f, 0.70f, 0.70f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.20f, 0.20f, 0.20f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
        
}


char buf_out[40960] = { 0 };
char buf_err[40960] = { 0 };

static sexp ctx;
static sexp env;




void scheme_init() {

    #ifdef __ANDROID__
        fclose(stdout);
        fclose(stderr);
        stdout = fmemopen(buf_out, sizeof(buf_out), "w");
        stderr = fmemopen(buf_err, sizeof(buf_err), "w");
        setbuf(stdout, NULL);
        setbuf(stderr, NULL);
        __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "LOKI Hello world from C.\n");
    #endif

    sexp_scheme_init();
    ctx = sexp_make_eval_context(NULL, NULL, NULL, 0, 0);
    env = sexp_context_env(ctx);


    sexp tmp;
    #ifdef __ANDROID__
        char append_path[] = "/sdcard/Loki/chibi-lib";
        sexp_add_module_directory(ctx, sexp_c_string(ctx,append_path,-1), SEXP_TRUE);

        char include_path1[] = "/sdcard/Loki/chibi-ffi";
        sexp_add_module_directory(ctx, tmp=sexp_c_string(ctx,include_path1,-1), SEXP_FALSE);
        
        char include_path2[] = "/sdcard/Loki/chibi-scm";
        sexp_add_module_directory(ctx, tmp=sexp_c_string(ctx,include_path2,-1), SEXP_FALSE);

    #else
        char include_path3[] = "/home/nawal/data/loki-core/deps/chibi-scheme-static/lib";
        sexp_add_module_directory(ctx, tmp=sexp_c_string(ctx,include_path3,-1), SEXP_FALSE);
    #endif

    sexp e_ = sexp_load_standard_env(ctx, env, SEXP_SEVEN);
    sexp_load_standard_ports(ctx, e_, stdin, stdout, stderr, 0);
    check_exception(ctx, e_);
}












void loki_init() {
    imgui_init();
    scheme_init();

    #ifdef __ANDROID__
        __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "LOKI ----------\n");
    #endif
    printf("foo");
    fprintf(stderr, "%s", "test stderr worked!\n");

    #ifdef __ANDROID__    
        __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "stdout: %s", buf_out);
        __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "stderr: %s", buf_err);
    #endif

    sexp obj1;
    sexp_eval_string(ctx, "(display \"LOKI scheme prints... called from C code.\")", -1, NULL);
    sexp_eval_string(ctx, "(newline)", -1, NULL);
    sexp_eval_string(ctx, "(define lucky-number 666)", -1, NULL);
    sexp ret = sexp_eval_string(ctx, "lucky-number", -1, NULL);

    int lucky_number = -1;
    if (sexp_integerp(ret)) {
        lucky_number = sexp_unbox_fixnum(ret);
    }
    #ifdef __ANDROID__    
        __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "Lucky number: %d\n", lucky_number);
    #else
        printf("Lucky number: %d\n", lucky_number);
    #endif

    printf("list directory:\n");
    obj1 = sexp_eval_string(ctx, "(import (chibi filesystem))", -1, NULL);
    sexp_debug(ctx, "obj1: ", obj1);
    check_exception(ctx, obj1);

    obj1 = sexp_eval_string(ctx, "(import (imgui))", -1, NULL);
    sexp_debug(ctx, "obj1: ", obj1);
    check_exception(ctx, obj1);

    #ifdef __ANDROID__          
        __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "stdout: %s", buf_out);
        __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "stderr: %s", buf_err);
        __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "LOKI ----------\n");
    #endif

    sexp_eval_string(ctx, "(define (scm_loop) '()", -1, NULL);
}





ImVec4 loki_main() {
    static bool show_imgui_demo_window = false;
    static bool show_console_window = true;

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("System")) {
            ImGui::Checkbox("ImGui Demo", &show_imgui_demo_window);
            ImGui::Checkbox("System Console", &show_console_window);

            ImGui::Separator();
            if (ImGui::MenuItem("Exit", "CTRL+Q")) {
                exit(0);
            }            
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    
    if (show_imgui_demo_window) {
        ImGui::Begin("Dear ImGui Demo", &show_imgui_demo_window, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar);
        ImGui::End();
        ImGui::ShowDemoWindow(&show_imgui_demo_window);
    }
    
    if (show_console_window) {

        ImGui::SetNextWindowSize(ImVec2(1020,800), ImGuiCond_Once);

        ImGui::Begin("System Console", &show_console_window, ImGuiWindowFlags_NoCollapse); // | ImGuiWindowFlags_MenuBar);

        #ifdef __ANDROID__
            static char text[BUF_SIZE] = "(+ 1 2)";
        #else
            static char text[BUF_SIZE] = "(+ 1 2)";
        #endif

        static ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput;
        char response[BUF_SIZE+8];


        // Left
        {
            ImGui::BeginChild("left pane", ImVec2(500, 0), true);
            ImGui::InputTextMultiline("##source", text, IM_ARRAYSIZE(text), ImVec2(490, ImGui::GetTextLineHeight() * 16), flags);
            //std::cout << text << std::endl;
            ImGui::EndChild();
        } // left
        ImGui::SameLine();
        // Right
        {
            ImGui::BeginGroup();
                ImGui::BeginChild("item view", ImVec2(500, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
                    static ImGuiInputTextFlags flags_out = ImGuiInputTextFlags_ReadOnly;
                    ImGui::InputTextMultiline("##result", text_out, IM_ARRAYSIZE(text_out), ImVec2(490, ImGui::GetTextLineHeight() * 16), flags_out);
                ImGui::EndChild();
                if (ImGui::Button("Run")) {
                    std::cout << "Run this:" << text << std::endl;
                    
                    sexp obj1 = sexp_eval_string(ctx, text, -1, NULL);
                    sexp_debug(ctx, "obj1: ", obj1);
                    check_exception(ctx, obj1);

                    sexp str_data = sexp_write_to_string(ctx, obj1);
                    strncpy(text_out, sexp_string_data(str_data), BUF_SIZE);                    
                }
            ImGui::EndGroup();
        } // right
        ImGui::End();
    } // console



    sexp_eval_string(ctx, "(scm_loop)", -1, NULL);


    return ImVec4(0.0f, 0.5f, 0.50f, 1.00f);

}



void loki_destroy() {
    sexp_destroy_context(ctx);
}



