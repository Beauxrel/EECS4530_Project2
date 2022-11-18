#include "IndexedPolygonObject.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))

IndexedPolygonObject::IndexedPolygonObject(GLfloat* vertices, int nbrVertices, GLfloat* colors, int nbrColors, GLushort *triangles, int nbrTriangles,
	GLuint progID, std::string vertexAttributeName, std::string colorAttributeName)
{

	programID = progID;
	nbrIndices = nbrTriangles;
	glGenBuffers(1, &elementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nbrTriangles*sizeof(GLushort), triangles, GL_STATIC_DRAW);


	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(1, &bufferArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, bufferArrayObject);
	glBufferData(GL_ARRAY_BUFFER,
		nbrVertices * sizeof(GLfloat) + nbrColors * sizeof(GLfloat),
		NULL, GL_STATIC_DRAW);
	//                               offset in bytes   size in bytes     ptr to data    
	glBufferSubData(GL_ARRAY_BUFFER, 0, nbrVertices * sizeof(GLfloat), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, nbrVertices * sizeof(GLfloat), nbrColors * sizeof(GLfloat), colors);

	GLuint vPosition = glGetAttribLocation(programID, vertexAttributeName.c_str());
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint vColor = glGetAttribLocation(programID, colorAttributeName.c_str());
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(nbrVertices * sizeof(GLfloat)));
}

void IndexedPolygonObject::display()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, bufferArrayObject);
	glDrawElements(GL_TRIANGLES, nbrIndices, GL_UNSIGNED_SHORT, NULL);
}
