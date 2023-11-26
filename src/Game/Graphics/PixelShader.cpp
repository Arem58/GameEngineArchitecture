#include "PixelShader.h"

PixelShader getShader(ShaderType type)
{
    switch (type)
    {
    case ShaderType::Red:
        return PixelShader{
            [](Uint32 color) -> Uint32
            { return (color == 0xF3F2C0FF) ? 0xD2B48CFF : color; },
            "red"};
        break;
    case ShaderType::Negative:
        return PixelShader{
            [](Uint32 color) -> Uint32
            {
                Uint8 r = (color >> 24) & 0xFF;
                Uint8 g = (color >> 16) & 0xFF;
                Uint8 b = (color >> 8) & 0xFF;
                Uint8 a = color & 0xFF;

                r = 255 - r;
                g = 255 - g;
                b = 255 - b;

                return (r << 24) | (g << 16) | (b << 8) | a;
            },
            "negative"};

    case ShaderType::Sepia:
        return PixelShader{
            [](Uint32 color) -> Uint32
            {
                Uint8 r = (color >> 24) & 0xFF;
                Uint8 g = (color >> 16) & 0xFF;
                Uint8 b = (color >> 8) & 0xFF;
                Uint8 a = color & 0xFF; 

                Uint8 outR = static_cast<Uint8>(std::min(255.0, r * 0.393 + g * 0.769 + b * 0.189));
                Uint8 outG = static_cast<Uint8>(std::min(255.0, r * 0.349 + g * 0.686 + b * 0.168));
                Uint8 outB = static_cast<Uint8>(std::min(255.0, r * 0.272 + g * 0.534 + b * 0.131));

                return (outR << 24) | (outG << 16) | (outB << 8) | a;
            },
            "sepia"};

    default:
        break;
    }
}