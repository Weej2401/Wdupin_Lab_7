#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

void Thud(PhysicsBodyCollisionResult result) {
    cout << "thud";
}

int main()
{
    RenderWindow window(VideoMode(800, 600), "Bounce");
    World world(Vector2f(0, 1));
    PhysicsCircle ball;
    ball.setCenter(Vector2f(400, 100));
    ball.setRadius(20);
    world.AddPhysicsBody(ball);
    float angle(22);
    PhysicsRectangle floor;
    floor.setSize(Vector2f(800, 20));
    floor.setCenter(Vector2f(400, 590));
    floor.setStatic(true);
    PhysicsRectangle ceiling;//code to generate the ceiling
    ceiling.setSize(Vector2f(800, 10));
    ceiling.setCenter(Vector2f(400, 5));
    ceiling.setStatic(true);
    PhysicsRectangle Lwall;
    Lwall.setSize(Vector2f(10, 600));
    Lwall.setCenter(Vector2f(5, 300));
    Lwall.setStatic(true);
    PhysicsRectangle Rwall;
    Rwall.setSize(Vector2f(10, 600));
    Rwall.setCenter(Vector2f(795, 300));
    Rwall.setStatic(true);
    PhysicsRectangle bangbox;//code to generate the center box
    bangbox.setSize(Vector2f(40, 30));
    bangbox.setCenter(Vector2f(400, 300));
    bangbox.setRotation(angle);
    bangbox.setStatic(true);
    

    
    int thudCount(0);
    int bangCount(0);
    floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount << endl;
        thudCount++;
    };
    bangbox.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
        cout << "bang " << bangCount + 1 << endl;
        bangCount++;
    };
    world.AddPhysicsBody(floor);
    world.AddPhysicsBody(ceiling);
    world.AddPhysicsBody(Lwall);
    world.AddPhysicsBody(Rwall);
    world.AddPhysicsBody(bangbox);

    Clock clock;
    Time lastTime(clock.getElapsedTime());
    while (bangCount < 3) {
        // calculate MS since last frame
        Time currentTime(clock.getElapsedTime());
        Time deltaTime(currentTime - lastTime);
        int deltaTimeMS(deltaTime.asMilliseconds());
        if (deltaTimeMS > 0) {
            world.UpdatePhysics(deltaTimeMS);
            lastTime = currentTime;
        }
        window.clear(Color(0, 0, 0));
        window.draw(ball);
        window.draw(floor);
        window.draw(ceiling);
        window.draw(Lwall);
        window.draw(Rwall);
        window.draw(bangbox);
        window.display();
        
    }
}
