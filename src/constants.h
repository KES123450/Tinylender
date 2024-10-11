#pragma once

// 스크린 크기
const unsigned int SCR_WIDTH = 1503;
const unsigned int SCR_HEIGHT = 820;

const float MODIFY_VERTEX_SPEED = 0.002f;
const float CAMERA_ROTATE_SPEED = 15.0f;
const float PEN_SPEED = 1.0f;
const float SCROLL_SPEED = 0.003f;

const float LAYER_SIZE_X = 0.3111111111111111f;
const float LAYER_SIZE_Y = 0.08351219512195122f;

const float UI_GAURD_SCR_X = 310.0f;
const float CURVE_DISTANCE = 0.1f;

const unsigned int LIGHT_SIZE = 32;

enum class eImageType
{
    JPG,
    PNG
};

enum class eUIState
{
    EMPTY,
    LAYER,
    DOT,
    LINE,
    SURFACE
};

enum class eLayerType
{
    EMPTY,
    SHAPE,
    CAMERA,
    LIGHT,
    TEXT,
    MODEL
};

enum eInputState
{
    Pressed,
    Released,
    PressedAndReleased,
    NotChanged
};

enum eUIType
{
    EMPTY,
    BUTTON,
    LAYER,
    PANEL,
    TEXTBOX
};