/**
* \file help.h
* Вспомогательный файл с функциями и переменными
**/


#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glut.h>

#define GL_CLAMP_TO_EDGE 0x812F
using namespace sf;

// Глобальные переменные



inline int counter = 0; // Счетчик
inline int a = 0; // Переменная для общего использования

inline int Mode = 2; // Режим игры

inline bool getblue = 0; // Флаг получения синего эффекта
inline bool getred = 0; // Флаг получения красного эффекта
inline bool activateblue = 0; // Флаг активации синего эффекта
inline bool activatered = 0; // Флаг активации красного эффекта
inline bool activatepurple = 0; // Флаг активации фиолетового эффекта
inline int domainusage = 0; // Использование домена

// Угол поворота камеры
float angleX, angleY;

// Константа PI
float PI = 3.141592;

// Размер блока
float size = 20.f;

// Массив блоков
bool mass[1200][1200][1200];

/**
 * Функция проверки, проверяет, что объект не за границами
 * \param[in] x координата объекта по x
 * \param[in] y координата объекта по y
 * \param[in] z координата объекта по z
 * \return false, если объект за границами. Если все верно, возвращает 1 или 0 (в зависимости от наличия блока в точке)
 */
bool check(int x, int y, int z)
{
    if ((x < 0) || (x >= 1200) ||
        (y < 0) || (y >= 1200) ||
        (z < 0) || (z >= 1200)) return false;

    return mass[x][y][z];
}

/**
 * Класс игрока
 */
class Player
{
public:
    float x, y, z;  // начальные координаты
    float dx, dy, dz; // смещение персонажа
    float w, h, d;  // ширина, высота, глубина
    int hp; // здоровье
    bool onGround; // на земле ли игрок
    float speed; // скорость

    /**
     * Конструктор игрока
     * \param[in] x0 начальная координата x
     * \param[in] y0 начальная координата y
     * \param[in] z0 начальная координата z
     * \param[in] hp0 начальное здоровье (по умолчанию 100)
     */
    Player(float x0, float y0, float z0, int hp0 = 100)
    {
        x = x0; y = y0; z = z0;
        hp = hp0;
        dx = 0; dy = 0; dz = 0;
        w = 5; h = 20; d = 5; speed = 5;
        onGround = false;
    }

    /**
     * Обновление положения игрока с проверкой на коллизию
     * \param[in] time время обновления
     */
    void update(float time)
    {
        // если не на земле, спускаем на землю
        if (!onGround) dy -= 2.0 * time;
        onGround = 0;

        x += dx * time;
        collision(dx, 0, 0);
        y += dy * time;
        collision(0, dy, 0);
        z += dz * time;
        collision(0, 0, dz);

        // обнуляем смещение
        dx = dz = 0;
    }

    /**
     * Функция для проверки коллизии
     * \param[in] Dx смещение по x
     * \param[in] Dy смещение по y
     * \param[in] Dz смещение по z
     */
    void collision(float Dx, float Dy, float Dz)
    {
        // проверка коллизии через переменные высоты, ширины и глубины
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

    /**
     * Считывание нажатий на клавиши, смещение подсчитывается по особой формуле
     */
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

    /**
     * Уменьшение здоровья игрока
     */
    void hit() {
        hp -= 1;
    }
};

/**
 * Класс врага
 */
class Enemy
{
public:
    float x, y, z;  // начальные координаты
    float dx, dy, dz; // смещение персонажа
    float w, h, d;  // ширина, высота, глубина
    int hp; // здоровье
    bool onGround; // на земле ли враг
    float speed; // скорость

    /**
     * Конструктор врага
     * \param[in] x0 начальная координата x
     * \param[in] y0 начальная координата y
     * \param[in] z0 начальная координата z
     */
    Enemy(float x0, float y0, float z0)
    {
        x = x0; y = y0; z = z0;
        dx = 0; dy = 0; dz = 0;
        w = 20; h = 20; d = 20; speed = 5;
        hp = 50;
        onGround = false;
    }

    /**
     * Обновление положения врага с проверкой на коллизию
     * \param[in] time время обновления
     */
    void update(float time)
    {
        // если не на земле, спускаем на землю
        if (!onGround) dy -= 1.5 * time;
        onGround = 0;

        x += dx * time;
        collision(dx, 0, 0);
        y += dy * time;
        collision(0, dy, 0);
        z += dz * time;
        collision(0, 0, dz);

        // обнуляем смещение
        dx = dz = 0;
    }

    /**
     * Функция для проверки коллизии
     * \param[in] Dx смещение по x
     * \param[in] Dy смещение по y
     * \param[in] Dz смещение по z
     */
    void collision(float Dx, float Dy, float Dz)
    {
        // проверка коллизии через переменные высоты, ширины и глубины
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

    // Функция для преследования игрока (закомментирована)
    // int chase(float px, float py, float pz, int php, int counter)
    // {
    //     return 1;
    // }
};

/**
 * Загрузка текстуры
 * \param[in] name путь к файлу изображения
 * \return идентификатор текстуры
 */
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

/**
 * Рисование куба с текстурами
 * \param[in] skybox массив текстур
 * \param[in] size размер куба
 * \param[in] xc координата x центра куба (по умолчанию 0)
 * \param[in] yc координата y центра куба (по умолчанию 0)
 * \param[in] zc координата z центра куба (по умолчанию 0)
 */
void createBox(GLuint skybox[], float size, float xc = 0, float yc = 0, float zc = 0)
{
    // Левая грань
    glBindTexture(GL_TEXTURE_2D, skybox[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 0); glVertex3f(size + xc, -size + yc, -size + zc);
    glTexCoord2f(1, 1); glVertex3f(size + xc, size + yc, -size + zc);
    glTexCoord2f(0, 1); glVertex3f(-size + xc, size + yc, -size + zc);
    glTexCoord2f(0, 0); glVertex3f(-size + xc, -size + yc, -size + zc);
    glEnd();

    // Передняя грань
    glBindTexture(GL_TEXTURE_2D, skybox[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 0); glVertex3f(size + xc, -size + yc, size + zc);
    glTexCoord2f(1, 1); glVertex3f(size + xc, size + yc, size + zc);
    glTexCoord2f(0, 1); glVertex3f(size + xc, size + yc, -size + zc);
    glTexCoord2f(0, 0); glVertex3f(size + xc, -size + yc, -size + zc);
    glEnd();

    // Задняя грань
    glBindTexture(GL_TEXTURE_2D, skybox[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 0); glVertex3f(-size + xc, -size + yc, size + zc);
    glTexCoord2f(1, 1); glVertex3f(-size + xc, size + yc, size + zc);
    glTexCoord2f(0, 1); glVertex3f(-size + xc, size + yc, -size + zc);
    glTexCoord2f(0, 0); glVertex3f(-size + xc, -size + yc, -size + zc);
    glEnd();

    // Правая грань
    glBindTexture(GL_TEXTURE_2D, skybox[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 0); glVertex3f(size + xc, -size + yc, size + zc);
    glTexCoord2f(1, 1); glVertex3f(size + xc, size + yc, size + zc);
    glTexCoord2f(0, 1); glVertex3f(-size + xc, size + yc, size + zc);
    glTexCoord2f(0, 0); glVertex3f(-size + xc, -size + yc, size + zc);
    glEnd();

    // Нижняя грань
    glBindTexture(GL_TEXTURE_2D, skybox[4]);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 1); glVertex3f(size + xc, -size + yc, -size + zc);
    glTexCoord2f(0, 1); glVertex3f(-size + xc, -size + yc, -size + zc);
    glTexCoord2f(0, 0); glVertex3f(-size + xc, -size + yc, size + zc);
    glTexCoord2f(1, 0); glVertex3f(size + xc, -size + yc, size + zc);
    glEnd();

    // Верхняя грань
    glBindTexture(GL_TEXTURE_2D, skybox[5]);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 0); glVertex3f(size + xc, size + yc, -size + zc);
    glTexCoord2f(1, 1); glVertex3f(size + xc, size + yc, size + zc);
    glTexCoord2f(0, 1); glVertex3f(-size + xc, size + yc, size + zc);
    glTexCoord2f(0, 0); glVertex3f(-size + xc, size + yc, -size + zc);
    glEnd();
}
