;; https://docs.scheme.org/guide/ffi-c/
(define-library (imgui)
  (import (scheme base)
          (chibi)
          (chibi optional))
  (export
   is-android? sld_stuff  use_bool

   imgui_bool make-imgui-bool imgui-bool-get imgui-bool-set
   imgui-begin imgui-end
   imgui-flags/no-collapse

   ImVec2_t make-imgui-imvec2 imgui-imvec2-x-get imgui-imvec2-x-set imgui-imvec2-y-get imgui-imvec2-y-set
   imgui-flags/once
   imgui-set-next-window-size
   imgui-button imgui-same-line
   imgui-begin-child imgui-end-child
   imgui-get-frame-height-with-spacing
   imgui-begin-group imgui-end-group
   imgui-input-text-multiline

   make-imgui-text-buf   
   set-imgui-text-buffer
   get-imgui-text-buffer
   imgui-input-text-multiline

   imgui-get-text-line-height
   imgui-flags/read-only
   imgui-flags/allow-tab-input

   )




  
  (begin
    (define sld_stuff "hello")


    ;; bool Begin(const char* name, bool* p_open = NULL, ImGuiWindowFlags flags = 0)
    ;; bool imgui_begin1(const char*, int);
    ;; bool imgui_begin2(const char*, struct imgui_bool*, int);
    (define (imgui-begin name . plist)
      (let-optionals
       plist ((p_open '())
              (flags imgui-flags/no-collapse))
       (if (eq? p_open '())
           (imgui-begin1 name flags))
           ;; TODO: assert p_open is of type imgui_bool
           (imgui-begin2 name p_open flags))
      ) ;; imgui-begin




    (define (imgui-begin-child name . plist)
      (let-optionals
       plist ((size (make-imgui-imvec2 0.0 0.0))
              (border #f)
              (flags 0))
       (imgui-begin-child-c name size border flags))
      );; imgui-begin-child


    (define (make-imgui-text-buf len)
        (let ((x (make-imgui_text_buffer)))
          (begin
            (init_imgui_text_buffer x len)
            x)))

    (define (imgui-input-text-multiline name buf . plist)
      (let-optionals
       plist ((size (make-imgui-imvec2 0.0 0.0))
              (flags 0))
       (imgui-input-text-multiline-c name buf size flags)))






    ) ;; begin
  (include-shared "imgui/imgui")
)
