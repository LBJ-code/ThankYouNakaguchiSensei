#include "printNumber.h"

PrintNumber::PrintNumber(LovyanGFX *parent) : _parent(parent)
{
    _type = 0;
    _size = 13;
    _x0 = _y0 = 0;
    _textColor = _backgroundColor = _shadowColor = 0;
}

// 数字列をプリントする
void PrintNumber::printText(int num, int len)
{
    int draw[len];
    for (int i = 0; i < len; i++)
    {
        draw[len - i - 1] = num % 10;
        num /= 10;
    }
    for (int i = 0; i < len; i++)
    {
        print(draw[i]);
        setCursor(_x0 + (_width[_type] + 1) * _size, _y0);
    }
}

// typeに応じたフォントで数字を描画する
void PrintNumber::print(int c)
{
    if (c < 0 || c >= 10)
        return;
    if (_type == 0)
    {
        // 時計用の数字 9×4
        sprite_number.createSprite(_size * 4, _size * 9);
        _print(_numberData1[c], 1, 1, false);
    }
    else if (_type == 1)
    {
        // 影付きの数字 7×3
        // 影の分だけ下にスプライトの大きさを広げる
        sprite_number.createSprite(_size * 3, _size * 7 + floor(_size / 2));
        _print(_numberData2[c], 0.5, 1, true);
    }
    else if (_type == 2)
    {
        // 数字 5×4
        sprite_number.createSprite(_size * 4, _size * 5);
        _print(_numberData3[c], 1, 1, false);
    }
    sprite_number.pushSprite(_parent, _x0, _y0);
}
void PrintNumber::_print(std::vector<std::vector<uint8_t>> data, float wRate, float hRate, bool isShadow)
{
    int xSize = _size * wRate;
    int ySize = _size * hRate;
    sprite_number.fillScreen(_backgroundColor);
    for (int i = 0; i < data.size(); i++)
    {
        sprite_number.fillRect(data[i][0] * xSize,
                               data[i][1] * ySize,
                               (data[i][2] - data[i][0] + 1) * xSize,
                               (data[i][3] - data[i][1] + 1) * ySize,
                               _textColor);
        // 横線のとき影をつける処理
        // WARN: 縦方向に変形すると，きちんと動作しなさそう
        // とりあえず不要なので放置
        if (isShadow)
        {
            if (data[i][3] == data[i][1])
            {
                // 横線
                sprite_number.fillRect(data[i][0] * xSize,
                                       (data[i][1] + 1) * ySize,
                                       (data[i][2] - data[i][0] + 1) * xSize,
                                       ySize / 2,
                                       _shadowColor);
            }
            else
            {
                // 縦線
                sprite_number.fillRect(data[i][0] * xSize,
                                       (data[i][3] + 1) * ySize,
                                       (data[i][2] - data[i][0] + 1) * xSize,
                                       ySize / 2,
                                       _shadowColor);
            }
        }
    }
}

const std::vector<std::vector<std::vector<uint8_t>>> PrintNumber::_numberData1 = {
    {{0, 0, 3, 0}, {3, 0, 3, 8}, {0, 0, 0, 8}, {0, 8, 3, 8}},
    {{2, 0, 2, 8}},
    {{0, 0, 3, 0}, {3, 0, 3, 4}, {0, 4, 3, 4}, {0, 4, 0, 8}, {0, 8, 3, 8}},
    {{0, 0, 3, 0}, {0, 4, 3, 4}, {0, 8, 3, 8}, {3, 0, 3, 8}},
    {{0, 0, 0, 4}, {0, 4, 3, 4}, {3, 0, 3, 8}},
    {{0, 0, 3, 0}, {0, 0, 0, 4}, {0, 4, 3, 4}, {3, 4, 3, 8}, {0, 8, 3, 8}},
    {{0, 0, 3, 0}, {0, 0, 0, 8}, {0, 4, 3, 4}, {3, 4, 3, 8}, {0, 8, 3, 8}},
    {{0, 0, 3, 0}, {0, 0, 0, 3}, {3, 0, 3, 8}},
    {{0, 0, 3, 0}, {0, 4, 3, 4}, {0, 8, 3, 8}, {0, 0, 0, 8}, {3, 0, 3, 8}},
    {{0, 0, 3, 0}, {0, 4, 3, 4}, {0, 8, 3, 8}, {0, 0, 0, 4}, {3, 0, 3, 8}}};
// HACK:横線→縦線の順で記述することで影の描画対応してる
const std::vector<std::vector<std::vector<uint8_t>>> PrintNumber::_numberData2 = {
    {{0, 0, 5, 0}, {0, 6, 5, 6}, {0, 0, 1, 6}, {4, 0, 5, 6}},
    {{1, 0, 4, 0}, {1, 6, 5, 6}, {3, 0, 4, 6}},
    {{0, 0, 5, 0}, {0, 3, 5, 3}, {0, 6, 5, 6}, {4, 0, 5, 3}, {0, 3, 1, 6}},
    {{0, 0, 5, 0}, {0, 3, 5, 3}, {0, 6, 5, 6}, {4, 0, 5, 6}},
    {{0, 4, 5, 4}, {0, 0, 1, 4}, {3, 0, 4, 6}},
    {{0, 0, 5, 0}, {0, 3, 5, 3}, {0, 6, 5, 6}, {0, 0, 1, 3}, {4, 3, 5, 6}},
    {{0, 0, 5, 0}, {0, 3, 5, 3}, {0, 6, 5, 6}, {0, 0, 1, 6}, {4, 3, 5, 6}},
    {{0, 0, 5, 0}, {4, 0, 5, 6}},
    {{0, 0, 5, 0}, {0, 3, 5, 3}, {0, 6, 5, 6}, {0, 0, 1, 6}, {4, 0, 5, 6}},
    {{0, 0, 5, 0}, {0, 3, 5, 3}, {0, 0, 1, 3}, {4, 0, 5, 6}}};
const std::vector<std::vector<std::vector<uint8_t>>> PrintNumber::_numberData3 = {
    {{0, 0, 3, 0}, {0, 4, 3, 4}, {0, 0, 0, 4}, {3, 0, 3, 4}},
    {{1, 0, 2, 0}, {1, 4, 3, 4}, {2, 0, 2, 4}},
    {{0, 0, 3, 0}, {0, 2, 3, 2}, {0, 4, 3, 4}, {3, 0, 3, 2}, {0, 2, 0, 4}},
    {{0, 0, 3, 0}, {0, 2, 3, 2}, {0, 4, 3, 4}, {3, 0, 3, 4}},
    {{0, 3, 3, 3}, {0, 0, 0, 3}, {2, 0, 2, 4}},
    {{0, 0, 3, 0}, {0, 2, 3, 2}, {0, 4, 3, 4}, {0, 0, 0, 2}, {3, 2, 3, 4}},
    {{0, 0, 3, 0}, {0, 2, 3, 2}, {0, 4, 3, 4}, {0, 0, 0, 4}, {3, 2, 3, 4}},
    {{0, 0, 3, 0}, {3, 0, 3, 4}},
    {{0, 0, 3, 0}, {0, 2, 3, 2}, {0, 4, 3, 4}, {0, 0, 0, 4}, {3, 0, 3, 4}},
    {{0, 0, 3, 0}, {0, 2, 3, 2}, {0, 0, 0, 2}, {3, 0, 3, 4}}};

const int32_t PrintNumber::_width[3] = {4, 3, 4};
