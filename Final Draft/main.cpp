#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>
#include <map>
#include <unordered_map>
#include "Graph.h"
#include <set>
#include <queue>
#include <algorithm>
#include <stack>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <SFML/Graphics.hpp>

using namespace std::chrono;

typedef high_resolution_clock Clock;


using namespace std;

struct Movie {
    string title;
    int keyCount;
    string date;
};

//create a vector with the keywords of the source
void splitThestring(string curr, vector<string>& keywords) {
    string word = "";
    for (int i = 0; i < curr.length(); ++i) {
        if (curr[i] == ' ') {
            keywords.push_back(word);
            word = "";
        }
        else {
            word.push_back(curr[i]);
        }
    }
    keywords.push_back(word);
}

void printContents(vector<string> keywords) {
    for (int i = 0; i < keywords.size(); ++i) {
        cout << keywords[i] << endl;
    }
}

//create a vector with keywords of the other movies to compare with the source
void splitString(string curr, vector<string>& newLine) {
    string word = "";
    for (int i = 0; i < curr.length(); ++i) {
        if (curr[i] == ' ') {
            newLine.push_back(word);
            word = "";
        }
        else {
            word.push_back(curr[i]);
        }
    }
    newLine.push_back(word);
}

void print(vector<string> newLine) {
    for (int i = 0; i < newLine.size(); ++i) {
        cout << newLine[i] << endl;
    }
}

//bfs algorithm for to find most similar movies
vector<string> bfsMostSimilar(const Graph& graph, string src, unordered_map <string, int> movieMap, int maxKeywords) {
    int j = 0;
    int keywordVal;
    int indexVal = 0;
    int iterCounter = 0;
    set<string> verticesUsed;
    queue<string> queueOfVertices;
    vector<string>leastSimMovies;
    string currentVertex;
    vector<string> mostSimMovies;
    verticesUsed.insert(src);
    queueOfVertices.push(src);
    while (!queueOfVertices.empty()) {
        //start at the source movie
        currentVertex = queueOfVertices.front();
        queueOfVertices.pop();

        vector<string> vertexNeighbors = graph.adjList[movieMap[currentVertex]];
        for (string theVertex : vertexNeighbors) {
            if (verticesUsed.count(theVertex) == 0) {
                verticesUsed.insert(theVertex);
                queueOfVertices.push(theVertex);
                ++iterCounter;
            }
            if (iterCounter == 1 && movieMap[currentVertex] != maxKeywords) {
                iterCounter = 0;
                break;
            }
        }

        keywordVal = movieMap[currentVertex];

        if (keywordVal == maxKeywords) {
            //while (keywordVal > 0) {
            for (int i = 0; i < graph.adjList[keywordVal - 1].size(); i++) {
                mostSimMovies.push_back(graph.adjList[maxKeywords - 1][i]);
                if (mostSimMovies.size() == 10) {
                    return mostSimMovies;
                }

            }
            break;
        }

    }
    return mostSimMovies;
}

//bfs algorithm to find least similar movies
vector<string> bfsLeastSimilar(const Graph& graph, string src, unordered_map <string, int> movieMap, int maxKeywords) {
    int j = 0;
    int keywordVal;
    int indexVal = 0;
    set<string> verticesUsed;
    queue<string> queueOfVertices;
    vector<string>leastSimMovies;
    vector<string> results;
    string currentVertex;
    verticesUsed.insert(src);
    queueOfVertices.push(src);
    while (!queueOfVertices.empty()) {
        currentVertex = queueOfVertices.front();

        queueOfVertices.pop();
        vector<string> vertexNeighbors = graph.adjList[movieMap[currentVertex]];
        if (movieMap[currentVertex] == 0) {
            for (int i = 0; i < vertexNeighbors.size(); ++i) {
                leastSimMovies.push_back(vertexNeighbors[i]);
                if (leastSimMovies.size() == 10)
                    return leastSimMovies;
            }
        }
    }
    return leastSimMovies;;
}

//dfs algorithm to find most similar movies
vector<string> dfsMostSimilar(const Graph& graph, string src, unordered_map <string, int> movieMap, int maxKeywords) {
    int j = 0;
    int keywordVal;
    int indexVal = 0;
    int iterCounter = 0;
    set<string> verticesUsed;
    stack<string> stackOfVertices;
    vector<string> leastSimMovies;
    vector<string> dfsMost;
    string currentVertex;
    verticesUsed.insert(src);
    stackOfVertices.push(src);
    while (!stackOfVertices.empty()) {
        currentVertex = stackOfVertices.top();

        stackOfVertices.pop();
        vector<string> vertexNeighbors = graph.adjList[movieMap[currentVertex]];
        for (string theVertex : vertexNeighbors) {
            if (verticesUsed.count(theVertex) == 0) {
                verticesUsed.insert(theVertex);
                stackOfVertices.push(theVertex);
                ++iterCounter;
            }
            if (iterCounter == 1 && movieMap[currentVertex] != maxKeywords) {
                iterCounter = 0;
                break;
            }
        }

        keywordVal = movieMap[currentVertex];
        if (keywordVal == maxKeywords) {
            for (int i = 0; i < graph.adjList[keywordVal - 1].size(); i++) {
                dfsMost.push_back(graph.adjList[maxKeywords - 1][i]);
                if (dfsMost.size() == 10) {
                    return dfsMost;
                }
            }
            break;
        }
    }
    return dfsMost;
}

//dfs algorithm to find least similar movies
vector <string> dfsLeastSimilar(const Graph& graph, string src, unordered_map <string, int> movieMap, int maxKeywords) {
    int j = 0;
    int keywordVal;
    int indexVal = 0;
    set<string> verticesUsed;
    stack<string> stackOfVertices;
    vector<string> leastSimMovies;
    vector<string> dfsLeast;
    string currentVertex;
    verticesUsed.insert(src);
    stackOfVertices.push(src);
    while (!stackOfVertices.empty()) {
        currentVertex = stackOfVertices.top();

        stackOfVertices.pop();
        vector<string> vertexNeighbors = graph.adjList[movieMap[currentVertex]];
        if (movieMap[currentVertex] == 0) {
            for (int i = 0; i < vertexNeighbors.size(); ++i) {
                leastSimMovies.push_back(vertexNeighbors[i]);
                if (leastSimMovies.size() == 10)
                    return leastSimMovies;
            }
        }

    }
    return dfsLeast;
}


int main() {
    ////////////////////////////////////////////////////////////////////////////////////////INITIAILZIE VARIABLES////////////////////////////////////////////////////////////////
    Movie practice;
    string input;
    string curr;
    string key;
    int value = 0;
    vector<Movie*> allMovies;
    unordered_map <string, int> movieMap;
    int count = 0;
    string place;
    int off;
    string key1;
    string key2;
    Graph graph;
    vector <string> keywords;
    vector <string> newLine;
    vector<string> temp;
    int distTosource = 1;
    int maxKeywords = 0;
    vector <string> bfs1;
    vector <string> bfs2;
    vector <string> dfs1;
    vector <string> dfs2;
    vector<string> algoReturn;

    //////////////////////////////////////////////CSV FILE READING FUNCTIONALITY, CURRENTLY NOT UTILIZED BUT WOULD BE IF SUFFICIENTLY LARGE DATA SET WAS FOUND, COULD BE USED INSTEAD OF THE RANDOM NUMBER GENERATION
    /*ifstream someFile("FILE NAME HERE");
    string line;
    bool found = false;
    if (someFile.is_open()) {
        while (getline(someFile, line, ',')) {
            if (line == input) {
                //cout << line << '\n';
                practice.title = line;
                found = true;
                (getline(someFile, line, ','));
                splitThestring(line, keywords);
                printContents(keywords);
                getline(someFile, line, ',');
                practice.date = line;
                movieMap.emplace(practice.title, 0);
                break;
            }
            getline(someFile, line);
        }
        if (found == false) {
            cout << "movie is not found";
            return 0;
        }

        someFile.clear();
        someFile.seekg(0);
        while (getline(someFile, line, ',')) {
            key = line;
            if (line == practice.title) {
                getline(someFile, line);
            }
            else if (line != practice.title) {
                getline(someFile, line, ',');
                newLine.clear();
                splitString(line, newLine);
                print(newLine);
                count = 0;
                for (int i = 0; i < keywords.size(); i++) {
                    for (int j = 0; j < newLine.size(); j++) {
                        key1 = keywords[i];
                        key2 = newLine[j];
                        if (key1 == key2) {
                            count++;
                        }
                    }
                }
                value = count;
                movieMap.emplace(key, value);
                getline(someFile, line);
            }
        }
        someFile.close();
    }
    else {
        cout << "file is not open";
    }*/
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // add in all of the movies and use random names
    char letters[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' ' };
    srand(time(NULL));

    /////////////////////////////////////////////////////////////// //PRELOADED  MOVIES///////////////////////////////////////////////////////////////////////////////
    movieMap.emplace("Avengers", 7);
    movieMap.emplace("Avatar", 7);
    movieMap.emplace("Avatar The Last Airbender", 7);
    movieMap.emplace("Arcane", 7);
    movieMap.emplace("Breaking Bad", 7);
    movieMap.emplace("Pixels", 7);
    movieMap.emplace("Band Of Brothers", 7);
    movieMap.emplace("Game Of Thrones", 7);
    movieMap.emplace("Parasite", 7);
    movieMap.emplace("Tenet", 7);
    movieMap.emplace("Ironman", 7);
    movieMap.emplace("Spiderman", 7);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    ///////////////////////////////////////////////////////////CREATING 100,000 DATA POINTS//////////////////////////////////////////////////////////////////////////
    for (int i = 0; i < 100000; i++)
    {
        Movie* temp = new Movie;
        int randomSize = rand() % 20 + 10;
        string name = "";
        for (int j = 0; j < randomSize; j++)
        {
            int randomL = rand() % 27;
            name = name + letters[randomL];
        }
        int randomKeyV = rand() % 7 + 1;
        int randomDate = rand() & 2021 + 1960;
        string date_ = to_string(randomDate);
        temp->keyCount = randomKeyV;
        temp->title = name;
        temp->date = date_;
        allMovies.push_back(temp);
        movieMap.emplace(name, randomKeyV);
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////ADDING TO THE GRAPH//////////////////////////////////////////////////////////////////////
    auto iter = movieMap.begin();
    while (distTosource < 1000) {
        for (; iter != movieMap.end(); ++iter) {
            if (iter->second > maxKeywords) {
                maxKeywords = iter->second;
            }
            if (iter->second == distTosource) {
                temp.push_back(iter->first);
            }

        }
        graph.adjList.push_back(temp);
        temp.clear();
        ++distTosource;
        iter = movieMap.begin();
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    string CurrentScene = "home"; //VARIABLE TO KEEP TRACK OF CURRENT SCREEN BEING DISPLAYED

    sf::RenderWindow window(sf::VideoMode(1200, 800), "Movie Magic"); //WINDOW THE UI IS BUILD ON
    window.setKeyRepeatEnabled(true);

    //////////////////////////////////////////////////////////////////////////////COLORS///////////////////////////////////////////////////////////////////////////////
    const sf::Color& backGroundColor = sf::Color(200, 200, 200, 255);
    const sf::Color& buttonColor = sf::Color(220, 220, 220, 255);
    const sf::Color& grey = sf::Color(69, 69, 69, 255);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////DRAWING RECTANGLES////////////////////////////////////////////////////////////////////////////
    //HOME SCREEN BUTTONS
    sf::RectangleShape homeB1(sf::Vector2f(400.f, 150.f));
    sf::RectangleShape homeB2(sf::Vector2f(400.f, 150.f));
    sf::RectangleShape searchBar(sf::Vector2f(1000.f, 75.f));


    //SCREEN 2 BUTTONS
    sf::RectangleShape chooseB1(sf::Vector2f(700.f, 75.f));
    sf::RectangleShape chooseB2(sf::Vector2f(700.f, 75.f));

    //SCREEN 3 BUTTONS
    sf::RectangleShape prevB(sf::Vector2f(400.f, 150.f));
    sf::RectangleShape nextB(sf::Vector2f(400.f, 150.f));
    sf::RectangleShape movieTitleB(sf::Vector2f(1160.f, 150.f));
    sf::RectangleShape resetB(sf::Vector2f(300.f, 70.f));
    sf::RectangleShape returnB(sf::Vector2f(300.f, 70.f));


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////TEXT//////////////////////////////////////////////////////////////////////////////
    //HOME SCREEN TEXT
    sf::Text textKeyW;
    sf::Text textDiag;
    sf::Text textSearch;

    //SCREEN 2 TEXT
    sf::Text textChooseB1;
    sf::Text textChooseB2;

    //SCREEN 3 TEXT
    sf::Text textMovieT;
    sf::Text textKeyword1;
    sf::Text textKeyword2;
    sf::Text textkeywordI;
    sf::Text textNext;
    sf::Text textPrev;
    sf::Text homeT;
    sf::Text returnT;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    ///////////////////////////////////////////////////////////////////FONT LOADING//////////////////////////////////////////////////////////////////////////////////
    sf::Font font;

    if (!font.loadFromFile("arial.ttf"))
    {
        // error...
        std::cout << "error with font" << endl;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////SETTING POSITIONS, TEXT AND COLOR OF BUTTONS AND TEXT////////////////////////////////////////////////////////////
    textKeyW.setFont(font);
    textKeyW.setCharacterSize(100);
    textKeyW.setString("Search");
    textKeyW.setStyle(sf::Text::Bold);

    textDiag.setFont(font);
    textDiag.setCharacterSize(100);
    textDiag.setString("Test");
    textDiag.setStyle(sf::Text::Bold);

    textChooseB1.setFont(font);
    textChooseB1.setCharacterSize(50);
    textChooseB1.setString("Find Most Similar Movies");
    textChooseB1.setStyle(sf::Text::Bold);

    textChooseB2.setFont(font);
    textChooseB2.setCharacterSize(50);
    textChooseB2.setString("Find Least Similar Movies");
    textChooseB2.setStyle(sf::Text::Bold);

    textSearch.setFont(font);
    textSearch.setCharacterSize(60);
    textSearch.setString("Insert Movie Name");

    textMovieT.setFont(font);
    textMovieT.setCharacterSize(80);

    textNext.setFont(font);
    textNext.setCharacterSize(150);
    textNext.setString("Next");

    textPrev.setFont(font);
    textPrev.setCharacterSize(150);
    textPrev.setString("Last");

    homeT.setFont(font);
    homeT.setCharacterSize(80);
    homeT.setStyle(sf::Text::Bold);
    homeT.setString("Home");

    returnT.setFont(font);
    returnT.setCharacterSize(80);
    returnT.setStyle(sf::Text::Bold);
    returnT.setString("Return");


    homeB1.setPosition(400, 350);
    homeB1.setOutlineColor(grey);
    homeB1.setOutlineThickness(2.f);
    homeB1.setFillColor(buttonColor);

    homeB2.setPosition(400, 550);
    homeB2.setOutlineColor(grey);
    homeB2.setOutlineThickness(2.f);
    homeB2.setFillColor(buttonColor);

    chooseB1.setPosition(250, 300);
    chooseB1.setOutlineColor(grey);
    chooseB1.setOutlineThickness(2.f);
    chooseB1.setFillColor(buttonColor);

    chooseB2.setPosition(250, 500);
    chooseB2.setOutlineColor(grey);
    chooseB2.setOutlineThickness(2.f);
    chooseB2.setFillColor(buttonColor);

    searchBar.setPosition(100, 200);
    searchBar.setOutlineColor(grey);
    searchBar.setFillColor(buttonColor);
    searchBar.setOutlineThickness(2.f);

    textKeyW.setPosition(437, 357);
    textKeyW.setFillColor(sf::Color::Black);

    textDiag.setPosition(480, 557);
    textDiag.setFillColor(sf::Color::Black);

    textSearch.setPosition(115, 200);
    textSearch.setFillColor(sf::Color::Black);

    textChooseB1.setPosition(265, 305);
    textChooseB1.setFillColor(sf::Color::Black);

    textChooseB2.setPosition(265, 505);
    textChooseB2.setFillColor(sf::Color::Black);

    prevB.setPosition(20, 625);
    prevB.setOutlineColor(grey);
    prevB.setOutlineThickness(2.f);
    prevB.setFillColor(buttonColor);

    nextB.setPosition(780, 625);
    nextB.setOutlineColor(grey);
    nextB.setOutlineThickness(2.f);
    nextB.setFillColor(buttonColor);

    movieTitleB.setPosition(20, 20);
    movieTitleB.setOutlineColor(grey);
    movieTitleB.setOutlineThickness(2.f);
    movieTitleB.setFillColor(buttonColor);

    resetB.setPosition(450, 705);
    resetB.setOutlineColor(grey);
    resetB.setOutlineThickness(2.f);
    resetB.setFillColor(buttonColor);

    returnB.setPosition(450, 620);
    returnB.setOutlineColor(grey);
    returnB.setOutlineThickness(2.f);
    returnB.setFillColor(buttonColor);



    textMovieT.setPosition(25, 25);
    textMovieT.setFillColor(sf::Color::Black);

    textNext.setPosition(825, 600);
    textNext.setFillColor(sf::Color::Black);

    textPrev.setPosition(60, 600);
    textPrev.setFillColor(sf::Color::Black);

    homeT.setPosition(485, 690);
    homeT.setFillColor(sf::Color::Black);

    returnT.setPosition(475, 605);
    returnT.setFillColor(sf::Color::Black);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool takeKI = false; //VARIABLE TO DETERMINE IF KEY INPUT SHOULD BE TAKEN IN THE SEARCH BAR
    sf::String pInput; //SFML STRING TO KEEP TRACK OF USER LETTER INPUT
    sf::Text test; //TEXT THAT WILL DISPLAY THE LETTERS
    int currentMovie = 0;//VARIABLE TO KEEP TRACK OF WHICH MOVIE TO DISPLAY

    while (window.isOpen()) //OPENING WINDOW
    {
        sf::Event event; //KEEPING TRACK OF EVENTS AND POLLING FOR EVENTS
        while (window.pollEvent(event))
        {
            sf::Vector2i mouseP = sf::Mouse::getPosition(window);
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                //IF LEFT CLICK DETECTED, DETERMINE WHERE
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (CurrentScene == "home")
                    {
                        //IF HOME BUTTON PRESSED, TAKE IN USER INPUT AND MOVE TO NEXT SCREEN
                        if (homeB1.getGlobalBounds().contains(mouseP.x, mouseP.y))
                        {
                            practice.title = pInput;
                            movieMap.emplace(practice.title, 0);
                            CurrentScene = "Choose";
                        }
                        //IF HOME BUTTON 2 IS PRESSED, PRINT PERFORMANCE DATA IN THE TERMINAL
                        else if (homeB2.getGlobalBounds().contains(mouseP.x, mouseP.y))
                        {
                            practice.title = pInput;
                            movieMap.emplace(practice.title, 0);
                            auto t1 = Clock::now();//USING CLOCKS TO TIME THE ALGORITHMS
                            bfs1 = bfsMostSimilar(graph, practice.title, movieMap, maxKeywords);
                            auto t2 = Clock::now();
                            std::cout << "BFS Most Similar: " << duration_cast<milliseconds>(t2 - t1).count() << " milliseconds" << std::endl;

                            t1 = Clock::now();
                            bfs2 = bfsLeastSimilar(graph, practice.title, movieMap, maxKeywords);
                            t2 = Clock::now();
                            std::cout << "BFS Least Similar: " << duration_cast<milliseconds>(t2 - t1).count() << " milliseconds" << std::endl;

                            t1 = Clock::now();
                            dfs1 = dfsMostSimilar(graph, practice.title, movieMap, maxKeywords);
                            t2 = Clock::now();
                            std::cout << "DFS Most Similar: " << duration_cast<milliseconds>(t2 - t1).count() << " milliseconds" << std::endl;

                            t1 = Clock::now();
                            dfs2 = dfsLeastSimilar(graph, practice.title, movieMap, maxKeywords);
                            t2 = Clock::now();
                            std::cout << "DFS Least Similar: " << duration_cast<milliseconds>(t2 - t1).count() << " milliseconds" << std::endl;
                            cout << endl;
                        }
                        //IF NOTHING IS CLICKED, RESET THE SEARCH BAR
                        else if (!searchBar.getGlobalBounds().contains(mouseP.x, mouseP.y))
                        {
                            textSearch.setString("Insert Movie Name");
                            pInput = "";
                            takeKI = false;
                        }
                        //IF THE SEARCH BAR IS CLICKED, CLEAR IT AND BEGIN ALLOWING KEYBOARD INPUT TO BE TAKEN IN
                        else if (searchBar.getGlobalBounds().contains(mouseP.x, mouseP.y))
                        {
                            textSearch.setString(" ");
                            takeKI = true;
                        }
                    }
                    else if (CurrentScene == "Choose") //2ND SCREEN BUTTONS
                    {
                        //IF THE FIRST BUTTON IS CLICKED, CONDUCT A BFS AND DFS TO FIND MOST SIMILAR MOVIES
                        if (chooseB1.getGlobalBounds().contains(mouseP.x, mouseP.y))
                        {
                            currentMovie = 0;
                            algoReturn = bfsMostSimilar(graph, practice.title, movieMap, maxKeywords);
                            dfs1 = dfsMostSimilar(graph, practice.title, movieMap, maxKeywords);
                            CurrentScene = "Show";
                        }
                        //IF THE 2ND BUTTON IS CLICKED, CONDUCTS A DFS AND BFS TO FIND THE LEAST SIMILAR MOVIES
                        if (chooseB2.getGlobalBounds().contains(mouseP.x, mouseP.y))
                        {
                            currentMovie = 0;
                            algoReturn = dfsLeastSimilar(graph, practice.title, movieMap, maxKeywords);
                            bfs2 = bfsLeastSimilar(graph, practice.title, movieMap, maxKeywords);
                            CurrentScene = "Show";
                        }
                    }
                    else if (CurrentScene == "Show")//BUTTONS FOR THE 3RD SCREEN
                    {
                        //NEXT BUTTON WILL MOVE ONTO THE NEXT MOVIE IN THE MOVIES VECTOR BY INCREMENTING THE CURRENTMOVIE VARIABLE
                        if (textNext.getGlobalBounds().contains(mouseP.x, mouseP.y))
                        {

                            currentMovie++;
                        }
                        //PREV BUTTON WILL MOVE ONTO THE PREVIOUS MOVIE IN THE MOVIES VECTOR BY DECREMENTING THE CURRENTMOVIE VARIABLE
                        if (textPrev.getGlobalBounds().contains(mouseP.x, mouseP.y))
                        {

                            currentMovie--;
                        }
                        //RESET BUTTON WILL RESET THE UI TO THE HOME SCREEN AND CLEAR THE SOURCE MOVIE TO ALLOW FOR NEW INPUT
                        if (resetB.getGlobalBounds().contains(mouseP.x, mouseP.y))
                        {
                            CurrentScene = "home";
                            movieMap.erase(practice.title);
                            practice.title = "";
                            pInput = "";
                            textSearch.setString("Insert Movie Name");
                        }
                        if (returnB.getGlobalBounds().contains(mouseP.x, mouseP.y))
                        {
                            CurrentScene = "Choose";
                        }
                    }
                }
            }
            //TAKES IN KEYBOARD INPUT
            if (event.type == sf::Event::TextEntered)
            {
                //ONLY TAKE INPUT IN IF ALLOWED I.E. WHEN THE SEARCH BAR HAS BEEN SELECTED
                if (takeKI == true)
                {
                    //CHECKING IF THE CHARACTER TYPED IS VALID UNICODE
                    if (event.text.unicode >= 32 && event.text.unicode <= 127)
                    {
                        pInput += event.text.unicode;
                        textSearch.setString(pInput);
                    }
                    //CHECKING FOR BACKSPACE, WHICH DELETES THE LAST CHARACTER TYPED IF THERE IS A LETTER IN THE SEARCH BAR
                    else if (event.text.unicode == 8)
                    {
                        if (!pInput.isEmpty())
                        {
                            pInput.erase(pInput.getSize() - 1, 1);
                            textSearch.setString(pInput);
                        }
                    }
                }
            }
        }

        //CLEAR THE WINDOW TO ALLOW FOR DRAWING OF UI ELEMENTS; CLEARS TO CUSTOM GREY COLOR
        window.clear(backGroundColor);
        //////////////////////////////////////////////DRAWING UI ELEMENTS TO THE SCREEN//////////////////////////////////////////////////////////////////
        if (CurrentScene == "home")
        {
            //DRAWING BUTTONS AND TEXT FOR THE HOME SCREEN
            window.draw(homeB1);
            window.draw(homeB2);
            window.draw(searchBar);
            window.draw(textKeyW);
            window.draw(textSearch);
            window.draw(textDiag);
        }
        else if (CurrentScene == "Choose")
        {
            //DRAWING BUTTONS AND TEXT FOR THE 2ND SCREEN
            window.draw(chooseB1);
            window.draw(chooseB2);
            window.draw(textChooseB1);
            window.draw(textChooseB2);

        }
        else if (CurrentScene == "Show")
        {
            //EDGE CASE HANDLEINE
            //CANNOT ALLOW NEGATVE INDECIES OR INDECIES OVER THE SIZE OF THE MOVIES VECTOR
            if (currentMovie < 0)
            {
                currentMovie = 0;
            }
            if (currentMovie >= algoReturn.size())
            {
                currentMovie = algoReturn.size() - 1;
            }
            //SETTIONG THE STRING OF THE MOVIE DISPLAY BOX TO THE CURRENT MOVIE IN THE VECTOR; CHANGES IF NEXT OR PREV BUTTON ARE PRESSED
            textMovieT.setString(algoReturn[currentMovie]);
            //DRAWING BUTTONS AND TEXT FOR THE HOME SCREEN
            window.draw(nextB);
            window.draw(prevB);
            window.draw(movieTitleB);
            window.draw(textMovieT);
            window.draw(textNext);
            window.draw(textPrev);
            window.draw(resetB);
            window.draw(homeT);
            window.draw(returnB);
            window.draw(returnT);
        }
        window.display();//DISPLAYING THE WINDOW
    }
    for (int i = 0; i < allMovies.size(); i++)
    {
        Movie* tempD = allMovies[i];
        delete tempD;
    }
    return 0;
}


