#pragma once

class Timer
{
private:
	Timer() { }
	~Timer() { }

public:
	static Timer* GetInstance()
	{
		static Timer instance;
		return &instance;
	}

public:
	void Init();
	void Update();

	uint32 GetFps() { return _fps; }
	float GetDeltaTime() { return _deltaTime; }

private:
	uint64	_frequency = 0;
	uint64	_prevCount = 0;
	float	_deltaTime = 0.f;

private:
	uint32	_frameCount = 0;
	float	_frameTime = 0.f;
	uint32	_fps = 0;
};
