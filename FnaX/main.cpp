//Jest soczewka :o

#include <SFML/Graphics.hpp>
#include <iostream>

const std::string vertexShader = R"(
void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_MultiTexCoord0;
}
)";

const std::string fragmentShader = R"(
uniform sampler2D texture;
uniform vec2 resolution;
//uniform float curvature;

float map(float value, float min1, float max1, float min2, float max2) {
  return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

void main()
{
    vec2 uv = gl_TexCoord[0].xy / resolution;
    
    //orginalnie a = -+0.6 / power = 1
    float dist = pow(distance(gl_TexCoord[0].x, resolution.x / 2.0) / resolution.x, 2);
    
    uv.y = map(uv.y, 0, 1, 0.8 * dist, -0.8 * dist + 1);
    //uv.y = uv.y / 2 + 0.5;

    gl_FragColor = texture2D(texture, uv );
}
)";

sf::Vector2f mouseTracking(sf::Window& tmpWindow) {
    sf::Mouse mouse;
    sf::Vector2f direction;
    sf::Vector2i position = mouse.getPosition(tmpWindow);

    int size = tmpWindow.getSize().x;
    double relativePosition = position.x - ( size / 2 );

    //if (position.x > tmpWindow.getSize().x / 2) {
    //    direction.x = 5;
    //}
    //else {
    //    direction.x = -5;
    //}

    if (relativePosition > tmpWindow.getSize().x / 2 * 0.2 || relativePosition < tmpWindow.getSize().x / 2 * -0.2) {
        direction.x = relativePosition / ( size / 32 );
    } 
    //std::cout << direction.x << std::endl;
    double XD = ( position.x - (tmpWindow.getSize().x / 2) ) / tmpWindow.getSize().x;
    //double XD = relativePosition / size;
    //std::cout << relativePosition << std::endl;
    //std::cout << position.x - (tmpWindow.getSize().x / 2) << std::endl;
    std::cout << XD << std::endl;
    return direction;
}

void checkViewMove(sf::View& tmpView, sf::Vector2f tmpVector, int tmpTextureSizeX) {
    if (tmpView.getCenter().x < tmpTextureSizeX - tmpView.getSize().x / 2 && tmpVector.x > 0) { 
        tmpView.move(tmpVector); 
        if (tmpView.getCenter().x > tmpTextureSizeX - tmpView.getSize().x / 2) {
            tmpView.setCenter(tmpTextureSizeX - tmpView.getSize().x / 2, tmpView.getCenter().y);
        }
    }
    if (tmpView.getCenter().x > tmpView.getSize().x / 2 && tmpVector.x < 0) {
        tmpView.move(tmpVector);
        if (tmpView.getCenter().x < tmpView.getSize().x / 2) {
            tmpView.setCenter(tmpView.getSize().x / 2, tmpView.getCenter().y);
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Shader Example");
    window.setFramerateLimit(60);
    sf::RenderTexture preWindow;
    preWindow.create(1280, 720);
    sf::Texture preWindowTexture;
    sf::View view1(sf::FloatRect(0.f, 0.f, 1280.f, 720.f));

    sf::Shader shader;
    if (!shader.loadFromMemory(vertexShader, fragmentShader))
    {
        std::cerr << "Failed to load shader" << std::endl;
        return EXIT_FAILURE;
    }

    sf::Texture texture;
    if (!texture.loadFromFile("office.png"))
    {
        std::cerr << "Failed to load texture" << std::endl;
        return EXIT_FAILURE;
    }

    shader.setUniform("texture", sf::Shader::CurrentTexture);
    //shader.setUniform("resolution", sf::Vector2f(texture.getSize()));
    shader.setUniform("resolution", view1.getSize());
    //shader.setUniform("curvature", 5.5f); // Dostosuj wartość zakrzywienia według potrzeb

    sf::Sprite preWindowSprite;
    sf::Sprite sprite;
    sprite.setTexture(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        checkViewMove(view1, mouseTracking(window), texture.getSize().x);

        preWindow.clear();
        preWindow.draw(sprite);
        preWindow.setView(view1);
        preWindow.display();

        preWindowTexture = preWindow.getTexture();
        preWindowSprite.setTexture(preWindowTexture);

        window.clear();;
        window.draw(preWindowSprite, &shader);
        window.display();
    }

    return EXIT_SUCCESS;
}
