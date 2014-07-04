#pragma once

/*
 * Image.h
 *
 *  Created on: 2 Jul 2014
 *      Author: Dimitri Kourkoulis
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include <string>
#include <boost/smart_ptr.hpp>
#include "GameLog.h"
#include "Configuration.h"

using namespace std;

namespace AvoidTheBug3D {


class Image {
public:
	Image(string fileLocation, const boost::shared_ptr<Configuration> &cfg,
				const boost::shared_ptr<GameLog> &log);

	virtual ~Image();
};

}
#endif /* IMAGE_H_ */
