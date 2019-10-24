#include "ECS.hpp"

void Component::init() {}
void Component::update() {}
void Component::draw() {}

Component::~Component() {}

Entity::Entity()  = default;
Entity::~Entity() = default;
void Entity::update() {
    for (auto &c : components)
        c->update();
}
void Entity::draw() {
    for (auto &c : components)
        c->draw();
}
bool Entity::isActive() const {
    return active;
}
void Entity::destroy() {
    active = false;
}

Manager::Manager()  = default;
Manager::~Manager() = default;
void Manager::update() {
    for (auto &e : entities)
        e->update();
}
void Manager::draw() {
    for (auto &e : entities)
        e->draw();
}

void Manager::refresh() {
    entities.erase(std::remove_if(std::begin(entities), std::end(entities),
                                  [](const std::unique_ptr<Entity> &mEntity) {
                                      return !mEntity->isActive();
                                  }),
                   std::end(entities));
}

Entity &Manager::addEntity() {
    Entity *e = new Entity();
    std::unique_ptr<Entity> uPtr{e};
    entities.emplace_back(std::move(uPtr));
    return *e;
}

// To add components
// player.addComponent<PositionComponent>();
// player.addComponent<SpriteComponent("assets/player.png");
