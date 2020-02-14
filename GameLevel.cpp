#include "GameLevel.h"
#include <fstream>
#include <sstream>

void GameLevel::Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight)
{
  this->Bricks.clear();
  GLuint tileCode;
  GameLevel level;
  std::string line;
  std::ifstream fstream(file);
  std::vector<std::vector<GLuint>> tileData;

  if (fstream)
    {
      while (std::getline(fstream, line))
	{
	  std::istringstream sstream(line);
	  std::vector<GLuint> row;
	  while (sstream >> tileCode)
	    row.push_back(tileCode);
	  tileData.push_back(row);
	}
      if (tileData.size() > 0)
	this->init(tileData, levelWidth, levelHeight);
    }
}

void GameLevel::Draw(SpriteRenderer &renderer)
{
  for (GameObject &title : this->Bricks)
    if (!title.Destroyed)
      title.Draw(renderer);
}

GLboolean GameLevel::IsCompleted()
{
  for (GameObject &title : this->Bricks)
    if (!title.IsSolid && !title.Destroyed)
      return GL_FALSE;
  return GL_TRUE;
}

void GameLevel::init(std::vector<std::vector<GLuint>> titleData, GLuint levelWidth, GLuint levelHeight)
{
  GLuint height = titleData.size();
  GLuint width = titleData[0].size();
  GLfloat uint_width = levelWidth / static_cast<GLfloat>(width);
  GLfloat uint_height = levelHeight / height;

  for (GLuint y = 0; y < height; ++y)
    {
      for (GLuint x = 0; x < width; ++x)
	{
	  if (titleData[y][x] == 1)
	    {
	      glm::vec2 pos(uint_width * x, uint_height * y);
	      glm::vec2 size(uint_width, uint_height);
	      GameObject obj(pos, size, ResourceManager::GetTexture("block_solid"), glm::vec3(0.8f, 0.8f, 0.7f));
	      obj.IsSolid = GL_TRUE;
	      this->Bricks.push_back(obj);
	    }
	  else if (titleData[y][x] > 1)
	    {
	      glm::vec3 color = glm::vec3(1.0f);
	      if (titleData[y][x] == 2)
		color = glm::vec3(0.2f, 0.6f, 1.0f);
	      else if (titleData[y][x] == 3)
		color = glm::vec3(0.0f, 0.7f, 0.0f);
	      else if (titleData[y][x] == 4)
		color == glm::vec3(0.8f, 0.8f, 0.4f);
	      else if (titleData[y][x] == 5)
		color == glm::vec3(1.0f, 0.5f, 0.0f);

	      glm::vec2 pos(uint_width * x, uint_height * y);
	      glm::vec2 size(uint_width, uint_height);
	      this->Bricks.push_back(GameObject(pos, size, ResourceManager::GetTexture("block"), color));
	    }
	}
    }
}//end function init
