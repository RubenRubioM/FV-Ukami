#include <SFML/Graphics.hpp>
#include "AnimationSprite.h"
#include <iostream>

int main()
{
    // setup window
    sf::Vector2i screenDimensions(800,600);
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Dash animation");
    window.setFramerateLimit(60);

    // load texture (spritesheet)
    sf::Texture textureMoveRight;
    textureMoveRight.loadFromFile("right.png");

    sf::Texture textureMoveLeft;
    textureMoveLeft.loadFromFile("left.png");

    sf::Texture textureDashRight;
    textureDashRight.loadFromFile("dash_right.png");

    sf::Texture textureDashLeft;
    textureDashLeft.loadFromFile("dash_left.png");

    // set up the animations for all four directions (set spritesheet and push frames)
    Animation walkingAnimationLeft;
    walkingAnimationLeft.setSpriteSheet(textureMoveLeft);
    walkingAnimationLeft.addFrame(sf::IntRect(750, 0, 150, 90));
    walkingAnimationLeft.addFrame(sf::IntRect(600, 0, 150, 90));
    walkingAnimationLeft.addFrame(sf::IntRect(450, 0, 150, 90));
    walkingAnimationLeft.addFrame(sf::IntRect(300, 0, 150, 90));
    walkingAnimationLeft.addFrame(sf::IntRect(150, 0, 150, 90));
    walkingAnimationLeft.addFrame(sf::IntRect(0, 0, 150, 90));

    Animation walkingAnimationRight;
    walkingAnimationRight.setSpriteSheet(textureMoveRight);
    walkingAnimationRight.addFrame(sf::IntRect(0, 0, 150, 90));
    walkingAnimationRight.addFrame(sf::IntRect(150, 0, 150, 90));
    walkingAnimationRight.addFrame(sf::IntRect(300, 0, 150, 90));
    walkingAnimationRight.addFrame(sf::IntRect(450, 0, 150, 90));
    walkingAnimationRight.addFrame(sf::IntRect(600, 0, 150, 90));
    walkingAnimationRight.addFrame(sf::IntRect(750, 0, 150, 90));

    Animation dashRight;
    dashRight.setSpriteSheet(textureDashRight);
    dashRight.addFrame(sf::IntRect(0, 0, 120, 104));
    dashRight.addFrame(sf::IntRect(0, 0, 120, 104));


    Animation dashLeft;
    dashLeft.setSpriteSheet(textureDashLeft);
    dashLeft.addFrame(sf::IntRect(0, 0, 120, 104));
    dashLeft.addFrame(sf::IntRect(0, 0, 120, 104));

    Animation* currentAnimation = &walkingAnimationRight;
    // set up AnimatedSprite
    AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
    animatedSprite.setPosition(sf::Vector2f(screenDimensions / 2));

    sf::Clock frameClock;

    float speed = 80.f;
    bool noKeyWasPressed = true;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        sf::Time frameTime = frameClock.restart();

        // if a key was pressed set the correct animation and move correctly
        sf::Vector2f movement(0.f, 0.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            currentAnimation = &walkingAnimationLeft;
            movement.x -= speed;
            noKeyWasPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            currentAnimation = &walkingAnimationRight;
            movement.x += speed;
            noKeyWasPressed = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            sf::Clock clock;

            if(currentAnimation == &walkingAnimationRight){
                currentAnimation = &dashRight;
                movement.x += +1350;
            }
            noKeyWasPressed = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if(currentAnimation == &walkingAnimationLeft){
                currentAnimation = &dashLeft;
                movement.x += -1350;
            }
            noKeyWasPressed = false;
        }

        animatedSprite.play(*currentAnimation);
        animatedSprite.move(movement * frameTime.asSeconds());

        // if no key was pressed stop the animation
        if (noKeyWasPressed)
        {
            animatedSprite.stop();
        }
        noKeyWasPressed = true;

        // update AnimatedSprite
        animatedSprite.update(frameTime);

        // draw
        window.clear();
        window.draw(animatedSprite);
        window.display();
    }

    return 0;
}
