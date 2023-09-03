import keyboard
import mouse

is_mouse_mode = False


def toggle_mouse_mode():
    global is_mouse_mode
    is_mouse_mode = not is_mouse_mode


keyboard.add_hotkey('win+shift+x', toggle_mouse_mode)

dx = 0
dy = 0


def set_movement(x, y):
    global dx, dy
    dx = x
    dy = y


def move_mouse(x, y):
    global dx, dy
    mouse.move(x, y, False)
    dx = 0
    dy = 0


keyboard.add_hotkey("h", lambda: set_movement(-5, 0), suppress=True)
keyboard.add_hotkey("j", lambda: set_movement(0, 5), suppress=True)
keyboard.add_hotkey("k", lambda: set_movement(0, -5), suppress=True)
keyboard.add_hotkey("l", lambda: set_movement(5, 0), suppress=True)

