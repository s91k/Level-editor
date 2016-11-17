#include "GameEngine.h"

GameEngine::GameEngine()
{
	this->m_ScreenWidth = 0;
	this->m_ScreenHeight = 0;

	this->m_background = NULL;

	this->m_selectedPlanet = NULL;
	this->m_selectedShip = NULL;

	this->m_selectedType = GameEngine::NONE;
	this->m_nextAction = GameEngine::SELECT;
	this->m_currentWave = 0;

	this->m_ship.push_back(vector<Ship*>());
}
GameEngine::~GameEngine()
{
	delete this->m_background;
	delete this->m_spaceStation;
	
	for(unsigned int i = 0; i < this->m_planet.size(); i++)
	{
		delete this->m_planet[i];
	}

	for(unsigned int i = 0; i < this->m_ship.size(); i++)
	{
		for(unsigned int j = 0; j < this->m_ship[i].size(); i++)
		{
			delete this->m_ship[i][j];
		}
	}
}

HRESULT GameEngine::Init(HWND hWnd, int width, int height)
{
	this->m_ScreenWidth = width;
	this->m_ScreenHeight = height;

	this->m_graphicsHandler.init(width, height, hWnd);
	this->m_graphicsHandler.useForwardRendering();
	this->m_resourceHolder = ResourceHolder(&this->m_graphicsHandler);

	this->m_background = new Background(&this->m_graphicsHandler, &this->m_resourceHolder);
	this->m_spaceStation = new SpaceStation(&this->m_graphicsHandler, &this->m_resourceHolder, D3DXVECTOR3(0.0f, -5.0f, 0.0f), 1.0f);
	
	this->m_camera = Camera(D3DXVECTOR3(0.0f, 24.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 25.0f, 0.0f), (float)D3DX_PI * 0.6f, (float)(this->m_ScreenWidth / this->m_ScreenHeight), 1.0f, 1000000.0f);
	this->m_moveCamera = this->m_camera.getPos();

	//Load in all models at initilization to avoid freezes
	this->m_resourceHolder.getModel("PlanetImport");
	this->m_resourceHolder.getModel("Ship_1_Phantom");
	this->m_resourceHolder.getModel("Ship_1_ArrowHead");
	this->m_resourceHolder.getModel("Ship_1_SpeedsterK4");
	this->m_resourceHolder.getModel("Ship_1_Hellreaver"); 

	return S_OK;
}
HRESULT GameEngine::Shutdown()
{
	return S_OK;
}

HRESULT GameEngine::ProcessFrame()
{
	FrameFunc();
	RenderFunc();
	return S_OK;
}
HRESULT GameEngine::OnResize(int width, int height)
{
	m_ScreenWidth = width;
	m_ScreenHeight = height;

	return S_OK;
}

bool GameEngine::FrameFunc()
{
	//D3DXVECTOR3 pos = this->m_camera.getPos();

	////Move up
	//if(GetAsyncKeyState('W'))
	//{
	//	
	//}
	////Move down
	//if(GetAsyncKeyState('S'))
	//{
	//	pos.z = pos.z - 0.01f;
	//}
	////Move left
	//if(GetAsyncKeyState('A'))
	//{
	//	pos.x = pos.x - 0.01f;
	//}
	////Move right
	//if(GetAsyncKeyState('D'))
	//{
	//	pos.x = pos.x + 0.01f;
	//}

	this->m_camera.update(100, D3DXVECTOR2(this->m_moveCamera.x, this->m_moveCamera.z), D3DXVECTOR2(this->m_moveCamera.x, this->m_moveCamera.z));
	this->m_camera.calcViewMatrix();
	this->m_moveCamera = this->m_camera.getPos();

	this->m_background->update(this->m_camera.getPos());

	return false;
}

void GameEngine::RenderFunc()
{
	this->m_graphicsHandler.applyCamera(this->m_camera);
	this->m_graphicsHandler.clearDefaultRenderTargetView();

	this->m_background->render();
	this->m_spaceStation->render();

	for(unsigned int i = 0; i < this->m_planet.size(); i++)
	{
		this->m_planet[i]->render();
	}

	for(unsigned int i = 0; i < this->m_ship[this->m_currentWave].size(); i++)
	{
		this->m_ship[this->m_currentWave][i]->render();
	}

	this->m_graphicsHandler.present();
}

void GameEngine::setWave(int wave, bool moveSelected)
{
	int MAX_NR_OF_WAVES = 20;

	if(wave < 0 )
	{
		wave = 0;
	}
	else if(wave >= MAX_NR_OF_WAVES)
	{
		wave = MAX_NR_OF_WAVES - 1;
	}

	//Check if any new waves needs to be created
	while((int)this->m_ship.size() <= wave)
	{
		this->m_ship.push_back(vector<Ship*>());
	}

	if(moveSelected == true)
	{
		for(unsigned int i = 0; i < this->m_ship[this->m_currentWave].size(); i++)
		{
			if(this->m_ship[this->m_currentWave][i] == this->m_selectedShip)
			{
				//Copy the selected ship and remove the original
				this->m_selectedShip = new Ship(*this->m_selectedShip);
				this->m_ship[this->m_currentWave].erase(this->m_ship[this->m_currentWave].begin() + i);
				i = this->m_ship[this->m_currentWave].size();
			}
		}

		this->m_ship[wave].push_back(this->m_selectedShip);
	}
	else if(this->m_selectedType == GameEngine::SHIP)
	{
		this->m_selectedShip = NULL;
		this->m_selectedPlanet = NULL;
		this->m_selectedType = GameEngine::NONE;
	}

	this->m_currentWave = wave;
}

int GameEngine::getWave()
{
	return this->m_currentWave;
}

void GameEngine::spawnPlanetAtPos(D3DXVECTOR2 pos)
{
	Planet *p = new Planet(&this->m_graphicsHandler, &this->m_resourceHolder, D3DXVECTOR3(pos.x, 0.0f,pos.y), 1.0f, Planet::SURFACE_ICE);

	this->m_planet.push_back(p);
	this->m_selectedPlanet = p;
	this->m_selectedType = PLANET;
}

void GameEngine::spawnEnemyAtPos(D3DXVECTOR2 pos)
{
	Ship *s = new Ship(&this->m_graphicsHandler, &this->m_resourceHolder, D3DXVECTOR3(pos.x, 0.0f, pos.y), 1.0f, Ship::SHIP_PHANTOM, Ship::PILOT_STANDARD);

	this->m_ship[this->m_currentWave].push_back(s);
	this->m_selectedShip = s;
	this->m_selectedType = SHIP;
}

void GameEngine::selectPlanetAtPos(D3DXVECTOR2 pos)
{
	this->m_selectedPlanet = NULL;

	//Convert coordinates
	float distance = 0.0f;
	D3DXVECTOR2 planetPos;

	for(unsigned int i = 0; i < this->m_planet.size(); i++)
	{
		planetPos = this->m_planet[i]->get2DPosition();
		distance = sqrt(pow((pos.x - planetPos.x), 2.0f) + pow((pos.y - planetPos.y), 2.0f));

		if(distance < 4.0f)	//Find a way to get planet radius
		{
			this->m_selectedPlanet = this->m_planet[i];
			this->m_selectedType = GameEngine::PLANET;
			break;
		}
	}
}

void GameEngine::selectShipAtPos(D3DXVECTOR2 pos)
{
	this->m_selectedShip = NULL;

	//Convert coordinates
	float distance = 0.0f;
	D3DXVECTOR2 shipPos;

	for(unsigned int i = 0; i < this->m_ship.size(); i++)
	{
		for(unsigned int j = 0; j < this->m_ship[i].size(); j++)
		{
			shipPos = this->m_ship[i][j]->get2DPosition();
			distance = sqrt(pow((pos.x - shipPos.x), 2.0f) + pow((pos.y - shipPos.y), 2.0f));

			if(distance < 2.0f)	//Find a way to get planet radius
			{
				this->m_selectedShip = this->m_ship[i][j];
				this->m_selectedType = GameEngine::SHIP;
				break;
			}
		}
	}
}

int GameEngine::getSelectedType()
{
	return (int)this->m_selectedType;
}

void GameEngine::handleMouseClick(float x, float y)
{
	D3DXVECTOR2 mousePos;
	D3DXVECTOR3 cameraPos = this->m_camera.getPos();

	mousePos.x = (tanf(45.0f) * (x / (this->m_ScreenWidth / 2) - 1.0f) / (this->m_ScreenWidth / this->m_ScreenHeight) * 20.0f + cameraPos.x);
	mousePos.y = (tanf(45.0f) * (1.0f - y / (this->m_ScreenHeight / 2)) * 10.6f + cameraPos.z);

	switch(this->m_nextAction)
	{
	case GameEngine::SELECT:
		this->m_selectedType = GameEngine::NONE;
		this->selectPlanetAtPos(mousePos);

		if(this->m_selectedType == GameEngine::NONE)
		{
			this->selectShipAtPos(mousePos);
		}

		break;

	case GameEngine::SPAWN_PLANET:
		this->spawnPlanetAtPos(mousePos);
		this->m_nextAction = GameEngine::SELECT;
		break;

	case GameEngine::SPAWN_ENEMY:
		this->spawnEnemyAtPos(mousePos);
		this->m_nextAction = GameEngine::SELECT;
		break;
	}
}

void GameEngine::spawnPlanet()
{
	this->m_nextAction = GameEngine::SPAWN_PLANET;
}

void GameEngine::spawnEnemy()
{
	this->m_nextAction = GameEngine::SPAWN_ENEMY;
}

void GameEngine::setTexture(int texture)
{
	switch(this->m_selectedType)
	{
	case GameEngine::PLANET:
		this->m_selectedPlanet->setSurface((Planet::Surfaces)texture);
		break;
	case GameEngine::SHIP:
		break;
	}
}

int GameEngine::getTexture()
{
	switch(this->m_selectedType)
	{
	case GameEngine::PLANET:
		return (int)this->m_selectedPlanet->getSurface();
	default:
		return 0;
	}
}

D3DXVECTOR3 GameEngine::getSelectedPos()
{
	switch(this->m_selectedType)
	{
	case GameEngine::PLANET:
		return this->m_selectedPlanet->getPosition();
		
	case GameEngine::SHIP:
		return this->m_selectedShip->getPosition();

	default:
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

float GameEngine::getSelectedScale()
{
	if(this->m_selectedPlanet != NULL)
	{
		return this->m_selectedPlanet->getScale();
	}
	else
	{
		return 0.0f;
	}
}

bool GameEngine::getSelectedSolid()
{
	if(this->m_selectedPlanet != NULL)
	{
		return this->m_selectedPlanet->getSolid();
	}
	else
	{
		return false;
	}
}

int GameEngine::getSelectedShipType()
{
	if(this->m_selectedShip != NULL)
	{
		return (int)this->m_selectedShip->getShipType();
	}
	else
	{
		return 0;
	}
}

int GameEngine::getSelectedPilot()
{
	if(this->m_selectedShip != NULL)
	{
		return (int)this->m_selectedShip->getPilot();
	}
	else
	{
		return 0;
	}
}

void GameEngine::setSelectedPos(D3DXVECTOR3 pos)
{
	switch(this->m_selectedType)
	{
	case GameEngine::PLANET:
		this->m_selectedPlanet->setPosition(pos);
		break;
		
	case GameEngine::SHIP:
		this->m_selectedShip->setPosition(pos);
		break;
	}
}

void GameEngine::setSelectedScale(float scale)
{
	if(this->m_selectedPlanet != NULL)
	{
		this->m_selectedPlanet->setScale(scale);
	}
}

void GameEngine::setSelectedSolid(bool solid)
{
	if(this->m_selectedPlanet != NULL)
	{
		this->m_selectedPlanet->setSolid(solid);
	}
}

void GameEngine::setSelectedShipType(int shipType)
{
	if(this->m_selectedType == GameEngine::SHIP)
	{
		this->m_selectedShip->setShipType((Ship::ShipTypes)shipType, &this->m_resourceHolder);
	}
}

void GameEngine::setSelectedPilot(int pilot)
{
	if(this->m_selectedType == GameEngine::SHIP)
	{
		this->m_selectedShip->setPilot((Ship::PilotTypes)pilot);
	}
}

char* GameEngine::getSelectedInfo()
{
	char* output;

	switch(this->m_selectedType)
	{
	case GameEngine::SHIP:
		output = "Ship";
		break;
	case GameEngine::PLANET:
		output = "Planet";
		break;
	default:
		output = "None";
		break;
	}

	return output;
}

void GameEngine::removeSelected()
{
	switch(this->m_selectedType)
	{
	case GameEngine::PLANET:
		for(unsigned int i = 0; i < this->m_planet.size(); i++)
		{
			if(this->m_planet[i] == this->m_selectedPlanet)
			{
				this->m_selectedPlanet = NULL;
				this->m_planet.erase(this->m_planet.begin() + i);
				this->m_selectedType = GameEngine::NONE;
			}
		}

		break;
	case GameEngine::SHIP:
		for(unsigned int i = 0; i < this->m_ship.size(); i++)
		{
			for(unsigned int j = 0; j < this->m_ship[i].size(); j++)
			{
				if(this->m_ship[i][j] == this->m_selectedShip)
				{
					this->m_selectedShip = NULL;
					this->m_ship[i].erase(this->m_ship[i].begin() + j);
					this->m_selectedType = GameEngine::NONE;
				}
			}
		}

		break;
	}
}

void GameEngine::clearLevel()
{
	for(unsigned int i = 0; i < this->m_ship.size(); i++)
	{
		this->m_ship[i].clear();
	}

	this->m_ship.clear();
	this->m_planet.clear();

	this->m_ship.push_back(vector<Ship*>());
	this->m_currentWave = 0;
	this->m_selectedPlanet = NULL;
	this->m_selectedShip = NULL;
	this->m_selectedType = GameEngine::NONE;

	this->m_camera = Camera(D3DXVECTOR3(0.0f, 24.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 25.0f, 0.0f), (float)D3DX_PI * 0.6f, (float)(this->m_ScreenWidth / this->m_ScreenHeight), 1.0f, 1000000.0f);
	this->m_camera.calcViewMatrix();
}

void GameEngine::exportLevel(char* path)
{
	ofstream output;
	output.open(path, ios::out);

	if(output.is_open() == true)
	{
		//print the planets
		for(unsigned int i = 0; i < this->m_planet.size(); i++)
		{
			output << "planet\n";
			output << "pos " << this->m_planet[i]->getPosition().x << " " << this->m_planet[i]->getPosition().y<< " " << this->m_planet[i]->getPosition().z << "\n";
			output << "scale " << this->m_planet[i]->getScale() << "\n";
			output << "texture " << (int)this->m_planet[i]->getSurface() << "\n";
			output << "solid " << (int)this->m_planet[i]->getSolid() << "\n";
			output << "end\n";
		}

		//print the ships
		for(unsigned int i = 0; i < this->m_ship.size(); i++)
		{
			for(unsigned int j = 0; j < this->m_ship[i].size(); j++)
			{
				output << "ship\n";
				output << "pos " << this->m_ship[i][j]->getPosition().x << " " << this->m_ship[i][j]->getPosition().y<< " " << this->m_ship[i][j]->getPosition().z << "\n";
				output << "type " << (int)this->m_ship[i][j]->getShipType() << "\n";
				output << "pilot " << (int)this->m_ship[i][j]->getPilot() << "\n";
				output << "wave " << i << "\n";
				output << "end\n";
			}
		}

		output.close();
	}
}

bool GameEngine::importLevel(char* path)
{
	enum ObjectType{NONE, PLANET, SHIP};

	D3DXVECTOR3 pos;
	float scale = 1.0f;
	int texture = 0;
	int type = 0;
	int pilot = 0;
	bool solid = true;
	unsigned int wave = 0;

	ObjectType currentType = NONE;

	ifstream stream;
	stream.open(path);

	if(stream.is_open() == true)
	{
		this->clearLevel();

		while(stream.eof() == false)
		{
			char buf[1024];
			char key[100];
			stream.getline(buf, 1024);
			sscanf(buf, "%s", key);

			if(strcmp(key, "planet") == 0) // New planet
			{
				currentType = PLANET;

				//Set default values
				pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				texture = (int)Planet::SURFACE_ICE;
				scale = 1.0f;
			}
			else if(strcmp(key, "wave") == 0) // New ship
			{
				int i;
				sscanf(buf, "wave %d", &i);
				wave = (int)i;	
			}
			else if(strcmp(key, "ship") == 0) // New ship
			{
				currentType = SHIP;

				//Set default values
				pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				type = 0;
				pilot = 0;
			}
			else if(strcmp(key, "pos") == 0) // Position
			{
				float x, y, z;
				sscanf(buf, "pos %f %f %f", &x, &y, &z);
				pos = D3DXVECTOR3(x, y, z);			
			}
			else if(strcmp(key, "texture") == 0) // Texture
			{
				int i;
				sscanf(buf, "texture %d", &i);
				texture = (int)i;				
			}
			else if(strcmp(key, "type") == 0) // Ship type
			{
				int i;
				sscanf(buf, "type %d", &i);
				type = (int)i;				
			}
			else if(strcmp(key, "pilot") == 0) // Pilot
			{
				int i;
				sscanf(buf, "pilot %d", &i);
				pilot = (int)i;				
			}
			else if(strcmp(key, "scale") == 0) // Scale
			{
				float f;
				sscanf(buf, "scale %f", &f);
				scale = f;	
			}
			else if(strcmp(key, "solid") == 0) // Texture
			{
				int i;
				sscanf(buf, "solid %d", &i);
				solid = (bool)i;				
			}
			else if(strcmp(key, "end") == 0) // Create current object
			{
				switch(currentType)
				{
				case PLANET:
					this->m_planet.push_back(new Planet(&this->m_graphicsHandler, &this->m_resourceHolder, pos, scale, (Planet::Surfaces)texture));
					this->m_planet[this->m_planet.size() - 1]->setSolid(solid);

					break;

				case SHIP:
					//Add new waves if needed
					while(wave >= this->m_ship.size())
					{
						this->m_ship.push_back(vector<Ship*>());
					}

					Ship *s = new Ship(&this->m_graphicsHandler, &this->m_resourceHolder, D3DXVECTOR3(pos.x, pos.y, pos.z), 1.0f, (Ship::ShipTypes)type, (Ship::PilotTypes)pilot);
					this->m_ship[wave].push_back(s);
					
					break;
				}
			}
		}

		stream.close();
		return true;
	}
	else
	{
		return false;
	}
}

void GameEngine::moveCameraUp(float distance)
{
	this->m_moveCamera.z = this->m_moveCamera.z + distance;
}

void GameEngine::moveCameraDown(float distance)
{
	this->m_moveCamera.z = this->m_moveCamera.z - distance;
}

void GameEngine::moveCameraLeft(float distance)
{
	this->m_moveCamera.x = this->m_moveCamera.x - distance;
}

void GameEngine::moveCameraRight(float distance)
{
	this->m_moveCamera.x = this->m_moveCamera.x + distance;
}