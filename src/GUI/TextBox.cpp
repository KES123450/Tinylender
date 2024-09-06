#include "TextBox.h"

TextBox::TextBox(glm::vec3 textBoxPos, float sizeX, float sizeY, std::string text, float textSize, glm::vec3 textColor, bool stringFlag, float dragOffset)
{
    mPushed = false;
    mType = eUIType::TEXTBOX;
    mSizeX = sizeX;
    mSizeY = sizeY;
    mPos = textBoxPos;
    mDragOffset = dragOffset;

    float halfX = mSizeX / 2;
    float halfY = mSizeY / 2;

    glm::vec3 vertex[4];
    vertex[0] = glm::vec3(textBoxPos.x - halfX, textBoxPos.y + halfY, 0.0f);
    vertex[1] = glm::vec3(textBoxPos.x - halfX, textBoxPos.y - halfY, 0.0f);
    vertex[2] = glm::vec3(textBoxPos.x + halfX, textBoxPos.y + halfY, 0.0f);
    vertex[3] = glm::vec3(textBoxPos.x + halfX, textBoxPos.y - halfY, 0.0f);

    glm::vec2 texCoord[4];
    texCoord[0] = glm::vec2(0.0f, 1.0f);
    texCoord[1] = glm::vec2(0.0f, 0.0f);
    texCoord[2] = glm::vec2(1.0f, 1.0f);
    texCoord[3] = glm::vec2(1.0f, 0.0f);

    for (int i = 0; i < 4; i++)
    {
        mVertexArray[i * 5 + 0] = vertex[i].x;
        mVertexArray[i * 5 + 1] = vertex[i].y;
        mVertexArray[i * 5 + 2] = vertex[i].z;
        mVertexArray[i * 5 + 3] = texCoord[i].x;
        mVertexArray[i * 5 + 4] = texCoord[i].y;
    }

    glGenBuffers(1, &mVBO);
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mEBO);

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mVertexArray), mVertexArray, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mIndices), mIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    int a = SCR_WIDTH;
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
    mTextShader->use();
    glUniformMatrix4fv(glGetUniformLocation(mTextShader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&mFreeType))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }

    // find path to font
    std::string font_name = "resource/font/LINESeedSans_A_Th.ttf";
    if (font_name.empty())
    {
        std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
    }

    if (FT_New_Face(mFreeType, mFont.c_str(), 0, &mFace))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }
    else
    {
        // set size to load glyphs as
        FT_Set_Pixel_Sizes(mFace, 0, 48);

        // disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // load first 128 characters of ASCII set
        for (unsigned char c = 0; c < 128; c++)
        {
            // Load character glyph
            if (FT_Load_Char(mFace, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                mFace->glyph->bitmap.width,
                mFace->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                mFace->glyph->bitmap.buffer);
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character = {
                texture,
                glm::ivec2(mFace->glyph->bitmap.width, mFace->glyph->bitmap.rows),
                glm::ivec2(mFace->glyph->bitmap_left, mFace->glyph->bitmap_top),
                static_cast<unsigned int>(mFace->glyph->advance.x)};
            mCharacters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    FT_Done_Face(mFace);
    FT_Done_FreeType(mFreeType);

    SetText(text);

    mTextSize = textSize;
    mTextColor = textColor;
    glGenVertexArrays(1, &mTextVAO);
    glGenBuffers(1, &mTextVBO);
    glBindVertexArray(mTextVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mTextVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextBox::OnPointerDown(float xpos, float ypos, float xdelta, float ydelta)
{
    if (!bVisible)
        return;

    glm::vec3 pointNDC = ScreenToNDC(glm::vec2(xpos, ypos));
    glm::vec2 sizeHalf = glm::vec2(mSizeX / 2, mSizeY / 2);

    if (pointNDC.x >= (mPos.x - sizeHalf.x) && pointNDC.x <= (mPos.x + sizeHalf.x) && pointNDC.y >= (mPos.y - sizeHalf.y) && pointNDC.y <= (mPos.y + sizeHalf.y))
    {
        bTextActive = true;
        bDragged = true;
    }
    else
    {
        bTextActive = false;
        bDragged = false;
    }
}

void TextBox::OnPointer(float xpos, float ypos, float xdelta, float ydelta)
{
    if (!bVisible || !bDragged || bString)
        return;

    float textDelta = std::stof(mStr) + xdelta * mDragOffset;
    mStr = std::to_string(textDelta);
    
    if (mEventCallback)
        mEventCallback(mStr);
}

void TextBox::OnPointerUp(float xpos, float ypos, float xdelta, float ydelta)
{
    bDragged = false;
}

void TextBox::GeyKeyDown(std::string str)
{
    if (!bVisible)
        return;

    if (!bTextActive)
        return;

    if (str == "BACKSPACE")
    {
        mStr.pop_back();
        if (mEventCallback)
            mEventCallback(mStr);
        return;
    }

    if (!bString && str[0] < 48 && str[0] > 58)
    {
        return;
    }

    mStr.append(str);
    if (mEventCallback)
        mEventCallback(mStr);
}

void TextBox::SetText(std::string str)
{
    mStr = str;
}

void TextBox::SetEventCallback(std::function<void(std::string)> str)
{
    if (!str)
        return;
    mEventCallback = str;
}

void TextBox::renderText(Shader *shader, std::string text, float scale, glm::vec3 color)
{
    float halfX = mSizeX / 2;
    float halfY = mSizeY / 2;

    glm::vec2 screenPoint = NDCToScreen(glm::vec2(mPos.x - halfX, mPos.y - halfY));
    float x = screenPoint.x;
    float y = screenPoint.y;

    // activate corresponding render state
    shader->use();
    glUniform3f(glGetUniformLocation(shader->ID, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(mTextVAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = mCharacters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos, ypos, 0.0f, 1.0f},
            {xpos + w, ypos, 1.0f, 1.0f},

            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos + w, ypos, 1.0f, 1.0f},
            {xpos + w, ypos + h, 1.0f, 0.0f}};
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, mTextVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextBox::Draw()
{
    if (!bVisible)
        return;

    glEnable(GL_STENCIL_TEST);
    glDisable(GL_DEPTH_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);
    UIShader->use();
    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glStencilFunc(GL_EQUAL, 1, 0xFF);
    glStencilMask(0x00);
    renderText(mTextShader, mStr, mTextSize, mTextColor);

    glStencilFunc(GL_ALWAYS, 0, 0xFF); // Restore default stencil function
    glStencilMask(0xFF);
    glEnable(GL_DEPTH_TEST);
}