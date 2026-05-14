#pragma once
#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
using namespace std;

enum class GameState { MENU, PLAYING, GAMEOVER };
class Piece
{
protected:
	char Colour;
	bool hasMoved;
public:
	Piece(char c);
	virtual bool IsValidMove(int sx, int sy, int dx, int dy, Piece* Board[8][8]);
	virtual char GetSymbol()const = 0;
	char GetColour()const;
	bool GetHasMoved()const;
	void SetHasMoved(bool v);
	virtual ~Piece();
};
class Pawn : public Piece
{
public:
	Pawn(char c);
	bool IsValidMove(int sx, int sy, int dx, int dy, Piece* Board[8][8])override;
	char GetSymbol()const override;
};
class Rook : public Piece
{
public:
	Rook(char c);
	bool IsValidMove(int sx, int sy, int dx, int dy, Piece* Board[8][8])override;
	char GetSymbol()const override;
};
class Knight : public Piece
{
public:
	Knight(char c);
	bool IsValidMove(int sx, int sy, int dx, int dy, Piece* Board[8][8])override;
	char GetSymbol()const override;
};
class Bishop : public Piece
{
public:
	Bishop(char c);
	bool IsValidMove(int sx, int sy, int dx, int dy, Piece* Board[8][8])override;
	char GetSymbol()const override;
};
class Queen : public Piece
{
public:
	Queen(char c);
	bool IsValidMove(int sx, int sy, int dx, int dy, Piece* Board[8][8])override;
	char GetSymbol()const override;
};
class King : public Piece
{
public:
	King(char c);
	bool IsValidMove(int sx, int sy, int dx, int dy, Piece* Board[8][8])override;
	char GetSymbol()const override;
};
class Board
{
private:
	void Setup();
public:
	Board();
	Piece* Grid[8][8];
	int lastMoveSX, lastMoveSY, lastMoveDX, lastMoveDY;
	void Display();
	bool IsCheck(char Colour)const;
	bool HasAnyValidMove(char Colour);
	void PromotePawn(int x, int y);
	bool Move(int sx, int sy, int dx, int dy, char Turn);
	~Board();
};
class Game
{
private:
	Board B;
	char Turn;
	sf::RenderWindow Window;
	sf::Font font;
	std::map<char, sf::Texture> pieceTextures;
	int selectedX;
	int selectedY;
	std::string statusMessage;
	GameState state;
	bool vsComputer;

	void LoadAssets();
	void HandleEvents();
	void Render();
	void RenderMenu();
	void MakeComputerMove();
public:
	Game();
	void Start();
};
bool convert(std::string POS, int& x, int& y);