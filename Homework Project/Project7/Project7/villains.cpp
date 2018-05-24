// trading.cpp

#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <cassert>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;              // max number of rows in the colosseum
const int MAXCOLS = 20;              // max number of columns in the colosseum
const int MAXVILLAINS = 100;          // max number of villains allowed

const int NORTH = 0;
const int EAST  = 1;
const int SOUTH = 2;
const int WEST  = 3;
const int NUMDIRS = 4;

const int EMPTY      = 0;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Colosseum;  // This is needed to let the compiler know that Colosseum is a
// type name, since it's mentioned in the Villain declaration.

class Villain
{
public:
    // Constructor
    Villain(Colosseum* colosseum, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;
    
    
    // Mutators
    void move();
    void setDead();
    void push(int dir); // pushes this villain in this direction.
    
private:
    Colosseum* m_colosseum;
    int    m_row;
    int    m_col;
	bool   m_dead;
};

class Player
{
public:
    // Constructor
    Player(Colosseum *colosseum, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;
    
    // Mutators
    string move(int dir);
    string push();
    void   setDead();
    
private:
    Colosseum* m_colosseum;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

class Colosseum
{
public:
    // Constructor/destructor
    Colosseum(int nRows, int nCols);
    ~Colosseum();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     villainCount() const;
    int     getCellStatus(int r, int c) const;
    int     numberOfVillainsAt(int r, int c) const;
    void    display(string msg) const;
    
    // Mutators
    void setCellStatus(int r, int c, int status);
    bool addVillain(int r, int c);
    bool addPlayer(int r, int c);
    void moveVillains();
    void pushAllVillains(int r, int c, int dir); // pushes all villains at [r,c] in the given direction
    
private:
    int     m_grid[MAXROWS][MAXCOLS];
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Villain* m_villains[MAXVILLAINS];
    int     m_nVillains;
    int     m_turns;
    
    // Helper functions
    void checkPos(int r, int c) const;
    bool isPosInBounds(int r, int c) const;
};

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nVillains);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Colosseum* m_colosseum;
    
    // Helper functions
    string takePlayerTurn();
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int randInt(int lowest, int highest);
bool charToDir(char ch, int& dir);
bool attemptMove(const Colosseum& colosseum, int dir, int& r, int& c);
bool recommendMove(const Colosseum& colosseum, int r, int c, int& bestDir);
int computeDanger(const Colosseum& colosseum, int r, int c);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Villain implementation
///////////////////////////////////////////////////////////////////////////

Villain::Villain(Colosseum* colosseum, int r, int c)
{
    if (colosseum == NULL)
    {
        cout << "***** A villain must be created in some Colosseum!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > colosseum->rows()  ||  c < 1  ||  c > colosseum->cols())
    {
        cout << "***** Villain created with invalid coordinates (" << r << ","
        << c << ")!" << endl;
        exit(1);
    }
    m_colosseum = colosseum;
    m_row = r;
    m_col = c;
    m_dead = false;
}

int Villain::row() const
{
    return m_row;
}

int Villain::col() const
{
	return m_col;
}

bool Villain::isDead() const
{
    return m_dead;
}

void Villain::move()
{
	if (isDead() == false)
    {
        int dir = randInt(NORTH, WEST);
        switch (dir)
        {
            case NORTH:
                if (row() > 1 && row() <= m_colosseum->rows())
                {
                    m_row--;
                }
                break;
            
            case EAST:
                if (col() >= 1 && col() < m_colosseum->cols())
                {
                    m_col++;
                }
                break;
            
            case SOUTH:
                if (row() >= 1 && row() < m_colosseum->rows())
                {
                    m_row++;
                }
                break;
            
            case WEST:
                if (col() > 1 && col() <= m_colosseum->cols())
                {
                    m_col--;
                }
                break;
            
            
            default:
                break;
        }
    }
}

void Villain::setDead()
{
	if (row() < 1 || row() > m_colosseum->rows() || col() < 1 || col() > m_colosseum->cols())
    {
        m_dead = true;
    }
}

//Special case: if a villain is located in the first row, if pushed north, the villain should die
//Consider special cases for 4 directions
//Then the normal cases
void Villain::push(int dir)
{
    switch (dir)
    {
        case NORTH:
            if (row() == 1)
            {
                m_row--;
                setDead();
            }
            else if (row() > 1 && row() <= m_colosseum->rows())
            {
                m_row--;
            }
            break;
            
        case EAST:
            if (col() == m_colosseum->cols())
            {
                m_col++;
                setDead();
            }
            else if (col() >= 1 && col() < m_colosseum->cols())
            {
                m_col++;
            }
            break;
            
        case SOUTH:
            if (row() == m_colosseum->rows())
            {
                m_row++;
                setDead();
            }
            else if (row() >= 1 && row() < m_colosseum->rows())
            {
                m_row++;
            }
            break;
            
        case WEST:
            if (col() == 1)
            {
                m_col++;
                setDead();
            }
            else if (col() > 1 && col() <= m_colosseum->cols())
            {
                m_col++;
            }
            break;
            
            
            
        default:
            break;
    }
}

///////////////////////////////////////////////////////////////////////////
//  Player implementation
///////////////////////////////////////////////////////////////////////////

Player::Player(Colosseum* colosseum, int r, int c)
{
    if (colosseum == NULL)
    {
        cout << "***** The player must be created in some Colosseum!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > colosseum->rows()  ||  c < 1  ||  c > colosseum->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
        << "," << c << ")!" << endl;
        exit(1);
    }
    m_colosseum = colosseum;
    m_row = r;
    m_col = c;
    m_dead = false;
}

int Player::row() const
{
	return m_row;
}

int Player::col() const
{
	return m_col;
}

//Player should push 4 directions one by one
string Player::push()
{
    for (int m = 0; m < NUMDIRS; m++)
    {
        switch (m)
        {
            case NORTH:
                if (row() > 1 && row() <= m_colosseum->rows())
                {
                    m_colosseum->pushAllVillains(row() - 1, col(), NORTH);
                }
                break;
            
            case EAST:
                if (col() >= 1 && col() < m_colosseum->cols())
                {
                    m_colosseum->pushAllVillains(row(), col() + 1, EAST);
                }
                break;
            
            case SOUTH:
                if (row() >= 1 && row() < m_colosseum->rows())
                {
                    m_colosseum->pushAllVillains(row() + 1, col(), SOUTH);
                }
                break;
            
            case WEST:
                if (col() > 1 && col() <= m_colosseum->cols())
                {
                    m_colosseum->pushAllVillains(row(), col() - 1, WEST);
                }
                break;
            
            
            default:
                break;
        }
    }
    return "Player pushed.";
}

string Player::move(int dir)
{
    switch (dir)
    {
        case NORTH:
            if (row() > 1 && row() <= m_colosseum->rows())
            {
                m_row--;
                
                if (m_colosseum->numberOfVillainsAt(row(), col()) != 0)
                {
                    setDead();
                    return "Player walked into a villain and died.";
                }
                else
                {
                    return "Player moved north.";
                }
            }
            break;
        
        case EAST:
            if (col() >= 1 && col() < m_colosseum->cols())
            {
                m_col++;
                
                if (m_colosseum->numberOfVillainsAt(row(), col()) != 0)
                {
                    setDead();
                    return "Player walked into a villain and died.";
                }
                else
                {
                    return "Player moved east.";
                }
            }
            break;
        
        case SOUTH:
            if (row() >= 1 && row() < m_colosseum->rows())
            {
                m_row++;
                
                if (m_colosseum->numberOfVillainsAt(row(), col()) != 0)
                {
                    setDead();
                    return "Player walked into a villain and died.";
                }
                else
                {
                    return "Player moved south.";
                }
                
            }
            break;
        
        case WEST:
            if (col() > 1 && col() <= m_colosseum->cols())
            {
                m_col--;
                
                if (m_colosseum->numberOfVillainsAt(row(), col()) != 0)
                {
                    setDead();
                    return "Player walked into a villain and died.";
                }
                else
                {
                    return "Player moved west.";
                }
            }
            break;
            
        
        default:
            break;
    }
    return "Player couldn't move; player stands.";
}

bool Player::isDead() const
{
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Colosseum implementation
///////////////////////////////////////////////////////////////////////////

Colosseum::Colosseum(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Colosseum created with invalid size " << nRows << " by "
        << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = NULL;
    m_nVillains = 0;
    m_turns = 0;
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            setCellStatus(r, c, EMPTY);
}

Colosseum::~Colosseum()
{
    delete m_player;
    for (int i = 0; i < m_nVillains; i++)
    {
        delete m_villains[i];
    }
}

int Colosseum::rows() const
{
    return m_rows;
    
}

int Colosseum::cols() const
{
    return m_cols;
}

Player* Colosseum::player() const
{
    return m_player;
}

int Colosseum::villainCount() const
{
    return m_nVillains;
}

int Colosseum::getCellStatus(int r, int c) const
{
    checkPos(r, c);
    return m_grid[r-1][c-1];
}

int Colosseum::numberOfVillainsAt(int r, int c) const
{
    checkPos(r, c);
    int num = 0;
    for (int i = 0; i < m_nVillains; i++)
    {
        if (r == m_villains[i]->row() && c == m_villains[i]->col())
        {
            num++;
        }
    }
    return num;
}

void Colosseum::display(string msg) const
{
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill displayGrid with dots (empty)
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
            displayGrid[r-1][c-1] = (getCellStatus(r,c) == EMPTY ? '.' : '*');
    
    // Indicate each villain's position
    for (int k = 0; k < m_nVillains; k++)
    {
        const Villain* vp = m_villains[k];
        char& gridChar = displayGrid[vp->row()-1][vp->col()-1];
        switch (gridChar)
        {
            case '.':  gridChar = 'V'; break;
            case 'V':  gridChar = '2'; break;
            case '9':  break;
            default:   gridChar++; break;  // '2' through '8'
        }
    }
    
    // Indicate player's position
    if (m_player != NULL)
        displayGrid[m_player->row()-1][m_player->col()-1] = (m_player->isDead() ? 'X' : '@');
    
    // Draw the grid
    clearScreen();
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
            cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;
    
    // Write message, villain, and player info
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << villainCount() << " villains remaining." << endl;
    if (m_player == NULL)
        cout << "There is no player!" << endl;
    else if (m_player->isDead())
        cout << "The player is dead." << endl;
    cout << m_turns << " turns have been taken." << endl;
}

void Colosseum::setCellStatus(int r, int c, int status)
{
    checkPos(r, c);
    m_grid[r-1][c-1] = status;
}

bool Colosseum::addVillain(int r, int c)
{
    if (! isPosInBounds(r, c))
        return false;
    if (m_player != NULL  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;
    if (m_nVillains == MAXVILLAINS)
        return false;
    m_villains[m_nVillains] = new Villain(this, r, c);
    m_nVillains++;
    return true;
}

bool Colosseum::addPlayer(int r, int c)
{
    if (m_player != NULL  ||  ! isPosInBounds(r, c))
        return false;
    if (numberOfVillainsAt(r, c) > 0)
        return false;
    m_player = new Player(this, r, c);
    return true;
}

void Colosseum::moveVillains()
{
    for (int i = 0; i < m_nVillains; i++)
    {
        m_villains[i]->move();
        if (m_villains[i]->row() == m_player->row() && m_villains[i]->col() == m_player->col())
        {
            m_player->setDead();
        }
    }
    m_turns++;
}

//if m_villains[index] died, decrease the indices of following elements by one, and delete the last element then
void Colosseum::pushAllVillains(int r, int c, int dir)
{
    checkPos(r, c);
    for (int index = 0; index < m_nVillains; index++)
    {
        
        if (m_villains[index]->row() == r && m_villains[index]->col() == c)
        {
            m_villains[index]->push(dir);
            m_villains[index]->setDead();
            
            if (m_villains[index]->isDead())
            {
                for (int j = index; j < m_nVillains; j++)
                {
                    m_villains[j] = m_villains[j + 1];
                }
                delete m_villains[m_nVillains];
                m_nVillains--;
                continue;
            }
        }
    }
}


bool Colosseum::isPosInBounds(int r, int c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}

void Colosseum::checkPos(int r, int c) const
{
    if (!isPosInBounds(r, c))
    {
        cout << "***** " << "Invalid colosseum position (" << r << ","
        << c << ")" << endl;
        exit(1);
    }
}

///////////////////////////////////////////////////////////////////////////
//  Game implementation
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nVillains)
{
    if (nVillains < 0  ||  nVillains > MAXVILLAINS)
    {
        cout << "***** Game created with invalid number of villains:  "
        << nVillains << endl;
        exit(1);
    }
    int nEmpty = rows * cols - nVillains - 1;  // 1 for Player
    if (nEmpty < 0)
    {
        cout << "***** Game created with a " << rows << " by "
        << cols << " colosseum, which is too small too hold a player and "
        << nVillains << " villains!" << endl;
        exit(1);
    }
    
    // Create Colosseum
    m_colosseum = new Colosseum(rows, cols);
    
    // Add player
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(1, rows);
        cPlayer = randInt(1, cols);
    } while (m_colosseum->getCellStatus(rPlayer, cPlayer) != EMPTY);
    m_colosseum->addPlayer(rPlayer, cPlayer);
    
    // Populate with villains
    while (nVillains > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (r == rPlayer && c == cPlayer)
            continue;
        m_colosseum->addVillain(r, c);
        nVillains--;
    }
}

Game::~Game()
{
    delete m_colosseum;
}

string Game::takePlayerTurn()
{
    for (;;)
    {
        cout << "Your move (n/e/s/w/p or nothing): ";
        string playerMove;
        getline(cin, playerMove);
        
        Player* player = m_colosseum->player();
        int dir;
        
        if (playerMove.size() == 0)
        {
            if (recommendMove(*m_colosseum, player->row(), player->col(), dir))
                return player->move(dir);
            else
                return player->push();
        }
        else if (playerMove.size() == 1)
        {
            if (tolower(playerMove[0]) == 'p')
                return player->push();
            else if (charToDir(playerMove[0], dir))
                return player->move(dir);
        }
        cout << "Player move must be nothing, or 1 character n/e/s/w/p." << endl;
    }
}

void Game::play()
{
    m_colosseum->display("");
    while ( ! m_colosseum->player()->isDead()  &&  m_colosseum->villainCount() > 0)
    {
        string msg = takePlayerTurn();
        Player* player = m_colosseum->player();
        if (player->isDead())
            break;
        m_colosseum->moveVillains();
        m_colosseum->display(msg);
    }
    if (m_colosseum->player()->isDead())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementation
///////////////////////////////////////////////////////////////////////////

// Return a uniformly distributed random int from lowest to highest, inclusive
int randInt(int lowest, int highest)
{
    if (highest < lowest)
        swap(highest, lowest);
    return lowest + (rand() % (highest - lowest + 1));
}

bool charToDir(char ch, int& dir)
{
    switch (tolower(ch))
    {
        default:  return false;
        case 'n': dir = NORTH; break;
        case 'e': dir = EAST;  break;
        case 's': dir = SOUTH; break;
        case 'w': dir = WEST;  break;
    }
    return true;
}

// Return false without changing anything if moving one step from (r,c)
// in the indicated direction would hit a run off the edge of the colosseum.
// Otherwise, update r and c to the position resulting from the move and
// return true.
bool attemptMove(const Colosseum& colosseum, int dir, int& r, int& c)
{
    switch (dir)
    {
        case NORTH:
            if (r > 1 && r <= colosseum.rows())
            {
                r--;
            }
            else
            {
                return false;
            }
            break;
        
        case EAST:
            if (c >= 1 && c < colosseum.cols())
            {
                c++;
            }
            else
            {
                return false;
            }
            break;
        
        case SOUTH:
            if (r >= 1 && r < colosseum.rows())
            {
                r++;
            }
            else
            {
                return false;
            }
            break;
        
        case WEST:
            if (c > 1 && c <= colosseum.cols())
            {
                c--;
            }
            else
            {
                return false;
            }
            break;
        
        
        default:
            break;
    }
    return true;
}

// Recommend a move for a player at (r,c):  A false return means the
// recommendation is that the player should push and not move;
// otherwise, this function sets bestDir to the recommended direction
// to move and returns true.
bool recommendMove(const Colosseum& colosseum, int r, int c, int& bestDir)
{
	if (colosseum.numberOfVillainsAt(r - 1, c) == 0 && r > 1 && r <= colosseum.rows())
    {
        bestDir = NORTH;
        return true;
    }
    else if (colosseum.numberOfVillainsAt(r, c - 1) == 0 && c > 1 && c <= colosseum.cols())
    {
        bestDir = WEST;
        return true;
    }
    else if (colosseum.numberOfVillainsAt(r + 1, c) == 0 && r < colosseum.rows() && r >= 1)
    {
        bestDir = SOUTH;
        return true;
    }
    else if (colosseum.numberOfVillainsAt(r, c + 1) == 0 && c < colosseum.cols() && c >= 1)
    {
        bestDir = EAST;
        return true;
    }
    return false;

}

int computeDanger(const Colosseum& colosseum, int r, int c)
{
    // Our measure of danger will be the number of villains that might move
    // to position r,c.  If a villain is at that position, it is fatal,
    // so a large value is returned.
    
    if (colosseum.numberOfVillainsAt(r,c) > 0)
        return MAXVILLAINS+1;
    
    int danger = 0;
    if (r > 1)
        danger += colosseum.numberOfVillainsAt(r-1,c);
    if (r < colosseum.rows())
        danger += colosseum.numberOfVillainsAt(r+1,c);
    if (c > 1)
        danger += colosseum.numberOfVillainsAt(r,c-1);
    if (c < colosseum.cols())
        danger += colosseum.numberOfVillainsAt(r,c+1);
    
    return danger;
}

// DO NOT MODIFY THE CODE BETWEEN HERE AND THE MAIN ROUTINE
#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                               &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <cstring>

void clearScreen()
{
    static const char* term = getenv("TERM");
    static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
    if (term == NULL  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
}

#endif

///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    // Initialize the random number generator
    srand(static_cast<unsigned int>(time(0)));
    
    // Create a game
    // Use this instead to create a mini-game:
    Game g(3, 5, 2);
    //Game g(10, 12, 40);
    
    // Play the game
    g.play();
}
