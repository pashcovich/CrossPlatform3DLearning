/*
* BoundingBoxes.cpp
*
*  Created on: Oct 10, 2014
*      Author: Dimitri Kourkoulis
*/

#include "BoundingBoxes.h"
#include <fstream>
#include "GameException.h"
#include "GetTokens.h"
#include <stdlib.h>
#include <glm/glm.hpp>
#include "GameMath.h"

namespace AvoidTheBug3D {

	/**
	* Constructor
	* 
	* @param	cfg	The configuration.
	* @param	log	The log.
	*/
	BoundingBoxes::BoundingBoxes(const boost::shared_ptr<Configuration> cfg, const boost::shared_ptr<GameLog> log) {
		this->cfg = cfg;
		this->log = log;

		vertices = new vector<float *>();
		vertices->clear();
		facesVertexIndexes = new vector<int *>();
		facesVertexIndexes->clear();
	}

	BoundingBoxes::~BoundingBoxes() {
		if (vertices != NULL)
		{
			for (int i = 0; i != vertices->size(); ++i)
			{
				delete[] vertices->at(i);
			}
			vertices->clear();
			delete vertices;
			vertices = NULL;
		}

		if (facesVertexIndexes != NULL)
		{
			for (int i = 0; i != facesVertexIndexes->size(); ++i)
			{
				delete[] facesVertexIndexes->at(i);
			}
			facesVertexIndexes->clear();
			delete facesVertexIndexes;
			facesVertexIndexes = NULL;
		}
	}

	void BoundingBoxes::loadFromFile( string fileLocation )
	{
		if (vertices->size() != 0)
		{
			throw GameException(
				"Illegal attempt to reload bounding boxes. Please use another object.");
		}
		ifstream file((cfg->getHomeDirectory() + fileLocation).c_str());
		string line;
		if (file.is_open())
		{
			while (getline(file, line))
			{
				if (line[0] == 'v' || line[0] == 'f')
				{
					string *tokens = new string[5]; // Max 5 such tokens in the specific kind of
					// Wavefront file

					int numTokens = getTokens(line, ' ', tokens);

					int idx = 0;

					if (line[0] == 'v')
					{
						// get vertex
						float *v = new float[4];

						for (int tokenIdx = 0; tokenIdx < numTokens; ++tokenIdx)
						{
							string t = tokens[tokenIdx];
							if (idx > 0)   // The first token is the vertex indicator
							{
								v[idx - 1] = (float) atof(t.c_str());
							}
							++idx;
						}
						vertices->push_back(v);
					}
					else
					{
						// get vertex index
						int *v = new int[4];

						for (int tokenIdx = 0; tokenIdx < numTokens; ++tokenIdx)
						{
							string t = tokens[tokenIdx];
							if (idx > 0)   // The first token is face indicator
							{
								v[idx - 1] = atoi(t.c_str());
							}
							++idx;
						}
						facesVertexIndexes->push_back(v);

					}

					if (tokens != NULL)
					{
						delete[] tokens;
					}
				}
			}
		}
		file.close();

		numBoxes = facesVertexIndexes->size() / 6;
	}

	bool BoundingBoxes::pointCollides( const float &pointX, const float &pointY, const float &pointZ, 
		const float &boxesX, const float &boxesY, const float &boxesZ, const float &boxesRotation)
	{
		bool collides = false;
		glm::mat4x4 *rotationMatrix = rotateY(boxesRotation);
	
		for (int idx = 0; idx < numBoxes; ++idx) {
			float minZ, maxZ, minX, maxX, minY, maxY;

			glm::vec4 *coords = new glm::vec4(vertices->at(idx * 8)[0], vertices->at(idx * 8)[1], vertices->at(idx * 8)[2], 1);
			glm::vec4 *rotatedCoords = new glm::vec4(0.0f, 0.0f, 0.0f, 1.0f); 
			
			*rotatedCoords = (*rotationMatrix) * (*coords);

			rotatedCoords->x += boxesX;
			rotatedCoords->y += boxesY;
			rotatedCoords->z += boxesZ;

			minX = rotatedCoords->x;
			maxX = rotatedCoords->x;
			minY = rotatedCoords->y;
			maxY = rotatedCoords->y;
			minZ = rotatedCoords->z;
			maxZ = rotatedCoords->z;

			for (int checkidx = idx * 8; checkidx < (idx + 1) * 8; ++checkidx )
			{
				*coords = glm::vec4(vertices->at(checkidx)[0], vertices->at(checkidx)[1], vertices->at(checkidx)[2], 1);
				*rotatedCoords = (*rotationMatrix) * (*coords);
				
				rotatedCoords->x += boxesX;
				rotatedCoords->y += boxesY;
				rotatedCoords->z += boxesZ;

				if (rotatedCoords->x < minX)
					minX = rotatedCoords->x;
				if (rotatedCoords->x > maxX)
					maxX = rotatedCoords->x;
				if (rotatedCoords->y < minY)
					minY = rotatedCoords->y;
				if (rotatedCoords->y > maxY)
					maxY = rotatedCoords->y;
				if (rotatedCoords->z < minZ)
					minZ = rotatedCoords->z;
				if (rotatedCoords->z > maxZ)
					maxZ = rotatedCoords->z;
			}

			delete coords;
			delete rotatedCoords;

			if (pointX > minX && pointX < maxX &&
				pointY > minY && pointY < maxY &&
				pointZ > minZ && pointZ < maxZ) {
					collides = true;
					break;
			}
		}
		delete rotationMatrix;
		
		return collides;
	}

}