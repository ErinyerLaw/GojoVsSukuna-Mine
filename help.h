/**
* \file help.h
* ��������������� ���� � ��������� � �����������
**/


#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glut.h>

#define GL_CLAMP_TO_EDGE 0x812F
using namespace sf;

// ���������� ����������



inline int counter = 0; // �������
inline int a = 0; // ���������� ��� ������ �������������

inline int Mode = 2; // ����� ����

inline bool getblue = 0; // ���� ��������� ������ �������
inline bool getred = 0; // ���� ��������� �������� �������
inline bool activateblue = 0; // ���� ��������� ������ �������
inline bool activatered = 0; // ���� ��������� �������� �������
inline bool activatepurple = 0; // ���� ��������� ����������� �������
inline int domainusage = 0; // ������������� ������

// ���� �������� ������
float angleX, angleY;

// ��������� PI
float PI = 3.141592;

// ������ �����
float size = 20.f;

// ������ ������
bool mass[1200][1200][1200];

/**
 * ������� ��������, ���������, ��� ������ �� �� ���������
 * \param[in] x ���������� ������� �� x
 * \param[in] y ���������� ������� �� y
 * \param[in] z ���������� ������� �� z
 * \return false, ���� ������ �� ���������. ���� ��� �����, ���������� 1 ��� 0 (� ����������� �� ������� ����� � �����)
 */
bool check(int x, int y, int z)
{
    if ((x < 0) || (x >= 1200) ||
        (y < 0) || (y >= 1200) ||
        (z < 0) || (z >= 1200)) return false;

    return mass[x][y][z];
}

/**
 * ����� ������
 */
class Player
{
public:
    float x, y, z;  // ��������� ����������
    float dx, dy, dz; // �������� ���������
    float w, h, d;  // ������, ������, �������
    int hp; // ��������
    bool onGround; // �� ����� �� �����
    float speed; // ��������

    /**
     * ����������� ������
     * \param[in] x0 ��������� ���������� x
     * \param[in] y0 ��������� ���������� y
     * \param[in] z0 ��������� ���������� z
     * \param[in] hp0 ��������� �������� (�� ��������� 100)
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
     * ���������� ��������� ������ � ��������� �� ��������
     * \param[in] time ����� ����������
     */
    void update(float time)
    {
        // ���� �� �� �����, �������� �� �����
        if (!onGround) dy -= 2.0 * time;
        onGround = 0;

        x += dx * time;
        collision(dx, 0, 0);
        y += dy * time;
        collision(0, dy, 0);
        z += dz * time;
        collision(0, 0, dz);

        // �������� ��������
        dx = dz = 0;
    }

    /**
     * ������� ��� �������� ��������
     * \param[in] Dx �������� �� x
     * \param[in] Dy �������� �� y
     * \param[in] Dz �������� �� z
     */
    void collision(float Dx, float Dy, float Dz)
    {
        // �������� �������� ����� ���������� ������, ������ � �������
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
     * ���������� ������� �� �������, �������� �������������� �� ������ �������
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
     * ���������� �������� ������
     */
    void hit() {
        hp -= 1;
    }
};

/**
 * ����� �����
 */
class Enemy
{
public:
    float x, y, z;  // ��������� ����������
    float dx, dy, dz; // �������� ���������
    float w, h, d;  // ������, ������, �������
    int hp; // ��������
    bool onGround; // �� ����� �� ����
    float speed; // ��������

    /**
     * ����������� �����
     * \param[in] x0 ��������� ���������� x
     * \param[in] y0 ��������� ���������� y
     * \param[in] z0 ��������� ���������� z
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
     * ���������� ��������� ����� � ��������� �� ��������
     * \param[in] time ����� ����������
     */
    void update(float time)
    {
        // ���� �� �� �����, �������� �� �����
        if (!onGround) dy -= 1.5 * time;
        onGround = 0;

        x += dx * time;
        collision(dx, 0, 0);
        y += dy * time;
        collision(0, dy, 0);
        z += dz * time;
        collision(0, 0, dz);

        // �������� ��������
        dx = dz = 0;
    }

    /**
     * ������� ��� �������� ��������
     * \param[in] Dx �������� �� x
     * \param[in] Dy �������� �� y
     * \param[in] Dz �������� �� z
     */
    void collision(float Dx, float Dy, float Dz)
    {
        // �������� �������� ����� ���������� ������, ������ � �������
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

    // ������� ��� ������������� ������ (����������������)
    // int chase(float px, float py, float pz, int php, int counter)
    // {
    //     return 1;
    // }
};

/**
 * �������� ��������
 * \param[in] name ���� � ����� �����������
 * \return ������������� ��������
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
 * ��������� ���� � ����������
 * \param[in] skybox ������ �������
 * \param[in] size ������ ����
 * \param[in] xc ���������� x ������ ���� (�� ��������� 0)
 * \param[in] yc ���������� y ������ ���� (�� ��������� 0)
 * \param[in] zc ���������� z ������ ���� (�� ��������� 0)
 */
void createBox(GLuint skybox[], float size, float xc = 0, float yc = 0, float zc = 0)
{
    // ����� �����
    glBindTexture(GL_TEXTURE_2D, skybox[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 0); glVertex3f(size + xc, -size + yc, -size + zc);
    glTexCoord2f(1, 1); glVertex3f(size + xc, size + yc, -size + zc);
    glTexCoord2f(0, 1); glVertex3f(-size + xc, size + yc, -size + zc);
    glTexCoord2f(0, 0); glVertex3f(-size + xc, -size + yc, -size + zc);
    glEnd();

    // �������� �����
    glBindTexture(GL_TEXTURE_2D, skybox[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 0); glVertex3f(size + xc, -size + yc, size + zc);
    glTexCoord2f(1, 1); glVertex3f(size + xc, size + yc, size + zc);
    glTexCoord2f(0, 1); glVertex3f(size + xc, size + yc, -size + zc);
    glTexCoord2f(0, 0); glVertex3f(size + xc, -size + yc, -size + zc);
    glEnd();

    // ������ �����
    glBindTexture(GL_TEXTURE_2D, skybox[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 0); glVertex3f(-size + xc, -size + yc, size + zc);
    glTexCoord2f(1, 1); glVertex3f(-size + xc, size + yc, size + zc);
    glTexCoord2f(0, 1); glVertex3f(-size + xc, size + yc, -size + zc);
    glTexCoord2f(0, 0); glVertex3f(-size + xc, -size + yc, -size + zc);
    glEnd();

    // ������ �����
    glBindTexture(GL_TEXTURE_2D, skybox[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 0); glVertex3f(size + xc, -size + yc, size + zc);
    glTexCoord2f(1, 1); glVertex3f(size + xc, size + yc, size + zc);
    glTexCoord2f(0, 1); glVertex3f(-size + xc, size + yc, size + zc);
    glTexCoord2f(0, 0); glVertex3f(-size + xc, -size + yc, size + zc);
    glEnd();

    // ������ �����
    glBindTexture(GL_TEXTURE_2D, skybox[4]);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 1); glVertex3f(size + xc, -size + yc, -size + zc);
    glTexCoord2f(0, 1); glVertex3f(-size + xc, -size + yc, -size + zc);
    glTexCoord2f(0, 0); glVertex3f(-size + xc, -size + yc, size + zc);
    glTexCoord2f(1, 0); glVertex3f(size + xc, -size + yc, size + zc);
    glEnd();

    // ������� �����
    glBindTexture(GL_TEXTURE_2D, skybox[5]);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 0); glVertex3f(size + xc, size + yc, -size + zc);
    glTexCoord2f(1, 1); glVertex3f(size + xc, size + yc, size + zc);
    glTexCoord2f(0, 1); glVertex3f(-size + xc, size + yc, size + zc);
    glTexCoord2f(0, 0); glVertex3f(-size + xc, size + yc, -size + zc);
    glEnd();
}
