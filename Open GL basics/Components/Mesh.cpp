#include "Mesh.h"
#include <vector>

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	for (int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(vertices[i].GetPos());
		model.texCoords.push_back(vertices[i].GetTexCoords());
		model.normals.push_back(vertices[i].GetNormal());
	}

	for (int i = 0; i < numIndices; i++)
	{
		model.indices.push_back(indices[i]);
	}
}

Mesh::Mesh(const std::string& fileName)
{
	model = OBJModel(fileName).ToIndexedModel();
}

Mesh::~Mesh()
{
	//Освобожадем память, выделенную под вершины
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void Mesh::Update()
{
	glBindVertexArray(vertexArrayObject);

	//Рисует массив вершин, определенный в предыдущей функции
	//Первый параметр - способ рисования. Поскольку мы рисуем меш, нам нужны треугольники, но возможно также рисовать
	//линиями или отдельными точками
	//Второй и третий параметры определяют начальную позицию и количество вершин, которое необходимо нарисовать, соответственно
	//glDrawArrays(GL_TRIANGLES, 0, drawCount);

	glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Mesh::Init()
{
	drawCount = model.indices.size();

	//Выделяем память под один массив вершин
	glGenVertexArrays(1, &vertexArrayObject);

	//Далее, все операции, касающиеся массива вершин будут совершаться с этим объектом.
	glBindVertexArray(vertexArrayObject);

	//Выделяет буффер памяти на GPU размером NUM_BUFFERS и заносит его в массив vertexArrayBuffers
	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);

	//Аналогично массиву вершин, связывает переданный буффер со всем, что будет происходить со сгенерированным
	//буффером на GPU
	//Поскольку буффер - это просто блок памяти GPU, который может означать что угодно, первый параметр говорит,
	//что данный буффер является массивом
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);

	//Передает данные в буффер на GPU
	//Первый параметр - тип передаваемых данных
	//Второй параметр - размер данных (длина массива, умноженная на размер одного элемента)
	//Третий параметр определяет, как эти данные будут использоваться на GPU. Например, в данном случае подразумевается,
	//что, будучи однажды отрисованными, они не будут подвергаться изменениям, поэтому им будет отведено место в памяти 
	//с быстрым доступом, но достаточно медленной записью
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);


	//Говорит OpenGL, как ему интрепретировать переданные данные. Другими словами, нужно идентифицировать каждое поле 
	//класса Vertex своим собственным индексом, что бы GPU имело возможность их различать.
	//В данном случае, класс имеет только одно поле, поэтому вызов этой функции не столь критичен. В дальнейшем эта 
	//привязка будет использована в шейдерах
	glEnableVertexAttribArray(0);

	//Эта функция предоставляет OpenGL более подробную информацию об аттрибутах, объявленных ранее
	//Первый параметр - индекс аттрибута. В нашем случае - позиции
	//Второй параметр - количество данных внутри аттрибута. Поскольку мы имеем дело с трехмерным вектором, то количество 
	//равно трем
	//Третий параметр - тип данных внутри аттрибута, в нашем случае - float
	//Четвертый - смещение, необходимое для того, что бы найти следующий аттрибут. Поскольку наш массив аттрибутов 
	//состоит из одного типа аттрибутов, оно равно нулю
	//Пятый - указатель на первый аттрибут этого типа. Так же равен нулю
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	//Аналогичные действия для текстурных координат
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.texCoords.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	//Отменяем привязку - далее наш vertexArrayObject не будет подвержен никаким воздействиям, напрвленным на массив вершин
	glBindVertexArray(0);
}