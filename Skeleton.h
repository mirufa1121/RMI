#ifndef SKELETON_H__
#define SKELETON_H__

/**
 * All skeleton objects inherit from this class.
 **/

class Skeleton {

public:
	virtual char *invoke(char *);
	virtual ~Skeleton() = 0;
};

inline Skeleton::~Skeleton(){}

#endif // REMOTE_H__