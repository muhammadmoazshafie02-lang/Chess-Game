#include "Header.h"

Piece::Piece(char c) : Colour(c), hasMoved(false)
{

}
char Piece::GetColour() const
{
	return Colour;
}
bool Piece::GetHasMoved()const
{
	return hasMoved;
}
void Piece::SetHasMoved(bool v)
{
	hasMoved = v;
}
Piece::~Piece()
{

}
bool Piece::IsValidMove(int sx, int sy, int dx, int dy, Piece* Board[8][8])
{
	return false;
}
Pawn::Pawn(char c) : Piece(c)
{

}
bool Pawn::IsValidMove(int sx, int sy, int dx, int dy, Piece* Board[8][8])
{
	int Direction = (Colour == 'W') ? -1 : 1;
	if (sy == dy && !Board[dx][dy])
	{
		if (dx == sx + Direction)
		{
			return true;
		}
		if ((Colour == 'W' && sx == 6) || (Colour == 'B' && sx == 1))
		{
			if (dx == sx + 2 * Direction && !Board[sx + Direction][sy])
			{
				return true;
			}
		}
	}
	if (abs(dy - sy) == 1 && dx == sx + Direction && Board[dx][dy] && Board[dx][dy]->GetColour() != Colour)
	{
		return true;
	}
	return false;
}
char Pawn::GetSymbol()const
{
	return (Colour == 'W') ? 'P' : 'p';
}
Rook::Rook(char c) : Piece(c)
{

}
bool Rook::IsValidMove(int sx, int sy, int dx, int dy, Piece* Board[8][8])
{
	if (sx != dx && sy != dy)
	{
		return false;
	}
	int StepX = (dx - sx == 0) ? 0 : (dx - sx) / abs(dx - sx);
	int StepY = (dy - sy == 0) ? 0 : (dy - sy) / abs(dy - sy);
	int x = sx + StepX, y = sy + StepY;
	while (x != dx || y != dy)
	{
		if (Board[x][y])
		{
			return false;
		}
		x = x + StepX;
		y = y + StepY;
	}
	if (Board[dx][dy] && Board[dx][dy]->GetColour() == Colour)
	{
		return false;
	}
	return true;
}
char Rook::GetSymbol()const
{
	return (Colour == 'W') ? 'R' : 'r';
}
Knight::Knight(char c) : Piece(c)
{

}
bool Knight::IsValidMove(int sx, int sy, int dx, int dy, Piece* Board[8][8])
{
	int dxA = abs(dx - sx), dyA = abs(dy - sy);
	if (!((dxA == 2 && dyA == 1) || (dxA == 1 && dyA == 2)))
	{
		return false;
	}
	if (Board[dx][dy] && Board[dx][dy]->GetColour() == Colour)
	{
		return false;
	}
	return true;
}
char Knight::GetSymbol()const
{
	return (Colour == 'W') ? 'N' : 'n';
}
Bishop::Bishop(char c) : Piece(c)
{

}
bool Bishop::IsValidMove(int sx, int sy, int dx, int dy, Piece* Board[8][8])
{
	if (abs(dx - sx) != abs(dy - sy))
	{
		return false;
	}
	int StepX = (dx - sx == 0) ? 0 : (dx - sx) / abs(dx - sx);
	int StepY = (dy - sy == 0) ? 0 : (dy - sy) / abs(dy - sy);
	int x = sx + StepX, y = sy + StepY;
	while (x != dx || y != dy)
	{
		if (Board[x][y])
		{
			return false;
		}
		x = x + StepX;
		y = y + StepY;
	}
	if (Board[dx][dy] && Board[dx][dy]->GetColour() == Colour)
	{
		return false;
	}
	return true;
}
char Bishop::GetSymbol() const
{
	return (Colour == 'W') ? 'B' : 'b';
}
Queen::Queen(char c) : Piece(c)
{

}
bool Queen::IsValidMove(int sx, int sy, int dx, int dy, Piece* Board[8][8])
{
	Rook r(Colour);
	Bishop b(Colour);
	return r.IsValidMove(sx, sy, dx, dy, Board) || b.IsValidMove(sx, sy, dx, dy, Board);
}
char Queen::GetSymbol() const
{
	return (Colour == 'W') ? 'Q' : 'q';
}
King::King(char c) : Piece(c)
{

}
bool King::IsValidMove(int sx, int sy, int dx, int dy, Piece* Board[8][8])
{
	if (abs(dx - sx) <= 1 && abs(dy - sy) <= 1)
	{
		if (Board[dx][dy] && Board[dx][dy]->GetColour() == Colour)
		{
			return false;
		}
		return true;
	}
	if (!hasMoved && sx == dx && abs(dy - sy) == 2)
	{
		int rookY = (dy > sy) ? 7 : 0;
		if (Board[sx][rookY] && !Board[sx][rookY]->GetHasMoved())
		{
			int step = (dy > sy) ? 1 : -1;
			for (int y = sy + step; y != rookY; y = y + step)
			{
				if (Board[sx][y])
				{
					return false;
				}
			}
			return true;
		}
	}
	return false;
}
char King::GetSymbol() const
{
	return (Colour == 'W') ? 'K' : 'k';
}
Board::Board() : lastMoveSX(-1), lastMoveSY(-1), lastMoveDX(-1), lastMoveDY(-1)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Grid[i][j] = nullptr;
		}
	}
	Setup();
}
Board::~Board()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			delete Grid[i][j];
		}
	}
}
void Board::Setup()
{
	for (int i = 0; i < 8; i++)
	{
		Grid[1][i] = new Pawn('B');
		Grid[6][i] = new Pawn('W');
	}
	Grid[0][0] = new Rook('B');
	Grid[0][7] = new Rook('B');
	Grid[7][0] = new Rook('W');
	Grid[7][7] = new Rook('W');

	Grid[0][1] = new Knight('B');
	Grid[0][6] = new Knight('B');
	Grid[7][1] = new Knight('W');
	Grid[7][6] = new Knight('W');

	Grid[0][2] = new Bishop('B');
	Grid[0][5] = new Bishop('B');
	Grid[7][2] = new Bishop('W');
	Grid[7][5] = new Bishop('W');

	Grid[0][3] = new Queen('B');
	Grid[7][3] = new Queen('W');

	Grid[0][4] = new King('B');
	Grid[7][4] = new King('W');
}
void Board::Display()
{
	cout << "  a b c d e f g h" << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << 8 - i << " ";
		for (int j = 0; j < 8; j++)
		{
			if (Grid[i][j])
			{
				cout << Grid[i][j]->GetSymbol() << " ";
			}
			else
			{
				cout << ". ";
			}
		}
		cout << 8 - i << endl;
	}
	cout << "  a b c d e f g h" << endl;
}
bool Board::IsCheck(char Colour) const
{
	int kx = -1, ky = -1;
	Piece* tempGrid[8][8];
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			tempGrid[i][j] = Grid[i][j];
		}
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (Grid[i][j] && Grid[i][j]->GetColour() == Colour && dynamic_cast<King*>(Grid[i][j]))
			{
				kx = i;
				ky = j;
			}
		}
	}
	if (kx == -1)
	{
		return false;
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (tempGrid[i][j] && tempGrid[i][j]->GetColour() != Colour)
			{
				if (tempGrid[i][j]->IsValidMove(i, j, kx, ky, tempGrid))
				{
					return true;
				}
			}
		}
	}
	return false;
}
void Board::PromotePawn(int x, int y)
{
	Pawn* p = dynamic_cast<Pawn*>(Grid[x][y]);
	if (!p)
	{
		return;
	}
	char c = p->GetColour();
	if (!((c == 'W' && x == 0) || (c == 'B' && x == 7)))
	{
		return;
	}
	delete Grid[x][y];
	Grid[x][y] = new Queen(c);
}
bool Board::HasAnyValidMove(char Colour)
{
	for (int sx = 0; sx < 8; sx++)
	{
		for (int sy = 0; sy < 8; sy++)
		{
			if (Grid[sx][sy] && Grid[sx][sy]->GetColour() == Colour)
			{
				for (int dx = 0; dx < 8; dx++)
				{
					for (int dy = 0; dy < 8; dy++)
					{
						bool isEnPassant = false;
						if (dynamic_cast<Pawn*>(Grid[sx][sy]) && !Grid[dx][dy] && abs(dy - sy) == 1 && dx == sx + (Colour == 'W' ? -1 : 1))
						{
							if (lastMoveSX != -1 && lastMoveDX == sx && lastMoveDY == dy && abs(lastMoveSX - lastMoveDX) == 2 && dynamic_cast<Pawn*>(Grid[lastMoveDX][lastMoveDY]))
							{
								isEnPassant = true;
							}
						}

						if (isEnPassant || Grid[sx][sy]->IsValidMove(sx, sy, dx, dy, Grid))
						{
							Piece* Temp = Grid[dx][dy];
							Grid[dx][dy] = Grid[sx][sy];
							Grid[sx][sy] = nullptr;
							bool check = IsCheck(Colour);
							Grid[sx][sy] = Grid[dx][dy];
							Grid[dx][dy] = Temp;
							if (!check)
							{
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}
bool Board::Move(int sx, int sy, int dx, int dy, char Turn)
{
	if (!Grid[sx][sy] || Grid[sx][sy]->GetColour() != Turn)
	{
		return false;
	}
	if (Grid[dx][dy] && Grid[dx][dy]->GetColour() == Turn)
	{
		return false;
	}
	bool isEnPassant = false;
	if (dynamic_cast<Pawn*>(Grid[sx][sy]) && !Grid[dx][dy] && abs(dy - sy) == 1 && dx == sx + (Turn == 'W' ? -1 : 1))
	{
		if (lastMoveSX != -1 && lastMoveDX == sx && lastMoveDY == dy && abs(lastMoveSX - lastMoveDX) == 2 && dynamic_cast<Pawn*>(Grid[lastMoveDX][lastMoveDY]))
		{
			isEnPassant = true;
		}
	}
	if (!isEnPassant && !Grid[sx][sy]->IsValidMove(sx, sy, dx, dy, Grid))
	{
		return false;
	}
	bool isCastling = (dynamic_cast<King*>(Grid[sx][sy]) && abs(dy - sy) == 2);
	Piece* Temp = Grid[dx][dy];
	Piece* EnPassantVictim = nullptr;
	if (isEnPassant)
	{
		EnPassantVictim = Grid[sx][dy];
		Grid[sx][dy] = nullptr;
	}
	Piece* Moving = Grid[sx][sy];
	Grid[dx][dy] = Moving;
	Grid[sx][sy] = nullptr;
	int rookSX = -1, rookSY = -1, rookDX = -1, rookDY = -1;
	if (isCastling)
	{
		int step = (dy > sy) ? 1 : -1;
		rookSY = (step == 1) ? 7 : 0;
		rookSX = sx;
		rookDX = sx;
		rookDY = sy + step;
		Grid[rookDX][rookDY] = Grid[rookSX][rookSY];
		Grid[rookSX][rookSY] = nullptr;
	}
	if (IsCheck(Turn))
	{
		Grid[sx][sy] = Moving;
		Grid[dx][dy] = Temp;
		if (isEnPassant)
		{
			Grid[sx][dy] = EnPassantVictim;
		}
		if (isCastling)
		{
			Grid[rookSX][rookSY] = Grid[rookDX][rookDY];
			Grid[rookDX][rookDY] = nullptr;
		}
		return false;
	}
	if (isCastling)
	{
		int step = (dy > sy) ? 1 : -1;
		Grid[dx][dy] = nullptr;
		Grid[sx][sy + step] = Moving;
		bool passingCheck = IsCheck(Turn);
		Grid[sx][sy + step] = nullptr;
		Grid[dx][dy] = Moving;
		if (passingCheck)
		{
			Grid[sx][sy] = Moving;
			Grid[dx][dy] = Temp;
			Grid[rookSX][rookSY] = Grid[rookDX][rookDY];
			Grid[rookDX][rookDY] = nullptr;
			return false;
		}
	}
	if (Temp)
	{
		delete Temp;
	}
	if (EnPassantVictim)
	{
		delete EnPassantVictim;
	}
	Moving->SetHasMoved(true);
	if (isCastling)
	{
		Grid[rookDX][rookDY]->SetHasMoved(true);
	}
	PromotePawn(dx, dy);
	lastMoveSX = sx; lastMoveSY = sy; lastMoveDX = dx; lastMoveDY = dy;
	return true;
}
//SFML GUI Integration
Game::Game() : Window(sf::VideoMode(1000, 800), "Chess Master - SFML"), selectedX(-1), selectedY(-1)
{
	Turn = 'W';
	Window.setFramerateLimit(60);
	statusMessage = "Select Game Mode";
	state = GameState::MENU;
	vsComputer = false;
	LoadAssets();
}
void Game::LoadAssets()
{
	// Load a fallback font from Windows standard dir or local assets
	if (!font.loadFromFile("assets/board_font.ttf") && !font.loadFromFile("C:/Windows/Fonts/arial.ttf") && !font.loadFromFile("C:/Windows/Fonts/consola.ttf"))
	{
		std::cout << "Warning: Could not Load any Text Font." << std::endl;
	}
	struct PieceTextureEntry
	{
		char symbol;
		const char* filename;
	};
	const int pieceTextureCount = 12;
	PieceTextureEntry pieces[pieceTextureCount] =
	{
		{'P', "w_pawn.png"}, {'R', "w_rook.png"}, {'N', "w_knight.png"},
		{'B', "w_bishop.png"}, {'Q', "w_queen.png"}, {'K', "w_king.png"},
		{'p', "b_pawn.png"}, {'r', "b_rook.png"}, {'n', "b_knight.png"},
		{'b', "b_bishop.png"}, {'q', "b_queen.png"}, {'k', "b_king.png"}
	};
	for (int pi = 0; pi < pieceTextureCount; pi++)
	{
		sf::Texture tex;
		std::string path = std::string("assets/") + pieces[pi].filename;
		if (tex.loadFromFile(path))
		{
			tex.setSmooth(true);
			pieceTextures[pieces[pi].symbol] = tex;
		}
	}
}
void Game::HandleEvents()
{
	sf::Event event;
	while (Window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			Window.close();
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				int mouseX = event.mouseButton.x;
				int mouseY = event.mouseButton.y;
				if (state == GameState::MENU)
				{
					if (mouseX >= 350 && mouseX <= 650 && mouseY >= 400 && mouseY <= 460)
					{
						vsComputer = true;
						state = GameState::PLAYING;
						statusMessage = "Player 1 (White)'s Turn";
					}
					else if (mouseX >= 350 && mouseX <= 650 && mouseY >= 500 && mouseY <= 560)
					{
						vsComputer = false;
						state = GameState::PLAYING;
						statusMessage = "Player 1 (White)'s Turn";
					}
					continue;
				}
				if (state != GameState::PLAYING || (vsComputer && Turn == 'B'))
				{
					continue;
				}
				// Ensure click is inside the 800x800 board area
				if (mouseX >= 0 && mouseX < 800 && mouseY >= 0 && mouseY < 800)
				{
					int col = mouseX / 100;
					int row = mouseY / 100;

					if (selectedX == -1 && selectedY == -1)
					{
						// Select piece
						if (B.Grid[row][col] && B.Grid[row][col]->GetColour() == Turn)
						{
							selectedX = row;
							selectedY = col;
							statusMessage = (Turn == 'W' ? "White" : "Black");
							statusMessage += " Selected...";
						}
					}
					else if (selectedX == row && selectedY == col)
					{
						// Deselect
						selectedX = -1;
						selectedY = -1;
						statusMessage = (Turn == 'W' ? "Player 1 (White)'s Turn" : "Player 2 (Black)'s Turn");
					}
					else
					{
						// Attempt Move
						if (B.Grid[row][col] && B.Grid[row][col]->GetColour() == Turn) 
						{
							// Switched selection to another ally
							selectedX = row;
							selectedY = col;
						} 
						else 
						{
							// Try to move
							if (B.Move(selectedX, selectedY, row, col, Turn))
							{
								Turn = (Turn == 'W') ? 'B' : 'W';
								statusMessage = (Turn == 'W' ? "Player 1 (White)'s Turn" : "Player 2 (Black)'s Turn");
								if (B.IsCheck(Turn))
								{
									statusMessage = (Turn == 'W' ? "Player 1 (White) " : "Player 2 (Black) ");
									if (!B.HasAnyValidMove(Turn))
									{
										statusMessage = statusMessage + "IS CHECKMATED! GAME OVER";
									}
									else
									{
										statusMessage = statusMessage + "is in CHECK!";
									}
								}
								else if (!B.HasAnyValidMove(Turn))
								{
									statusMessage = "STALEMATE! GAME OVER";
								}
							}
							else
							{
								statusMessage = "Invalid Move!";
							}
							selectedX = -1;
							selectedY = -1;
						}
					}
				}
			}
		}
	}
}
void Game::Render()
{
	Window.clear(sf::Color(35, 35, 35));
	// Draw 8x8 Board
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			sf::RectangleShape square(sf::Vector2f(100.f, 100.f));
			square.setPosition(j * 100.f, i * 100.f);

			if ((i + j) % 2 == 0)
			{
				square.setFillColor(sf::Color(240, 217, 181)); // Light Wood
			}
			else
			{
				square.setFillColor(sf::Color(181, 136, 99));  // Dark Wood
			}
			// Highlight selection
			if (i == selectedX && j == selectedY)
			{
				square.setFillColor(sf::Color(246, 246, 105, 200)); // Yellowish
			}
			Window.draw(square);
			if (B.Grid[i][j])
			{
				char symbol = B.Grid[i][j]->GetSymbol();
				if (pieceTextures.count(symbol) > 0)
				{
					sf::Sprite sprite;
					sprite.setTexture(pieceTextures[symbol]);
					sf::Vector2u size = pieceTextures[symbol].getSize();
					// Scale texture so it roughly fits in 100x100
					sprite.setScale(100.f / size.x, 100.f / size.y);
					sprite.setPosition(j * 100.f, i * 100.f);
					Window.draw(sprite);
				}
				else
				{
					// Fallback to text
					sf::Text text;
					text.setFont(font);
					text.setString(std::string(1, symbol));
					text.setCharacterSize(64);
					text.setFillColor(B.Grid[i][j]->GetColour() == 'W' ? sf::Color::White : sf::Color::Black);
					text.setPosition(j * 100.f + 25.f, i * 100.f + 5.f);
					Window.draw(text);
				}
			}
		}
	}
	// Draw Side Menu
	sf::RectangleShape menuBackground(sf::Vector2f(200.f, 800.f));
	menuBackground.setPosition(800.f, 0.f);
	menuBackground.setFillColor(sf::Color(50, 50, 55));
	Window.draw(menuBackground);
	sf::Text title;
	title.setFont(font);
	title.setString("CHESS\nMASTER");
	title.setCharacterSize(28);
	title.setFillColor(sf::Color::White);
	title.setPosition(820.f, 40.f);
	title.setStyle(sf::Text::Bold);
	Window.draw(title);

	sf::Text status;
	status.setFont(font);
	status.setString(statusMessage);
	// Adjust char size dynamic to string length roughly
	if (statusMessage.length() > 15) 
	{
		status.setCharacterSize(16);
	} 
	else 
	{
		status.setCharacterSize(20);
	}
	// Coloring based on turn / check
	if (statusMessage.find("Invalid") != std::string::npos || statusMessage.find("CHECK") != std::string::npos)
	{
		status.setFillColor(sf::Color(255, 100, 100)); // Red ish
	}
	else
	{
		status.setFillColor(sf::Color(180, 255, 180)); // Green ish
	}
	status.setPosition(820.f, 400.f);
	Window.draw(status);
	Window.display();
}

void Game::RenderMenu()
{
	Window.clear(sf::Color(35, 35, 35));

	sf::Text title;
	title.setFont(font);
	title.setString("CHESS MASTER");
	title.setCharacterSize(64);
	title.setFillColor(sf::Color::White);
	title.setPosition(250.f, 200.f);
	Window.draw(title);

	sf::RectangleShape singleBtn(sf::Vector2f(300.f, 60.f));
	singleBtn.setPosition(350.f, 400.f);
	singleBtn.setFillColor(sf::Color(100, 150, 100));
	Window.draw(singleBtn);

	sf::Text singleTxt;
	singleTxt.setFont(font);
	singleTxt.setString("1 Player (vs PC)");
	singleTxt.setCharacterSize(24);
	singleTxt.setFillColor(sf::Color::White);
	singleTxt.setPosition(370.f, 415.f);
	Window.draw(singleTxt);

	sf::RectangleShape multiBtn(sf::Vector2f(300.f, 60.f));
	multiBtn.setPosition(350.f, 500.f);
	multiBtn.setFillColor(sf::Color(100, 100, 150));
	Window.draw(multiBtn);

	sf::Text multiTxt;
	multiTxt.setFont(font);
	multiTxt.setString("2 Players (Local)");
	multiTxt.setCharacterSize(24);
	multiTxt.setFillColor(sf::Color::White);
	multiTxt.setPosition(370.f, 515.f);
	Window.draw(multiTxt);

	Window.display();
}

void Game::MakeComputerMove()
{
	if (Turn != 'B' || !vsComputer || state != GameState::PLAYING)
	{
		return;
	}
	struct Mv { int sx, sy, dx, dy; };
	const int maxValidMoves = 512;
	Mv validMoves[maxValidMoves];
	int validMoveCount = 0;
	for (int sx = 0; sx < 8; sx++)
	{
		for (int sy = 0; sy < 8; sy++)
		{
			if (B.Grid[sx][sy] && B.Grid[sx][sy]->GetColour() == 'B')
			{
				for (int dx = 0; dx < 8; dx++)
				{
					for (int dy = 0; dy < 8; dy++)
					{
						bool isEnPassant = false;
						if (dynamic_cast<Pawn*>(B.Grid[sx][sy]) && !B.Grid[dx][dy] && abs(dy - sy) == 1 && dx == sx + 1)
							if (B.lastMoveSX != -1 && B.lastMoveDX == sx && B.lastMoveDY == dy && abs(B.lastMoveSX - B.lastMoveDX) == 2 && dynamic_cast<Pawn*>(B.Grid[B.lastMoveDX][B.lastMoveDY]))
							{
								isEnPassant = true;
							}
						if (isEnPassant || B.Grid[sx][sy]->IsValidMove(sx, sy, dx, dy, B.Grid))
						{
							Piece* Temp = B.Grid[dx][dy];
							B.Grid[dx][dy] = B.Grid[sx][sy];
							B.Grid[sx][sy] = nullptr;
							bool check = B.IsCheck('B');
							B.Grid[sx][sy] = B.Grid[dx][dy];
							B.Grid[dx][dy] = Temp;
							if (!check && validMoveCount < maxValidMoves)
							{
								validMoves[validMoveCount].sx = sx;
								validMoves[validMoveCount].sy = sy;
								validMoves[validMoveCount].dx = dx;
								validMoves[validMoveCount].dy = dy;
								validMoveCount++;
							}
						}
					}
				}
			}
		}
	}
	if (validMoveCount == 0)
	{
		return;
	}
	static bool seeded = false;
	if (!seeded) 
	{ 
		srand(time(0)); seeded = true; 
	}
	Mv chosen = validMoves[rand() % validMoveCount];
	if (B.Move(chosen.sx, chosen.sy, chosen.dx, chosen.dy, 'B'))
	{
		Turn = 'W';
		statusMessage = "Player 1 (White)'s Turn";
		if (B.IsCheck(Turn))
		{
			statusMessage = "Player 1 (White) ";
			if (!B.HasAnyValidMove(Turn))
			{
				statusMessage = statusMessage + "IS CHECKMATED! GAME OVER";
			}
			else
			{
				statusMessage = statusMessage + "is in CHECK!";
			}
		}
		else if (!B.HasAnyValidMove(Turn))
		{
			statusMessage = "STALEMATE! GAME OVER";
		}
	}
}
void Game::Start()
{
	while (Window.isOpen())
	{
		HandleEvents();
		if (state == GameState::MENU)
		{
			RenderMenu();
		}
		else
		{
			if (state == GameState::PLAYING && vsComputer && Turn == 'B')
			{
				MakeComputerMove();
			}
			Render();
		}
	}
}
// Convert is now practically unused, but kept for legacy compliance.
bool convert(std::string POS, int& x, int& y)
{
	if (POS.size() < 2) return false;
	if (POS[0] < 'a' || POS[0] > 'h') return false;
	if (POS[1] < '1' || POS[1] > '8') return false;
	y = POS[0] - 'a';
	x = 8 - (POS[1] - '0');
	return true;
}