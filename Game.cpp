//
// Created by DELL on 5/18/2024.
//

#include "Game.h"

#include <iostream>

void Game::initVariable() {
    this->window = nullptr;
    this->endGame = false;
    this->points = 0;
    this->health = 20;
    this->enemySpawnTimerMax = 20.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 10;
    this->mouseHold = false;
}

void Game::initWindow() {
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode, "Qinh Qinh Game", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initFonts() {
    if (!this->font.loadFromFile("Dosis-Light.ttf")) {
        std::cout << "ERROR::GAME::INITFONTS::Fail to load font!" << "\n";
    }
}

void Game::initText() {
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(26);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}

void Game::initEnemies() {
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    // this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    // this->enemy.setOutlineColor((sf::Color::Green));
    // this->enemy.setOutlineThickness(1.f);
}

Game::Game() {
    this->initVariable();
    this->initWindow();
    this->initFonts();
    this->initText();
    this->initEnemies();
}

Game::~Game() {
    delete this->window;
}

const bool Game::running() const {
    return this->window->isOpen();
}

const bool Game::getEndGame() const {
    return this->endGame;
}

void Game::spawnEnemy() {
    // this->enemy.setPosition(
    //     static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
    //     static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y)));
    this->enemy.setPosition(
           static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
           0.f);

    int type = rand() %5;
    switch (type) {
        case 0:
            this->enemy.setSize(sf::Vector2f(30.f, 30.f));
            this->enemy.setFillColor(sf::Color::Magenta);
            break;
        case 1:
            this->enemy.setSize(sf::Vector2f(40.f, 40.f));
            this->enemy.setFillColor(sf::Color::Blue);
            break;
        case 2:
            this->enemy.setSize(sf::Vector2f(50.f, 50.f));
            this->enemy.setFillColor(sf::Color::Cyan);
            break;
        case 3:
            this->enemy.setSize(sf::Vector2f(60.f, 60.f));
            this->enemy.setFillColor(sf::Color::Red);
            break;
        case 4:
            this->enemy.setSize(sf::Vector2f(70.f, 70.f));
            this->enemy.setFillColor(sf::Color::Green);
            break;
        default:
            this->enemy.setSize(sf::Vector2f(80.f, 80.f));
            this->enemy.setFillColor(sf::Color::Yellow);
            break;
    }
    this->enemies.push_back(this->enemy);
}

void Game::pollEvents() {
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
        }
    }
}

void Game::updateMousePosition() {
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText() {
    std::stringstream ss;
    ss << "Points: " << this->points << "\n" << "Health: " << this->health << "\n";
    this->uiText.setString(ss.str());
}

void Game::updateEnemies() {
    if (this->enemies.size() < this->maxEnemies) {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 1.f;
    }

    for (int i = 0; i < this->enemies.size(); ++i) {
        this->enemies[i].move(0.f, 5.f);
        if (this->enemies[i].getPosition().y > this->window->getSize().y) {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!this->mouseHold) {
            this->mouseHold = true;
            bool deleted = false;
            for (size_t i = 0; i < this->enemies.size() && deleted == false; ++i) {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
                    if (this->enemies[i].getFillColor() == sf::Color::Magenta) {
                        this->points +=10;
                    } else if (this->enemies[i].getFillColor() == sf::Color::Blue) {
                        this->points +=7;
                    } else if (this->enemies[i].getFillColor() == sf::Color::Cyan) {
                        this->points +=5;
                    } else if (this->enemies[i].getFillColor() == sf::Color::Red) {
                        this->points +=3;
                    } else if (this->enemies[i].getFillColor() == sf::Color::Green) {
                        this->points +=1;
                    } else if (this->enemies[i].getFillColor() == sf::Color::Yellow) {
                        this->points +=1;
                    }
                    std::cout << "Points:" << this->points << "\n";
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                }
            }
        }
    } else {
        this->mouseHold = false;
    }
}

void Game::update() {
    this->pollEvents();
    if (!this->endGame) {
        this->updateMousePosition();
        this->updateEnemies();
        this->updateText();
    }
    if(this->health <= 0) {
        this->endGame = true;
    }
}

void Game::renderText(sf::RenderTarget& target) {
    target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target) {
    for (auto &e: this->enemies) {
        target.draw(e);
    }
}

void Game::render() {
    this->window->clear();
    this->renderEnemies(*this->window);
    this->renderText(*this->window);
    this->window->display();
}


