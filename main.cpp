/**
* \file main.cpp
* Основной файл
**/
#include "help.h"


//главная функция
int main()
{


    // create the window




    //правильно снизу
    sf::RenderWindow window(VideoMode(windowx, windowy), "Gojo vs Sukuna epic minecraft battle", Style::Default, ContextSettings(32));






    //параметры необходимые для правильной работы
    //test glubini
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);
    //rezhim matrici menyau potom chtob vsue bilo vidno
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //==================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================
    gluPerspective(90.f, 1.f, 1.f, 2000.f);
    //rezhim textur
    glEnable(GL_TEXTURE_2D);

    //vert sync
    window.setVerticalSyncEnabled(true);


    //ochistka buferov
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   

    ShowCursor(FALSE);






    /////////////////Карта высот/////////////////////////////////////

    //так подгружается начальная карта (в виде картинки)

    sf::Image im;  im.loadFromFile("textures/heightmap.png");

    for (int x = 0; x < 256; x++)
        for (int z = 0; z < 256; z++)
        {
            int c = im.getPixel(x, z).r / 15; //пиксель по красному цвету
            for (int y = 0; y < c; y++)
                if (y > c - 2) mass[x][y][z] = 1; //тут высота столбов блоков
        }



    ////////////////////////////////////////////////////////////



    //Текстуры............................................................................................................


    Texture t,th,tbh,tinv,tat,tgo,tjo,tsukuna,tblock,tpurple;
    t.loadFromFile("textures/cursor.png");
    Sprite s(t); 
    s.setOrigin(8, 8); 
    s.setPosition(windowx/2, windowy/2);
    s.setScale(5, 5);

    /* эту часть переноим в главный код
    th.loadFromFile("textures/hp.png");
    Sprite h(th);
    h.setOrigin(2, 10);
    h.setPosition(p.h, 30);
    h.setScale(p.h, 1);
    */

    th.loadFromFile("textures/hp.png");
    Sprite h(th);
    h.setOrigin(0, 10);
    h.setPosition(20, 30);

    tbh.loadFromFile("textures/gojohp.png");
    Sprite bh(tbh);
    bh.setOrigin(0, 10);
    bh.setPosition(20, 50);

    tinv.loadFromFile("textures/inventory.png");
    Sprite inventory(tinv);
    inventory.setOrigin(500, 175);
    inventory.setPosition(windowx / 2, windowy * 7 / 8 + 40);
    inventory.setScale(0.6, 0.6);


    tgo.loadFromFile("textures/go.png");
    Sprite go(tgo);
    go.setOrigin(150, 150);
    go.setPosition(windowx / 2 + 70, windowy * 7 / 8);
    go.setScale(0.35, 0.35);

    tjo.loadFromFile("textures/jo.png");
    Sprite jo(tjo);
    jo.setOrigin(150, 150);
    jo.setPosition(windowx / 2 + 210, windowy * 7 / 8);
    jo.setScale(0.35, 0.35);

    tsukuna.loadFromFile("textures/sukuna.jpeg");
    Sprite sukuna(tsukuna);
    sukuna.setOrigin(150, 150);
    sukuna.setPosition(windowx / 2 -90, windowy * 7 / 8);
    sukuna.setScale(0.35, 0.35);


    tpurple.loadFromFile("textures/purple.jpeg");
    Sprite purple(tpurple);
    purple.setOrigin(150, 150);
    purple.setPosition(windowx / 2 + 70, windowy * 7 / 8);
    purple.setScale(0.35, 0.35);


    GLuint box[6];

    
    box[0] = LoadTexture("textures/side.png");
    box[1] = LoadTexture("textures/side.png");
    box[2] = LoadTexture("textures/side.png");
    box[3] = LoadTexture("textures/side.png");
    box[4] = LoadTexture("textures/bottom.png");
    box[5] = LoadTexture("textures/top.png");

    GLuint lobotomy[6];


    lobotomy[0] = LoadTexture("textures/domain.jpeg");
    lobotomy[1] = LoadTexture("textures/domain.jpeg");
    lobotomy[2] = LoadTexture("textures/domain.jpeg");
    lobotomy[3] = LoadTexture("textures/domain.jpeg");
    lobotomy[4] = LoadTexture("textures/domain.jpeg");
    lobotomy[5] = LoadTexture("textures/domain.jpeg");


    /*
    box[0] = LoadTexture("textures/1.jpg");
    box[1] = LoadTexture("textures/2.jpg");
    box[2] = LoadTexture("textures/3.jpg");
    box[3] = LoadTexture("textures/4.jpg");
    box[4] = LoadTexture("textures/5.jpg");
    box[5] = LoadTexture("textures/6.jpg");
    */


    GLuint skybox[6];

    skybox[0] = LoadTexture("textures/skybox_front.png");
    skybox[1] = LoadTexture("textures/skybox_back.png");
    skybox[2] = LoadTexture("textures/skybox_left.png");
    skybox[3] = LoadTexture("textures/skybox_right.png");
    skybox[4] = LoadTexture("textures/skybox_bottom.png");
    skybox[5] = LoadTexture("textures/skybox_top.png");


    GLuint skybox2[6];

    skybox2[0] = LoadTexture("textures/one.jpg");
    skybox2[1] = LoadTexture("textures/one.jpg");
    skybox2[2] = LoadTexture("textures/one.jpg");
    skybox2[3] = LoadTexture("textures/one.jpg");
    skybox2[4] = LoadTexture("textures/one.jpg");
    skybox2[5] = LoadTexture("textures/one.jpg");


    GLuint boss1[6];

    boss1[0] = LoadTexture("textures/boss1.jpg");
    boss1[1] = LoadTexture("textures/boss1.jpg");
    boss1[2] = LoadTexture("textures/boss1.jpg");
    boss1[3] = LoadTexture("textures/boss1.jpg");
    boss1[4] = LoadTexture("textures/boss1.jpg");
    boss1[5] = LoadTexture("textures/boss1.jpg");

    GLuint boss2[6];

    boss2[0] = LoadTexture("textures/boss2.jpg");
    boss2[1] = LoadTexture("textures/boss2.jpg");
    boss2[2] = LoadTexture("textures/boss2.jpg");
    boss2[3] = LoadTexture("textures/boss2.jpg");
    boss2[4] = LoadTexture("textures/boss2.jpg");
    boss2[5] = LoadTexture("textures/boss2.jpg");








    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




    sf::Clock clock;
    bool mLeft = 0, mRight = 0; // mouse buttons
    Player p(100, 300, 100);//игрок и координаты

    Enemy e(500, 200, 500);


    // run the main loop
    bool running = true;
    while (running) {



        float time = clock.getElapsedTime().asMilliseconds();
        clock.restart();
        time = time / 50;
        if (time > 3) time = 3;






        ///////////////////EVENTS////////////////////////
        sf::Event event;
        while (window.pollEvent(event))
        {   //если окно закрыто
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;

            }


            //добавляем выключение при нажатии escape
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                running = false;


            //добавляем считывание нажатия клавиш
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.key.code == sf::Mouse::Right) mRight = 1;
                if (event.key.code == sf::Mouse::Left)  mLeft = 1;
            }

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num1))
                Mode = 1;

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num2))
                Mode = 2;

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num3))
                Mode = 3;

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num4))
                Mode = 4;




        }
        ///////////////////////////////////////////////////////////////////////////////////////////



//ocist buff
glClear(GL_DEPTH_BUFFER_BIT);

//obnov vvoda i mesta
p.keyboard();
p.update(time);
if (e.hp > 0) {
    e.update(time);
}
        
        




///////////////////////////////////////////////////КУРСОР///////////////////////////
POINT mousexy;
GetCursorPos(&mousexy);
int xt = window.getPosition().x + 400;
int yt = window.getPosition().y + 300;

angleX += (xt - mousexy.x) / sens; //sens — чувствительность 
angleY += (yt - mousexy.y) / sens;

//вводятся ограничения поворота по y чтобы нельзя было сальто сделать

if (angleY < -89.0) { angleY = -89.0; }
if (angleY > 89.0) { angleY = 89.0; }

SetCursorPos(xt, yt);
//.....................................................................................................................................................

   
            //Проверка расстояния между врагом и игроком и урон

if (e.hp > 0) {


    if (sqrt(pow(p.x - e.x, 2) + pow(p.z - e.z, 2)) < 100 and counter % 100 == 0) {
        p.hp -= strengthe;
    

    }



    if (p.hp <= 0) {
        running = false;
        //std::cout << "bro lost to strongest";
    }





    a = sqrt(pow(p.x - e.x, 2) + pow(p.z - e.z, 2)); //расстояние между врагом и игроком


    if (a < 300 and a>100) {

     


        if (e.x < p.x) {
            e.x += 0.5;
        }

        if (e.z < p.z) {
            e.z += 0.5;
        }
        if (e.x > p.x) {
            e.x -= 0.5;
        }

        if (e.z > p.z) {
            e.z -= 0.5;
        }
    }
}
    //---------------------------------------------------------------------------------------------------------------------------------



        //полоска хп

        h.setScale(p.hp, 1);

            


           ////-------------------------------ставить ломать блоки------------в мод 2 урон--------------------------------------


            if (Mode == 1) {


                if (mRight or mLeft)
                {
                    float x = p.x;
                    float y = p.y + p.h / 2;
                    float z = p.z;

                    int X, Y, Z, oldX = 0, oldY = 0, oldZ = 0;
                    int dist = 0;




                    while (dist < 120)  // радиус действия
                    {
                        dist++;


                        //просчитывается точка, куда мы смотрим и высчитывается блок, с которым мы работаем
                        x += -sin(angleX / 180 * PI);  
                        X = x / size;
                        y += tan(angleY / 180 * PI);    
                        Y = y / size;
                        z += -cos(angleX / 180 * PI);    
                        Z = z / size;



                        //тут в массиве заменяем значения блока на ноль если ломаем и задаем новые значения 1 если ставим
                        
                        if (check(X, Y, Z))
                            if (mLeft) { mass[X][Y][Z] = 0; break; }
                            else { mass[oldX][oldY][oldZ] = 1; break; }

                        oldX = X; oldY = Y; oldZ = Z;
                        
                    }
                }
            }

            if (Mode == 2) {
                if (mLeft or mRight) {
                    if (mLeft==true and a < 150) {
                        e.hp -= strengthp;

                    }
                    if (mRight) {
                        e.hp += 20;

                    }
                }
            }

            if (Mode == 3 and getblue == 1) {
                if (mLeft) { activateblue = 1; }

            }

            if (Mode == 3 and activatered == 1 and activateblue == 1) {
                if (mLeft) { activatepurple = 1; }
            }

            if (Mode == 4 and getred == 1) {
                if (mLeft) { activatered = 1; }
            }
                    /////////////////

mLeft = mRight = 0;





        //Две строчки снизу исправили проблему с уплывающей камерой, пока непонятно как
        //glClear(GL_DEPTH_BUFFER_BIT);

glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
/////


//==================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================
gluLookAt(p.x, p.y + p.h / 2, p.z, p.x - sin(angleX / 180 * PI), p.y + p.h / 2 + (tan(angleY / 180 * PI)), p.z - cos(angleX / 180 * PI), 0, 1, 0);





    ///............................Отрисовка коробок.......................................


    int R = 30;

    int X = p.x / size;
    int Y = p.y / size;
    int Z = p.z / size;

    for (int x = X - R; x < X + R; x++)
        for (int y = 0; y < 25; y++)
            for (int z = Z - R; z < Z + R; z++)
            {
                if (!check(x, y, z)) continue;

                glTranslatef(size * x + size / 2, size * y + size / 2, size * z + size / 2);
                if (activatepurple == 0) {
                    createBox(box, size / 2);
                }
                if (activatepurple == 1) {
                    createBox(lobotomy, size / 2);
                }
                glTranslatef(-size * x - size / 2, -size * y - size / 2, -size * z - size / 2);
            }





    ////........................................................................................









            // clear the buffers

            //glClear(GL_DEPTH_BUFFER_BIT);
            //glClear(GL_COLOR_BUFFER_BIT);




            // draw... рисуются объекты здесь(после очистки буфера)




        //createBox(box, 1000);
        glTranslatef(p.x, p.y, p.z);
        if (activatepurple == 0) {
            createBox(skybox, 1000);
        }
        if (activatepurple == 1) {
            createBox(skybox2, 1000);
        }
        glTranslatef(-p.x, -p.y, -p.z);

        
        counter += 1;
        


        if (counter > 700) {
            counter = 0;
            //std::cout << p.hp;
            //std::cout << p.x << 100000;
            //std::cout << p.y << 100000;
            //std::cout<< p.z<< 1000000;
        }

        if (activatepurple == 1) {
            domainusage += 1;
            if (domainusage > 500) {
                activatepurple = 0;
                domainusage = 0;
            }
        }


        if (p.y < -100) {
            p.y = 2000;
        }

        if (e.hp > 0) {
            createBox(boss1, 20, e.x, e.y, e.z);
            bh.setScale(e.hp, 1);
            getblue = 0;
            getred = 0;
        }

        if (e.hp <= 0) {
            createBox(boss2, 20, e.x, e.y, e.z);
            bh.setScale(1, 1);
            getblue = 1;
            getred = 1;
        }


        //ниже картинки отрисовываем


        window.pushGLStates();
        window.draw(s);      //рисуем курсор
        window.draw(h);
        window.draw(bh);
        window.draw(inventory);
        if (getblue == 1 and activateblue == 0) {
            window.draw(go);
        }
        if (getred == 1 and activatered == 0){
            window.draw(jo);
        }
        if (activateblue == 1 and activatered == 1) {
            window.draw(purple);
        }
        window.draw(sukuna);
        window.popGLStates();


        
       
        

       


        //Очищаем буфер цвета и глубины чтобы все правильно отрисовывалось









        //Ниже проверки работы программ
        //GLuint tex[1];

        //tex[0] = texture;

        //createBox(tex, 10);

        //DrawCube(box, 10);
       

        //DrawCube(0.4, 0, -0.2, 0.2);
        //DrawCube(0.4, 0.4, -0.2, 0.2);
        //Крутим кубики для проверки
        //Пределы коробки от -1 до 1, того что происходит за ней не видно << !!!
        //glRotatef(0.1, 1, 1, 1);
        //<< !!! нужно импрортировать новую библиотеку 


        // end the current frame (internally swaps the front and back buffers)
        window.display();

    }

    // release resources...

    return 0;
}
