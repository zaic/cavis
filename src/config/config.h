#pragma once

class Config {
	Config(const Config& );
	Config& operator=(const Config& );

protected:
	Config();

	// TODO: с целью уменьшения интерфейся, возможно, стоит прям здесь сделать счётчик фрэймов

public:
	virtual ~Config();

	virtual bool prevFrame() = 0;
	virtual bool nextFrame() = 0;
	virtual bool setFrame(int frame) = 0;
	virtual int getFramesCount() { return 1; }

	virtual char* getRealData() const = 0;
	virtual int getRealDimSize(int dim) const = 0;
	virtual int getRealDimSizeX() const { return getRealDimSize(0); }
	virtual int getRealDimSizeY() const { return getRealDimSize(1); }
	virtual int getRealDimSizeZ() const { return getRealDimSize(2); }

	// TODO: thinking...
	//virtual void setLogicSize(int x, int y) = 0;
};
