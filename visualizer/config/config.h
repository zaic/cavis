#pragma once

class Config {
	Config(const Config& );
	Config& operator=(const Config& );

protected:
	Config();

public:
	Config(const char *filename, int x = 0, int y = 0);
	virtual ~Config();

	virtual bool prev() = 0;
	virtual bool next() = 0;
	virtual bool setFrame(int frame) = 0;
	virtual int getFramesCount() const = 0;

	virtual char* getRealData() const = 0;
	virtual int getRealDimSize(int dim) const = 0;
	virtual int getRealDimSizeX() const { return getRealDimSize(0); }
	virtual int getRealDimSizeY() const { return getRealDimSize(1); }
	virtual int getRealDimSizeZ() const { return getRealDimSize(2); }

	virtual void setLogicSize(int x, int y) = 0;
};
