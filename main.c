#include "SFML/Graphics/Font.h"
#include "SFML/Graphics/RenderTexture.h"
#include "SFML/Graphics/Sprite.h"
#include <SFML/Graphics.h>
#include <SFML/System.h>

sfSprite *createTemplateSprite(sfTexture *texture) {
  sfSprite *sprite = sfSprite_create();
  sfSprite_setTexture(sprite, texture, sfTrue);
  sfVector2f center = {sfSprite_getGlobalBounds(sprite).width / 2,
                       sfSprite_getGlobalBounds(sprite).height / 2};
  sfSprite_setOrigin(sprite, center);
  sfVector2f scale = {4, 4};
  sfSprite_setScale(sprite, scale);

  return sprite;
}

sfText *createTemplateText(sfFont *font) {
  sfText *text = sfText_create();
  sfText_setString(text, "Hello, CSFML!");
  sfText_setFont(text, font);
  sfText_setCharacterSize(text, 30);
  sfText_setFillColor(text, sfWhite);
  sfVector2f textCenter = {sfText_getGlobalBounds(text).width / 2,
                           sfText_getGlobalBounds(text).height / 2};
  sfText_setOrigin(text, textCenter);
  sfVector2f scale = {4, 4};
  sfText_setScale(text, scale);

  return text;
}

void setSpriteAndTextToMiddleOfScreen(sfSprite *sprite, sfText *text,
                                      sfVector2i windowSize) {
  sfVector2f spritePosition = {windowSize.x / 2.0, windowSize.y / 2.0 - 50};
  sfSprite_setPosition(sprite, spritePosition);

  sfVector2f textPosition = {windowSize.x / 2.0, windowSize.y / 2.0 + 50};
  sfText_setPosition(text, textPosition);
}

int main() {
  // Create the window
  sfVideoMode mode = {800, 600, 32};
  sfRenderWindow *window =
      sfRenderWindow_create(mode, "CSFML Example", sfResize | sfClose, NULL);
  if (!window)
    return 1;

  // Load a texture
  sfTexture *texture = sfTexture_createFromFile("texture.png", NULL);
  if (!texture)
    return 1;

  // Create a sprite
  sfSprite *sprite = createTemplateSprite(texture);

  // Load a font
  sfFont *font = sfFont_createFromFile("font.ttf");
  sfFont_setSmooth(font, sfFalse);
  if (!font)
    return 1;

  // Create a text
  sfText *text = createTemplateText(font);

  // Main loop
  while (sfRenderWindow_isOpen(window)) {
    sfEvent event;
    while (sfRenderWindow_pollEvent(window, &event)) {
      switch (event.type) {
      case sfEvtClosed:
        sfRenderWindow_close(window);
        break;
      case sfEvtResized: {
        sfVector2i windowSize = {event.size.width, event.size.height};
        setSpriteAndTextToMiddleOfScreen(sprite, text, windowSize);

        sfFloatRect viewport = {0.0, 0.0, (float)windowSize.x,
                                (float)windowSize.y};
        sfRenderWindow_setView(window, sfView_createFromRect(viewport));
        break;
      }
      case sfEvtKeyPressed: {
        switch (event.key.code) {
        case sfKeyS: // enable / disable smoothing
            {
                sfFont_setSmooth(font, !sfFont_isSmooth(font));
                sfTexture_setSmooth(texture, !sfTexture_isSmooth(texture));
                break;
              }
        default:
          break;
        }
        break;
      }
      default:
        break;
      }
    }

    sfRenderWindow_clear(window, sfBlack);

    // Draw the sprite
    sfRenderWindow_drawSprite(window, sprite, NULL);

    // Draw the text
    sfRenderWindow_drawText(window, text, NULL);

    sfRenderWindow_display(window);
  }

  // Cleanup
  sfTexture_destroy(texture);
  sfSprite_destroy(sprite);
  sfFont_destroy(font);
  sfText_destroy(text);
  sfRenderWindow_destroy(window);

  return 0;
}
