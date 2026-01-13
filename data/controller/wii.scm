;; data/controller/wii.scm
;; Wii controller configuration for Pingus
;;
;; This configuration supports multiple controller types:
;; - Wii Remote (held upright, IR pointer for mouse)
;; - Wii Remote + Nunchuck (IR pointer + stick for scrolling)
;; - Classic Controller / Classic Controller Pro
;; - GameCube Controller
;;
;; SDL-Wii Button Mapping (from libogc/SDL-wii):
;; +-----------+--------+-------------+-----------+
;; | Button ID | Remote | Nunchuck    | Classic   |
;; +-----------+--------+-------------+-----------+
;; |     0     | A      |             |           |
;; |     1     | B      |             |           |
;; |     2     | 1      |             |           |
;; |     3     | 2      |             |           |
;; |     4     | Minus  |             |           |
;; |     5     | Plus   |             |           |
;; |     6     | Home   |             |           |
;; |     7     |        | Z           |           |
;; |     8     |        | C           |           |
;; |     9     |        |             | A         |
;; |    10     |        |             | B         |
;; |    11     |        |             | X         |
;; |    12     |        |             | Y         |
;; |    13     |        |             | L         |
;; |    14     |        |             | R         |
;; |    15     |        |             | ZL        |
;; |    16     |        |             | ZR        |
;; |    17     |        |             | Minus     |
;; |    18     |        |             | Plus      |
;; |    19     |        |             | Home      |
;; |    Hat    | D-Pad  |             | D-Pad     |
;; +-----------+--------+-------------+-----------+
;;
;; Axis Mapping:
;; Axis 0 = Nunchuck Stick X / Classic Left Stick X
;; Axis 1 = Nunchuck Stick Y / Classic Left Stick Y
;; Axis 2 = Classic Right Stick X
;; Axis 3 = Classic Right Stick Y

(pingus-controller
  ;; Standard keyboard bindings (for USB keyboard support)
  (standard-keyboard
    (sdl:keyboard))

  ;; Pointer control:
  ;; - Wii Remote: Use IR sensor (mapped as SDL mouse)
  ;; - Nunchuck: Left stick emulates mouse movement (handled in driver)
  (standard-pointer
    (sdl:mouse-pointer))

  ;; Camera scrolling/panning:
  ;; - Wii Remote standalone: D-Pad pans camera (Mapped as Hat 0)
  ;; - Classic/GameCube: Right stick (C-stick) pans camera
  (standard-scroller
    (core:button-scroller
      (up    (sdl:joystick-hat (device 0) (hat 0) (dir "up")))
      (down  (sdl:joystick-hat (device 0) (hat 0) (dir "down")))
      (left  (sdl:joystick-hat (device 0) (hat 0) (dir "left")))
      (right (sdl:joystick-hat (device 0) (hat 0) (dir "right"))))
    (core:axis-scroller
      (x-axis (sdl:joystick-axis (device 0) (axis 2)))
      (y-axis (sdl:joystick-axis (device 0) (axis 3)))))

  ;; Primary action (Select/Confirm)
  ;; Remote: A | Nunchuck: C | Classic: A
  (primary-button
    (sdl:joystick-button (device 0) (button 0))
    (sdl:joystick-button (device 0) (button 8))
    (sdl:joystick-button (device 0) (button 9)))

  ;; Secondary action (Cancel/Back)
  ;; Remote: B | Classic: B
  (secondary-button
    (sdl:joystick-button (device 0) (button 1))
    (sdl:joystick-button (device 0) (button 10)))

  ;; Pause game
  ;; Remote: Plus | Classic: Plus
  (pause-button
    (sdl:joystick-button (device 0) (button 5))
    (sdl:joystick-button (device 0) (button 18)))

  ;; Fast forward
  ;; Remote: Minus | Classic: Minus
  (fast-forward-button
    (sdl:joystick-button (device 0) (button 4))
    (sdl:joystick-button (device 0) (button 17)))

  ;; Escape/Menu
  ;; Remote: Home | Classic: Home
  (escape-button
    (sdl:joystick-button (device 0) (button 6))
    (sdl:joystick-button (device 0) (button 19)))

  ;; Cycle actions up
  ;; Remote: 1 | Classic: Y / L
  (action-up-button
    (sdl:joystick-button (device 0) (button 2))
    (sdl:joystick-button (device 0) (button 12))
    (sdl:joystick-button (device 0) (button 13)))

  ;; Cycle actions down
  ;; Remote: 2 | Classic: X / R
  (action-down-button
    (sdl:joystick-button (device 0) (button 3))
    (sdl:joystick-button (device 0) (button 11))
    (sdl:joystick-button (device 0) (button 14)))

  ;; Armageddon - "nuke all" command
  ;; Mapped to Nunchuck Z (Button 7)
  (armageddon-button
    (sdl:joystick-button (device 0) (button 7))
    (sdl:joystick-button (device 0) (button 15)))
)

;; EOF
