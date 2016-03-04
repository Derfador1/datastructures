#ifndef DEVICE_H
	#define DEVICE_H

#include "graph/graph.h"
#include "llist/llist.h"

struct device {
	double battery_power;
	double longitude;
	double latitude;
	float altitude;
	unsigned int source_dev_id;
	int count;	
};

#endif
