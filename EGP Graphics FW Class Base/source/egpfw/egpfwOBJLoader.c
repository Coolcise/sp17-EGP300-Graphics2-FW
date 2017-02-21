// By Dan Buckstein
// Modified by: _______________________________________________________________
#include "egpfw/egpfw/egpfwOBJLoader.h"


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define BUFFER_OFFSET_BYTE(p,n) ((char *)(p) + n)


// helper structures
union float2
{
	struct { float f0, f1; };
	float f[2];
};
union float3
{
	struct { float f0, f1, f2; };
	float f[3];
};
union float4
{
	struct { float f0, f1, f2, f3; };
	float f[4];
};
union int4
{
	struct { int i0, i1, i2, i3; };
	int i[4];
};
union face
{
	struct { unsigned int v0, v1, v2, vt0, vt1, vt2, vn0, vn1, vn2; };
	struct { unsigned int v[3], vt[3], vn[3]; };
};

struct uniqueTriFace;
struct uniqueVertex;
struct uniqueTexcoord;
struct uniqueNormal;

#ifndef __cplusplus
typedef union float2			float2;
typedef union float3			float3;
typedef union float4			float4;
typedef union int4				int4;
typedef union face				face;
typedef struct uniqueTriFace	uniqueTriFace;
typedef struct uniqueVertex		uniqueVertex;
typedef struct uniqueTexcoord	uniqueTexcoord;
typedef struct uniqueNormal		uniqueNormal;
#endif	// __cplusplus


//-----------------------------------------------------------------------------


// ****
// load triangulated OBJ file
egpTriOBJDescriptor egpfwLoadTriangleOBJ(const char *objPath, const egpMeshNormalMode normalMode, const double globalScale)
{
	egpTriOBJDescriptor obj = { 0 };

	//FILE *file = fopen(objPath, "r");

	//if (file == NULL)
	//	printf("\nCould not open file %s!\n", objPath);

	////Get file size
	//fseek(file, 0L, SEEK_END);
	//int fileSize = ftell(file);
	//rewind(file);

	//float* theData = (float*)malloc(fileSize);

	////Set start index for vertecies
	//obj.attribOffset[ATTRIB_POSITION] = 0;

	//int count = 0;
	//int currStrIndex;
	//int currAttrIndex = 0;
	//int currNumIndex = 0;

	//char str[100] = { '\0' };
	//char num[10] = { '\0' };

	////Read first line
	//if (fgets(str, 100, file) == NULL)
	//	printf("Cound not read from OBJ file!\n");

	////Skip unwanted lines
	//while (!(str[0] == 'v' && str[1] == ' '))
	//{
	//	if (fgets(str, 100, file) == NULL)
	//	{
	//		printf("Could not read from OBJ file");
	//		break;
	//	}
	//}

	////Read vertecies
	//while (str[0] == 'v' && str[1] == ' ')
	//{
	//	//Skip the identifier ("v ")
	//	currStrIndex = 2;

	//	//3 numbers per vertex
	//	for (int i = 0; i < 3; i++)
	//	{
	//		while (str[currStrIndex] != ' ')
	//			num[currNumIndex++] = str[currStrIndex++];

	//		float temp = strtof(num, NULL);
	//		//Convert from 1 indexed to 0 indexed
	//		theData[currAttrIndex] = temp - 1;

	//		for (int j = 0; j < 10; j++)
	//			num[j] = '\0';

	//		currNumIndex = 0;
	//		currStrIndex++;
	//		count++;
	//		currAttrIndex++;
	//	}

	//	if (fgets(str, 100, file) == NULL)
	//	{
	//		printf("Could not read from OBJ file");
	//		break;
	//	}
	//}

	////Set start index for UVs
	//obj.attribOffset[ATTRIB_TEXCOORD] = currAttrIndex;
	//count = 0;

	////Read UVs
	//while (str[0] == 'v' && str[1] == 't' && str[2] == ' ')
	//{
	//	//Skip the identifier ("vt ")
	//	currStrIndex = 3;

	//	//2 numbers per UV
	//	for (int i = 0; i < 2; i++)
	//	{
	//		//Parse line to get number
	//		while (str[currStrIndex] != ' ')
	//			num[currNumIndex++] = str[currStrIndex++];

	//		float temp = strtof(num, NULL);
	//		theData[currAttrIndex] = temp;

	//		for (int j = 0; j < 10; j++)
	//			num[j] = '\0';

	//		currNumIndex = 0;
	//		currStrIndex++;
	//		count++;
	//		currAttrIndex++;
	//	}

	//	if (fgets(str, 100, file) == NULL)
	//	{
	//		printf("Could not read from OBJ file");
	//		break;
	//	}
	//}

	////Set starting index for the normals
	//obj.attribOffset[ATTRIB_NORMAL] = currAttrIndex;
	//count = 0;

	////Read in normals
	//while (str[0] == 'v' && str[1] == 'n' && str[2] == ' ')
	//{
	//	//Skip the identifier ("vn ")
	//	currStrIndex = 3;

	//	//3 numbers per normal
	//	for (int i = 0; i < 3; i++)
	//	{
	//		while (str[currStrIndex] != ' ')
	//			num[currNumIndex++] = str[currStrIndex++];

	//		float temp = strtof(num, NULL);
	//		theData[currAttrIndex] = temp;

	//		for (int j = 0; j < 10; j++)
	//			num[j] = '\0';

	//		currNumIndex = 0;
	//		currStrIndex++;
	//		count++;
	//		currAttrIndex++;
	//	}


	//	if (fgets(str, 100, file) == NULL)
	//		printf("Could not read from OBJ file");
	//}

	//obj.dataSize = (count + obj.attribOffset[ATTRIB_NORMAL]) * sizeof(float);

	//obj.faces = (int*)malloc(fileSize);

	//while (!(str[0] == 'f' && str[1] == ' '))
	//{
	//	fgets(str, 100, file);
	//	if (str == NULL)
	//		printf("Could not read from OBJ file");
	//}

	////Reuse for face array
	//currAttrIndex = 0;
	//count = 0;
	//char* token;

	////Read in faces
	//while (str[0] == 'f' && str[1] == ' ' && !feof(file))
	//{
	//	//Skip the identifier ("f ")
	//	currStrIndex = 2;

	//	//3 sets of indeces
	//	for (int i = 0; i < 3; i++)
	//	{
	//		while (str[currStrIndex] != ' ')
	//			num[currNumIndex++] = str[currStrIndex++];

	//		//Get ints divided by delimiter '/'
	//		token = strtok(num, "/");
	//		while (token)
	//		{
	//			int temp = atoi(token);
	//			obj.faces[currAttrIndex++] = temp;
	//			token = strtok(NULL, "/");
	//		}

	//		for (int j = 0; j < 10; j++)
	//			num[j] = '\0';

	//		currNumIndex = 0;
	//		currStrIndex++;
	//	}

	//	count++;

	//	if (fgets(str, 100, file) == NULL)
	//	{
	//		printf("Could not read from OBJ file");
	//		break;
	//	}
	//}

	//obj.numFaces = count;

	//fclose(file);

	//obj.data = theData;
	return obj;
}


// ****
// convert OBJ to VAO & VBO
int egpfwCreateVAOFromOBJ(const egpTriOBJDescriptor *obj, egpVertexArrayObjectDescriptor *vao_out, egpVertexBufferObjectDescriptor *vbo_out)
{
	//...
	return 0;
}


// ****
// free obj data
int egpfwReleaseOBJ(egpTriOBJDescriptor *obj)
{
	free(obj->data);
	free(obj->faces);
	return 0;
}


// ****
// save/load binary
int egpfwSaveBinaryOBJ(const egpTriOBJDescriptor *obj, const char *binPath)
{
	//...
	return 0;
}

egpTriOBJDescriptor egpfwLoadBinaryOBJ(const char *binPath)
{
	egpTriOBJDescriptor obj = { 0 };
	//...
	return obj;
}


// these functions are complete!
// get attribute data from OBJ
const void *egpfwGetOBJAttributeData(const egpTriOBJDescriptor *obj, const egpAttributeName attrib)
{
	if (obj && obj->data && obj->attribOffset[attrib])
		return BUFFER_OFFSET_BYTE(obj->data, obj->attribOffset[attrib]);
	return 0;
}

unsigned int egpfwGetOBJNumVertices(const egpTriOBJDescriptor *obj)
{
	if (obj && obj->data)
		return *((unsigned int *)obj->data);
	return 0;
}
