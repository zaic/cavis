#pragma once

class Config {
	Config(const Config& );
	Config& operator=(const Config& );

protected:
	int current_frame_id;

	Config();

public:
	virtual ~Config();

	static const int FRAME_NOT_CHANGED = -1807;
	virtual int prevFrame() { return setFrame(current_frame_id - 1); }
	virtual int nextFrame() { return setFrame(current_frame_id + 1); }
	virtual int setFrame(int) { return FRAME_NOT_CHANGED; }
	virtual int getFramesCount() { return 0; }

	virtual const char* getRealData() const = 0;
	virtual int getRealDimSize(int dim) const = 0;
	virtual int getRealDimSizeX() const { return getRealDimSize(0); }
	virtual int getRealDimSizeY() const { return getRealDimSize(1); }
	virtual int getRealDimSizeZ() const { return getRealDimSize(2); }

	// TODO: thinking...
	//virtual void setLogicSize(int x, int y) = 0;
};
