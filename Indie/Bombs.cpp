#include "Character.h"

void place_bomb(Mesh bomb_mesh, game_t *game, Player bomberman, MyEventReceiver receiver)
{
    vector3df position = bomberman.getnode()->getPosition();
    int posx = round(position.X / 2) * 2;
    int posz = round(position.Z / 2) * 2;
    if (receiver.IsKeyDown(bomberman.getKeyBomb()) && game->map2D[posz / 2][posx / 2] == ' ') {
        Bomb bomb(bomb_mesh, "../media/Albedo2.png", game, bomberman.getPower());
        bomb.getnode()->setScale(vector3df(4, 4, 4));
        bomb.getnode()->setPosition(vector3df(posx, position.Y + 0.5, posz));
        game->map2D[posz / 2][posx / 2] = 'O';
        game->bombs.emplace_back(bomb);
    }
}

std::vector <Bomb> bomb_explosion_anim(std::vector <Bomb> explosions, f32 frameDeltaTime, game_t *game)
{
    static f32 time = 0;

    time += frameDeltaTime;
    for (int i = explosions.size() - 1; i >= 0; i--) {
        explosions.at(i).getTime() += frameDeltaTime;
       // printf("delta time = %f et time:%f\n", frameDeltaTime, explosions.at(i).getTime());
        if (time >= 0.1) {
            explosions.at(i).getnode()->setScale(explosions.at(i).getnode()->getScale() + vector3df(10, 10, 10) * frameDeltaTime);
        }
        else {
            explosions.at(i).getnode()->setScale(explosions.at(i).getnode()->getScale() - vector3df(10, 10, 10) * frameDeltaTime);
        }
        if (explosions.at(i).getTime() >= 0.5) {
            vector3df position = explosions.at(i).getnode()->getPosition();
            int posx = round(position.X / 2);
            int posz = round(position.Z / 2);
            if (game->map2D[posz][posx] == 'F')
                game->map2D[posz][posx] = ' ';
            explosions.at(i).getnode()->remove();
            explosions.erase(explosions.begin() + i);

        }
    }
    if (time >= 0.2)
        time = 0;
    return explosions;
}

std::vector <Bomb> bomb_explosion_create(game_t* game, std::vector <Bomb> explosions, int z, int x)
{
    x *= 2;
    z *= 2;

    Mesh explo_mesh("../media/explode.obj", game);
    Bomb explo_node(explo_mesh, "../media/fire.jpg", game, 0);
    explo_node.getnode()->setPosition(vector3df(x, 0, z));
    explosions.emplace_back(explo_node);
    game->map2D[z / 2][x / 2] = 'F';
    return (explosions);
}

char spawn_bonus(game_t* game, int x, int z, bool first)
{
    if (first)
        std::srand(std::time(nullptr));
    int rand = std::rand() % 100;
    Mesh bonus_mesh("../media/Bonus.obj", game);
    char bonus_char = ' ';

    if (rand < 30) {
        Node bonus(bonus_mesh, "../media/bonus_bomb.png", game);
        bonus.getnode()->setPosition(vector3df(z * 2, 1, x * 2));
        bonus.getnode()->setRotation(vector3df(90, 0, 0));
        game->bonus.emplace_back(bonus);
        bonus_char = 'b';
    }
    else if (rand < 60) {
        Node bonus(bonus_mesh, "../media/bonus_speed.png", game);
        bonus.getnode()->setPosition(vector3df(z * 2, 1, x * 2));
        bonus.getnode()->setRotation(vector3df(90, 0, 0));
        game->bonus.emplace_back(bonus);
        bonus_char = 's';
    }
    else if (rand < 90) {
        Node bonus(bonus_mesh, "../media/bonus_power.png", game);
        bonus.getnode()->setPosition(vector3df(z * 2, 1, x * 2));
        bonus.getnode()->setRotation(vector3df(90, 0, 0));
        game->bonus.emplace_back(bonus);
        bonus_char = 'p';
    }
    else if (rand == 99) {
        Node bonus(bonus_mesh, "../media/bonus.png", game);
        bonus.getnode()->setPosition(vector3df(z * 2, 1, x * 2));
        bonus.getnode()->setRotation(vector3df(90, 0, 0));
        game->bonus.emplace_back(bonus);
        bonus_char = 'w';
    }
    return (bonus_char);
}

void destroy_bonus(game_t* game, int x, int z)
{
    vector3df position(x, 0, z);
    int posx = round(position.X);
    int posz = round(position.Z);

    for (int i = 0; i < game->bonus.size(); i++) {
        position = game->bonus.at(i).getnode()->getPosition();
        if (round(position.X / 2) == posx && round(position.Z / 2) == posz) {
            game->bonus.at(i).getnode()->remove();
            game->bonus.erase(game->bonus.begin() + i);
        }
    }
}

std::vector <Bomb> bomb_explosion(game_t* game, Bomb bomb, int x, int z, static std::vector <Bomb> explosions)
{
    bool first = true;
    for (int i = 1; i <= bomb.getPower(); i++) { // gauche
        if (game->map2D[z][x - i] == '*') {
            explosions = bomb_explosion_create(game, explosions, z, x - i);
            game->map2D[z][x - i] = spawn_bonus(game, z, x - i, first);
            first = false;
            for (int i = 0; game->map2D[i]; i++) {
                printf("%s", game->map2D[i]);
            }
            printf("\n");
            break;
        } else if (game->map2D[z][x - i] == '#' || game->map2D[z][x - i] == 'O')
            break;
        else {
            game->map2D[z][x - i] = ' ';
            destroy_bonus(game, x - i, z);
            explosions = bomb_explosion_create(game, explosions, z, x - i);
        }
    }
    for (int i = 1; i <= bomb.getPower(); i++) { // droite
        if (game->map2D[z][x + i] == '*') {
            explosions = bomb_explosion_create(game, explosions, z, x + i);
            game->map2D[z][x + i] = spawn_bonus(game, z, x + i, first);
            first = false;
            break;
        }
        else if (game->map2D[z][x + i] == '#' || game->map2D[z][x + i] == 'O')
            break;
        else {
            game->map2D[z][x + i] = ' ';
            destroy_bonus(game, x + i, z);
            explosions = bomb_explosion_create(game, explosions, z, x + i);
        }
    }
    for (int i = 1;i <= bomb.getPower(); i++) { // haut
        if (game->map2D[z - i][x] == '*') {
            explosions = bomb_explosion_create(game, explosions, z - i, x);
            game->map2D[z - i][x] = spawn_bonus(game, z - i, x, first);
            first = false;
            for (int i = 0; game->map2D[i]; i++) {
                printf("%s", game->map2D[i]);
            }
            printf("\n");
            break;
        }
        else if (game->map2D[z - i][x] == '#' || game->map2D[z - i][x] == 'O')
            break;
        else {
            game->map2D[z - i][x] = ' ';
            destroy_bonus(game, x, z - i);
            explosions = bomb_explosion_create(game, explosions, z - i, x);
        }
    }
    for (int i = 1; i <= bomb.getPower(); i++) { // bas
        if (game->map2D[z + i][x] == '*') {
            explosions = bomb_explosion_create(game, explosions, z + i, x);
            game->map2D[z + i][x] = spawn_bonus(game, z + i, x, first);
            first = false;
            break;
        }
        else if (game->map2D[z + i][x] == '#' || game->map2D[z + i][x] == 'O')
            break;
        else {
            game->map2D[z + i][x] = ' ';
            destroy_bonus(game, x, z + i);
            explosions = bomb_explosion_create(game, explosions, z + i, x);
        }
    }
    explosions = bomb_explosion_create(game, explosions, z, x);
    return (explosions);
}

void update_bomb(game_t *game, f32 frameDeltaTime, std::vector <Node> *blocks, Mesh crate_mesh)
{
    vector3df position;
    static f32 time = 0;
    static std::vector <Bomb> explosions;

    time += frameDeltaTime;
    for (int i = 0; i < game->bombs.size(); i++) {
        position = game->bombs.at(i).getnode()->getPosition();
        int posx = round(position.X / 2);
        int posz = round(position.Z / 2);
        game->bombs.at(i).getTime() += frameDeltaTime;
        if (time >= 0.1) {
            game->bombs.at(i).getnode()->setScale(game->bombs.at(i).getnode()->getScale() + vector3df(0.1, 0.1, 0.1));
        }
        if (game->bombs.at(i).getTime() >= 2) {
            game->bombs.at(i).getnode()->remove();
            game->map2D[posz][posx] = ' ';
            explosions = bomb_explosion(game, game->bombs.at(i), posx, posz, explosions);
            *blocks = reloadMap(*blocks, crate_mesh, game);
            game->bombs.erase(game->bombs.begin() + i);
        }
        else if (game->bombs.at(i).getTime() >= 1.5) {
            game->bombs.at(i).getnode()->setMaterialTexture(0, game->driver->getTexture("../media/bomb_red.png"));
        } else if (game->bombs.at(i).getTime() >= 1)
            game->bombs.at(i).getnode()->setMaterialTexture(0, game->driver->getTexture("../media/bomb_orange.png"));
    }
    explosions = bomb_explosion_anim(explosions, frameDeltaTime, game);
    if (time >= 0.1)
        time = 0;
}