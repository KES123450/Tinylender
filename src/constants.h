#pragma once

// 스크린 크기
const unsigned int SCR_WIDTH = 1512;
const unsigned int SCR_HEIGHT = 982;

const float MODIFY_VERTEX_SPEED = 0.002f;
const float CAMERA_ROTATE_SPEED = 15.0f;
const float PEN_SPEED = 1.0f;

const float layerX = 0.2962962962962963f;
const float layerY = 0.04073319755600815f;

enum class eImageType{
    JPG,
    PNG
};

enum class eUIState{
    EMPTY,
    LAYER,
    DOT,
    LINE,
    SURFACE
};

enum class eLayerType{
    EMPTY,
    SHAPE,
    CAMERA,
    LIGHT,
    TEXT,
    MODEL
};

enum eInputState{
    Pressed,
    Released,
    PressedAndReleased,
    NotChanged
};