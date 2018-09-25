#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Player{
public:
    float x,y,w,h,dx,dy;  //кординаты игрока x и y высота и ширина
    float speed;
    int dir; //направления движения
    String  File; //файл с расширением
    Image image;
    Texture texture;
    Sprite sprite;

    Player(String F, float X, float Y, float W, float H){
        dx = 0; dy = 0; speed = 0; dir = 0;
        File = F;
        w = W;
        h = H;
        image.loadFromFile("foto/" + File);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        x = X; y = Y;
        sprite.setTextureRect(IntRect(0,0,w,h));
    }

    void update(float time){
        switch (dir){
            case 0: dx = speed; dy = 0; break;
            case 1: dx = -speed; dy = 0; break;
            case 2: dx = 0; dy = speed; break;
            case 3: dx = 0; dy = -speed; break;
        }

        x += dx*time;
        y += dy*time;

        speed = 0; //зануление скорости
        sprite.setPosition(x,y);
    }
};

int main() {
    RenderWindow window(sf::VideoMode(600, 600), "Mario"); //увеличили для удобства размер окна

    Player p("Marrio.png" ,0,10,124,124);

    float  CurrentFrame = 0;
    Clock clock;

    /*Texture herotexture;//создаем объект Texture (текстура)
    herotexture.loadFromFile("/home/milka404/2 КУРС/Mario/foto/Marrio.png");//загружаем картинку

    Sprite herosprite;//создаем объект Sprite(спрайт)
    herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)
    herosprite.setTextureRect(IntRect(0,10,124,124));
    herosprite.setPosition(200, 200);//задаем начальные координаты появления спрайта
    */

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

                /////// дижение //////////////
        if (Keyboard::isKeyPressed(Keyboard::Left) ||(Keyboard::isKeyPressed(Keyboard::A))) {
            p.dir = 1;
            p.speed = 0.1;
            CurrentFrame += 0.0001 * time;
            if (CurrentFrame > 1) CurrentFrame -= 1;
            p.sprite.setTextureRect(IntRect(124 * int(CurrentFrame), 115, 124, 124));
        }

        if (Keyboard::isKeyPressed(Keyboard::Right) ||(Keyboard::isKeyPressed(Keyboard::D))) {
            p.dir = 0;
            p.speed = 0.1;
            CurrentFrame += 0.0001 * time;
            if (CurrentFrame > 1) CurrentFrame -= 1;
            p.sprite.setTextureRect(IntRect(124 * int(CurrentFrame), 10, 124, 124));
        }

        if (Keyboard::isKeyPressed(Keyboard::Up) ||(Keyboard::isKeyPressed(Keyboard::W))) {
            p.dir = 3;
            p.speed = 0.1;
            CurrentFrame += 0.0001 * time;
            if (CurrentFrame > 1) CurrentFrame -= 1;
            p.sprite.setTextureRect(IntRect(124 * int(CurrentFrame), 10, 124, 124));
        }

        if (Keyboard::isKeyPressed(Keyboard::Down) ||(Keyboard::isKeyPressed(Keyboard::S))) {
            p.dir = 2;
            p.speed = 0.1;
            CurrentFrame += 0.0001 * time;
            if (CurrentFrame > 1) CurrentFrame -= 1;
            p.sprite.setTextureRect(IntRect(124 * int(CurrentFrame), 10, 124, 124));
        }

        p.update(time);

        window.clear();
        window.draw(p.sprite);//выводим спрайт на экран
        window.display();
    }

    return 0;
}