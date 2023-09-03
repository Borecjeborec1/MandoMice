#include <iostream>
#include <Windows.h>

#define VK_LEFTWIN 0x5B
#define VK_SHIFT 0x10
#define VK_X 0x58

bool mouseMode = false;

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

int c = 0;
LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
  if (nCode >= 0) {
    KBDLLHOOKSTRUCT *pKeyStruct = (KBDLLHOOKSTRUCT *)lParam;
    if (pKeyStruct->vkCode == 'X') {
      c++;
      mouseMode = (c % 2 == 0);

      std::cout << "Activating mouse mode" << mouseMode << c << "\n";
      Sleep(300);
      return 1;
    }

    if (mouseMode) {
      if (pKeyStruct->vkCode == 'H' || pKeyStruct->vkCode == 'J' ||
          pKeyStruct->vkCode == 'K' || pKeyStruct->vkCode == 'L' ||
          pKeyStruct->vkCode == 'I' || pKeyStruct->vkCode == 'O') {
        int dx = 0;
        int dy = 0;

        if (pKeyStruct->vkCode == 'H') {
          dx -= 10;
        } else if (pKeyStruct->vkCode == 'J') {
          dy += 10;
        } else if (pKeyStruct->vkCode == 'K') {
          dy -= 10;
        } else if (pKeyStruct->vkCode == 'L') {
          dx += 10;
        } else if (pKeyStruct->vkCode == 'I') {
          MouseClick(MOUSEEVENTF_LEFTDOWN);
          Sleep(50);
          MouseClick(MOUSEEVENTF_LEFTUP);
          Sleep(50);
        } else if (pKeyStruct->vkCode == 'O') {
          MouseClick(MOUSEEVENTF_RIGHTDOWN);
          Sleep(50);
          MouseClick(MOUSEEVENTF_RIGHTUP);
          Sleep(50);
        }

        MoveMouse(dx, dy);
        return 1;
      }
    }
  }
  return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
  HHOOK keyboardHook =
      SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookProc, NULL, 0);

  std::cout << "Keyboard hook installed. Press Left Win + Shift + 'x' to block "
            << "\n";

  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  UnhookWindowsHookEx(keyboardHook);

  return 0;
}
