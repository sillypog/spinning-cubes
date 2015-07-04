using namespace std;

class Framecounter {
	float t0;
	int frames;

public:
	Framecounter() : t0(glfwGetTime()), frames(0) {}

	~Framecounter(){
		float t1 = glfwGetTime();
		float dt = t1 - t0;
	    float fps = frames/dt;
	    float mspf = (dt * 1000) / frames;
	    cout << "FPS: " << fps << " over " << dt << " seconds." << endl;
	    cout << "MSPF: " << mspf << " over " << frames << " frames." << endl;
	}

	void tick(){
		frames++;
	}
};
