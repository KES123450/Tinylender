#pragma once

// 스크린 크기
const unsigned int SCR_WIDTH = 1512;
const unsigned int SCR_HEIGHT = 982;

const float CAMERA_ROTATE_SPEED = 15.0f;

enum eImageType{
    JPG,
    PNG
};

enum eUIState{
    LAYER,
    DOT,
    LINE,
    SURFACE
};