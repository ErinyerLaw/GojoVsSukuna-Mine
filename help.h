
#include <cmath>
#include <iostream>


#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glut.h>




#define GL_CLAMP_TO_EDGE 0x812F
using namespace sf;


inline float windowx = 1800;
inline float windowy = 1200;
inline float sens = 30;


inline int strengthe = 20;
inline int strengthp = 10;



inline int counter = 0;
inline int a = 0;


inline int Mode = 2;

inline bool getblue = 0;
inline bool getred = 0;
inline bool activateblue = 0;
inline bool activatered = 0;
inline bool activatepurple = 0;
inline int domainusage = 0;





//resolution

//main
float angleX, angleY; //угол поворота камеры






//help
float PI = 3.141592;//
float size = 20.f;
bool mass[1200][1200][1200]; //массив блоков


/**
* Функция проверки, проверяет, что объект не за границами
* \param[in] x координата объекта по x
* \param[in] y координата объекта по y
* \param[in] z координата объекта по z
* \return 0,если объект за границами. если все верно, возвращает 1 или 0 ( в зависимости от наличия блока в точке)
**/
bool check(int x, int y, int z)
{
    if ((x < 0) || (x >= 1200) ||
        (y < 0) || (y >= 1200) ||
        (z < 0) || (z >= 1200)) return false;

    return mass[x][y][z];
}



/**
* Класс игрока
* \param[in] x координата игока по x
* \param[in] y координата игока по y
* \param[in] z координата игока по z
**/
class Player
{
public:
    float x, y, z;  // начальные координаты
    float dx, dy, dz; // смещение персонажа
    float w, h, d;  // width, height, depth 
    int hp;
    bool onGround;
    float speed;

    Player(float x0, float y0, float z0, int hp0 = 100)
    {
        x = x0; y = y0; z = z0;
        hp = hp0;
        dx = 0; dy = 0; dz = 0;
        w = 5; h = 20; d = 5; speed = 5;
        onGround = false;
    }


    //обновление положения игрока с проверкой на коллизию
    void hit() {
        hp -= 1;
    }


    void update(float time)
    {
        //если не на земле, спускаем на землю
        if (!onGround) dy -= 2.0 * time;
        onGround = 0;


        x += dx * time;
        collision(dx, 0, 0);
        y += dy * time;
        collision(0, dy, 0);
        z += dz * time;
        collision(0, 0, dz);

        //обнуляем смещение
        dx = dz = 0;
    }

    void collision(float Dx, float Dy, float Dz)
    {
        //проверка коллизии через переменные высоты,ширины и глубины
        for (int X = (x - w) / size; X < (x + w) / size; X++)
            for (int Y = (y - h) / size; Y < (y + h) / size; Y++)
                for (int Z = (z - d) / size; Z < (z + d) / size; Z++)
                    if (check(X, Y, Z)) {
                        if (Dx > 0)  x = X * size - w;
                        if (Dx < 0)  x = X * size + size + w;
                        if (Dy > 0)  y = Y * size - h;
                        if (Dy < 0) { y = Y * size + size + h; onGround = true; dy = 0; }
                        if (Dz > 0)  z = Z * size - d;
                        if (Dz < 0)  z = Z * size + size + d;
                    }
    }



    //считывание нажатий на клаву, смещение подсчитывается по особой формуле
    void keyboard()
    {
        if (Keyboard::isKeyPressed(Keyboard::Space)) if (onGround) { onGround = false; dy = 12; };

        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            dx = -sin(angleX / 180 * PI) * speed;
            dz = -cos(angleX / 180 * PI) * speed;
        }

        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            dx = sin(angleX / 180 * PI) * speed;
            dz = cos(angleX / 180 * PI) * speed;
        }

        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            dx = sin((angleX + 90) / 180 * PI) * speed;
            dz = cos((angleX + 90) / 180 * PI) * speed;
        }

        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            dx = sin((angleX - 90) / 180 * PI) * speed;
            dz = cos((angleX - 90) / 180 * PI) * speed;
        }
        if (Keyboard::isKeyPressed(Keyboard::LShift))
        {
            speed = 10;
        }
        if (!Keyboard::isKeyPressed(Keyboard::LShift))
        {
            speed = 5;
        }
        if (Keyboard::isKeyPressed(Keyboard::H))
        {
            hp += 1;
        }


    }

};




/**
* Класс врага
**/
class Enemy
{
public:
    float x, y, z;  // начальные координаты
    float dx, dy, dz; // смещение персонажа
    float w, h, d;  // width, height, depth 
    int hp;
    bool onGround;
    float speed;


    Enemy(float x0, float y0, float z0)
    {
        x = x0; y = y0; z = z0;
        dx = 0; dy = 0; dz = 0;
        w = 20; h = 20; d = 20; speed = 5;
        hp = 50;
        onGround = false;
    }

    void update(float time)
    {
        //если не на земле, спускаем на землю
        if (!onGround) dy -= 1.5 * time;
        onGround = 0;

        x += dx * time;
        collision(dx, 0, 0);
        y += dy * time;
        collision(0, dy, 0);
        z += dz * time;
        collision(0, 0, dz);

        //обнуляем смещение
        dx = dz = 0;
    }


    void collision(float Dx, float Dy, float Dz)
    {
        //проверка коллизии через переменные высоты,ширины и глубины
        for (int X = (x - w) / size; X < (x + w) / size; X++)
            for (int Y = (y - h) / size; Y < (y + h) / size; Y++)
                for (int Z = (z - d) / size; Z < (z + d) / size; Z++)
                    if (check(X, Y, Z)) {
                        if (Dx > 0)  x = X * size - w;
                        if (Dx < 0)  x = X * size + size + w;
                        if (Dy > 0)  y = Y * size - h;
                        if (Dy < 0) { y = Y * size + size + h; onGround = true; dy = 0; }
                        if (Dz > 0)  z = Z * size - d;
                        if (Dz < 0)  z = Z * size + size + d;
                    }
    }
    /*
    int chase(float px,float py,float pz,int php,int counter) {
        if (5 < sqrt(pow(px + x, 2) + pow(pz + z, 2)) < 10) {

            if (x < px) {
                x += 0.5;
            }

            if (z < pz) {
                z += 0.5;
            }
            if (x > px) {
                x -= 0.5;
            }

            if (z > pz) {
                z -= 0.5;
            }
        }
    }*/

};








//подфункция для подгрузки текстур принимает путь к файлу и возвращает текстуру
//процедура взятия текстуры стандартная, далее ее надо привязывать к объектам

/**
* Функция для прогрузки текстуры принимает на вход путь к картинке
**/
GLuint LoadTexture(sf::String name)
{
    sf::Image image;
    if (!image.loadFromFile(name))
        return EXIT_FAILURE;

    image.flipVertically();

    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    //==================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return texture;
}





//проверка текстур
//std::string s{ "up.jpg" };

// проверка
//GLuint texture{ LoadTexture(s)};











//отрисовка блоков
/**
* Функция для отрисовки блоков
* /param[in] skybox[] массив из 6 картинок
* /param[in] size размер коробки
* /param[in] xc опционально расположение по x
* /param[in] yc опционально расположение по y
* /param[in] zc опционально расположение по z
**/
void createBox(GLuint skybox[], float size, float xc = 0, float yc = 0, float zc = 0)
{

    //в отрисовке слева привязка текстуры, справа отрисовка кватрата
    //и так для всех граней
    glBindTexture(GL_TEXTURE_2D, skybox[0]);
    glBegin(GL_QUADS);
    //front

    glTexCoord2f(0, 0);   glVertex3f(xc - size, yc - size, zc - size);
    glTexCoord2f(1, 0);   glVertex3f(xc + size, yc - size, zc - size);
    glTexCoord2f(1, 1);   glVertex3f(xc + size, yc + size, zc - size);
    glTexCoord2f(0, 1);   glVertex3f(xc - size, yc + size, zc - size);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, skybox[1]);
    glBegin(GL_QUADS);
    //back
    glTexCoord2f(0, 0); glVertex3f(xc + size, yc - size, zc + size);
    glTexCoord2f(1, 0); glVertex3f(xc - size, yc - size, zc + size);
    glTexCoord2f(1, 1); glVertex3f(xc - size, yc + size, zc + size);
    glTexCoord2f(0, 1); glVertex3f(xc + size, yc + size, zc + size);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, skybox[2]);
    glBegin(GL_QUADS);
    //left
    glTexCoord2f(0, 0); glVertex3f(xc - size, yc - size, zc + size);
    glTexCoord2f(1, 0); glVertex3f(xc - size, yc - size, zc - size);
    glTexCoord2f(1, 1); glVertex3f(xc - size, yc + size, zc - size);
    glTexCoord2f(0, 1); glVertex3f(xc - size, yc + size, zc + size);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, skybox[3]);
    glBegin(GL_QUADS);
    //right
    glTexCoord2f(0, 0); glVertex3f(xc + size, yc - size, zc - size);
    glTexCoord2f(1, 0); glVertex3f(xc + size, yc - size, zc + size);
    glTexCoord2f(1, 1); glVertex3f(xc + size, yc + size, zc + size);
    glTexCoord2f(0, 1); glVertex3f(xc + size, yc + size, zc - size);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, skybox[4]);
    glBegin(GL_QUADS);
    //bottom
    glTexCoord2f(0, 0); glVertex3f(xc - size, yc - size, zc + size);
    glTexCoord2f(1, 0); glVertex3f(xc + size, yc - size, zc + size);
    glTexCoord2f(1, 1); glVertex3f(xc + size, yc - size, zc - size);
    glTexCoord2f(0, 1); glVertex3f(xc - size, yc - size, zc - size);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, skybox[5]);
    glBegin(GL_QUADS);
    //top  		
    glTexCoord2f(0, 0); glVertex3f(xc - size, yc + size, zc - size);
    glTexCoord2f(1, 0); glVertex3f(xc + size, yc + size, zc - size);
    glTexCoord2f(1, 1); glVertex3f(xc + size, yc + size, zc + size);
    glTexCoord2f(0, 1); glVertex3f(xc - size, yc + size, zc + size);
    glEnd();

}


