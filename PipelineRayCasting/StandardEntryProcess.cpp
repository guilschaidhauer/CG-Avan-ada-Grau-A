#include "StandardEntryProcess.h"
#include <iostream>
#include <string>


StandardEntryProcess::StandardEntryProcess()
{
}


StandardEntryProcess::~StandardEntryProcess()
{
}

ParamsFile StandardEntryProcess::processEntry(ParamsFile *paramsFile)
{
	ifstream file;
	file.open("files/params.txt");

	if (!file.is_open())
	{
		exit(EXIT_FAILURE);
	}
	
	string line;
	string ReadingParam;
	int nLights, nObjects;
	char program[3];
	char outputType;
	int raio;
	Vec3f pos = Vec3f(0, 0, 0);
	Vec3f color = Vec3f(0, 0, 0);
	Color tempColor;

	while (file.good())
	{
		getline(file, line);
		if (line[0] != '#' || line[1] != '#')
		{
			if (line == "begin stage 1")
			{
				//camera
				cout << line << endl;
				getline(file, line); //descarta a linha
				cout << "Configuring the camera..." << endl;
				file >> ReadingParam >> paramsFile->cameraDefinition.position.x >> paramsFile->cameraDefinition.position.y >> paramsFile->cameraDefinition.position.z; //define a posicao da c�mera
				cout << ReadingParam << " " << paramsFile->cameraDefinition.position.x << ", " << paramsFile->cameraDefinition.position.y << ", " << paramsFile->cameraDefinition.position.z << endl;

				//light
				getline(file, line); //descarta a linha
				getline(file, line); //descarta a linha

				file >> ReadingParam >> nLights; //pega o numero de luzes
				getline(file, line); //descarta a linha
				cout << "Configuring the lights..." << endl;
				for (int i = 1; i <= nLights; i++)
				{
					getline(file, line); //descarta a linha
					cout << line << i << endl;
					file >> ReadingParam >> pos.x >> pos.y >> pos.z; //seta a posicao em valores temporarios
					
					paramsFile->lightPointDefinition.setCenter(Vec3f(pos.x, pos.y, pos.z)); //seta a posicao
					cout << ReadingParam << " " << pos.x << ", " << pos.y << ", " << pos.z << endl;

					getline(file, line); //descarta a linha

					file >> ReadingParam >> color.x >> color.y >> color.z; // seta a cor	
					paramsFile->lightPointDefinition.setColor(color);

					cout << ReadingParam << " " << paramsFile->lightPointDefinition.getColor().getColorRed() << ", " << paramsFile->lightPointDefinition.getColor().getColorGreen() << ", " << paramsFile->lightPointDefinition.getColor().getColorBlue() << endl;
					getline(file, line); //descarta a linha
					getline(file, line); //descarta a linha
					cout << line << i << endl;
				}

				//primitives
				getline(file, line); //descarta a linha
				file >> ReadingParam >> nObjects; //pega o numero de objetos
				getline(file, line); //descarta a linha
				getline(file, line); //descarta a linha
				cout << "Configuring the primitives..." << endl;
				for (int i = 1; i <= nObjects; i++)
				{
					getline(file, line); //descarta a linha
					cout << line << i << endl;
					file >> ReadingParam >> raio;
					cout << ReadingParam << " " << raio << endl;

					getline(file, line); //descarta a linha
					file >> ReadingParam >> color.x >> color.y >> color.z;
					cout << ReadingParam << " " << color.x << ", " << color.y << ", " << color.z << endl;

					getline(file, line); //descarta a linha
					file >> ReadingParam >> pos.x >> pos.y >> pos.z;
					cout << ReadingParam << " " << pos.x << ", " << pos.y << ", " << pos.z << endl;

					Sphere newSphere(Vec3f(pos.x, pos.y, pos.z), raio, color);
					newSphere.setColor(color);
					paramsFile->objects.push_back(dynamic_cast<Object*>(&newSphere));

					getline(file, line); //descarta a linha
				}
			}
			else if (line == "begin stage 3")
			{
				cout << line << endl;
				getline(file, line); //descarta a linha
				getline(file, line); //descarta a linha
				file >> ReadingParam >> program;
				cout << ReadingParam << " " <<  program << endl;
				//program � o tipo do algoritimo de render rc ou rt
			}
			else if (line == "begin stage 4")
			{
				cout << line << endl;
				cout << "Aqui ler filtros pos-render!" << endl;
			}
			else if (line == "begin stage 5")
			{
				//output
				cout << line << endl;
				getline(file, line); //descarta a linha
				file >> ReadingParam >> paramsFile->height >> paramsFile->width >> outputType;
				cout << ReadingParam << " " << paramsFile->height << " x " << paramsFile->width << " - " << outputType << endl;
				//outputType � um char que recebe s|f
			}
		}
	}

	return paramsFile;
}