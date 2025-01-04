#include "doomkeys_rl.h"
#include "m_argv.h"
#include "d_event.h"
#include "sounds.h"
#include "doomgeneric.h"

#include <stdio.h>
#include <unistd.h>

#include <stdbool.h>
#include <raylib.h>

// Global state
Texture frame;
Shader shader;
Music music[64] = {0};
size_t current_song;

#define DOOM_SENS 10

const char *frag_shader = 
"#version 330\n"
"in vec2 fragTexCoord;\n"
"out vec4 finalColor;\n"
"uniform sampler2D texture0;\n"
"void main()\n"
"{\n"
"    vec4 texColor = texture(texture0, fragTexCoord);\n"
"    finalColor = vec4(texColor.bgr, 1.0);\n"
"}\n";

#define KEYQUEUE_SIZE 16
unsigned short key_queue[KEYQUEUE_SIZE];
int key_windex = 0;
int key_rindex = 0;

#define KEY_COUNT 30
int bound_keys[KEY_COUNT] = {
  KEY_ENTER, KEY_Y, KEY_ESCAPE, KEY_LEFT, KEY_A, KEY_RIGHT, KEY_D, KEY_UP, 
  KEY_W, KEY_DOWN, KEY_S, KEY_LEFT_CONTROL, KEY_RIGHT_CONTROL, KEY_SPACE, KEY_LEFT_SHIFT,
  KEY_RIGHT_SHIFT, KEY_LEFT_ALT, KEY_RIGHT_ALT, KEY_F2, KEY_F3, KEY_F4,
  KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_EQUAL, KEY_MINUS
};

static unsigned char convert_to_doom_key(int key) {
    switch (key) {
        case KEY_ENTER:
          key = DKEY_ENTER;
          break;
        case KEY_Y:
          key = 'y';
          break;
        case KEY_ESCAPE:
          key = DKEY_ESCAPE;
          break;
        case KEY_LEFT:
          key = DKEY_LEFTARROW;
          break;
        case KEY_A:
          key = DKEY_STRAFE_L;
          break;
        case KEY_RIGHT:
          key = DKEY_RIGHTARROW;
          break;
        case KEY_D:
          key = DKEY_STRAFE_R;
          break;
        case KEY_UP:
        case KEY_W:
          key = DKEY_UPARROW;
          break;
        case KEY_DOWN:
        case KEY_S:
          key = DKEY_DOWNARROW;
          break;
        case KEY_LEFT_CONTROL:
        case KEY_RIGHT_CONTROL:
          key = DKEY_FIRE;
          break;
        case KEY_SPACE:
          key = DKEY_USE;
          break;
        case KEY_LEFT_SHIFT:
        case KEY_RIGHT_SHIFT:
          key = DKEY_RSHIFT;
          break;
        case KEY_LEFT_ALT:
        case KEY_RIGHT_ALT:
          key = DKEY_LALT;
          break;
        case KEY_F2:
          key = DKEY_F2;
          break;
        case KEY_F3:
          key = DKEY_F3;
          break;
        case KEY_F4:
          key = DKEY_F4;
          break;
        case KEY_F5:
          key = DKEY_F5;
          break;
        case KEY_F6:
          key = DKEY_F6;
          break;
        case KEY_F7:
          key = DKEY_F7;
          break;
        case KEY_F8:
          key = DKEY_F8;
          break;
        case KEY_F9:
          key = DKEY_F9;
          break;
        case KEY_F10:
          key = DKEY_F10;
          break;
        case KEY_F11:
          key = DKEY_F11;
          break;
        case KEY_EQUAL:
          key = DKEY_EQUALS;
          break;
        case KEY_MINUS:
          key = DKEY_MINUS;
          break;
    }
    return key;
}

void update_key_queue() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
          key_queue[key_windex++] = (1 << 8) | DKEY_FIRE;
          key_windex %= KEYQUEUE_SIZE;
    } else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
          key_queue[key_windex++] = (0 << 8) | DKEY_FIRE;
          key_windex %= KEYQUEUE_SIZE;
    }

    // standard keys
    for (size_t i = 0; i < KEY_COUNT; i++) {
      int key = bound_keys[i];
      if (IsKeyPressed(key)) {
          key_queue[key_windex++] = (1 << 8) | convert_to_doom_key(key);
          key_windex %= KEYQUEUE_SIZE;
      } else if (IsKeyReleased(key)) {
          key_queue[key_windex++] = (0 << 8) | convert_to_doom_key(key);
          key_windex %= KEYQUEUE_SIZE;
      }
    }
}

void DG_Init() {
    InitWindow(DOOMGENERIC_RESX, DOOMGENERIC_RESY, "DOOM");
    InitAudioDevice();
    SetTargetFPS(120);
    SetExitKey(0);
    DisableCursor();
    
    music[mus_introa] = LoadMusicStream("res/intro.mp3");
    printf("Intro: %d\n", mus_intro);
    music[mus_inter] = LoadMusicStream("res/inter.mp3");
    music[mus_e1m1] = LoadMusicStream("res/e1m1.mp3");
    music[mus_e1m2] = LoadMusicStream("res/e1m2.mp3");

    SetMasterVolume(0.5);

    frame = LoadRenderTexture(DOOMGENERIC_RESX, DOOMGENERIC_RESY).texture;
    shader = LoadShaderFromMemory(NULL, frag_shader);
}

void DG_StartMusic(int musicnum) {
    PlayMusicStream(music[musicnum]);
    printf("SONG: %d\n", musicnum);
    current_song = musicnum;
}

void DG_StopMusic() {
    StopMusicStream(music[current_song]);
}

void DG_UpdateMusic() {
    UpdateMusicStream(music[current_song]);
}

void DG_DrawFrame() {
    // update texture with Doom Frame Buffer
    UpdateTexture(frame, DG_ScreenBuffer);

    BeginDrawing();
    ClearBackground(RAYWHITE);

    // apply shader to flip color values
    BeginShaderMode(shader);
    DrawTexture(frame, 0, 0, WHITE);
    EndShaderMode();

    DrawFPS(10, 10);
    EndDrawing();


    //UpdateMusicStream(music);
    update_key_queue();
}

void DG_SleepMs(uint32_t ms) {
    WaitTime(ms * 0.001);
}

uint32_t DG_GetTicksMs() {
    return GetTime() * 1000;
}

int DG_GetKey(int *pressed, unsigned char *doomKey) {
    if (key_rindex == key_windex) return 0;

    unsigned short key = key_queue[key_rindex++];
    key_rindex %= KEYQUEUE_SIZE;
    *pressed = key >> 8 ? 1 : 0;
    *doomKey = key & 0xFF;
    return 1;
}

int DG_MouseEvent(event_t *event) {
    const float delta_x = GetMouseDelta().x;

    event->type = ev_mouse;
    event->data1 = 0;
    event->data2 = DOOM_SENS * delta_x;
    event->data3 = 0;
    return 1;
}

void DG_SetWindowTitle(const char *title) {
    SetWindowTitle(title);
}

int main(int argc, char **argv) {
    doomgeneric_Create(argc, argv);

    while(!WindowShouldClose()) {
        doomgeneric_Tick();
    }

    return 0;
}

