#pragma once

#include <string>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <vector>
#include <boost/smart_ptr.hpp>
#include "GameLog.h"
#include "Configuration.h"

using namespace std;

namespace AvoidTheBug3D {

/// A game character
class Model {
private:
	vector<float*> *vertices;
	vector<int*> *faces;
	boost::shared_ptr<Configuration> cfg;
	boost::shared_ptr<GameLog> log;
	void loadFromFile(string fileLocation);
	float *vertexData;
	int vertexDataSize;
	int vertexDataComponentCount;
	bool multiColour;
	bool indexedDrawing;
	int *indexData;
	int indexDataSize;
	int indexDataIndexCount;

public:
	/**
	 * Initialisation of the model.
	 * @param fileLocation The model file location. This must be a Wavefront .obj file and it must have been
	 * exported from Blender with the options "Triangulate faces" and "Keep Vertex Order" checked
	 * @param multiColour Whether or not each face will be rendered with a random colour
	 * @param cfg The game configuration
	 * @param log The log
	 */
	Model(string fileLocation, bool multiColour, bool indexedDrawing,
			const boost::shared_ptr<Configuration> &cfg, const boost::shared_ptr<GameLog> &log);
	~Model(void);

	/**
	 * Output vertices to stdout
	 */
	void outputVertices();

	/**
	 * Output faces to stdout
	 */
	void outputFaces();

	/**
	 * Get the number of vertices in the model
	 * @return The number of vertices
	 */
	int getNumVertices();

	/**
	 * Get the number of faces in the model
	 * @return The number of faces
	 */
	int getNumFaces();

	/**
	 * Get the vertices of the model
	 * @return The vertices
	 */
	vector<float*>* getVertices();

	/**
	 * Get the faces of the model
	 * @return The faces
	 */
	vector<int*>* getFaces();

	/**
	 * Get the index data, i.e. the indexes of each vertex to be drawn
	 * when the indexed drawing flag has been set.
	 * @return
	 */
	int * getIndexData();

	/**
	 * Get the vertex data, e.g. to be sent to glBindBuffer.
	 * The structure of the data can be defined via the Model's state.
	 * @return The vertex data
	 */
	float * getVertexData();


	/**
	 * Output the vertex data. The structure of the data can be defined
	 * via the Model's state.
	 */
	void outputVertexData();

	/**
	 * Get the number of components in the vertex data array
	 * @return The number of vertex data components
	 */
	int getVertexDataComponentCount();

	/**
	 * Get the size of the vertex data, in bytes.
	 * @return The size of the vertex data
	 */
	int getVertexDataSize();

	/**
	 * Is the model in indexed drawing mode?
	 * @return True if in indexed drawing mode, false otherwise
	 */
	bool isIndexedDrawing() const;

	/**
	 * Get the size of the index data
	 * @return The size of the index data
	 */
	int getIndexDataSize() const;

	/**
	 * Has the model been set to be drawn in random multiple colours?
	 * @return True if the model has been set to be drawn in random multiple colours, false otherwise
	 */
	bool isMultiColour() const;
};

}
