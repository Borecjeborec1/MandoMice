#include <iostream>
#include <windows.h>

bool isMouseControlActive = false;

void ToggleMouseControl() {
  isMouseControlActive = !isMouseControlActive;

  if (isMouseControlActive) {
    std::cout << "Mouse control activated. Use 'H' to move left, 'J' to move "
                 "down, 'K' to move up, 'L' to move right, 'I' for left-click, "
                 "and 'O' for right-click."
              << std::endl;
  } else {
    std::cout << "Mouse control deactivated." << std::endl;
  }
}

void MoveMouse(int dx, int dy) {
  INPUT input = {0};
  input.type = INPUT_MOUSE;
  input.mi.dx = dx;
  input.mi.dy = dy;
  input.mi.dwFlags = MOUSEEVENTF_MOVE;

  SendInput(1, &input, sizeof(INPUT));
}

void MouseClick(DWORD button) {
  INPUT input = {0};
  input.type = INPUT_MOUSE;
  input.mi.dwFlags = button;

  SendInput(1, &input, sizeof(INPUT));
}

int main() {
  int mouseSpeed = 5;

  while (true) {

    if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
      mouseSpeed = 15;
    } else if (GetAsyncKeyState(VK_CONTROL) & 0x8000) {
      mouseSpeed = 2;
    } else {
      mouseSpeed = 5;
    }

    if (GetAsyncKeyState(VK_LWIN) & 0x8000 &&
        GetAsyncKeyState(VK_SHIFT) & 0x8000 &&
        (GetAsyncKeyState('X') & 0x8000)) {
      ToggleMouseControl();
      Sleep(200);
    }

    if (isMouseControlActive) {
      int dx = 0;
      int dy = 0;

      if ((GetAsyncKeyState('H') & 0x8000) ||
          (GetAsyncKeyState(VK_LEFT) & 0x8000)) {
        dx -= mouseSpeed;
      }

      if ((GetAsyncKeyState('J') & 0x8000) ||
          (GetAsyncKeyState(VK_DOWN) & 0x8000)) {
        dy += mouseSpeed;
      }

      if ((GetAsyncKeyState('K') & 0x8000) ||
          (GetAsyncKeyState(VK_UP) & 0x8000)) {
        dy -= mouseSpeed;
      }

      if ((GetAsyncKeyState('L') & 0x8000) ||
          (GetAsyncKeyState(VK_RIGHT) & 0x8000)) {
        dx += mouseSpeed;
      }

      if (GetAsyncKeyState('I') & 0x8000) {
        MouseClick(MOUSEEVENTF_LEFTDOWN);
        Sleep(50);
        MouseClick(MOUSEEVENTF_LEFTUP);
        Sleep(50);
      }

      if (GetAsyncKeyState('O') & 0x8000) {
        MouseClick(MOUSEEVENTF_RIGHTDOWN);
        Sleep(50);
        MouseClick(MOUSEEVENTF_RIGHTUP);
        Sleep(50);
      }

      // Move the mouse based on dx and dy
      MoveMouse(dx, dy);
    }

    Sleep(10);
  }

  return 0;
}
