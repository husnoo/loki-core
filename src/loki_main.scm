
(import (scheme base)
        (chibi)
        (chibi optional))

(define (print . a)
  (display a)
  (newline))

(begin
  (define show-console2 (make-imgui-bool #t))
  (define input_txt_buf (make-imgui-text-buf 1024))
  (define output_txt_buf (make-imgui-text-buf 1024))

  (set-imgui-text-buffer input_txt_buf "(load \"/home/nawal/data/Loki/src/loki_main.scm\")")

  
  (if (is-android?)
      (begin (display "is android!")(newline))
      (begin (display "is not android!")(newline)))


;;  (define (test-opt . plist)
;;      (let-keywords
;;       plist ((a "a")
;;              (b "b"))
;;       (display a)
;;       (display b)
;;       (newline)))
;;  (test-opt 'a: "x" 'b: "d")
  
  (define (scm_loop)
    
    
    (if (imgui-bool-get show-console2)
        (begin
          (imgui-set-next-window-size (make-imgui-imvec2 1020.0 800.0) imgui-flags/once)
          (imgui-begin "System console 2" show-console2)

          (imgui-begin-group)
          (imgui-text "source code:")
          (imgui-begin-child "left pane" (make-imgui-imvec2 500.0 0.0))
          (imgui-input-text-multiline "##source" input_txt_buf (make-imgui-imvec2 490.0 (* 16 (imgui-get-text-line-height))) imgui-flags/allow-tab-input)
          (imgui-end-child) ;; left-pane
          (imgui-end-group)

          (imgui-same-line)

          (imgui-begin-group)
          (imgui-text "output:")
          (imgui-begin-child "right pane" (make-imgui-imvec2 500.0 (- 0 (imgui-get-frame-height-with-spacing)))) ;; leave 1 line for button
          (imgui-input-text-multiline "##output" output_txt_buf (make-imgui-imvec2 490.0 (* 16 (imgui-get-text-line-height))) imgui-flags/read-only)
          (imgui-end-child)
          (if (imgui-button "Run")
              (begin
                (display "run!!!")
                (newline)
                (display (get-imgui-text-buffer input_txt_buf))
                (newline)
                )) ;; if run button pressed
          (imgui-end-group)
          (imgui-end))) ;; console2






;;        // Right
;;        static ImGuiInputTextFlags flags_out = ImGuiInputTextFlags_ReadOnly;
;;        ImGui::InputTextMultiline("##result", text_out, IM_ARRAYSIZE(text_out), ImVec2(490, ImGui::GetTextLineHeight() * 16), flags_out);

;;                if (ImGui::Button("Run")) {
;;                    std::cout << "Run this:" << text << std::endl;
;;                    sexp obj1 = sexp_eval_string(ctx, text, -1, NULL);
;;                    sexp_debug(ctx, "obj1: ", obj1);
;;                    check_exception(ctx, obj1);
;;                    sexp str_data = sexp_write_to_string(ctx, obj1);
;;                    strncpy(text_out, sexp_string_data(str_data), BUF_SIZE);
;;                }









        
        
        ) ;; define scm_loop
    ) ;; top-level-begin
















;; (write (+ 1 2))
;; (newline)

;; (define length
;;   (lambda (ls)
;;     (if (null? ls)
;;         0
;;         (+ (length (cdr ls)) 1))))

;; (write (length '()))
;; (newline)
;; (write (length '(a)))
;; (newline)
;; (write (length '(a b)))
;; (newline)
;; (display "hello\n")

;; (write (*s7* 'debug))
;; (newline)


;; (define length
;;   (lambda (ls)
;;     (if (null? ls)
;;         0
;;         (+ (length (cdr ls)) 1))))

;; (write (length '()))
;; (newline)

;; (write (length '(a)))
;; (newline)

;; (write (length '(a b)))
;; (newline)

;; (write (length '(a b c d)))
;; (newline)

;; (write (length '(a b c d)))
;; (newline)

;;(write "hello!")
;;(newline)




















