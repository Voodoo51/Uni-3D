#include "Model.h"

Model::Model(Primitive primitive)
{
	SetVertices(primitive);

	/*
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	*/
}

void Model::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Model::SetVertices(Primitive primitive)
{
	if (primitive == Cube_uv1)
	{
		//108
		float positions[] = {
		//BACK
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		//FRONT
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		//LEFT
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
		//RIGHT
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		//BOTTOM 
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
	    -0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		//TOP
		-0.5f,  0.5f, -0.5f, 
		 0.5f,  0.5f, -0.5f, 
		 0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f,  0.5f, 
		 0.5f,  0.5f,  0.5f };

		//108
		float normals[] = {
		//BACK 
		 0.0f, -1.0f, 0.0f,
		 0.0f, -1.0f, 0.0f,
		 0.0f, -1.0f, 0.0f, 
		 0.0f, -1.0f, 0.0f, 
		 0.0f, -1.0f, 0.0f, 
		 0.0f, -1.0f, 0.0f, 
		//FRONT 
		 0.0f,  0.0f,  1.0f, 
		 0.0f,  0.0f,  1.0f, 
		 0.0f,  0.0f,  1.0f,  
		 0.0f,  0.0f,  1.0f, 
		 0.0f,  0.0f,  1.0f, 
		 0.0f,  0.0f,  1.0f, 
		//LEFT
		-1.0f,  0.0f,  0.0f, 
		-1.0f,  0.0f,  0.0f, 
		-1.0f,  0.0f,  0.0f, 
		-1.0f,  0.0f,  0.0f, 
		-1.0f,  0.0f,  0.0f, 
		-1.0f,  0.0f,  0.0f, 
		//RIGHT
		 1.0f,  0.0f,  0.0f, 
		 1.0f,  0.0f,  0.0f, 
		 1.0f,  0.0f,  0.0f, 
		 1.0f,  0.0f,  0.0f, 
		 1.0f,  0.0f,  0.0f, 
		 1.0f,  0.0f,  0.0f, 
		//BOTTOM
		 0.0f, -1.0f,  0.0f, 
		 0.0f, -1.0f,  0.0f, 
		 0.0f, -1.0f,  0.0f, 
		 0.0f, -1.0f,  0.0f, 
		 0.0f, -1.0f,  0.0f, 
		 0.0f, -1.0f,  0.0f, 
		//TOP
		 0.0f,  1.0f,  0.0f, 
		 0.0f,  1.0f,  0.0f, 
		 0.0f,  1.0f,  0.0f, 
		 0.0f,  1.0f,  0.0f, 
		 0.0f,  1.0f,  0.0f, 
		 0.0f,  1.0f,  0.0f};

		//72
		float uv[] = {
		//BACK
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		//FRONT
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		//LEFT
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		//RIGHT
		1.0f, 1.0f, 
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		//BOTTOM
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		//TOP
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f };

		float tangents[108] = 
		{
		//BACK
		-1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0,
		//FRONT
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		//LEFT
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		//RIGHT
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		//BOTTOM
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		//TOP
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0
		};
		float bitangents[108] = { 0 };
		/*
		float bitangents[108] = 
		{ 
		//BACK
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		//FRONT
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		//LEFT
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		//RIGHT
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		//BOTTOM
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		//TOP
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0
		};
		*/
		int uvI = 0;

		
		for (int i = 0; i < 108; i += 18)
		{
			vec3 tangent1, tangent2;
			vec3 bitangent1, bitangent2;

			vec3 pos1 = vec3(positions[i + 0], positions[i + 1], positions[i + 2]);
			vec3 pos2 = vec3(positions[i + 3], positions[i + 4], positions[i + 5]);
			vec3 pos3 = vec3(positions[i + 6], positions[i + 7], positions[i + 8]);
			vec3 pos4 = vec3(positions[i + 12], positions[i + 13], positions[i + 14]);

			vec2 uv1 = vec2(uv[uvI + 0], uv[uvI + 1]);
			vec2 uv2 = vec2(uv[uvI + 2], uv[uvI + 3]);
			vec2 uv3 = vec2(uv[uvI + 4], uv[uvI + 5]);
			vec2 uv4 = vec2(uv[uvI + 8], uv[uvI + 9]);

			//triangle 1
			vec2 deltaUV1 = uv1 - uv4;
			vec2 deltaUV2 = uv2 - uv4;

			glm::vec3 edge1 = pos1 - pos4;
			glm::vec3 edge2 = pos2 - pos4;

			float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

			tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
			tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
			tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

			bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
			bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
			bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
			
			// triangle 2
			edge1 = pos2 - pos4;
			edge2 = pos3 - pos4;
			deltaUV1 = uv2 - uv4;
			deltaUV2 = uv3 - uv4;

			f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

			tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
			tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
			tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

			bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
			bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
			bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

			tangents[i + 0] = tangent1.x;
			tangents[i + 1] = tangent1.y;
			tangents[i + 2] = tangent1.z;

			tangents[i + 3] = tangent1.x;
			tangents[i + 4] = tangent1.y;
			tangents[i + 5] = tangent1.z;

			tangents[i + 6] = tangent1.x;
			tangents[i + 7] = tangent1.y;
			tangents[i + 8] = tangent1.z;

			tangents[i + 9] = tangent2.x;
			tangents[i + 10] = tangent2.y;
			tangents[i + 11] = tangent2.z;

			tangents[i + 12] = tangent2.x;
			tangents[i + 13] = tangent2.y;
			tangents[i + 14] = tangent2.z;

			tangents[i + 15] = tangent2.x;
			tangents[i + 16] = tangent2.y;
			tangents[i + 17] = tangent2.z;

			bitangents[i + 0] = bitangent1.x;
			bitangents[i + 1] = bitangent1.y;
			bitangents[i + 2] = bitangent1.z;

			bitangents[i + 3] = bitangent1.x;
			bitangents[i + 4] = bitangent1.y;
			bitangents[i + 5] = bitangent1.z;

			bitangents[i + 6] = bitangent1.x;
			bitangents[i + 7] = bitangent1.y;
			bitangents[i + 8] = bitangent1.z;

			bitangents[i + 9] = bitangent2.x;
			bitangents[i + 10] = bitangent2.y;
			bitangents[i + 11] = bitangent2.z;

			bitangents[i + 12] = bitangent2.x;
			bitangents[i + 13] = bitangent2.y;
			bitangents[i + 14] = bitangent2.z;

			bitangents[i + 15] = bitangent2.x;
			bitangents[i + 16] = bitangent2.y;
			bitangents[i + 17] = bitangent2.z;
			std::cout << "FACE: " << i / 18 + 1<< std::endl;
			std::cout << "TANGENT1:" << tangent1.x << ":" << tangent1.y << ":" << tangent1.z << std::endl;
			std::cout << "TANGENT2:" << tangent2.x << ":" << tangent2.y << ":" << tangent2.z << std::endl;
			std::cout << "BITANGENT1:" << bitangent1.x << ":" << bitangent1.y << ":" << bitangent1.z << std::endl;
			std::cout << "BITANGENT2:" << bitangent2.x << ":" << bitangent2.y << ":" << bitangent2.z << std::endl;
			uvI += 12;
		}
		

		float vertices[504] = { 0 };

		int vI = 0;
		uvI = 0;

		for (int i = 0; i < 504; i += 14)
		{
			vertices[i + 0] = positions[vI + 0];
			vertices[i + 1] = positions[vI + 1];
			vertices[i + 2] = positions[vI + 2];
			vertices[i + 3] = normals[vI + 0];
			vertices[i + 4] = normals[vI + 1];
			vertices[i + 5] = normals[vI + 2];
			vertices[i + 6] = uv[uvI + 0];
			vertices[i + 7] = uv[uvI + 1];
			vertices[i + 8] = tangents[vI + 0];
			vertices[i + 9] = tangents[vI + 1];
			vertices[i + 10] = tangents[vI + 2];
			vertices[i + 11] = bitangents[vI + 0];
			vertices[i + 12] = bitangents[vI + 1];
			vertices[i + 13] = bitangents[vI + 2];

			
			std::cout << vertices[i + 0] << " " << vertices[i + 1] << " " << vertices[i + 2] << " | "
				<< vertices[i + 3] << " " << vertices[i + 4] << " " << vertices[i + 5] << " | "
				<< vertices[i + 6] << " " << vertices[i + 7] << " | "
				<< vertices[i + 8] << " " << vertices[i + 9] << " " << vertices[i + 10] << " | "
				<< vertices[i + 11] << " " << vertices[i + 12] << " " << vertices[i + 13] << std::endl;
			

			uvI += 2;
			vI += 3;
		}

		/*
		float vertices[] = {
		//BACK
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,

		//FRONT
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,

		//LEFT
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

	    //RIGHT
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

		//BOTTOM
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,

		//TOP
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
		};
		*/

		SetLayout(primitive, vertices, sizeof(vertices));
	}
	
}

void Model::SetLayout(Primitive primitive, float* vertices, size_t verticesSize)
{
	unsigned int VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	if (primitive == Cube_uv1)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
		glEnableVertexAttribArray(3);

		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));
		glEnableVertexAttribArray(4);
	}
	else if (primitive == Cube_uv2)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
}

void Model::LoadTexture(std::string path)
{
	unsigned int texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
		{
			std::cout << path << ":" << "GL_RED" << std::endl;
			format = GL_RED;
		}
		else if (nrChannels == 3)
		{
			std::cout << path << ":" << "GL_RGB" << std::endl;
			format = GL_RGB;
		}
		else if (nrChannels == 4)
		{
			std::cout << path << ":" << "GL_RGBA" << std::endl;
			format = GL_RGBA;
		}
		
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture: "<< path << std::endl;
	}
	stbi_image_free(data);

	textures.push_back(texture);
}