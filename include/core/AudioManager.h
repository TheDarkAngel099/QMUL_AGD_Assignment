#pragma once
#include "SFML/Audio.hpp"
#include <iostream>

class AudioManager 
{
public:
    /*
    
    Sound sources:
    1) Damage by qubodup Freesound. Available at: https://freesound.org/people/qubodup/sounds/211634/
    [Damage http://www.freesound.org/people/qubodup/sounds/211634/ by Iwan ‘qubodup’ Gabovitch http://freesound.org/people/qubodup under CC-BY 3.0 License http://creativecommons.org/licenses/by/3.0/legalcode]

    2) Magic sound 1.wav by Jomellejager Freesound. Available at: https://freesound.org/people/JomelleJager/sounds/252681/
    [Magic sound 1 https://freesound.org/people/JomelleJager/sounds/252681/ by JomelleJager https://freesound.org/people/JomelleJager/ under CC-BY 3.0 License https://creativecommons.org/licenses/by/3.0/legalcode]

    3) Pop.wav by Yottasounds Freesound. Available at: https://freesound.org/people/yottasounds/sounds/176727/
    [Pop https://freesound.org/people/yottasounds/sounds/176727/ by yottasounds https://freesound.org/people/yottasounds/ under CC-BY 3.0 License http://creativecommons.org/licenses/by/3.0/legalcode]
    
    */

    ~AudioManager() {};

    void FireSound()
    {
        if (!fireBuffer.loadFromFile("sound/Pop.wav"))
        {
            std::cout << "No Fire sound file found" << std::endl;
        }
        fireSound.setBuffer(fireBuffer);
        fireSound.play();
    }

    void PotionSound()
    {
        if (!potionBuffer.loadFromFile("sound/Collect.wav"))
        {
            std::cout << "No Potion sound file found" << std::endl;
        }
        potionSound.setBuffer(potionBuffer);
        potionSound.play();
    }

    void AxeSound()
    {
        if (!axeBuffer.loadFromFile("sound/Axe.flac"))
        {
            std::cout << "No Axe sound file found" << std::endl;
        }
        axeSound.setBuffer(axeBuffer);
        axeSound.play();
    }

private:
    sf::SoundBuffer fireBuffer;
    sf::SoundBuffer potionBuffer;
    sf::SoundBuffer axeBuffer;

    sf::Sound fireSound;
    sf::Sound potionSound;
    sf::Sound axeSound;
};

class Locator 
{
public:
    static AudioManager& getAudioManager()
    {
        static AudioManager instance;
        return instance;
    }
};