#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "help.h"

// Test cases for the check function
TEST_CASE("Testing check function") {
    // Assuming mass is already defined and initialized properly


    SUBCASE("Coordinates within bounds") {
        mass[100][100][100] = true;
        CHECK(check(100, 100, 100) == true);
        CHECK(check(0, 0, 0) == false);
    }

    SUBCASE("Coordinates out of bounds") {
        CHECK(check(-1, 0, 0) == false);
        CHECK(check(1200, 0, 0) == false);
        CHECK(check(0, -1, 0) == false);
        CHECK(check(0, 1200, 0) == false);
        CHECK(check(0, 0, -1) == false);
        CHECK(check(0, 0, 1200) == false);
    }
}

// Test cases for the Player class
TEST_CASE("Testing Player class") {
    Player player(0, 0, 0);

    SUBCASE("Initial values") {
        CHECK(player.x == 0);
        CHECK(player.y == 0);
        CHECK(player.z == 0);
        CHECK(player.hp == 100);
        CHECK(player.dx == 0);
        CHECK(player.dy == 0);
        CHECK(player.dz == 0);
        CHECK(player.w == 5);
        CHECK(player.h == 20);
        CHECK(player.d == 5);
        CHECK(player.speed == 5);
        CHECK(player.onGround == false);
    }

    SUBCASE("Player hit") {
        player.hit();
        CHECK(player.hp == 99);
    }

    SUBCASE("Player update") {
        player.update(0);
        CHECK(player.x == 0);
        CHECK(player.y == 0);
        CHECK(player.z == 0);
    }
}

// Test cases for the Enemy class
TEST_CASE("Testing Enemy class") {
    Enemy enemy(0, 0, 0);

    SUBCASE("Initial values") {
        CHECK(enemy.x == 0);
        CHECK(enemy.y == 0);
        CHECK(enemy.z == 0);
        CHECK(enemy.hp == 50);
        CHECK(enemy.dx == 0);
        CHECK(enemy.dy == 0);
        CHECK(enemy.dz == 0);
        CHECK(enemy.w == 20);
        CHECK(enemy.h == 20);
        CHECK(enemy.d == 20);
        CHECK(enemy.speed == 5);
        CHECK(enemy.onGround == false);
    }

    SUBCASE("Enemy update") {
        enemy.update(0);
        CHECK(enemy.x == 0);
        CHECK(enemy.y == 0);
        CHECK(enemy.z == 0);
    }
}


TEST_CASE("Testing texture loading") {
    SUBCASE("Texture loading right image") {
        CHECK(LoadTexture("textures/domain.jpeg") == 0);
        CHECK(LoadTexture("textures/purple.jpeg") == 0);
        CHECK(LoadTexture("textures/go.jpeg") == 0);
        CHECK(LoadTexture("textures/jo.jpeg") == 0);
        CHECK(LoadTexture("textures/boss1.jpg") == 0);
        CHECK(LoadTexture("textures/boss2.jpg") == 0);
        CHECK(LoadTexture("textures/sukuna.jpeg") == 0);
    }
    SUBCASE("Texture loading non-existing image") {
        CHECK(LoadTexture("true.prk") == EXIT_FAILURE);
        CHECK(LoadTexture("something") == EXIT_FAILURE);
        CHECK(LoadTexture("that") == EXIT_FAILURE);
        CHECK(LoadTexture("doesn`t") == EXIT_FAILURE);
        CHECK(LoadTexture("exist") == EXIT_FAILURE);

    }

}