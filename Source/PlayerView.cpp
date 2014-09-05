/*
* PlayerView.cpp
*
*  Created on: Dec 26, 2013
*      Author: Dimitri Kourkoulis
*/

#include "PlayerView.h"


namespace AvoidTheBug3D {

	PlayerView::PlayerView(boost::shared_ptr<Configuration> cfg,
		boost::shared_ptr<GameLog> log) {

			this->cfg = cfg;
			this->log = log;

			groundTexture = boost::shared_ptr<Image>(
				new Image("/Game/Data/OtherTextures/grass.png", cfg, log));

			skyTexture = boost::shared_ptr<Image>(
				new Image("/Game/Data/OtherTextures/sky.png", cfg, log));

			goat = boost::shared_ptr<WorldObject> (
				new WorldObject("animal",
				"/Game/Data/UnspecifiedAnimal/UnspecifiedAnimalWithTexture.obj",
				"/Game/Data/UnspecifiedAnimal/UnspecifiedAnimalWithTextureRedBlackNumbers.png",
				cfg, log));
			box = boost::shared_ptr<WorldObject> (
				new WorldObject("animal",
				"/Game/Data/Cube/CubeNoTexture.obj",
				cfg, log));
			box->setColour(1.0f, 1.0f, 0.0f, 1.0f);
			box->setOffset(1.5f, -1.0f, -8.0f);
			goat->setOffset(-1.2f, -1.0f, -4.0f);
			scene = boost::shared_ptr<vector<boost::shared_ptr<WorldObject> > >(
				new vector<boost::shared_ptr<WorldObject> >());
			scene->push_back(box);
			scene->push_back(goat);

			rotation = 0.0f;

			renderer = boost::shared_ptr<Renderer>(new Renderer(cfg, log));
			renderer->init(640, 480, false);

	}

	PlayerView::~PlayerView() {
		// TODO Auto-generated destructor stub
	}

	void PlayerView::render()
	{
		float groundVerts[16] =
		{
			1.0f, 0.0f, 1.0f, 1.0f,
			-1.0f, 0.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f, 1.0f
		};

		float skyVerts[16] =
		{
			1.0f, 1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f, 1.0f,
			-1.0f, 0.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 1.0f
		};
		

		if (rotation > 6.28)
			rotation = 0.0;
		rotation += 0.03f;

		goat->setRotation(rotation, rotation, rotation);
		box->setRotation(-rotation, rotation, rotation);

		renderer->drawScene(scene);
		
		renderer->renderTexturedQuad(&groundVerts[0], groundTexture->getData(), groundTexture->getWidth(), groundTexture->getHeight());
		renderer->renderTexturedQuad(&skyVerts[0], skyTexture->getData(), skyTexture->getWidth(), skyTexture->getHeight());
		renderer->renderText("Hello");
		renderer->swapBuffers();

	}

} /* namespace AvoidTheBug3D */
