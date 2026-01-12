;; data/controller/wii.scm
;; Wii Remote controller configuration for Pingus
;;
;; Button Mapping (Standard SDL Wii):
;; Button 0 = A
;; Button 1 = B
;; Button 2 = 1
;; Button 3 = 2
;; Button 4 = Minus (-)
;; Button 5 = Plus (+)
;; Button 6 = Home
;;
;; Axis Mapping:
;; Axis 0/1 = IR Pointer (if enabled)
;; Axis 4/5 = D-Pad (sometimes mapped as Hat 0)

(pingus-controller
  ;; Standard keyboard bindings (for USB keyboard support)
  (standard-keyboard
    (sdl:keyboard))

  ;; Pointer control via Wii Remote IR (Axis 0 and 1)
  (standard-pointer
    (sdl:mouse-pointer))

  ;; Scrolling via D-Pad (mapped as axes on some SDL Wii ports)
  (standard-scroller
    (core:axis-scroller
      (x-axis (sdl:joystick-axis (device 0) (axis 0)))
      (y-axis (sdl:joystick-axis (device 0) (axis 1)))))

  ;; A button - Primary action (Select)
  (primary-button
    (sdl:joystick-button (device 0) (button 0)))

  ;; B button - Secondary action (Cancel/Back)
  (secondary-button
    (sdl:joystick-button (device 0) (button 1)))

  ;; Plus (+) button - Pause game
  (pause-button
    (sdl:joystick-button (device 0) (button 5)))

  ;; Minus (-) button - Fast forward
  (fast-forward-button
    (sdl:joystick-button (device 0) (button 4)))

  ;; HOME button - Escape/Menu
  (escape-button
    (sdl:joystick-button (device 0) (button 6)))

  ;; 1 button - Cycle actions up
  (action-up-button
    (sdl:joystick-button (device 0) (button 2)))

  ;; 2 button - Cycle actions down
  (action-down-button
    (sdl:joystick-button (device 0) (button 3)))
    
  ;; Armageddon (Plus + Minus + A) - Just mapped to Home for safety
  (armageddon-button
    (sdl:joystick-button (device 0) (button 6)))
)

;; EOF
