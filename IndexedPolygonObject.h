#ifndef __INDEXEDPOLYGONOBJECT_H__
#define __INDEXEDPOLYGONOBJECT_H__
#include <glad.h>
#include <string>
using namespace std;

class IndexedPolygonObject
{
private:
	GLuint elementBufferObject, vertexArrayObject, bufferArrayObject;
	GLuint programID;
	int nbrIndices;
protected:
public:
	IndexedPolygonObject(float* vertices, int nbrVertices, GLfloat* colors, int nbrColors, GLushort *triangles, int nbrTriangles, GLuint progID, string vertexAttributeString = "vPosition", string colorAttributeString="vColor");

	GLuint getProgramID() { return programID; }
	GLuint getElementBufferObject() { return elementBufferObject; }
	GLuint getVertexArrayObject() { return vertexArrayObject; }
	GLuint getBufferArrayObject() { return bufferArrayObject; }

	void display();
};

#endif
