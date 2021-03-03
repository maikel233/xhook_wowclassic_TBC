#ifndef INONCOPYABLE_H
#define INONCOPYABLE_H

class INonCopyable
{
protected:
	INonCopyable() {}
	virtual ~INonCopyable() {}

private:
	INonCopyable(const INonCopyable& rhs);
	const INonCopyable operator=(const INonCopyable& rhs);
};

class IManager
{
protected:
	IManager() {}
	virtual ~IManager() {}

public:
	virtual void vStartUp() = 0;
	virtual void vShutDown() = 0;
};

#endif // INONCOPYABLE_H