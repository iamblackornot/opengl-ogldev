#include <vector>

#include <GL/GLBuffer.h>
#include <GL/GLVertex.h>
#include <utility/helper.h>

class Cube
{
public:
	Cube();
	GLuint GetVertexBuffer();
	GLuint GetElementBuffer();
	
private:
	void FillVertexBuffer();
	void FillIndexBuffer();

private:
	GLVertexBuffer _vbuffer;
	GLElementBuffer _ebuffer;
};

